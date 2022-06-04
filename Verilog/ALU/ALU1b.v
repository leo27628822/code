`timescale 1ns/1ns
module ALU1b( dataA, dataB, Signal, dataOut, reset, cin, cout );
input reset ;
input dataA, dataB, cin ;
input [5:0] Signal ;
output dataOut, cout ;

//   Signal ( 6-bits)?
//   AND  : 36
//   OR   : 37
//   ADD  : 32
//   SUB  : 34
//   SLT  : 42

wire temp, tempB ;

parameter AND = 6'b100100;
parameter OR  = 6'b100101;
parameter ADD = 6'b100000;
parameter SUB = 6'b100010;
parameter SLT = 6'b101010;

// tempB = ( Signal == SUB )? ~dataB : dataB ;

// FA uFA( .a(dataA), .b(dataB), .cin(cin), .cout(cout), .sum(dataOut) ) ;
assign cout = ( Signal == ADD )? ( ( dataA & dataB ) | ( cin & ( dataA ^ dataB ) ) ) : ( Signal == SUB )? ( dataA & (~dataB) | ( cin & ( dataA ^ (~dataB) ) ) ) : 1'b0 ;
assign dataOut = ( Signal == ADD )? ( dataA ^ dataB ^ cin ) : ( Signal == SUB )? ( dataA ^ (~dataB) ^ cin ) : ( Signal == AND )? (dataA & dataB) : ( Signal == OR )? (dataA | dataB) : (reset)? 1'b0 : dataOut ;

endmodule