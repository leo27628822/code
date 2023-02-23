module AddSub4( a, b, cin, cout, sum, sel );

input [3:0] a, b ;
input cin, sel ;
output [3:0] sum ;
output [3:0] cout ;
wire w0, w1, w2, w3 ;

xor xor1( w0, b[0], sel ) ;
xor xor2( w1, b[1], sel ) ;
xor xor3( w2, b[2], sel ) ;
xor xor4( w3, b[3], sel ) ;

FullAdder FA1( .a(a[0]), .b(w0), .cin(sel), .cout(cout[0]), .sum(sum[0]) ) ;
FullAdder FA2( .a(a[1]), .b(w1), .cin(cout[0]), .cout(cout[1]), .sum(sum[1]) ) ;
FullAdder FA3( .a(a[2]), .b(w2), .cin(cout[1]), .cout(cout[2]), .sum(sum[2]) ) ;
FullAdder FA4( .a(a[3]), .b(w3), .cin(cout[2]), .cout(cout[3]), .sum(sum[3]) ) ;

endmodule