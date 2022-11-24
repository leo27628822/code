module updown_counter( clk, reset, control, count ) ;

input clk, reset, control ;
output [7:0] count ;
reg ctrl ;
reg [7:0] count ;

always @(posedge clk )
begin
	ctrl <= control ;
end

always @( negedge clk or posedge reset)
begin
	if ( reset ) count <= 0 ;
	else if ( control ) count <= count + 1 ;
	else count <= count - 1 ;
end

endmodule