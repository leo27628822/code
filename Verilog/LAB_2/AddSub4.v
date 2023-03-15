module AddSub4( a, b, cin, cout, sum, sel );

input [3:0] a, b ;
input cin, sel ;
output [3:0] sum ;
output cout ;

assign {cout,sum} = ( sel == 1'b0 ? {1'b0,a} + {1'b0,b} : {1'b0,a} + ( {1'b0,~b} + 5'd1 ) ) ;

endmodule