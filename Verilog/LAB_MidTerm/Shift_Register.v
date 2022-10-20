module DFF(q, d, clk, reset);

output q; 
input d, clk, reset;
reg q;

always @(posedge reset or negedge clk)
if (reset)
		q = 1'b0;
else
		q = d;

endmodule

module MUX4_1( s0, s1, i0, i1, i2, i3, o ) ;

endmodule

module Shift_Register( i, s, o, clk, reset, r ) ;

output [7:0] q; 
input clk, reset;

/*
DFF D0( q[0], 1'b1, clk, reset ) ;
DFF D1( q[1], q[0], clk, reset ) ;
DFF D2( q[2], q[1], clk, reset ) ;
DFF D3( q[3], q[2], clk, reset ) ;
DFF D4( q[4], q[3], clk, reset ) ;
DFF D5( q[5], q[4], clk, reset ) ;
DFF D6( q[6], q[5], clk, reset ) ;
DFF D7( q[7], q[6], clk, reset ) ;
*/

endmodule