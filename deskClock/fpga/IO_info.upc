#-------CLK---------
phycst.pin.set {clk_25M} H13
phycst.pin.set {clk_27M} N2
phycst.pin.set {clk_p3} N9
phycst.pin.set {clk_p4} N11
phycst.pin.set {clk_p5} P10

#-------调试接口---------
phycst.pin.set {SWDIO} C1
phycst.pin.set {SWCLK} H1

#-------按键---------
phycst.pin.set {key_pin[0]} D5
phycst.pin.set {key_pin[1]} E5
phycst.pin.set {key_pin[2]} F5

#-------LED---------
phycst.pin.set {led_core} B6

phycst.pin.set {led_pin[3]} E14
phycst.pin.set {led_pin[2]} F14
phycst.pin.set {led_pin[1]} G15
phycst.pin.set {led_pin[0]} D15

#-------BEEP---------
phycst.pin.set {beep_pin} E13

#-------SRAM---------
phycst.pin.set {SRAM_ADDR[0]} L11 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[1]} M13 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[2]} N15 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[3]} N14 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[4]} M12 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[5]} N5 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[6]} M4 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[7]} L5 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[8]} N3 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[9]} M3 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[10]} R2 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[11]} R3 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[12]} P3 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[13]} R4 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[14]} P4 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[15]} P14 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[16]} R15 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[17]} P15 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_ADDR[18]} R5 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[0]} M11 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[1]} M10 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[2]} L10 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[3]} L9 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[4]} N8 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[5]} N7 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[6]} L7 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[7]} N6 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[8]} P5 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[9]} P6 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[10]} R7 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[11]} P7 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[12]} R8 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[13]} P8 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[14]} R9 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_DQ[15]} P9 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_nLB} R13 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_nUB} P13 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_nWE} L6 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_nOE} R14 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {SRAM_nCE} N12 -attr "PULLMODE=NONE SLEWRATE=FAST"

#-------uart---------
phycst.pin.set {uart_ch340_rx} C15 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {uart_ch340_tx} E12 -attr "PULLMODE=NONE SLEWRATE=FAST"

phycst.pin.set {uart_DAP_rx} K2 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {uart_DAP_tx} L2 -attr "PULLMODE=NONE SLEWRATE=FAST"


#---------SPI SD-----------
phycst.pin.set {sd_sclk} E11
phycst.pin.set {sd_cs} D11
phycst.pin.set {sd_mosi} D12
phycst.pin.set {sd_miso} F11

#--------SPI FLASH----------
phycst.pin.set {flash_sclk} A1
phycst.pin.set {flash_cs} A8
phycst.pin.set {flash_mosi} G2
phycst.pin.set {flash_miso} G1

#--------SPI w5500-----------
phycst.pin.set {w5500_sclk} L15
phycst.pin.set {w5500_cs} K9
phycst.pin.set {w5500_mosi} M15
phycst.pin.set {w5500_miso} L14
phycst.pin.set {w5500_rstn} M14
phycst.pin.set {w5500_intn} K12

#----IIC pll-----------
phycst.pin.set {pll_i2c_scl} E3
phycst.pin.set {pll_i2c_sda} D3

#----iic eeprom-----------
phycst.pin.set {i2c_scl} K14
phycst.pin.set {i2c_sda} J11

#----------------数码管接口-----------------
#-------------数码管移位时钟-----------------
phycst.pin.set {seg7_SH_CP} E4
#-------------数码管数据锁存时钟-------------
phycst.pin.set {seg7_ST_CP} G6
#-------------移位串行数据------------------
phycst.pin.set {seg7_DS} H2

#-------------LCD------------------
phycst.pin.set {CS_8080} L12 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {RS_8080} L13 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {WR_8080} P12 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {RD_8080} K11 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[0]} R12 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[1]} K6 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[2]} P11 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[3]} N10 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[4]} R11 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[5]} J6 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[6]} K5 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[7]} J5 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[8]} K3 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[9]} F6 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[10]} J4 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[11]} E7 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[12]} E6 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[13]} G10 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[14]} H3 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {DATA_8080[15]} G3 -attr "PULLMODE=NONE SLEWRATE=FAST"

phycst.pin.set {LCD_BL} G5 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {LCD_RST} K10 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {LCDT_RST} J2 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {LCDT_PEN} J3 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {LCDT_SCL} J1 -attr "PULLMODE=NONE SLEWRATE=FAST"
phycst.pin.set {LCDT_SDA} N1 -attr "PULLMODE=NONE SLEWRATE=FAST"
