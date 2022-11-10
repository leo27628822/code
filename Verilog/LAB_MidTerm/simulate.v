module simulate ;

reg [7:0] i ;
reg [1:0] s ;
reg r, clk, reset ;
wire [7:0] o ;

Shift_Register shifter_register( i, s, o, clk, reset, r ) ;

initial clk = 1'b0 ;
always #5 clk = ~clk ;

initial
begin

	reset = 1'b1 ; i = 8'd0 ; s = 2'd0 ; r = 1'b0 ;
	
	#5  reset = 1'b0 ;
	#5  i = 8'b10100101 ; s = 2'b11 ; //並行載入I, output = 10100101
 
	#10 s = 2'b00 ;  //不變, output = 10100101
 
	#10 s = 2'b01 ;  //左移, output = 01001010
 
	#10 s = 2'b10 ; r = 1'b1 ; //右移且串列輸入設定為1 , output = 10100101
	
end
endmodule
