module stimulus;
  
reg clk,reset;
// wire [3:0]count;
wire [7:0]count;

ripple_carry_counter c(count, clk, reset);

initial clk = 1'b0;
always #5 clk = ~clk;


initial
begin


 reset = 1'b1;

 #5 reset = 1'b0;
 #20 reset = 1'b1;
 #5 reset = 1'b0;

 
end

// Monitor the outputs 
initial
	$monitor($time, " Output count = %d",  count);



endmodule