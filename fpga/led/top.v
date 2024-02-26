module top (
    // clk
    input wire clk_27M,
    input wire clk_25M,
    input wire clk_p3,
    input wire clk_p4,
    input wire clk_p5,

    //  led CORE
    output wire led_core,

    //  PLL EXT
    output wire pll_i2c_scl,
    inout wire pll_i2c_sda,

    //  SRAM
    output wire [ 18: 0 ] SRAM_ADDR,
    inout wire [ 15: 0 ] SRAM_DQ,
    output wire SRAM_nWE,
    output wire SRAM_nOE,
    output wire SRAM_nCE,
    output wire SRAM_nLB,
    output wire SRAM_nUB,

    //  FLASH
    output wire flash_sclk,
    output wire flash_cs,
    output wire flash_mosi,
    input wire flash_miso,

    //  dbg
    input wire SWCLK,
    inout wire SWDIO,

    // key
    input wire [ 2: 0 ] key_pin,

    //  led 0 on 1 off
    output wire [ 3: 0 ] led_pin,

    //  BEEP
    output wire beep_pin,

    //  uart
    input wire uart_DAP_rx,
    output wire uart_DAP_tx,

    input wire uart_ch340_rx,
    output wire uart_ch340_tx,

    //  sd
    output wire sd_sclk,
    output wire sd_cs,
    output wire sd_mosi,
    input wire sd_miso,

    // w5500
    input wire w5500_rstn,
    input wire w5500_intn,
    output wire w5500_sclk,
    output wire w5500_cs,
    output wire w5500_mosi,
    input wire w5500_miso,

    //数码管接口
    output wire seg7_SH_CP,   //移位时钟
    output wire seg7_ST_CP,   //数据锁存时钟
    output wire seg7_DS,      //移位串行数据

    //  iic 4 eeprom, rtc etc.
    output wire i2c_scl,
    inout wire i2c_sda,

    output wire osc_c6_pin

  );

  //  PLL EXT
  assign pll_i2c_scl = 1'bz;

  //  FLASH
  assign flash_sclk = 0;
  assign flash_cs = 1;
  assign flash_mosi = 0;

  // led
  //   assign led_core = 0;
  //   assign led_pin = 0;

  //  OSC
  assign osc_c6_pin = led_pin[ 0 ];

  //  BEEP
  //   assign beep_pin = 0;

  //  uart
  // assign uart_ch340_tx = 0;

  //  sd
  assign sd_sclk = 0;
  assign sd_cs = 1;
  assign sd_mosi = 0;


  // w5500
  assign w5500_sclk = 0;
  assign w5500_cs = 1;
  assign w5500_mosi = 0;

  //数码管接口
  //   assign seg7_SH_CP = 0;
  //   assign seg7_ST_CP = 1;
  //   assign seg7_DS = 0;

  //  iic 4 eeprom, rtc etc.
  assign i2c_scl = 1'bz;

  // sram
  assign SRAM_ADDR = 0;
  assign SRAM_nWE = 1;
  assign SRAM_nOE = 1;
  assign SRAM_nCE = 1;
  assign SRAM_nLB = 1;
  assign SRAM_nUB = 1;

  wire clk_200M;
  wire clk_100M;
  wire clk_50M;

  wire PLL1_lock;

  led_wf led_wf1( clk_25M, key_pin[ 1 ], led_pin );

  PLL_25to200 PLL_25to200_1( clk_25M, clk_200M, clk_100M, clk_50M, PLL1_lock );

  // CM3 CORE

  wire CLK_CM3 = clk_100M;

  reg CM3SYS_RSTN_buff = 0;
  reg CM3SYS_RSTN = 0;
  always@( posedge CLK_CM3)
    begin
      CM3SYS_RSTN_buff <= key_pin[ 0 ] & PLL1_lock;
      CM3SYS_RSTN <= CM3SYS_RSTN_buff;
    end

  wire [ 15: 0 ] CM3INTSIG;

  wire [ 31: 0 ] GPIO_IN = { 29'b0, uart_DAP_rx, key_pin[ 2: 1 ] } ;
  wire [ 31: 0] GPIO_OUT;
  wire [ 31: 0] GPIO_OUT_EN;

  assign led_core = GPIO_OUT[ 0 ];
  assign beep_pin = GPIO_OUT[ 1 ];
  assign uart_DAP_tx = GPIO_OUT[ 3 ];

  wire TMSOEN;
  wire TMSO;
  assign SWDIO = TMSOEN ? 1'bz : TMSO;

  //   wire AHB_CLK;

  wire [ 31: 0] TARGEXP0HADDR;
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

  wire [ 31: 0] TARGEXP1HADDR;
  wire [ 3: 0] TARGEXP1HPROT;
  wire [ 31: 0] TARGEXP1HRDATA;
  wire TARGEXP1HREADYMUX;
  wire TARGEXP1HREADYOUT ;
  wire TARGEXP1HRESP;
  wire TARGEXP1HSEL;
  wire [ 2: 0] TARGEXP1HSIZE;
  wire [ 1: 0] TARGEXP1HTRANS;
  wire [ 31: 0] TARGEXP1HWDATA;
  wire TARGEXP1HWRITE;

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
          .TARGEXP0HBURST ( ),
          .TARGEXP0HMASTLOCK ( ),
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
          .TARGEXP1HBURST ( ),
          .TARGEXP1HMASTLOCK ( ),
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

  wire uartIntSig;
  assign CM3INTSIG = { 15'b0 , uartIntSig };

  ahb_uart ahb_uart1(
             .HCLK ( CLK_CM3 ), //时钟
             .HRESETn ( CM3SYS_RSTN ), //复位

             .HSEL ( TARGEXP0HSEL ), // AHB inputs，设备选择
             .HADDR ( TARGEXP0HADDR[ 15: 0 ] ), //地址
             .HTRANS ( TARGEXP0HTRANS ), //传输控制信号
             .HSIZE ( TARGEXP0HSIZE ),  //传输大小
             .HWRITE ( TARGEXP0HWRITE ), //写控制
             .HWDATA ( TARGEXP0HWDATA ), //写数据
             .HREADY ( TARGEXP0HREADYMUX ), //传输完成

             .HREADYOUT ( TARGEXP0HREADYOUT ), // AHB Outputs，设备准备信号
             .HRDATA ( TARGEXP0HRDATA ), //读取到的数据
             .HRESP ( TARGEXP0HRESP ), //设备响应

             .INT_REQ( uartIntSig ),
             .TX_OUT( uart_ch340_tx ),
             .RX_IN( uart_ch340_rx)
           );

  ahb_seg7x8 seg_inst(
               .HCLK ( CLK_CM3 ), //时钟
               .HRESETn ( CM3SYS_RSTN ), //复位

               .HSEL ( TARGEXP1HSEL ), // AHB inputs，设备选择
               .HADDR ( TARGEXP1HADDR[ 15: 0 ] ), //地址
               .HTRANS ( TARGEXP1HTRANS ), //传输控制信号
               .HSIZE ( TARGEXP1HSIZE ),  //传输大小
               .HWRITE ( TARGEXP1HWRITE ), //写控制
               .HWDATA ( TARGEXP1HWDATA ), //写数据
               .HREADY ( TARGEXP1HREADYMUX ), //传输完成

               .HREADYOUT ( TARGEXP1HREADYOUT ), // AHB Outputs，设备准备信号
               .HRDATA ( TARGEXP1HRDATA ), //读取到的数据
               .HRESP ( TARGEXP1HRESP ), //设备响应

               .SH_CLK( seg7_SH_CP ),
               .LD_CLK( seg7_ST_CP ),
               .HC_DAT( seg7_DS)
             );

endmodule
