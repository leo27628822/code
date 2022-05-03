`timescale 1ns/1ns
module counter_sel( sel, dout, rst, clk, a, b ) ;

  output dout;
  input sel, rst, clk ;
  input [3:0] a, b ;
  reg[3:0] dout ;

  always @( posedge clk )
  begin
 
    if ( rst == 0 )
    	dout <= 0 ;
    else
	if ( sel == 0 ) 
	  dout <= a & b ;
	else
	  dout <= dout + 1 ;
  end 

endmodule