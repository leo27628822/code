module Simulate() ;

reg[3:0] X, Y ;
reg Z ;
wire[3:0] B, D ;

Subtractor sub( X, Y, Z, D, B ) ;

initial
begin

// design your test case here
	X = 4'd0 ; Y = 4'd0 ; Z = 1'd0 ;
	#50 X = 4'd7 ; Y = 4'd6 ;
	#50 X = 4'd4 ; Y = 4'd3 ;
	#50 X = 4'd3 ; Y = 4'd6 ;
	#50 X = 4'd13; Y = 4'd5 ;
	#50 $stop ;
	
end

endmodule