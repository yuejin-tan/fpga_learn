module ahb_sram
  #(
     // Parameter to define address width in ahb
     parameter AW = 20,
     parameter READCYCLE = 2,
     parameter WRITECYCLE = 2,
     parameter TURNAROUNDCYCLE = 2,
     parameter CFGSIZE = 1 // 0-8bit, 1-16bit
   )
   (
     input wire HCLK,    // Clock
     input wire HRESETn, // Reset
     input wire HSEL,    // Device select
     input wire [ AW - 1: 0] HADDR,   // Address
     input wire [ 1: 0] HTRANS,  // Transfer control
     input wire [ 2: 0] HSIZE,   // Transfer size
     input wire HWRITE,  // Write control
     input wire [ 31: 0] HWDATA,  // Write data
     input wire HREADY,  // Transfer phase done

     output wire HREADYOUT, // Device ready
     output wire [ 31: 0] HRDATA,  // Read data output
     output wire HRESP,   // Device response (always OKAY)

     //外部存储器 16bit dq
     output wire [ ( CFGSIZE ? AW - 2 : AW - 1 ) : 0 ] SRAM_ADDR,
     inout wire [ 15: 0 ] SRAM_DQ,
     output wire SRAM_nWE,
     output wire SRAM_nOE,
     output wire SRAM_nCE,
     output wire SRAM_nLB,
     output wire SRAM_nUB
   );


  reg RDREQ;   // Read request to memory i/f FSM
  reg WRREQ;   // Write request to memory i/f FSM
  wire DONE;    // memory i/f FSM done
  reg [ 1: 0] NXTBYTEMASK; // Early byte mask from AHB FSM to memory i/f FSM
  wire [ 2: 0] MEMFSMSTATE; // Memory Interface Finite State Machine
  wire [ 2: 0] BUSFSMSTATE; // Bus Interface Finite State Machine

  wire DATAOEn; // Tristate buffer output enable
  wire [ 15: 0] DATAIN = SRAM_DQ;  // Data input
  wire [ AW - 1: 0] ADDR;    // Address output
  reg [ 15: 0] DATAOUT; // Data output

  assign SRAM_ADDR = CFGSIZE? ADDR[ AW - 1: 1 ] : ADDR;
  assign SRAM_DQ = DATAOEn ? 16'hzzzz : DATAOUT;

  // --------------------------------------------------------------------------
  //   ahb fsm
  // This module divides each 32-bit AHB transfer or 16-bit AHB transfer
  // to multiple transfers if needed.
  // This module also handles data routing.
  // --------------------------------------------------------------------------

  // No err
  assign HRESP = 1'b0;

  // AHB bus FSM state
  reg [ 2: 0] reg_bstate;
  reg [ 2: 0] nxt_bstate;

  localparam BUSCNV_FSM_DEF = 3'b000;
  localparam BUSCNV_FSM_32BIT_8A = 3'b001;
  localparam BUSCNV_FSM_32BIT_8B = 3'b011;
  localparam BUSCNV_FSM_32BIT_8C = 3'b010;
  localparam BUSCNV_FSM_32BIT_16 = 3'b100;
  localparam BUSCNV_FSM_16BIT_8 = 3'b101;

  // State machine operation:
  //
  // Default (idle / first part of transfer)
  // BUSCNV_FSM_DEF
  //   |-> Transfers that can be handled in one go -> BUSCNV_FSM_DEF
  //   |-> 16-bit transfers on  8-bit memory -> BUSCNV_FSM_16BIT_8 -> BUSCNV_FSM_DEF
  //   |-> 32-bit transfers on 16-bit memory -> BUSCNV_FSM_32BIT_16 -> BUSCNV_FSM_DEF
  //   \-> 32-bit transfers on  8-bit memory -> BUSCNV_FSM_32BIT_8A
  //                                            \-> BUSCNV_FSM_32BIT_8B
  //                                                \-> BUSCNV_FSM_32BIT_8C
  //                                                    \-> BUSCNV_FSM_DEF

  wire trans_valid;    // Transfer valid
  reg reg_write;      // HWRITE in data phase
  reg reg_active;     // Active transfer
  reg [ 1: 0] reg_size;       // HSIZE in data phase

  reg [ 1: 0] reg_addr_low;   // Address bit [1:0] output
  reg [ 1: 0] nxt_addr_low;
  reg [ AW - 3: 0] reg_addr_high;  // Higher address bits output
  reg [ AW - 3: 0] nxt_addr_high;
  reg [ 1: 0] reg_lb_mux;     // Lower byte output multiplexer control
  reg [ 1: 0] nxt_lb_mux;
  reg [ 1: 0] reg_ub_mux;     // Upper byte output multiplexer control
  reg [ 1: 0] nxt_ub_mux;
  reg [ 1: 0] reg_byte_mask;  // Registered  NXTBYTEMASK (byte strobe)
  reg reg_rd_req;     // Registered RDREQ
  reg reg_wr_req;     // Registered WRREQ
  wire [ 2: 0] merged_cfgsize_hsize;  // Merged CFGSIZE and HSIZE information (for case statement)
  wire [ 2: 0] merged_cfgsize_reg_size; // Merged CFGSIZE and HSIZE (data phase) information (for case statement)
  wire [ 15: 0] i_dataout;      // Write data output mux
  reg [ 7: 0] read_buffer_0;  // Data buffer to hold read data
  reg [ 7: 0] read_buffer_1;  // Data buffer to hold read data
  reg [ 7: 0] read_buffer_2;  // Data buffer to hold read data

  reg [ 31: 0] i_hrdata;       // Read data mux

  // Detect if there is an active transfer
  assign trans_valid = HSEL & HREADY & HTRANS[ 1 ];

  // Registering transfer information for data phase
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          reg_write <= 1'b0;
          reg_active <= 1'b0;
          reg_size <= 2'b00;
        end
      else if ( HREADY)
        begin
          reg_write <= HWRITE;
          reg_active <= trans_valid;
          reg_size <= HSIZE[ 1: 0 ];
        end
    end

  // Merge size information for case statement
  assign merged_cfgsize_hsize = { CFGSIZE, HSIZE[ 1: 0 ] };

  // FSM
  always @( * )
    begin
      case ( reg_bstate)
        BUSCNV_FSM_DEF : // Default state
          // Idle or single memory transfer
          begin
            if ( trans_valid) // Note : trans_valid cannot be high until current
              begin          //        transfer is completed because of HREADY
                case ( merged_cfgsize_hsize)
                  3'b0_00 :
                    begin  // Byte transfer on 8-bit memory
                      nxt_bstate = BUSCNV_FSM_DEF;
                      nxt_addr_low = HADDR[ 1: 0 ];
                      nxt_addr_high= HADDR[ AW - 1: 2 ];
                      RDREQ = ~HWRITE;
                      WRREQ = HWRITE;
                      nxt_lb_mux = HADDR[ 1: 0 ]; // Lower byte port - byte 0/1/2/3
                      nxt_ub_mux = 2'b01;      // Upper byte port - Not used
                      NXTBYTEMASK = 2'b01;
                    end
                  3'b0_01 :
                    begin  // halfword transfer on 8-bit memory
                      nxt_bstate = BUSCNV_FSM_16BIT_8;
                      nxt_addr_low = HADDR[ 1: 0 ];
                      nxt_addr_high= HADDR[ AW - 1: 2 ];
                      RDREQ = ~HWRITE;
                      WRREQ = HWRITE;
                      nxt_lb_mux = HADDR[ 1: 0 ]; // Lower byte port - byte 0 / byte 2
                      nxt_ub_mux = 2'b01;      // Upper byte port - Not used
                      NXTBYTEMASK = 2'b01;
                    end
                  3'b0_10 :
                    begin  // word transfer on 8-bit memory
                      nxt_bstate = BUSCNV_FSM_32BIT_8A;
                      nxt_addr_low = HADDR[ 1: 0 ];
                      nxt_addr_high= HADDR[ AW - 1: 2 ];
                      RDREQ = ~HWRITE;
                      WRREQ = HWRITE;
                      nxt_lb_mux = HADDR[ 1: 0 ]; // Lower byte port - byte 0
                      nxt_ub_mux = 2'b01;      // Upper byte port - Not used
                      NXTBYTEMASK = 2'b01;
                    end
                  3'b1_00 :
                    begin  // Byte transfer on 16-bit memory
                      nxt_bstate = BUSCNV_FSM_DEF;
                      nxt_addr_low = HADDR[ 1: 0 ];
                      nxt_addr_high= HADDR[ AW - 1: 2 ];
                      RDREQ = ~HWRITE;
                      WRREQ = HWRITE;
                      nxt_lb_mux = { HADDR[ 1 ], 1'b0 }; // Lower byte port - byte 0/2
                      nxt_ub_mux = { HADDR[ 1 ], 1'b1 }; // Upper byte port - byte 1/3
                      NXTBYTEMASK = { HADDR[ 0 ], ~HADDR[ 0 ] };
                    end
                  3'b1_01 :
                    begin  // halfword transfer on 16-bit memory
                      nxt_bstate = BUSCNV_FSM_DEF;
                      nxt_addr_low = HADDR[ 1: 0 ];
                      nxt_addr_high= HADDR[ AW - 1: 2 ];
                      RDREQ = ~HWRITE;
                      WRREQ = HWRITE;
                      nxt_lb_mux = { HADDR[ 1 ], 1'b0 }; // Lower byte port - byte 0/2
                      nxt_ub_mux = { HADDR[ 1 ], 1'b1 }; // Upper byte port - byte 1/3
                      NXTBYTEMASK = 2'b11;
                    end
                  3'b1_10 :
                    begin  // word transfer on 16-bit memory
                      nxt_bstate = BUSCNV_FSM_32BIT_16;
                      nxt_addr_low = HADDR[ 1: 0 ];
                      nxt_addr_high= HADDR[ AW - 1: 2 ];
                      RDREQ = ~HWRITE;
                      WRREQ = HWRITE;
                      nxt_lb_mux = { HADDR[ 1 ], 1'b0 }; // Lower byte port - byte 0/2
                      nxt_ub_mux = { HADDR[ 1 ], 1'b1 }; // Upper byte port - byte 1/3
                      NXTBYTEMASK = 2'b11;
                    end
                  default :
                    begin // X propagation
                      nxt_bstate = 3'bxxx;
                      nxt_addr_low = 2'bxx;
                      nxt_addr_high= { ( AW - 2 ) { 1'bx } };
                      RDREQ = 1'bx;
                      WRREQ = 1'bx;
                      nxt_lb_mux = 2'bxx; // Lower byte port - byte 0/2
                      nxt_ub_mux = 2'bxx; // Upper byte port - byte 1/3
                      NXTBYTEMASK = 2'bxx;
                    end
                endcase
              end
            else    // trans_valid==0, previous transfer can still be ongoing
              begin // therefore hold the output stable
                nxt_bstate = BUSCNV_FSM_DEF;
                nxt_addr_low = reg_addr_low;
                nxt_addr_high= reg_addr_high;
                RDREQ = reg_rd_req & ( ~DONE );
                WRREQ = reg_wr_req & ( ~DONE );
                nxt_lb_mux = reg_lb_mux; // Lower byte port - byte 0/2
                nxt_ub_mux = reg_ub_mux; // Upper byte port - byte 1/3
                NXTBYTEMASK = reg_byte_mask; // Byte strobe output unchanged
              end
          end
        BUSCNV_FSM_32BIT_16 : // 32-bit transfer on 16-bit memory
          begin
            if ( ~DONE) // First half of the transfer still on going
              begin    // therefore hold the output stable
                nxt_bstate = reg_bstate;
                nxt_addr_low = reg_addr_low;
                nxt_addr_high= reg_addr_high;
                RDREQ = ~reg_write;
                WRREQ = reg_write;
                nxt_lb_mux = reg_lb_mux; // Lower byte port - byte 0
                nxt_ub_mux = { reg_ub_mux[ 1 ], 1'b1 }; // Upper byte port - byte 1
                NXTBYTEMASK = reg_byte_mask; // Byte strobe output unchanged
              end
            else    // First half of the transfer is done
              begin // therefore update the output
                nxt_bstate = BUSCNV_FSM_DEF;
                nxt_addr_low = 2'b10;
                nxt_addr_high= reg_addr_high;
                RDREQ = ~reg_write;
                WRREQ = reg_write;
                nxt_lb_mux = 2'b10; // Lower byte port - byte 2
                nxt_ub_mux = 2'b11; // Upper byte port - byte 3
                NXTBYTEMASK = reg_byte_mask;
              end
          end
        BUSCNV_FSM_32BIT_8A : // 32-bit transfer on 8-bit memory
          begin
            if ( ~DONE)  // First part of the transfer still on going
              begin     // therefore hold the output stable
                nxt_bstate = reg_bstate;
                nxt_addr_low = reg_addr_low;
                nxt_addr_high= reg_addr_high;
                RDREQ = ~reg_write;
                WRREQ = reg_write;
                nxt_lb_mux = reg_lb_mux; // Lower byte port - byte 0
                nxt_ub_mux = { reg_ub_mux[ 1 ], 1'b1 }; // Upper byte port - Not used
                NXTBYTEMASK = reg_byte_mask; // Byte strobe output unchanged
              end
            else    // First part of the transfer is done
              begin // therefore update the output
                nxt_bstate = BUSCNV_FSM_32BIT_8B;
                nxt_addr_low = 2'b01;
                nxt_addr_high= reg_addr_high;
                RDREQ = ~reg_write;
                WRREQ = reg_write;
                nxt_lb_mux = 2'b01;    // Lower byte port - byte 1
                nxt_ub_mux = { reg_ub_mux[ 1 ], 1'b1 }; // Upper byte port - Not used
                NXTBYTEMASK = reg_byte_mask; // Byte strobe output unchanged
              end
          end
        BUSCNV_FSM_32BIT_8B : // 32-bit transfer on 8-bit memory
          begin
            if ( ~DONE)  // second part of the transfer still on going
              begin     // therefore hold the output stable
                nxt_bstate = reg_bstate;
                nxt_addr_low = reg_addr_low;
                nxt_addr_high= reg_addr_high;
                RDREQ = ~reg_write;
                WRREQ = reg_write;
                nxt_lb_mux = reg_lb_mux; // Lower byte port - byte 1
                nxt_ub_mux = { reg_ub_mux[ 1 ], 1'b1 }; // Upper byte port - Not used
                NXTBYTEMASK = reg_byte_mask; // Byte strobe output unchanged
              end
            else    // second part of the transfer is done
              begin // therefore update the output
                nxt_bstate = BUSCNV_FSM_32BIT_8C;
                nxt_addr_low = 2'b10;
                nxt_addr_high= reg_addr_high;
                RDREQ = ~reg_write;
                WRREQ = reg_write;
                nxt_lb_mux = 2'b10;    // Lower byte port - byte 2
                nxt_ub_mux = { reg_ub_mux[ 1 ], 1'b1 }; // Upper byte port - Not used
                NXTBYTEMASK = reg_byte_mask; // Byte strobe output unchanged
              end
          end
        BUSCNV_FSM_32BIT_8C : // 32-bit transfer on 8-bit memory
          begin
            if ( ~DONE)  // third part of the transfer still on going
              begin     // therefore hold the output stable
                nxt_bstate = reg_bstate;
                nxt_addr_low = reg_addr_low;
                nxt_addr_high= reg_addr_high;
                RDREQ = ~reg_write;
                WRREQ = reg_write;
                nxt_lb_mux = reg_lb_mux; // Lower byte port - byte 2
                nxt_ub_mux = { reg_ub_mux[ 1 ], 1'b1 }; // Upper byte port - Not used
                NXTBYTEMASK = reg_byte_mask; // Byte strobe output unchanged
              end
            else    // third part of the transfer is done
              begin // therefore update the output
                nxt_bstate = BUSCNV_FSM_DEF;
                nxt_addr_low = 2'b11;
                nxt_addr_high= reg_addr_high;
                RDREQ = ~reg_write;
                WRREQ = reg_write;
                nxt_lb_mux = 2'b11;    // Lower byte port - byte 3
                nxt_ub_mux = { reg_ub_mux[ 1 ], 1'b1 }; // Upper byte port - Not used
                NXTBYTEMASK = reg_byte_mask; // Byte strobe output unchanged
              end
          end
        BUSCNV_FSM_16BIT_8 : // 16-bit transfer on 8-bit memory
          begin
            if ( ~DONE)  // first part of the transfer still on going
              begin     // therefore hold the output stable
                nxt_bstate = reg_bstate;
                nxt_addr_low = reg_addr_low;
                nxt_addr_high= reg_addr_high;
                RDREQ = ~reg_write;
                WRREQ = reg_write;
                nxt_lb_mux = reg_lb_mux; // Lower byte port - byte 0
                nxt_ub_mux = { reg_ub_mux[ 1 ], 1'b1 }; // Upper byte port - Not used
                NXTBYTEMASK = reg_byte_mask; // Byte strobe output unchanged
              end
            else    // first part of the transfer is done
              begin // therefore update the output
                nxt_bstate = BUSCNV_FSM_DEF;
                nxt_addr_low = { reg_addr_low[ 1 ], 1'b1 };
                nxt_addr_high= reg_addr_high;
                RDREQ = ~reg_write;
                WRREQ = reg_write;
                nxt_lb_mux = { reg_addr_low[ 1 ], 1'b1 }; // Lower byte port - byte 1/3
                nxt_ub_mux = { reg_ub_mux[ 1 ], 1'b1 };   // Upper byte port - Not used
                NXTBYTEMASK = reg_byte_mask; // Byte strobe output unchanged
              end
          end
        default : // X propagation
          begin
            nxt_bstate = 3'bxxx;
            nxt_addr_low = 2'bxx;
            nxt_addr_high= { ( AW - 2 ) { 1'bx } };
            RDREQ = 1'bx;
            WRREQ = 1'bx;
            nxt_lb_mux = 2'bxx; // Lower byte port
            nxt_ub_mux = 2'bxx; // Upper byte port
            NXTBYTEMASK = 2'bxx;
          end
      endcase
    end

  // Registering state machine signals
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          reg_bstate <= BUSCNV_FSM_DEF;
          reg_addr_low <= 2'b00;
          reg_addr_high <= { ( AW - 2 ) { 1'b0 } };
          reg_rd_req <= 1'b0;
          reg_wr_req <= 1'b0;
          reg_lb_mux <= 2'b00;
          reg_ub_mux <= 2'b00;
          reg_byte_mask <= 2'b00;
        end
      else
        begin
          reg_bstate <= nxt_bstate;
          reg_addr_low <= nxt_addr_low;
          reg_addr_high <= nxt_addr_high;
          reg_rd_req <= RDREQ;
          reg_wr_req <= WRREQ;
          reg_lb_mux <= nxt_lb_mux;
          reg_ub_mux <= nxt_ub_mux;
          reg_byte_mask <= NXTBYTEMASK;
        end
    end

  // Address to SRAM
  assign ADDR = { reg_addr_high, reg_addr_low };
  // Lower byte routing
  assign i_dataout[ 7:
                    0] = ( reg_lb_mux[ 1 ] ) ? ( ( reg_lb_mux[ 0 ] ) ? HWDATA[ 31 : 24] : HWDATA[ 23 : 16 ] ) :
         ( ( reg_lb_mux[ 0 ] ) ? HWDATA[ 15: 8] : HWDATA[ 7: 0 ] ) ;
  // Upper byte routing
  assign i_dataout[ 15:
                    8] = ( reg_ub_mux[ 1 ] ) ? HWDATA[ 31 : 24] : HWDATA[ 15: 8 ];
  // Note : reg_ub_mux[0] always 1

  // Register routed data out
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          DATAOUT <= { 16{ 1'b0 } };
        end
      else if ( reg_active)
        begin
          DATAOUT <= i_dataout;
        end
    end

  // Read data buffer byte 0
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          read_buffer_0 <= { 8{ 1'b0 } };
        end
      else if ( reg_active & ( ~reg_write ) )
        begin
          if ( DONE & ( reg_lb_mux[ 1: 0] == 2'b00 ) )
            begin
              read_buffer_0 <= DATAIN[ 7: 0 ];
            end
        end
    end

  // Read data buffer byte 1
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          read_buffer_1 <= { 8{ 1'b0 } };
        end
      else if ( reg_active & ( ~reg_write ) )
        begin
          if ( DONE & ( reg_bstate == BUSCNV_FSM_32BIT_16 ) ) // 32-bit transfer on 16-bit memory
            begin
              read_buffer_1 <= DATAIN[ 15: 8 ];
            end
          else if ( DONE & ( reg_bstate == BUSCNV_FSM_32BIT_8B ) ) // 32-bit transfer on 8-bit memory
            begin
              read_buffer_1 <= DATAIN[ 7: 0 ];
            end
        end
    end

  // Read data buffer byte 2
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          read_buffer_2 <= { 8{ 1'b0 } };
        end
      else if ( reg_active & ( ~reg_write ) )
        begin
          if ( DONE & ( reg_bstate == BUSCNV_FSM_16BIT_8 ) ) // 16-bit transfer on 8-bit memory
            begin
              read_buffer_2 <= DATAIN[ 7: 0 ];
            end
          else if ( DONE & ( reg_bstate == BUSCNV_FSM_32BIT_8C ) ) // 32-bit transfer on 8-bit memory
            begin
              read_buffer_2 <= DATAIN[ 7: 0 ];
            end
        end
    end


  assign merged_cfgsize_reg_size = { CFGSIZE , reg_size[ 1: 0 ] };

  // Routing of read data
  always @( merged_cfgsize_reg_size or DATAIN or read_buffer_0 or read_buffer_1 or read_buffer_2)
    begin
      case ( merged_cfgsize_reg_size)
        3'b0_00 :
          i_hrdata = { DATAIN[ 7: 0 ], DATAIN[ 7: 0 ], DATAIN[ 7: 0 ], DATAIN[ 7: 0 ] }; // Byte  read on 8-bit memory
        3'b0_01 :
          i_hrdata = { DATAIN[ 7: 0 ], read_buffer_2, DATAIN[ 7: 0 ], read_buffer_0 }; // HWord read on 8-bit memory
        3'b0_10 :
          i_hrdata = { DATAIN[ 7: 0 ], read_buffer_2, read_buffer_1, read_buffer_0 }; // Word  read on 8-bit memory
        3'b0_11 :
          i_hrdata = { DATAIN[ 7: 0 ], read_buffer_2, read_buffer_1, read_buffer_0 }; // Invalid
        3'b1_00 :
          i_hrdata = { DATAIN[ 15: 8 ], DATAIN[ 7: 0 ], DATAIN[ 15: 8 ], DATAIN[ 7: 0 ] }; // Byte  read on 16-bit memory
        3'b1_01 :
          i_hrdata = { DATAIN[ 15: 8 ], DATAIN[ 7: 0 ], DATAIN[ 15: 8 ], DATAIN[ 7: 0 ] }; // HWord read on 16-bit memory
        3'b1_10 :
          i_hrdata = { DATAIN[ 15: 8 ], DATAIN[ 7: 0 ], read_buffer_1, read_buffer_0 }; // Word  read on 16-bit memory
        3'b1_11 :
          i_hrdata = { DATAIN[ 15: 8 ], DATAIN[ 7: 0 ], read_buffer_1, read_buffer_0 }; // Invalid
        default :
          i_hrdata = { 32{ 1'bx } };
      endcase
    end

  // Ready if there is no active transfers, or
  // A transfer is completed
  assign HREADYOUT = ( ~reg_active) | ( ( reg_bstate == BUSCNV_FSM_DEF) & DONE );
  // Connect read data to AHB
  assign HRDATA = i_hrdata;
  // Connection to top for OVL checking in top level
  assign BUSFSMSTATE = reg_bstate;

  // --------------------------------------------------------------------------
  //   mem fsm
  // This module generates memory control for each memory access.
  // --------------------------------------------------------------------------

  reg [ 2: 0] reg_mstate;
  reg [ 2: 0] nxt_mstate;

  localparam EXTMEM_FSM_IDLE = 3'b000;
  localparam EXTMEM_FSM_WRITE1 = 3'b001;
  localparam EXTMEM_FSM_WRITE2 = 3'b011;
  localparam EXTMEM_FSM_WRITE3 = 3'b010;
  localparam EXTMEM_FSM_READ1 = 3'b100;

  reg reg_dataoe_n;
  reg nxt_dataoe_n;
  reg reg_we_n;
  reg nxt_we_n;
  reg reg_oe_n;
  reg nxt_oe_n;
  reg reg_ce_n;
  reg nxt_ce_n;
  reg [ 1:
        0] reg_bs_n;
  reg [ 1:
        0] nxt_bs_n;

  reg [ 2:
        0] reg_mcount;     // Counter for wait state
  reg [ 2:
        0] nxt_mcount;
  reg last_operation; // Record last operation (1=write, 0=read)
  wire nxt_last_operation;
  wire [ 2:
         0] dec_mcount;     // Decrement of reg_mcount

  assign dec_mcount = reg_mcount - 1'b1; // Decrement wait state counter

  // Memory interface FSM
  always @( * )
    begin
      case ( reg_mstate)
        EXTMEM_FSM_IDLE :
          begin
            if ( RDREQ)
              begin
                if ( ( reg_mcount != { 3{ 1'b0 } } ) & ( last_operation ) )
                  begin  // Wait for turn around
                    nxt_mstate = EXTMEM_FSM_IDLE;
                    nxt_mcount = dec_mcount;
                  end
                else
                  begin  // Goto read operation
                    nxt_mstate = EXTMEM_FSM_READ1;
                    nxt_mcount = READCYCLE;
                  end
              end
            else if ( WRREQ)
              begin
                if ( ( reg_mcount != { 3{ 1'b0 } } ) & ( ~last_operation ) )
                  begin  // Wait for turn around
                    nxt_mstate = EXTMEM_FSM_IDLE;
                    nxt_mcount = dec_mcount;
                  end
                else
                  begin  // Goto write operation
                    nxt_mstate = EXTMEM_FSM_WRITE1;
                    nxt_mcount = WRITECYCLE;
                  end
              end
            else if ( ( reg_mcount != { 3{ 1'b0 } } ) )
              begin
                nxt_mstate = EXTMEM_FSM_IDLE;
                nxt_mcount = dec_mcount;
              end
            else
              begin
                nxt_mstate = EXTMEM_FSM_IDLE;
                nxt_mcount = { 3{ 1'b0 } };
              end
          end
        EXTMEM_FSM_READ1:
          begin
            if ( reg_mcount != { 3{ 1'b0 } } )
              begin
                nxt_mstate = EXTMEM_FSM_READ1;
                nxt_mcount = dec_mcount;
              end
            else if ( RDREQ) // Read after read - no turn around cycle
              begin
                nxt_mstate = EXTMEM_FSM_READ1;
                nxt_mcount = READCYCLE;
              end
            else
              begin
                nxt_mstate = EXTMEM_FSM_IDLE;
                nxt_mcount = TURNAROUNDCYCLE;
              end
          end
        EXTMEM_FSM_WRITE1: // Address setup
          begin
            nxt_mstate = EXTMEM_FSM_WRITE2;
            nxt_mcount = WRITECYCLE;
          end
        EXTMEM_FSM_WRITE2:
          if ( reg_mcount != { 3{ 1'b0 } } )
            begin
              nxt_mstate = EXTMEM_FSM_WRITE2;
              nxt_mcount = dec_mcount;
            end
          else
            begin
              nxt_mstate = EXTMEM_FSM_WRITE3;
              nxt_mcount = { 3{ 1'b0 } };
            end
        EXTMEM_FSM_WRITE3:
          begin
            if ( WRREQ)
              begin
                nxt_mstate = EXTMEM_FSM_WRITE1;
                nxt_mcount = WRITECYCLE;
              end
            else
              begin
                nxt_mstate = EXTMEM_FSM_IDLE;
                nxt_mcount = TURNAROUNDCYCLE;
              end
          end
        default: // X propagation
          begin
            nxt_mstate = 3'bxxx;
            nxt_mcount = 3'bxxx;
          end
      endcase
    end

  // Generate DONE signal to indicate the memory interface is
  // read for another transfer
  assign DONE = ( ( reg_mstate == EXTMEM_FSM_READ1) & ( reg_mcount == 3'b000 ) ) |
         ( reg_mstate == EXTMEM_FSM_WRITE3 );

  // Record last operation
  assign nxt_last_operation = ( reg_mstate == EXTMEM_FSM_WRITE3 );

  // Registering last operation information
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          last_operation <= 1'b0;
        end
      else if ( DONE)
        begin
          last_operation <= nxt_last_operation;
        end
    end

  // Generate memory interface outputs
  always @( *)
    begin
      case ( nxt_mstate)
        EXTMEM_FSM_IDLE :
          begin
            nxt_dataoe_n = 1'b1;
            nxt_ce_n = 1'b1;
            nxt_oe_n = 1'b1;
            nxt_we_n = 1'b1;
            nxt_bs_n = 2'b11;
          end
        EXTMEM_FSM_READ1 :
          begin
            nxt_dataoe_n = 1'b1;
            nxt_ce_n = 1'b0;
            nxt_oe_n = 1'b0;
            nxt_we_n = 1'b1;
            nxt_bs_n = ~NXTBYTEMASK;
          end
        EXTMEM_FSM_WRITE1, EXTMEM_FSM_WRITE3 :
          begin
            nxt_dataoe_n = 1'b0; // active
            nxt_ce_n = 1'b0;
            nxt_oe_n = 1'b1;
            nxt_we_n = 1'b1;
            nxt_bs_n = ~NXTBYTEMASK;
          end
        EXTMEM_FSM_WRITE2 :
          begin
            nxt_dataoe_n = 1'b0; // active
            nxt_ce_n = 1'b0;
            nxt_oe_n = 1'b1;
            nxt_we_n = 1'b0;
            nxt_bs_n = ~NXTBYTEMASK;
          end
        default:
          begin  // X propagation
            nxt_dataoe_n = 1'bx;
            nxt_ce_n = 1'bx;
            nxt_oe_n = 1'bx;
            nxt_we_n = 1'bx;
            nxt_bs_n = 2'bxx;
          end
      endcase
    end

  // Registering state and outputs
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          reg_mstate <= EXTMEM_FSM_IDLE;
          reg_mcount <= 3'b000;
          reg_dataoe_n <= 1'b1;
          reg_ce_n <= 1'b1;
          reg_oe_n <= 1'b1;
          reg_we_n <= 1'b1;
          reg_bs_n <= 2'b11;
        end
      else
        begin
          reg_mstate <= nxt_mstate;
          reg_mcount <= nxt_mcount;
          reg_dataoe_n <= nxt_dataoe_n;
          reg_ce_n <= nxt_ce_n;
          reg_oe_n <= nxt_oe_n;
          reg_we_n <= nxt_we_n;
          reg_bs_n <= nxt_bs_n;
        end
    end

  // Connect to top level
  assign DATAOEn = reg_dataoe_n;
  assign SRAM_nCE = reg_ce_n;
  assign SRAM_nWE = reg_we_n;
  assign SRAM_nOE = reg_oe_n;
  assign SRAM_nLB = reg_bs_n[ 0 ];
  assign SRAM_nUB = reg_bs_n[ 1 ];

  assign MEMFSMSTATE = reg_mstate;

endmodule
