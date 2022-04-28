module TM_counter_4bit ;

reg		sel, clk, rst ;
wire[3:0]	dout;

parameter	t = 200 ;
parameter	th = 100 ;

counter_4bit	U_cnt( .dout(dout), .rst(rst), .clk(clk) ) ;

always #th clk = ~clk ;

initial
 begin
	rst = 1 ;
	sel = 1 ;
	clk = 0 ;

	#t rst = 0 ;
	#t rst = 1 ;
	#t ;
	#t ;
	#t ;
	#t ;
	#t ;
	#t ;
	#t ;
	#t ;
	#t ;
	#t ;
	#t ;
	#t ;
 	#t ;
 	#t ;
  
	#t 	$stop ;

 end
endmodule