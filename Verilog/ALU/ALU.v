`timescale 1ns/1ns
module ALU( dataA, dataB, Signal, dataOut, reset );
input reset ;
input [31:0] dataA ;
input [31:0] dataB ;
input [5:0] Signal ;
output [31:0] dataOut ;

//   Signal ( 6-bits)?
//   AND  : 36
//   OR   : 37
//   ADD  : 32
//   SUB  : 34
//   SLT  : 42

reg [31:0] temp ;

parameter AND = 6'b100100;
parameter OR  = 6'b100101;
parameter ADD = 6'b100000;
parameter SUB = 6'b100010;
parameter SLT = 6'b101010;
/*
定義各種訊號
*/

wire [32:0] c ;
assign c[0] = 0 ;

/*
=====================================================
下面為模擬範例，程式撰寫請遵照老師上課說明的方法來寫
=====================================================
*/
always@( dataA or dataB or Signal or reset )
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
		AND:
		begin
			// temp = dataA & dataB ;
			and and1( temp, dataA, dataB ) ;
		end
		OR:
		begin
			// temp = dataA | dataB ;
			or or1( temp, dataA, dataB ) ;
		end
		ADD:
		begin
			// temp = dataA + dataB ;

			genvar i ;
			for ( i = 0 ; i < 32 ; i = i + 1 )
			begin
				FA uFA1( .a(dataA[i]), .b(dataB[i], .cin(c[i]), .cout(c[i+1]), .sum( temp[i]) ) ;
			end
		end
		SUB:
		begin
			// temp = dataA - dataB ;
			assign dataB = ~dataB ;
			assign c[0] = 1 ;

			genvar i ;
			for ( i = 0 ; i < 32 ; i = i + 1 )
			begin 
				FA uFA2( .a(dataA[i]), .b(dataB[i], .cin(c[i]), .cout(c[i+1]), .sum( temp[i]) ) ;
		end
		SLT:
		begin
			/*
			if ( dataA < dataB )
				temp = 1 ;
			else
				temp = 0 ;
			*/

			assign temp = ( dataA < dataB )? 1 : 0 ;
		end
		default: temp = 32'b0 ;	
	
		endcase
	end
/*
上面這個case是在做訊號處理
分別根據傳進來的signal來做不同的運算
然後放進暫存器
*/
end
assign dataOut = temp ;
/*
=====================================================
上面為模擬範例，程式撰寫請遵照老師上課說明的方法來寫
=====================================================
*/

endmodule