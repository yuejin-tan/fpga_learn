create_clock -period 40 -waveform {0 20} -name {clkbase} {clk_25M}
# create_clock -period 5 -waveform {0 2.5} -name {clkPLL1} [get_nets {clk_200M} ]
# create_clock -period 10 -waveform {0 5} -name {clkPLL2} [get_nets {clk_100M} ]
# create_clock -period 20 -waveform {0 10} -name {clkPLL3} [get_nets {clk_50M} ]

# create_clock -period 10 -waveform {0 5} -name {clkCM3} [get_nets {CLK_CM3} ]
# create_clock -period 5 -waveform {0 2.5} -name {clkCM3} [get_nets {CLK_CM3} ]
