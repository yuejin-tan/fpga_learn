module cm3_sys (
    input wire CLK_CM3,
    input wire SYS_RSTN,
    input wire SWCLK,
    inout wire SWDIO,
    input wire [ 15: 0 ] INTSIG,
    input wire [ 31: 0 ] GPIO_IN,
    output wire [ 31: 0] GPIO_OUT,
    output wire [ 31: 0] GPIO_OUT_EN
  );

  wire TMSOEN;
  wire TMSO;
  assign SWDIO = TMSOEN ? 1'bz : TMSO;

  xsCM3 inst (
          .CIBCLK ( CLK_CM3 ),
          .DBG_SWDI_TMS ( SWDIO ),
          .DBG_SWDO ( TMSO ),
          .DBG_SWDO_EN ( TMSOEN ),
          .TDO_ENABLE (),
          .TDO_TMS (),
          .CS_TDI (),
          .CS_TCK ( SWCLK ),
          .CPURSTN ( SYS_RSTN ),
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
          .INITEXP0HADDR ( 32'b0 ),
          .INITEXP0HBURST ( 3'b0 ),
          .INITEXP0HMASTLOCK ( 1'b0 ),
          .INITEXP0HPROT ( 4'b0 ),
          .INITEXP0HRDATA (),
          .INITEXP0HREADY (),
          .INITEXP0HRESP (),
          .INITEXP0HSEL ( 1'b0 ),
          .INITEXP0HSIZE ( 3'b0 ),
          .INITEXP0HTRANS ( 2'b0 ),
          .INITEXP0HWDATA ( 32'b0 ),
          .INITEXP0HWRITE ( 1'b0 ),
          .INITEXP1HADDR ( 32'b0 ),
          .INITEXP1HBURST ( 3'b0 ),
          .INITEXP1HMASTLOCK ( 1'b0 ),
          .INITEXP1HPROT ( 4'b0 ),
          .INITEXP1HRDATA (),
          .INITEXP1HREADY (),
          .INITEXP1HRESP (),
          .INITEXP1HSEL ( 1'b0 ),
          .INITEXP1HSIZE ( 3'b0 ),
          .INITEXP1HTRANS ( 2'b0 ),
          .INITEXP1HWDATA ( 32'b0 ),
          .INITEXP1HWRITE ( 1'b0 ),
          .MTXRSTN ( SYS_RSTN ),
          .NSRST ( 1'b1 ),
          .NTRST ( 1'b1 ),
          .TARGEXP0HADDR (),
          .TARGEXP0HBURST (),
          .TARGEXP0HMASTLOCK (),
          .TARGEXP0HPROT (),
          .TARGEXP0HRDATA (),
          .TARGEXP0HREADYMUX (),
          .TARGEXP0HREADYOUT (),
          .TARGEXP0HRESP (),
          .TARGEXP0HSEL (),
          .TARGEXP0HSIZE (),
          .TARGEXP0HTRANS (),
          .TARGEXP0HWDATA (),
          .TARGEXP0HWRITE (),
          .TARGEXP1HADDR (),
          .TARGEXP1HBURST (),
          .TARGEXP1HMASTLOCK (),
          .TARGEXP1HPROT (),
          .TARGEXP1HRDATA (),
          .TARGEXP1HREADYMUX (),
          .TARGEXP1HREADYOUT (),
          .TARGEXP1HRESP (),
          .TARGEXP1HSEL (),
          .TARGEXP1HSIZE (),
          .TARGEXP1HTRANS (),
          .TARGEXP1HWDATA (),
          .TARGEXP1HWRITE (),
          .TREECLK ( CLK_CM3 )
        );

  defparam inst.PCLK_DIV = 0;
  defparam inst.CORECLK = "CLK_TREE";
  defparam inst.RSTN_ENABLE = "TRUE";
  defparam inst.MTXCLK = "CORECLK";
  defparam inst.CORECLK_EN = "TRUE";
  defparam inst.CORE_SET = "TRUE";

endmodule
