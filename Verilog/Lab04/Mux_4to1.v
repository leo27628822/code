`timescale 1ns/1ns
module Mux_4to1( in0, in1, in2, in3, out, sel ) ;

	output	out ;
	input	in3,in2,in1,in0;
	input	[1:0] sel;

	wire	out;

	assign	out = ( sel == 2'b00 ) ? in0 : ( sel == 2'b01 ) ? in1 : ( sel == 2'b10 ) ? in2 : in3 ;

endmodule