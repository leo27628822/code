module Sub_1bit ( X,Y,Z,B,D) ;

input X,Y,Z ;
output B,D ;

begin 
	assign D = ( ~X&~Y&Z ) | ( ~X&Y&~Z ) | ( X&~Y&~Z ) | ( X&Y&Z ) ;
	assign B = ( ~X&Y ) | ( ~X&Z ) | ( Y&Z ) ;
end
endmodule



module Subtractor( X, Y, Z, D, B) ;


input[3:0] X, Y ;
input Z ;
output[3:0] B, D ;

begin
	
	/*
	assign D = X ^ Y ^ Bi ;
	assign Bo = ( ~X&Y ) | ( ~X&Bi ) | ( Y&Bi ) ;
	*/
	
	Sub_1bit sub1( X[0], Y[0], Z, B[0], D[0]) ;
	Sub_1bit sub2( X[1], Y[1], B[0], B[1], D[1]) ;
	Sub_1bit sub3( X[2], Y[2], B[1], B[2], D[2]) ;
	Sub_1bit sub4( X[3], Y[3], B[2], B[3], D[3]) ;
	

end

endmodule







