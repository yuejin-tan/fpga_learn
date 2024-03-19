module AHBlite_Decoder
  #(
     /*RAMCODE enable parameter*/
     parameter Port0_en = 1,
     /************************/

     /*RAMDATA  enable parameter*/
     parameter Port1_en = 1,
     /************************/

     /*PERIPHRAL enable parameter*/
     parameter Port2_en = 1,
     /************************/

     /*PERIPHRAL enable parameter*/
     parameter Port3_en = 1
     /************************/
   )(
     input [31: 0] HADDR,

     /*RAMCODE OUTPUT SELECTION SIGNAL*/
     output wire P0_HSEL,

     /*RAMDATA OUTPUT SELECTION SIGNAL*/
     output wire P1_HSEL,

     /*PERIPHRAL OUTPUT SELECTION SIGNAL*/
     output wire P2_HSEL,

     /*PERIPHRAL OUTPUT SELECTION SIGNAL*/
     output wire P3_HSEL
   );

  //RAMCODE-----------------------------
  //0x00000000-0x0000ffff
  assign P0_HSEL = (HADDR[31: 16] == 16'h0000) ? Port0_en : 1'd0;
  /***********************************/

  //RAMDATA-----------------------------
  //0X20000000-0X2000FFFF
  assign P1_HSEL = (HADDR[31: 16] == 16'h2000) ? Port1_en : 1'd0;
  /***********************************/

  //PERIPHRAL-----------------------------
  assign P2_HSEL = (HADDR[31: 16] == 16'h4000) ? Port2_en : 1'd0;
  /***********************************/

  //PERIPHRAL-----------------------------
  assign P3_HSEL = (HADDR[31: 16] == 16'h4001) ? Port3_en : 1'd0;
  /***********************************/


endmodule
