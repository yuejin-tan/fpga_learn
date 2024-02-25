module cm3_sys (
    input wire CLK_CM3,
    input wire SYS_RSTN,
    input wire SWCLK,
    inout wire SWDIO,
    input wire [ 15: 0 ] INTSIG,
    input wire [ 31: 0 ] GPIO_IN,
    output wire [ 31: 0] GPIO_OUT,
    output wire [ 31: 0] GPIO_OUT_EN,

    //外部静态存储器SRAM端口
    output wire [ 18: 0 ] SRAM_ADDR,
    inout wire [ 15: 0 ] SRAM_DQ,
    output wire SRAM_nWE,
    output wire SRAM_nOE,
    output wire SRAM_nCE,
    output wire SRAM_nLB,
    output wire SRAM_nUB
  );

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
  wire [ 31: 0] TARGEXP1HRDATA = 0;
  wire TARGEXP1HREADYMUX;
  wire TARGEXP1HREADYOUT = 1;
  wire TARGEXP1HRESP = 0;
  wire TARGEXP1HSEL;
  wire [ 2: 0] TARGEXP1HSIZE;
  wire [ 1: 0] TARGEXP1HTRANS;
  wire [ 31: 0] TARGEXP1HWDATA;
  wire TARGEXP1HWRITE;

  xsCM3 inst (
          .CIBCLK ( CLK_CM3 ),
          .TREECLK ( CLK_CM3 ),
          //  .MTX_CLK ( AHB_CLK ), //AHB CLK
          .MTXRSTN ( SYS_RSTN ),
          .NSRST ( 1'b1 ),
          .NTRST ( 1'b1 ),
          .CPURSTN ( SYS_RSTN ),

          .DBG_SWDI_TMS ( SWDIO ),
          .DBG_SWDO ( TMSO ),
          .DBG_SWDO_EN ( TMSOEN ),
          .TDO_ENABLE (),
          .TDO_TMS (),
          .CS_TDI (),
          .CS_TCK ( SWCLK ),

          .EXTINT ( INTSIG ),
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

  ahb_sram ahb_sram1(
             .HCLK ( CLK_CM3 ), //时钟
             .HRESETn ( SYS_RSTN ), //复位

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

endmodule
