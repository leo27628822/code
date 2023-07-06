`timescale 1ns/1ps

module Top (

dout,

clk_src,
rst_clk,
rst,
en, 
up,

//clk1,
//clk2,
locked

);

output	[7:0]	dout;

input	clk_src, rst_clk, rst, en, up;

//output  clk1, clk2;
output  locked;

wire    clk_40MHz, clk_80MHz;
wire    locked;


Counter  U_Counter ( 

.dout    (dout),

.clk     (clk_40MHz),
//.clk     (clk_src),
.rst     (rst),
.en      (en), 
.up      (up)

);


pll   U_pll (
	
//.areset   (~rst),
.areset   (~rst_clk),
.inclk0   (clk_src),
.c0       (clk_40MHz),
.c1       (clk_80MHz),
.locked   (locked)

);

//assign clk1=clk_40MHz;
//assign clk2=clk_80MHz;


endmodule






