`timescale 1ns/1ns
module Shifter( dataA, dataB, Signal, dataOut, reset );
input reset ;
input [31:0] dataA ;
input [31:0] dataB ;
input [5:0] Signal ;
output [31:0] dataOut ;

reg [31:0] temp ;

parameter SLL = 6'b000000;

/*
=====================================================
下面為模擬範例，程式撰寫請遵照老師上課說明的方法來寫
=====================================================
*/
always@( Signal or dataA or dataB or reset )
begin
	if ( reset )
	begin
		temp = 32'b0 ;
	end
/*
reset訊號 如果是reset就做歸0
*/
	else
	begin
		case ( Signal )
		SLL:
		begin
			// temp = dataA << dataB ;

			temp = dataB[0] ? { dataA[30:0], 1'b0 } : dataA ;
			temp = dataB[1] ? { dataA[29:0], 2'b0 } : temp ;
			temp = dataB[2] ? { dataA[27:0], 4'b0 } : temp ;
			temp = dataB[3] ? { dataA[23:0], 8'b0 } : temp ;
			temp = dataB[4] ? { dataA[15:0], 16'b0 } : temp ;
 
		end
		default: temp = 32'b0 ;	
	
		endcase
	end
/*
移位器運算
*/
end
assign dataOut = temp ;
/*
=====================================================
上面為模擬範例，程式撰寫請遵照老師上課說明的方法來寫
=====================================================
*/

endmodule