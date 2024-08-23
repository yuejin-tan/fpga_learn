module ahb_epwm
  #(
     // 2M 驱动时钟，持续刷新
     parameter HC595_DRV_CLK_DIV = 99
   )
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

     // HC595 SIG
     output reg pwm_out1 = 0,
     output reg pwm_out2 = 0,
     output reg pwm_out3 = 0
   );

  reg [7: 0] mode = 0;

  reg [15: 0] TBPRD = 0;
  reg [15: 0] TBCNT = 0;

  reg CTRDOWN = 0;

  reg [15: 0] CMPA = 0;
  reg [15: 0] CMPB = 0;
  reg [15: 0] CMPC = 0;

  // --------------------------------------------------------------------------
  //   ahb interface logic
  // --------------------------------------------------------------------------

  reg [15: 0] TBPRD_shadow = 0;
  reg [15: 0] CMPA_shadow = 0;
  reg [15: 0] CMPB_shadow = 0;
  reg [15: 0] CMPC_shadow = 0;

  // No err
  assign HRESP = 1'b0;
  // slave always ready
  assign HREADYOUT = 1'b1;

  wire trans_en;
  assign trans_en = HSEL & HTRANS[1];

  wire write_en;
  assign write_en = trans_en & HWRITE;

  wire read_en;
  assign read_en = trans_en & (~HWRITE);

  reg [3: 0] size_dec;
  always@( * )
    begin
      case ({HADDR[1: 0], HSIZE[1: 0]})
        4'h0 :
          size_dec = 4'h1;
        4'h1 :
          size_dec = 4'h3;
        4'h2 :
          size_dec = 4'hf;
        4'h4 :
          size_dec = 4'h2;
        4'h8 :
          size_dec = 4'h4;
        4'h9 :
          size_dec = 4'hc;
        4'hc :
          size_dec = 4'h8;
        default :
          size_dec = 4'h0;
      endcase
    end

  reg [3: 0]size_reg; // 数据选择
  always@(posedge HCLK or negedge HRESETn)
    begin
      if (~HRESETn)
        size_reg <= 0;
      else if (write_en & HREADY)
        size_reg <= size_dec;
    end

  // 写逻辑
  reg [15: 0] addr_reg;
  always@(posedge HCLK or negedge HRESETn)
    begin
      if (~HRESETn)
        addr_reg <= 0;
      else if (trans_en & HREADY)
        addr_reg <= {HADDR[15: 2], 2'd0};
    end

  reg wr_en_reg;
  always@(posedge HCLK or negedge HRESETn)
    begin
      if (~HRESETn)
        wr_en_reg <= 1'b0;
      else if (HREADY)
        wr_en_reg <= write_en;
      else
        wr_en_reg <= 1'b0;
    end

  // 写逻辑
  always@(posedge HCLK or negedge HRESETn)
    begin
      if (~HRESETn)
        begin
          mode <= 0;
        end
      else
        if ((addr_reg[ 15: 2 ] == 14'd0 ) & wr_en_reg)
          begin
            if (size_reg[0])
              begin
                mode <= HWDATA[ 7: 0 ];
              end
          end
    end

  always@(posedge HCLK or negedge HRESETn)
    begin
      if (~HRESETn)
        begin
          TBPRD_shadow <= 0;
          CMPA_shadow <= 0;
        end
      else
        if ((addr_reg[ 15: 2 ] == 14'd1 ) & wr_en_reg)
          begin
            if (size_reg[0])
              begin
                TBPRD_shadow[ 7: 0 ] <= HWDATA[ 7: 0 ];
              end
            if (size_reg[1])
              begin
                TBPRD_shadow[ 15: 8 ] <= HWDATA[ 15: 8 ];
              end
            if (size_reg[2])
              begin
                CMPA_shadow[ 7: 0 ] <= HWDATA[ 23: 16 ];
              end
            if (size_reg[3])
              begin
                CMPA_shadow[ 15: 8 ] <= HWDATA[ 31: 24 ];
              end
          end
    end

  always@(posedge HCLK or negedge HRESETn)
    begin
      if (~HRESETn)
        begin
          CMPB_shadow <= 0;
          CMPC_shadow <= 0;
        end
      else
        if ((addr_reg[ 15: 2 ] == 14'd2 ) & wr_en_reg)
          begin
            if (size_reg[0])
              begin
                CMPB_shadow[ 7: 0 ] <= HWDATA[ 7: 0 ];
              end
            if (size_reg[1])
              begin
                CMPB_shadow[ 15: 8 ] <= HWDATA[ 15: 8 ];
              end
            if (size_reg[2])
              begin
                CMPC_shadow[ 7: 0 ] <= HWDATA[ 23: 16 ];
              end
            if (size_reg[3])
              begin
                CMPC_shadow[ 15: 8 ] <= HWDATA[ 31: 24 ];
              end
          end
    end

  reg [ 31: 0] HRDATA_reg = 0;

  //register read
  always @ ( *)
    begin
      if ( read_en)
        begin
          case ( addr_reg[ 15: 2 ] )
            14'd0:
              HRDATA_reg = {24'h0, mode};
            14'd1:
              HRDATA_reg = { CMPA_shadow, TBPRD_shadow};
            14'd2:
              HRDATA_reg = { CMPC_shadow, CMPB_shadow};
            default:
              HRDATA_reg = 0;
          endcase
        end
      else
        begin
          HRDATA_reg = { 32{ 1'bx } };
        end
    end

  assign HRDATA = HRDATA_reg;


  // --------------------------------------------------------------------------
  //   seg driver logic
  // --------------------------------------------------------------------------

  // TB 模块
  wire [15: 0] TBCNT_a1 = TBCNT + 16'h1;
  wire [15: 0] TBCNT_s1 = TBCNT + 16'hffff;

  // signals
  wire SIG_ZERO = TBCNT == 0 ? 1 : 0;
  wire SIG_PRD = TBCNT >= TBPRD? 1 : 0;

  wire SIG_CAE = TBCNT == CMPA ? 1 : 0;
  wire SIG_CAU = SIG_CAE && ~CTRDOWN;
  wire SIG_CAD = SIG_CAE && CTRDOWN;

  wire SIG_CBE = TBCNT == CMPB ? 1 : 0;
  wire SIG_CBU = SIG_CBE && ~CTRDOWN;
  wire SIG_CBD = SIG_CBE && CTRDOWN;

  wire SIG_CCE = TBCNT == CMPC ? 1 : 0;
  wire SIG_CCU = SIG_CCE && ~CTRDOWN;
  wire SIG_CCD = SIG_CCE && CTRDOWN;

  always @( posedge HCLK )
    begin
      if ( HRESETn == 1'b0 || ~mode[0])
        begin
          TBCNT <= 0;
        end
      else
        begin
          if (SIG_ZERO)
            begin
              if (TBPRD != 0)
                TBCNT <= TBCNT_a1;
            end
          else if (SIG_PRD)
            begin
              TBCNT <= TBCNT_s1;
            end
          else if (CTRDOWN)
            begin
              TBCNT <= TBCNT_s1;
            end
          else
            begin
              TBCNT <= TBCNT_a1;
            end
        end
    end

  always @( posedge HCLK )
    begin
      if ( HRESETn == 1'b0 )
        begin
          TBPRD <= 0;
          CMPA <= 0;
          CMPB <= 0;
          CMPC <= 0;
        end
      else
        begin
          if (SIG_ZERO)
            begin
              TBPRD <= TBPRD_shadow;
              CMPA <= CMPA_shadow;
              CMPB <= CMPB_shadow;
              CMPC <= CMPC_shadow;
            end
          else if (SIG_PRD)
            begin
              CMPA <= CMPA_shadow;
              CMPB <= CMPB_shadow;
              CMPC <= CMPC_shadow;
            end
        end
    end

  always @( posedge HCLK )
    begin
      if ( HRESETn == 1'b0 || ~mode[0])
        begin
          CTRDOWN <= 0;
        end
      else
        begin
          if (TBCNT_s1 == 0)
            begin
              CTRDOWN <= 0;
            end
          else if (TBCNT_a1 == TBPRD)
            begin
              CTRDOWN <= 1;
            end
        end
    end


  // AQ 模块
  always @( posedge HCLK )
    begin
      if ( HRESETn == 1'b0 || ~mode[0])
        begin
          pwm_out1 <= 0;
        end
      else
        begin
          if (SIG_CAU)
            begin
              pwm_out1 <= 1;
            end
          else if (SIG_CAD)
            begin
              pwm_out1 <= 0;
            end
        end
    end

  always @( posedge HCLK )
    begin
      if ( HRESETn == 1'b0 || ~mode[0])
        begin
          pwm_out2 <= 0;
        end
      else
        begin
          if (SIG_CBU)
            begin
              pwm_out2 <= 1;
            end
          else if (SIG_CBD)
            begin
              pwm_out2 <= 0;
            end
        end
    end

  always @( posedge HCLK )
    begin
      if ( HRESETn == 1'b0 || ~mode[0])
        begin
          pwm_out3 <= 0;
        end
      else
        begin
          if (SIG_CCU)
            begin
              pwm_out3 <= 1;
            end
          else if (SIG_CCD)
            begin
              pwm_out3 <= 0;
            end
        end
    end

endmodule
