`timescale 1ns/1ns
module counter_4bit( dout, rst, clk ) ;

  output dout ;

  reg[3:0] dout ;
  input rst, clk ;


  always @( posedge clk )
  begin
 
    if ( rst == 0 )
    	dout <= 0 ;
    else 
	dout <= dout + 1 ;
  end 

endmodule