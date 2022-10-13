`timescale 1ns/1ns
module Shifter( dataA, dataB, dataOut );
input [31:0] dataA ;
input [4:0] dataB ;
output [31:0] dataOut ;

reg [31:0] temp ;


/*
=====================================================
下面為模擬範例，程式撰寫請遵照老師上課說明的方法來寫
=====================================================
*/
always @ ( dataA or dataB )
begin

	// temp = dataA << dataB ;
	temp = dataB[0] ? { dataA[30:0], 1'b0 } : dataA ;
	temp = dataB[1] ? { dataA[29:0], 2'b0 } : temp ;
	temp = dataB[2] ? { dataA[27:0], 4'b0 } : temp ;
	temp = dataB[3] ? { dataA[23:0], 8'b0 } : temp ;
	temp = dataB[4] ? { dataA[15:0], 16'b0 } : temp ;
	
/*
移位器運算
*/
end

assign dataOut = temp ;


endmodule