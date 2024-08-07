module led_wf
  #(
     parameter CLK_DIV = 20 * 1000 * 1000 - 1,
     parameter LED_NUM = 4,
     parameter INIT_STA = 4'b1100
   )
   (
     input clk,
     input rst,
     output reg [ LED_NUM - 1: 0] led_sig = INIT_STA
   );

  reg [ $clog2(CLK_DIV): 0] cnt = 0;

  always @( posedge clk or negedge rst)
    begin
      if ( !rst)
        begin
          cnt <= 0;
          led_sig <= INIT_STA;
        end
      else
        begin
          if ( cnt == CLK_DIV)
            begin
              cnt <= 0;
              led_sig <= { led_sig[ 0 ], led_sig[ LED_NUM - 1: 1 ] };
            end
          else
            begin
              cnt <= cnt + 1;
            end
        end

    end

endmodule
