module Counter( dout, clk, rst, en, up ) ;

parameter WIDTH = 8 ;

input clk, rst, en, up ;
output reg[WIDTH-1:0] dout ;

always@( posedge clk or negedge rst )begin
	
	if ( rst == 1'b0 ) begin
		dout <= 8'd0 ;
	end		
	else begin
		case( {en,up} )
			2'b11: if ( dout != 8'hff ) dout <= dout + 1 ;
			2'b10: if ( dout != 8'd0 ) dout <= dout - 1 ;
			default: dout <= dout ;
		endcase
	end
end
endmodule