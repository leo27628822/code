module DFF( q, d, clk, reset);

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

input i0, i1, i2, i3, s0, s1 ;
output o ;

wire y0, y1, y2, y3 ;

assign y0 = i0 & (~s1) & (~s0) ;
assign y1 = i1 & (~s1) & s0 ;
assign y2 = i2 & s1 & (~s0) ;
assign y3 = i3 & s1 & s0 ;

assign o = y0 | y1 | y2 | y3 ;

endmodule

module Shift_Register( i, s, o, clk, reset, r ) ;

input [7:0] i ;
input [1:0] s ;
output [7:0] o; 
input clk, reset, r ;
wire [7:0] a ;

//     MUX(   s0,   s1,   i0,   i1,   i2,   i3,    o ) ;
MUX4_1 MUX0( s[0], s[1], o[0],    r, o[1], i[0], a[0] ) ;
MUX4_1 MUX1( s[0], s[1], o[1], o[0], o[2], i[1], a[1] ) ;
MUX4_1 MUX2( s[0], s[1], o[2], o[1], o[3], i[2], a[2] ) ;
MUX4_1 MUX3( s[0], s[1], o[3], o[2], o[4], i[3], a[3] ) ;
MUX4_1 MUX4( s[0], s[1], o[4], o[3], o[5], i[4], a[4] ) ;
MUX4_1 MUX5( s[0], s[1], o[5], o[4], o[6], i[5], a[5] ) ;
MUX4_1 MUX6( s[0], s[1], o[6], o[5], o[7], i[6], a[6] ) ;
MUX4_1 MUX7( s[0], s[1], o[7], o[6],    r, i[7], a[7] ) ;

//   DFF( q, d, clk, reset )
DFF DFF0( o[0], a[0], clk, reset ) ;
DFF DFF1( o[1], a[1], clk, reset ) ;
DFF DFF2( o[2], a[2], clk, reset ) ;
DFF DFF3( o[3], a[3], clk, reset ) ;
DFF DFF4( o[4], a[4], clk, reset ) ;
DFF DFF5( o[5], a[5], clk, reset ) ;
DFF DFF6( o[6], a[6], clk, reset ) ;
DFF DFF7( o[7], a[7], clk, reset ) ;

endmodule