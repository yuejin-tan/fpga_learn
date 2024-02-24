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
    output [ 18: 0 ] SRAM_ADDR,
    inout [ 15: 0 ] SRAM_DQ,
    output SRAM_nWE,
    output SRAM_nOE,
    output SRAM_nCE,
    output SRAM_nLB,
    output SRAM_nUB,

    //  FLASH
    output wire flash_sclk,
    output wire flash_cs,
    output wire flash_mosi,
    input wire flash_miso,

    //  dbg
    input wire swdclk,
    inout wire swddio,

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

  // sram
  assign SRAM_ADDR = 0;
  assign SRAM_nWE = 1;
  assign SRAM_nOE = 1;
  assign SRAM_nCE = 1;
  assign SRAM_nLB = 1;
  assign SRAM_nUB = 1;

  //  FLASH
  assign flash_sclk = 0;
  assign flash_cs = 1;
  assign flash_mosi = 0;

  // led
  //   assign led_core = 0;
  //   assign led_pin[ 3: 2 ] = 0;

  //  OSC
  assign osc_c6_pin = led_pin[ 0 ];

  //  BEEP
  //   assign beep_pin = 0;

  //  uart
  assign uart_ch340_tx = 0;

  //  sd
  assign sd_sclk = 0;
  assign sd_cs = 1;
  assign sd_mosi = 0;


  // w5500
  assign w5500_sclk = 0;
  assign w5500_cs = 1;
  assign w5500_mosi = 0;

  //数码管接口
  assign seg7_SH_CP = 0;
  assign seg7_ST_CP = 1;
  assign seg7_DS = 0;

  //  iic 4 eeprom, rtc etc.
  assign i2c_scl = 1'bz;

  // core
  wire fake1;
  wire [ 27: 0 ] fake28;
  wire [ 31: 0 ] fake32;

  wire clk_200M;
  wire PLL1_lock;

  wire cm3rstn;

  assign cm3rstn = key_pin[ 0 ] & PLL1_lock;

  led_wf led_wf1( clk_25M, key_pin[ 1 ], led_pin );

  cm3_sys cm3inst (
            .CLK_CM3( clk_200M ),
            .SYS_RSTN( key_pin[ 0 ] ),
            .SWCLK( swdclk ),
            .SWDIO( swddio ),
            .INTSIG( 16'b0 ),
            .GPIO_IN( { 29'b0, uart_DAP_rx, 2'b0} ),
            .GPIO_OUT( { fake28, uart_DAP_tx, fake1, beep_pin, led_core } ),
            .GPIO_OUT_EN( fake32 )
          );

  PLL_25to200 PLL_25to200_1( clk_25M, clk_200M, PLL1_lock );

endmodule
