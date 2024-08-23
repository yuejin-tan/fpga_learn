module top (
    // clk
    input wire clk_27M,
    input wire clk_25M,
    input wire clk_p3,
    input wire clk_p4,
    input wire clk_p5,

    // led CORE
    output wire led_core,

    // PLL EXT
    inout wire pll_i2c_scl,
    inout wire pll_i2c_sda,

    // SRAM
    output wire [ 18: 0 ] SRAM_ADDR,
    inout wire [ 15: 0 ] SRAM_DQ,
    output wire SRAM_nWE,
    output wire SRAM_nOE,
    output wire SRAM_nCE,
    output wire SRAM_nLB,
    output wire SRAM_nUB,

    //  FLASH
    inout wire flash_sclk,
    inout wire flash_cs,
    inout wire flash_mosi,
    inout wire flash_miso,

    // dbg
    input wire SWCLK,
    inout wire SWDIO,

    // key
    input wire [ 2: 0 ] key_pin,

    // led 0 on 1 off
    output wire [ 3: 0 ] led_pin,

    // BEEP
    output wire beep_pin,

    // uart
    inout wire uart_DAP_rx,
    inout wire uart_DAP_tx,

    input wire uart_ch340_rx,
    output wire uart_ch340_tx,

    // sd
    inout wire sd_sclk,
    inout wire sd_cs,
    inout wire sd_mosi,
    inout wire sd_miso,

    // w5500
    input wire w5500_rstn,
    input wire w5500_intn,
    output wire w5500_sclk,
    output wire w5500_cs,
    output wire w5500_mosi,
    input wire w5500_miso,

    // 数码管接口
    output wire seg7_SH_CP,   //移位时钟
    output wire seg7_ST_CP,   //数据锁存时钟
    output wire seg7_DS,      //移位串行数据

    // lcd
    output wire CS_8080,
    output wire RS_8080, // 0:CMD 1:DATA
    output wire WR_8080,
    output wire RD_8080,
    inout wire [ 15: 0] DATA_8080,
    inout wire LCD_BL,
    inout wire LCD_RST,
    inout wire LCDT_RST,
    inout wire LCDT_PEN,
    inout wire LCDT_SCL,
    inout wire LCDT_SDA,

    // iic 4 bme280.
    inout wire bme_scl,
    inout wire bme_sda,

    // iic 4 eeprom, rtc etc.
    inout wire i2c_scl,
    inout wire i2c_sda

  );

  wire [ 31: 0 ] GPIO;

  // PLL EXT
  assign pll_i2c_scl = 1'bz;
  assign pll_i2c_sda = 1'bz;

  // iic 4 eeprom, rtc etc.
  assign i2c_scl = 1'bz;
  assign i2c_sda = 1'bz;

  // iic 4 bme280.
  assign bme_scl = GPIO[ 20 ];
  assign bme_sda = GPIO[ 21 ];

  // key_pin
  assign GPIO[5: 4] = key_pin[2: 1];

  // led
  // assign led_core = GPIO[ 0 ];

  // BEEP
  // assign beep_pin = GPIO[ 1 ];

  // uart
  assign uart_DAP_rx = GPIO[ 2 ];
  assign uart_DAP_tx = GPIO[ 3 ];

  // FLASH
  assign flash_sclk = GPIO[ 11 ];
  assign flash_cs = GPIO[ 12 ];
  assign flash_mosi = GPIO[ 13 ];
  assign flash_miso = GPIO[ 14 ];

  // sd
  assign sd_sclk = GPIO[ 7 ];
  assign sd_cs = GPIO[ 8 ];
  assign sd_mosi = GPIO[ 9 ];
  assign sd_miso = GPIO[ 10 ];

  // w5500
  assign w5500_sclk = 0;
  assign w5500_cs = 1;
  assign w5500_mosi = 0;

  // LCD
  assign LCD_BL = GPIO[ 6 ];
  assign LCDT_SCL = GPIO[ 15 ];
  assign LCDT_SDA = GPIO[ 16 ];
  assign LCD_RST = GPIO[ 17 ];
  assign LCDT_RST = GPIO[ 18 ];
  assign LCDT_PEN = GPIO[ 19 ];

  // sram
  // assign SRAM_ADDR = 0;
  // assign SRAM_nWE = 1;
  // assign SRAM_nOE = 1;
  // assign SRAM_nCE = 1;
  // assign SRAM_nLB = 1;
  // assign SRAM_nUB = 1;

  // CLKS
  wire PLL1_lock;
  wire CLK_CM3;
  wire CLK_FPGA_SYS1;
  wire AHB_USR_CLK = CLK_CM3;
  PLL_FREQ PLL_inst1(
             .CLKI(clk_25M), // 25 IN
             .CLKOP(CLK_CM3),
             .CLKOS(CLK_FPGA_SYS1),
             //  .CLKOS2(),
             //  .CLKOS3(),
             .LOCK(PLL1_lock)
           );

  // RESET
  reg CM3SYS_RSTN_buff = 0;
  reg CM3SYS_RSTN = 0;
  always@( posedge CLK_CM3)
    begin
      CM3SYS_RSTN_buff <= key_pin[ 0 ] & PLL1_lock;
      CM3SYS_RSTN <= CM3SYS_RSTN_buff;
    end

  // fpga 流水灯
  led_wf led_wf_inst1 (
           .clk(CLK_FPGA_SYS1),
           .rst(CM3SYS_RSTN),
           .led_sig(led_pin)
         );

  // CM3 CORE
  wire [ 15: 0 ] CM3INTSIG;
  assign CM3INTSIG = { 16'b0 };
  wire [ 31: 0 ] GPIO_IN;
  wire [ 31: 0] GPIO_OUT;
  wire [ 31: 0] GPIO_OUT_EN;
  // GPIO CFG
  genvar i;
  generate
    for (i = 2;i < 22;i = i + 1)
      begin:setb
        xsIOBB inst_xsIOBB_GPIO (
                 .I (GPIO_OUT[i]),
                 .T (~GPIO_OUT_EN[i]),
                 .O (GPIO_IN[i]),
                 .B (GPIO[i])
               );
      end
  endgenerate
  assign GPIO_IN[1: 0] = 0;
  assign GPIO_IN[31: 22] = 0;
  assign GPIO[31: 22] = 0;

  // DEBUG
  wire TMSOEN;
  wire TMSO;
  assign SWDIO = TMSOEN ? 1'bz : TMSO;

  //   wire AHB_CLK;
  wire [ 31: 0] TARGEXP0HADDR;
  wire [ 2: 0] TARGEXP0HBURST;
  wire TARGEXP0HMASTLOCK;
  wire [ 3: 0] TARGEXP0HPROT;
  wire [ 31: 0] TARGEXP0HRDATA;
  wire TARGEXP0HREADYMUX;
  wire TARGEXP0HREADYOUT;
  wire TARGEXP0HRESP;
  wire TARGEXP0HSEL;
  wire [ 2: 0] TARGEXP0HSIZE;
  wire [ 1: 0] TARGEXP0HTRANS;
  wire [ 31: 0] TARGEXP0HWDATA;
  wire TARGEXP0HWRITE;

  // AHBlite Interconncet
  wire [ 31: 0] TARGEXP1HADDR;
  wire [ 2: 0] TARGEXP1HBURST;
  wire TARGEXP1HMASTLOCK;
  wire [ 3: 0] TARGEXP1HPROT;
  wire [ 31: 0] TARGEXP1HRDATA;
  wire TARGEXP1HREADYMUX;
  wire TARGEXP1HREADYOUT;
  wire TARGEXP1HRESP;
  wire TARGEXP1HSEL;
  wire [ 2: 0] TARGEXP1HSIZE;
  wire [ 1: 0] TARGEXP1HTRANS;
  wire [ 31: 0] TARGEXP1HWDATA;
  wire TARGEXP1HWRITE;

  wire HSEL_P0;
  wire [31: 0] HADDR_P0;
  wire [2: 0] HBURST_P0;
  wire HMASTLOCK_P0;
  wire [3: 0] HPROT_P0;
  wire [2: 0] HSIZE_P0;
  wire [1: 0] HTRANS_P0;
  wire [31: 0] HWDATA_P0;
  wire HWRITE_P0;
  wire HREADY_P0;
  wire HREADYOUT_P0;
  wire [31: 0] HRDATA_P0;
  wire HRESP_P0;

  wire HSEL_P1;
  wire [31: 0] HADDR_P1;
  wire [2: 0] HBURST_P1;
  wire HMASTLOCK_P1;
  wire [3: 0] HPROT_P1;
  wire [2: 0] HSIZE_P1;
  wire [1: 0] HTRANS_P1;
  wire [31: 0] HWDATA_P1;
  wire HWRITE_P1;
  wire HREADY_P1;
  wire HREADYOUT_P1;
  wire [31: 0] HRDATA_P1;
  wire HRESP_P1;

  wire HSEL_P2;
  wire [31: 0] HADDR_P2;
  wire [2: 0] HBURST_P2;
  wire HMASTLOCK_P2;
  wire [3: 0] HPROT_P2;
  wire [2: 0] HSIZE_P2;
  wire [1: 0] HTRANS_P2;
  wire [31: 0] HWDATA_P2;
  wire HWRITE_P2;
  wire HREADY_P2;
  wire HREADYOUT_P2;
  wire [31: 0] HRDATA_P2;
  wire HRESP_P2;

  // null 设备
  wire HSEL_P3;
  wire [31: 0] HADDR_P3;
  wire [2: 0] HBURST_P3;
  wire HMASTLOCK_P3;
  wire [3: 0] HPROT_P3;
  wire [2: 0] HSIZE_P3;
  wire [1: 0] HTRANS_P3;
  wire [31: 0] HWDATA_P3;
  wire HWRITE_P3;
  wire HREADY_P3;
  wire HREADYOUT_P3;
  wire [31: 0] HRDATA_P3;
  wire HRESP_P3;

  // ahb_lcd8080 ahb_lcd8080_inst1(
  //               .HCLK ( AHB_USR_CLK ),
  //               .HRESETn ( CM3SYS_RSTN ),

  //               .HSEL ( TARGEXP1HSEL ),
  //               .HADDR ( TARGEXP1HADDR[ 15: 0 ] ),
  //               .HTRANS ( TARGEXP1HTRANS ),
  //               .HSIZE ( TARGEXP1HSIZE ),
  //               .HWRITE ( TARGEXP1HWRITE ),
  //               .HWDATA ( TARGEXP1HWDATA ),
  //               .HREADY ( TARGEXP1HREADYMUX ),

  //               .HREADYOUT ( TARGEXP1HREADYOUT ),
  //               .HRDATA ( TARGEXP1HRDATA ),
  //               .HRESP ( TARGEXP1HRESP ),

  //               // UART SIG
  //               .CS_8080(CS_8080),
  //               .RS_8080(RS_8080), // 0:CMD 1:DATA
  //               .WR_8080(WR_8080),
  //               .RD_8080(RD_8080),

  //               .DATA_8080(DATA_8080)
  //             );

  AHBlite_Interconnect Interconncet(
                         .HCLK (AHB_USR_CLK),
                         .HRESETn (CM3SYS_RSTN),
                         //  .HRESETn (0),

                         // CORE SIDE
                         .HSEL_M (TARGEXP1HSEL),
                         .HADDR (TARGEXP1HADDR),
                         .HTRANS (TARGEXP1HTRANS),
                         .HSIZE (TARGEXP1HSIZE),
                         .HBURST (TARGEXP1HBURST),
                         .HPROT (TARGEXP1HPROT),
                         .HMASTLOCK (TARGEXP1HMASTLOCK),
                         .HWRITE (TARGEXP1HWRITE),
                         .HWDATA (TARGEXP1HWDATA),
                         .HRDATA (TARGEXP1HRDATA),
                         //  .HRDATA ( ),
                         .HREADY_master (TARGEXP1HREADYMUX),
                         .HREADY (TARGEXP1HREADYOUT),
                         //  .HREADY ( ),
                         .HRESP (TARGEXP1HRESP),
                         //  .HRESP ( ),

                         // P0
                         .HSEL_P0 (HSEL_P0),
                         .HADDR_P0 (HADDR_P0),
                         .HBURST_P0 (HBURST_P0),
                         .HMASTLOCK_P0 (HMASTLOCK_P0),
                         .HPROT_P0 (HPROT_P0),
                         .HSIZE_P0 (HSIZE_P0),
                         .HTRANS_P0 (HTRANS_P0),
                         .HWDATA_P0 (HWDATA_P0),
                         .HWRITE_P0 (HWRITE_P0),
                         .HREADY_P0 (HREADY_P0),
                         .HREADYOUT_P0 (HREADYOUT_P0),
                         .HRDATA_P0 (HRDATA_P0),
                         .HRESP_P0 (HRESP_P0),

                         // P1
                         .HSEL_P1 (HSEL_P1),
                         .HADDR_P1 (HADDR_P1),
                         .HBURST_P1 (HBURST_P1),
                         .HMASTLOCK_P1 (HMASTLOCK_P1),
                         .HPROT_P1 (HPROT_P1),
                         .HSIZE_P1 (HSIZE_P1),
                         .HTRANS_P1 (HTRANS_P1),
                         .HWDATA_P1 (HWDATA_P1),
                         .HWRITE_P1 (HWRITE_P1),
                         .HREADY_P1 (HREADY_P1),
                         .HREADYOUT_P1 (HREADYOUT_P1),
                         .HRDATA_P1 (HRDATA_P1),
                         .HRESP_P1 (HRESP_P1),

                         // P2
                         .HSEL_P2 (HSEL_P2),
                         .HADDR_P2 (HADDR_P2),
                         .HBURST_P2 (HBURST_P2),
                         .HMASTLOCK_P2 (HMASTLOCK_P2),
                         .HPROT_P2 (HPROT_P2),
                         .HSIZE_P2 (HSIZE_P2),
                         .HTRANS_P2 (HTRANS_P2),
                         .HWDATA_P2 (HWDATA_P2),
                         .HWRITE_P2 (HWRITE_P2),
                         .HREADY_P2 (HREADY_P2),
                         .HREADYOUT_P2 (HREADYOUT_P2),
                         .HRDATA_P2 (HRDATA_P2),
                         .HRESP_P2 (HRESP_P2),

                         // P3
                         .HSEL_P3 (HSEL_P3),
                         .HADDR_P3 (HADDR_P3),
                         .HBURST_P3 (HBURST_P3),
                         .HMASTLOCK_P3 (HMASTLOCK_P3),
                         .HPROT_P3 (HPROT_P3),
                         .HSIZE_P3 (HSIZE_P3),
                         .HTRANS_P3 (HTRANS_P3),
                         .HWDATA_P3 (HWDATA_P3),
                         .HWRITE_P3 (HWRITE_P3),
                         .HREADY_P3 (HREADY_P3),
                         .HREADYOUT_P3 (HREADYOUT_P3),
                         .HRDATA_P3 (HRDATA_P3),
                         .HRESP_P3 (HRESP_P3)
                       );

  ahb_lcd8080 ahb_lcd8080_inst1(
                .HCLK ( AHB_USR_CLK ),
                .HRESETn ( CM3SYS_RSTN ),

                .HSEL ( HSEL_P0 ),
                .HADDR ( HADDR_P0[ 15: 0 ] ),
                .HTRANS ( HTRANS_P0 ),
                .HSIZE ( HSIZE_P0 ),
                .HWRITE ( HWRITE_P0 ),
                .HWDATA ( HWDATA_P0 ),
                .HREADY ( HREADY_P0 ),

                .HREADYOUT ( HREADYOUT_P0 ),
                .HRDATA ( HRDATA_P0 ),
                .HRESP ( HRESP_P0 ),

                // UART SIG
                .CS_8080(CS_8080),
                .RS_8080(RS_8080), // 0:CMD 1:DATA
                .WR_8080(WR_8080),
                .RD_8080(RD_8080),

                .DATA_8080(DATA_8080)
              );

  // 8位数码管
  ahb_seg7x8 seg_inst(
               .HCLK ( AHB_USR_CLK ), //时钟
               .HRESETn ( CM3SYS_RSTN ), //复位

               .HSEL ( HSEL_P1 ), // AHB inputs，设备选择
               .HADDR ( HADDR_P1[ 15: 0 ] ), //地址
               .HTRANS ( HTRANS_P1 ), //传输控制信号
               .HSIZE ( HSIZE_P1 ), //传输大小
               .HWRITE ( HWRITE_P1 ), //写控制
               .HWDATA ( HWDATA_P1 ), //写数据
               .HREADY ( HREADY_P1 ), //传输完成

               .HREADYOUT ( HREADYOUT_P1 ), // AHB Outputs，设备准备信号
               .HRDATA ( HRDATA_P1 ), //读取到的数据
               .HRESP ( HRESP_P1 ), //设备响应

               .SH_CLK( seg7_SH_CP ),
               .LD_CLK( seg7_ST_CP ),
               .HC_DAT( seg7_DS)
             );

  // uart
  ahb_uart ahb_uart1(
             .HCLK ( AHB_USR_CLK ),
             .HRESETn ( CM3SYS_RSTN ),

             .HSEL ( HSEL_P2 ),
             .HADDR ( HADDR_P2[ 15: 0 ] ),
             .HTRANS ( HTRANS_P2 ),
             .HSIZE ( HSIZE_P2 ),
             .HWRITE ( HWRITE_P2 ),
             .HWDATA ( HWDATA_P2 ),
             .HREADY ( HREADY_P2 ),

             .HREADYOUT ( HREADYOUT_P2 ),
             .HRDATA ( HRDATA_P2 ),
             .HRESP ( HRESP_P2 ),

             .TX_OUT( uart_ch340_tx ),
             .RX_IN( uart_ch340_rx )
           );

  // ahb_null
  ahb_epwm ahb_epwm1(
             .HCLK ( AHB_USR_CLK ),
             .HRESETn ( CM3SYS_RSTN ),

             .HSEL ( HSEL_P3 ),
             .HADDR ( HADDR_P3[ 15: 0 ] ),
             .HTRANS ( HTRANS_P3 ),
             .HSIZE ( HSIZE_P3 ),
             .HWRITE ( HWRITE_P3 ),
             .HWDATA ( HWDATA_P3 ),
             .HREADY ( HREADY_P3 ),

             .HREADYOUT ( HREADYOUT_P3 ),
             .HRDATA ( HRDATA_P3 ),
             .HRESP ( HRESP_P3 ),

             .pwm_out1 (beep_pin),
             .pwm_out2 (led_core),
             .pwm_out3 ()
           );

  // EXT SRAM
  ahb_sram ahb_sram1(
             .HCLK ( CLK_CM3 ), //时钟
             .HRESETn ( CM3SYS_RSTN ), //复位

             .HSEL ( TARGEXP0HSEL ), // AHB inputs，设备选择
             .HADDR ( TARGEXP0HADDR[ 20 - 1: 0 ] ), //地址
             .HTRANS ( TARGEXP0HTRANS ), //传输控制信号
             .HSIZE ( TARGEXP0HSIZE ),  //传输大小
             .HWRITE ( TARGEXP0HWRITE ), //写控制
             .HWDATA ( TARGEXP0HWDATA ), //写数据
             .HREADY ( TARGEXP0HREADYMUX ), //传输完成

             .HREADYOUT ( TARGEXP0HREADYOUT ), // AHB Outputs，设备准备信号
             .HRDATA ( TARGEXP0HRDATA ), //读取到的数据
             .HRESP ( TARGEXP0HRESP ), //设备响应

             .SRAM_ADDR( SRAM_ADDR ),
             .SRAM_DQ( SRAM_DQ ),
             .SRAM_nWE( SRAM_nWE ),
             .SRAM_nOE( SRAM_nOE ),
             .SRAM_nCE( SRAM_nCE ),
             .SRAM_nLB( SRAM_nLB ),
             .SRAM_nUB( SRAM_nUB)
           );

  xsCM3 inst (
          .CIBCLK ( CLK_CM3 ),
          .TREECLK ( CLK_CM3 ),
          //  .MTX_CLK ( AHB_CLK ), //AHB CLK
          .MTXRSTN ( CM3SYS_RSTN ),
          .NSRST ( 1'b1 ),
          .NTRST ( 1'b1 ),
          .CPURSTN ( CM3SYS_RSTN ),

          .DBG_SWDI_TMS ( SWDIO ),
          .DBG_SWDO ( TMSO ),
          .DBG_SWDO_EN ( TMSOEN ),
          .TDO_ENABLE (),
          .TDO_TMS (),
          .CS_TDI (),
          .CS_TCK ( SWCLK ),

          .EXTINT ( CM3INTSIG ),
          .GPIOI ( GPIO_IN ),
          .GPIOO ( GPIO_OUT ),
          .GPIOOEN ( GPIO_OUT_EN ),

          .DMACBREQ ( 4'b0 ),
          .DMACLBREQ ( 4'b0 ),
          .DMACSREQ ( 4'b0 ),
          .DMACLSREQ ( 4'b0 ),
          .DMACCLR (),
          .DMACTC (),

          .INITEXP0HADDR	( 32'b0 ),
          .INITEXP0HBURST	( 3'b0 ),
          .INITEXP0HMASTLOCK	( 1'b0 ),
          .INITEXP0HPROT	( 4'b0 ),
          .INITEXP0HRDATA	(),
          .INITEXP0HREADY	(),
          .INITEXP0HRESP	(),
          .INITEXP0HSEL	( 1'b0 ),
          .INITEXP0HSIZE	( 3'b0 ),
          .INITEXP0HTRANS	( 2'b0 ),
          .INITEXP0HWDATA	( 32'b0 ),
          .INITEXP0HWRITE	( 1'b0 ),
          .INITEXP1HADDR	( 32'b0 ),
          .INITEXP1HBURST	( 3'b0 ),
          .INITEXP1HMASTLOCK	( 1'b0 ),
          .INITEXP1HPROT	( 4'b0 ),
          .INITEXP1HRDATA	(),
          .INITEXP1HREADY	(),
          .INITEXP1HRESP	(),
          .INITEXP1HSEL	( 1'b0 ),
          .INITEXP1HSIZE	( 3'b0 ),
          .INITEXP1HTRANS	( 2'b0 ),
          .INITEXP1HWDATA	( 32'b0 ),
          .INITEXP1HWRITE	( 1'b0 ),

          .TARGEXP0HADDR ( TARGEXP0HADDR ),
          .TARGEXP0HBURST ( TARGEXP0HBURST ),
          .TARGEXP0HMASTLOCK ( TARGEXP0HMASTLOCK ),
          .TARGEXP0HPROT ( TARGEXP0HPROT ),
          .TARGEXP0HRDATA ( TARGEXP0HRDATA ),
          .TARGEXP0HREADYMUX ( TARGEXP0HREADYMUX ),
          .TARGEXP0HREADYOUT ( TARGEXP0HREADYOUT ),
          .TARGEXP0HRESP ( TARGEXP0HRESP ),
          .TARGEXP0HSEL ( TARGEXP0HSEL ),
          .TARGEXP0HSIZE ( TARGEXP0HSIZE ),
          .TARGEXP0HTRANS ( TARGEXP0HTRANS ),
          .TARGEXP0HWDATA ( TARGEXP0HWDATA ),
          .TARGEXP0HWRITE ( TARGEXP0HWRITE ),

          .TARGEXP1HADDR ( TARGEXP1HADDR ),
          .TARGEXP1HBURST ( TARGEXP1HBURST ),
          .TARGEXP1HMASTLOCK ( TARGEXP1HMASTLOCK ),
          .TARGEXP1HPROT ( TARGEXP1HPROT ),
          .TARGEXP1HRDATA ( TARGEXP1HRDATA ),
          .TARGEXP1HREADYMUX ( TARGEXP1HREADYMUX ),
          .TARGEXP1HREADYOUT ( TARGEXP1HREADYOUT ),
          .TARGEXP1HRESP ( TARGEXP1HRESP ),
          .TARGEXP1HSEL ( TARGEXP1HSEL ),
          .TARGEXP1HSIZE ( TARGEXP1HSIZE ),
          .TARGEXP1HTRANS ( TARGEXP1HTRANS ),
          .TARGEXP1HWDATA ( TARGEXP1HWDATA ),
          .TARGEXP1HWRITE ( TARGEXP1HWRITE )
        );

  defparam inst.PCLK_DIV = 0;
  defparam inst.CORECLK = "CIB_CLK";
  defparam inst.RSTN_ENABLE = "TRUE";
  defparam inst.MTXCLK = "CORECLK";
  defparam inst.CORECLK_EN = "TRUE";
  defparam inst.CORE_SET = "TRUE";


endmodule
