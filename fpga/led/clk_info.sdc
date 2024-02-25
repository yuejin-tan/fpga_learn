create_clock -period 40 -waveform {0 20} -name {clk1} {clk_25M}
# create_clock -period 5 -waveform {0 2.5} -name {clk2} [get_nets {clk_200M} ]
create_clock -period 10 -waveform {0 5} -name {clk3} [get_nets {clk_100M} ]
# create_clock -period 20 -waveform {0 10} -name {clk4} [get_nets {clk_50M} ]
