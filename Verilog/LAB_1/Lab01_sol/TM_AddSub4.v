`timescale 1ns/1ns

module TM_AddSub4;

reg		[3:0] a, b;
reg			  sel;
wire	[3:0] s;
wire	cout;

AddSub4	U_AddSub4 (.a(a), .b(b), .sel(sel), .s(s), .cout(cout));

parameter	t = 200;
 // Enter fixture code here
 initial 
 begin
	#(2*t)
 	// 5+1
	a = 4'd5;
      	b = 4'd1;
      	sel = 1'b0;
	
	#t 	
      	// 5-1
	a = 4'd5;
      	b = 4'd1;
      	sel = 1'b1;

	#t 	
      	// 0+0
	a = 4'd0;
      	b = 4'd0;
      	sel = 1'b0;

	#t 	
      	// 0-0
	a = 4'd0;
      	b = 4'd0;
      	sel = 1'b1;

	#t 	
      	// 2+2
	a = 4'd2;
      	b = 4'd2;
      	sel = 1'b0;

	#t 	
      	// 2-2
	a = 4'd2;
      	b = 4'd2;
      	sel = 1'b1;

	#t 	
      	// 1+5
	a = 4'd1;
      	b = 4'd5;
      	sel = 1'b0;

	#t 	
      	// 1-5
	a = 4'd1;
      	b = 4'd5;
      	sel = 1'b1;
	#t
      $stop;
 end
 

endmodule




