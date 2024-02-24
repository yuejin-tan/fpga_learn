create_clock -period 40 -waveform {0 20} -name {clk1} {clk_25M}
create_clock -period 5 -waveform {0 2.5} -name {clk2} [get_nets {clk_200M} ]
