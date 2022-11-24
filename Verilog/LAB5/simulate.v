module simulate() ;

reg clk, reset, control ;
wire [7:0] count ;

updown_counter upc(  clk, reset, control, count ) ;

initial clk = 0 ;
always #5 clk = ~clk ;

initial 
begin
	reset = 1 ; control = 0 ;
	#5 reset = 0 ; control = 1 ;
	#100 reset = 1 ;
	
	 
	#5 reset = 0 ; control = 0 ;
	#100 ;
	
end
endmodule