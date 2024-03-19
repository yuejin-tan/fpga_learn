set WORK_DIR D:/fpga/ac208/workspace/fpga/led
set vfiles {}
lappend vfiles $WORK_DIR/cm3_sys.v
lappend vfiles $WORK_DIR/top.v
lappend vfiles $WORK_DIR/ipcore_dir/PLL_25to200/xsIP_PLL_25to200.v
lappend vfiles $WORK_DIR/led_wf.v
lappend vfiles $WORK_DIR/ahb_sram.v

dv.setup -synlib_only SEAL
rtl.analyze $vfiles
rtl.elaborate -top top -vio $WORK_DIR/vio/
exit
