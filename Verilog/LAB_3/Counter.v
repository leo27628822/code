module Counter( dout, clk, rst, en, up ) ;

parameter WIDTH = 8 ;

input clk, rst, en, up ;
output reg[WIDTH-1:0] dout ;

always@( posedge clk )begin
	if ( rst == 0 )begin
		dout <= 8'd0 ;
	end	
	else if ( en == 1 )begin
		if ( up == 1 )begin
			if ( dout != 8'hff ) dout <= dout + 1 ;
		end
		else begin
			if ( dout != 8'd0 ) dout <= dout - 1 ;
		end
	end
end

endmodule