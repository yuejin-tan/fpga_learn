create_clock -period 40 -waveform {0 20} -name {clkbase} {clk_25M}

create_clock -period 25 -waveform {0 12.5} -name {clkPLL40} [get_nets {clk_40M} ]
