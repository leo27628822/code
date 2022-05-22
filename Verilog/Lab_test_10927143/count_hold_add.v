`timescale 1ns/1ns
module counter_hold_add( sel, dout, rst, clk, a, b ) ;

  output dout ;
  input rst, clk ;
  input[1:0] sel ;
  input[2:0] a, b ;
  reg[3:0] dout ;

  always @( posedge clk )
  begin
    if ( rst == 0 )
      dout <= 0 ;
    else if ( sel == 2'b00 )
      dout <= dout + 1 ;
	  else if ( sel == 2'b10 )
		  dout <= a + b ;	
  end 

endmodule