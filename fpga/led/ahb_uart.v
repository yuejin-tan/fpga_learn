module ahb_uart
  (
    input wire HCLK,    // Clock
    input wire HRESETn, // Reset
    input wire HSEL,    // Device select
    input wire [ 15: 0] HADDR,   // Address
    input wire [ 1: 0] HTRANS,  // Transfer control
    input wire [ 2: 0] HSIZE,   // Transfer size
    input wire HWRITE,  // Write control
    input wire [ 31: 0] HWDATA,  // Write data
    input wire HREADY,  // Transfer phase done

    output wire HREADYOUT, // Device ready
    output wire [ 31: 0] HRDATA,  // Read data output
    output wire HRESP,   // Device response (always OKAY)

    // INT SIG
    output reg INT_REQ = 0,

    // UART SIG
    output wire TX_OUT,
    input wire RX_IN
  );


  // --------------------------------------------------------------------------
  //   ahb interface logic
  // --------------------------------------------------------------------------

  // No err
  assign HRESP = 1'b0;
  // slave always ready
  assign HREADYOUT = 1'b1;

  // Register interface
  wire [ 15: 0] addr;
  wire read_en;
  wire write_en;
  wire [ 3: 0] byte_strobe;

  // transfer request issued only in SEQ and NONSEQ status and slave is
  // selected and last transfer finish
  wire trans_req= HREADY & HSEL & HTRANS[ 1 ]; //传输请求
  wire ahb_read_req = trans_req & ( ~HWRITE ); // AHB read request；为低电平的时候，表示读
  wire ahb_write_req = trans_req & HWRITE;  // AHB write request
  wire update_read_req;    // To update the read enable register
  wire update_write_req;   // To update the write enable register

  reg [ 15: 0] addr_reg = 0;     // address signal, registered
  reg read_en_reg = 0;  // read enable signal, registered
  reg write_en_reg = 0; // write enable signal, registered

  reg [ 3: 0] byte_strobe_reg = 0; // registered output for byte strobe
  reg [ 3: 0] byte_strobe_nxt = 0; // next state for byte_strobe_reg

  // Address signal registering, to make the address and data active at the same cycle
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          addr_reg <= { ( 16 ) { 1'b0 } };
        end  //default address 0 is selected
      else if ( trans_req)
        begin
          addr_reg <= HADDR[ 15: 0 ];
        end //地址信号设定
    end


  // register read signal generation
  assign update_read_req = ahb_read_req | ( read_en_reg & HREADY ); // Update read enable control if
  //  1. When there is a valid read request
  //  2. When there is an active read, update it at the end of transfer (HREADY=1)

  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          read_en_reg <= 1'b0;
        end
      else if ( update_read_req)
        begin
          read_en_reg <= ahb_read_req;
        end
    end

  // register write signal generation
  assign update_write_req = ahb_write_req | ( write_en_reg & HREADY );  // Update write enable control if
  //  1. When there is a valid write request
  //  2. When there is an active write, update it at the end of transfer (HREADY=1)

  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          write_en_reg <= 1'b0;
        end
      else if ( update_write_req)
        begin
          write_en_reg <= ahb_write_req; //总线写请求
        end
    end

  // byte strobe signal
  always @( *)
    begin
      if ( HSIZE == 3'b000)    //byte，传输数据位数000：8 bits
        begin
          case ( HADDR[ 1: 0 ] )
            2'b00:
              byte_strobe_nxt = 4'b0001; //HxDATA[0:7]
            2'b01:
              byte_strobe_nxt = 4'b0010; //HxDATA[15:8]
            2'b10:
              byte_strobe_nxt = 4'b0100; //HxDATA[23:16]
            2'b11:
              byte_strobe_nxt = 4'b1000; ////HxDATA[31:24]
            default:
              byte_strobe_nxt = 4'bxxxx;
          endcase
        end
      else if ( HSIZE == 3'b001) //half word 16bits
        begin
          if ( HADDR[ 1 ] == 1'b1)
            begin
              byte_strobe_nxt = 4'b1100;
            end //HXDATA[0:15]
          else
            begin
              byte_strobe_nxt = 4'b0011;
            end //HXDATA[16:31]
        end
      else // default 32 bits, word
        begin
          byte_strobe_nxt = 4'b1111; //HXDATA[31:0]
        end
    end

  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          byte_strobe_reg <= { 4{ 1'b0 } };
        end
      else if ( update_read_req | update_write_req) //产生读请求或者写请求
        // Update byte strobe registers if
        // 1. if there is a valid read/write transfer request
        // 2. if there is an on going transfer
        begin
          byte_strobe_reg <= byte_strobe_nxt;
        end
    end

  // out
  assign addr = addr_reg[ 15: 0 ];
  assign read_en = read_en_reg;
  assign write_en = write_en_reg;
  assign byte_strobe = byte_strobe_reg;

  // --------------------------------------------------------------------------
  //   reg wr logic
  // --------------------------------------------------------------------------

  // bit0 enble & RESETn bit1 ERR bit[4:2] RX_aval_cnt bit[7:5] TX_aval_cnt
  reg uart_en = 0;
  reg [ 15: 0] baud_div = 0;

  reg [ 7: 0] TX_data_reg = 0;
  reg dataWrote_reg = 0;

  //写寄存器1
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          // reset data register to 0x00000000
          uart_en <= 0;
          TX_data_reg <= 0;
          baud_div <= 0;
          dataWrote_reg <= 0;
        end
      else if ( ( addr[ 15: 2 ] == 14'd0 ) & ( write_en ) )
        begin
          if ( byte_strobe[ 0 ] )
            begin
              uart_en <= HWDATA[ 0 ];
            end
          if ( byte_strobe[ 1 ] )
            begin
              TX_data_reg <= HWDATA[ 15: 8 ];
              dataWrote_reg <= 1;
            end
          else
            begin
              dataWrote_reg <= 0;
            end
          if ( byte_strobe[ 2 ] )
            begin
              baud_div[ 7: 0] <= HWDATA[ 23: 16 ];
            end
          if ( byte_strobe[ 3 ] )
            begin
              baud_div[ 15: 8] <= HWDATA[ 31: 24 ];
            end
        end
      else
        begin
          dataWrote_reg <= 0;
        end
    end
  reg uart_err = 0;
  reg [ 2: 0 ] RX_aval_cnt = 0;
  reg [ 2: 0 ] TX_aval_cnt = 0;

  reg [ 31: 0] HRDATA_reg = 0;
  reg [ 7: 0 ] RX_data_reg = 0;
  reg dataRead_reg = 0;

  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          HRDATA_reg <= 0;
          dataRead_reg <= 0;
        end
      else if ( ( addr[ 15: 2 ] == 14'd0 ) & ( read_en ) )
        begin
          if ( byte_strobe[ 0 ] )
            begin
              HRDATA_reg[ 7: 0 ] <= { TX_aval_cnt, RX_aval_cnt, uart_err, uart_en };
            end
          if ( byte_strobe[ 1 ] )
            begin
              HRDATA_reg[ 15: 8 ] <= RX_data_reg ;
              dataRead_reg <= 1;
            end
          else
            begin
              dataRead_reg <= 0;
            end
          if ( byte_strobe[ 2 ] )
            begin
              HRDATA_reg[ 23: 16 ] <= baud_div[ 7: 0] ;
            end
          if ( byte_strobe[ 3 ] )
            begin
              HRDATA_reg[ 31: 24 ] <= baud_div[ 15: 8] ;
            end
        end
      else
        begin
          dataRead_reg <= 0;
        end
    end

  assign HRDATA = HRDATA_reg;

  // --------------------------------------------------------------------------
  //   uart driver logic
  // --------------------------------------------------------------------------

  //   产生TX时钟
  reg [ 15: 0 ] TX_DIV_cnt = 0;
  reg CLK_TX_pulse = 0;

  reg TX_DIV_EN = 0;

  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          TX_DIV_cnt <= 0;
          CLK_TX_pulse <= 0;
        end
      else if ( !TX_DIV_EN )
        begin
          TX_DIV_cnt <= 0;
          CLK_TX_pulse <= 0;
        end
      else if ( TX_DIV_cnt == baud_div )
        begin
          TX_DIV_cnt <= 0;
          CLK_TX_pulse <= 1;
        end
      else
        begin
          TX_DIV_cnt <= TX_DIV_cnt + 1;
          CLK_TX_pulse <= 0;
        end
    end

  // TX控制逻辑
  reg [ 10: 0] TX_shift_reg = 11'b1_1111_1111_01;
  reg [ 4: 0 ] TX_shiftOUT_cnt = 0;
  reg TX_ready = 1;

  assign TX_OUT = TX_shift_reg[ 0 ];

  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          TX_shift_reg <= 11'b1_1111_1111_01;
          TX_shiftOUT_cnt <= 0;
          TX_ready <= 1;
          TX_DIV_EN <= 0;
        end
      else if ( !uart_en )
        begin
          TX_shift_reg <= 11'b1_1111_1111_01;
          TX_shiftOUT_cnt <= 0;
          TX_ready <= 1;
          TX_DIV_EN <= 0;
        end
      else if ( dataWrote_reg & TX_ready )
        begin
          TX_shift_reg <= { 2'b11, TX_data_reg, 1'b0 };
          TX_shiftOUT_cnt <= 0;
          TX_ready <= 0;
          TX_DIV_EN <= 1;
        end
      else if ( ( !TX_ready ) & CLK_TX_pulse )
        begin
          if ( TX_shiftOUT_cnt == 19)
            begin
              TX_shift_reg <= 11'b1_1111_1111_01;
              TX_shiftOUT_cnt <= 0;
              TX_ready <= 1;
              TX_DIV_EN <= 0;
            end
          else
            begin
              if ( TX_shiftOUT_cnt[ 0 ] )
                begin
                  TX_shift_reg <= { 1'b1, TX_shift_reg[ 10: 1 ] };
                end
              TX_shiftOUT_cnt <= TX_shiftOUT_cnt + 1;
            end
        end
    end


  //   产生RX时钟
  reg [ 15: 0 ] RX_DIV_cnt = 0;
  reg CLK_RX_pulse = 0;

  reg RX_DIV_EN = 0;

  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          RX_DIV_cnt <= 0;
          CLK_RX_pulse <= 0;
        end
      else if ( !RX_DIV_EN )
        begin
          RX_DIV_cnt <= 0;
          CLK_RX_pulse <= 0;
        end
      else if ( RX_DIV_cnt == baud_div )
        begin
          RX_DIV_cnt <= 0;
          CLK_RX_pulse <= 1;
        end
      else
        begin
          RX_DIV_cnt <= RX_DIV_cnt + 1;
          CLK_RX_pulse <= 0;
        end
    end

  // RX控制逻辑
  reg [ 5: 0 ] RX_samp_regs = 0;

  // 采样和判定
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          RX_samp_regs <= 0;
        end
      else
        begin
          RX_samp_regs <= { RX_IN, RX_samp_regs[ 5: 1 ] };
        end
    end

  reg regard_RX_samp_low = 1;
  reg regard_RX_samp_high = 0;
  always @(* )
    begin
      case ( RX_samp_regs)
        6'o00, 6'o10, 6'o20, 6'o40, 6'o01, 6'o02, 6'o04,
        6'o03, 6'o05, 6'o06, 6'o11, 6'o12, 6'o14, 6'o21, 6'o22, 6'o24, 6'o41, 6'o42, 6'o44, 6'o30, 6'o50, 6'o60 :
          begin
            regard_RX_samp_low = 1;
            regard_RX_samp_high = 0;
          end
        6'o77, 6'o76, 6'o73, 6'o75, 6'o67, 6'o57, 6'o37,
        6'o71, 6'o72, 6'o74, 6'o66, 6'o65, 6'o63, 6'o56, 6'o55, 6'o53, 6'o36, 6'o35, 6'o33, 6'o17, 6'o27, 6'o47 :
          begin
            regard_RX_samp_low = 0;
            regard_RX_samp_high = 1;
          end
        default:
          // 20种55开的情况
          begin
            regard_RX_samp_low = 0;
            regard_RX_samp_high = 0;
          end
      endcase
    end

  // 可能的起始位判定
  reg RX_samp_low_r = 1;
  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          RX_samp_low_r <= 1;
        end
      else
        begin
          RX_samp_low_r <= regard_RX_samp_low;
        end
    end

  wire RX_start_bit_req = ( ~RX_samp_low_r ) & regard_RX_samp_low;

  reg [ 8: 0 ] RX_shift_reg = 0;
  reg [ 4: 0 ] RX_shiftIN_cnt = 0;
  reg RX_recving = 0;

  always @( posedge HCLK or negedge HRESETn)
    begin
      if ( ~HRESETn)
        begin
          RX_shift_reg <= 0;
          RX_shiftIN_cnt <= 0;
          RX_recving <= 0;
          RX_DIV_EN <= 0;
          RX_data_reg <= 0;
        end
      else if ( !uart_en )
        begin
          RX_shift_reg <= 0;
          RX_shiftIN_cnt <= 0;
          RX_recving <= 0;
          RX_DIV_EN <= 0;
          RX_data_reg <= 0;
        end
      else if ( ( !RX_recving ) & RX_start_bit_req)
        begin
          RX_shift_reg <= 0;
          RX_shiftIN_cnt <= 0;
          RX_recving <= 1;
          RX_DIV_EN <= 1;
        end
      else if ( RX_recving & CLK_RX_pulse)
        begin
          if ( RX_shiftIN_cnt == 18)
            // 提前结束，预留时钟偏差余量
            begin
              RX_data_reg <= RX_shift_reg[ 8: 1 ];
              RX_shift_reg <= 0;
              RX_shiftIN_cnt <= 0;
              RX_recving <= 0;
              RX_DIV_EN <= 0;
            end
          else
            begin
              if ( ~RX_shiftIN_cnt[ 0 ] )
                begin
                  if ( regard_RX_samp_high)
                    begin
                      RX_shift_reg <= { 1'b1, RX_shift_reg[ 8: 1 ] };
                    end
                  else if ( regard_RX_samp_low)
                    begin
                      RX_shift_reg <= { 1'b0, RX_shift_reg[ 8: 1 ] };
                    end
                  else
                    begin
                      // 出错，认为是边沿不够陡峭，尝试挽救
                      RX_shift_reg <= { ~RX_shift_reg[ 8 ], RX_shift_reg[ 8: 1 ] };
                    end
                end

              RX_shiftIN_cnt <= RX_shiftIN_cnt + 1;
            end
        end
    end

endmodule
