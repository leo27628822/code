// module DFF with synchronous reset
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

module TFF(q, clk, reset);

output q; 
input clk, reset;
wire d;

DFF dff0(q, d, clk, reset); 
not n1(d, q); // not is a Verilog provided primitive.

endmodule

module ripple_carry_counter(q, clk, reset);

// output [3:0] q; 
output [7:0] q;
input clk, reset; 

//4 instances of the module TFF are created. 
TFF tff0(q[0],clk, reset);
TFF tff1(q[1],q[0], reset);
TFF tff2(q[2],q[1], reset);
TFF tff3(q[3],q[2], reset);
TFF tff4(q[4],q[3], reset);
TFF tff5(q[5],q[4], reset);
TFF tff6(q[6],q[5], reset);
TFF tff7(q[7],q[6], reset);

endmodule




