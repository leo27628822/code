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

wire [31:0] temp, tempB ;

parameter AND = 6'b100100;
parameter OR  = 6'b100101;
parameter ADD = 6'b100000;
parameter SUB = 6'b100010;
parameter SLT = 6'b101010;

// wire [32:0] c ;
wire c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23, c24, c25, c26, c27, c28, c29, c30, c31, c32 ;

assign c0 = ( Signal == SUB )? 1 : 0 ;
ALU1b uA1( dataA[0], dataB[0], Signal, temp[0], reset, c0, c1 ) ; 
ALU1b uA2( dataA[1], dataB[1], Signal, temp[1], reset, c1, c2 ) ; 
ALU1b uA3( dataA[2], dataB[2], Signal, temp[2], reset, c2, c3 ) ; 
ALU1b uA4( dataA[3], dataB[3], Signal, temp[3], reset, c3, c4 ) ; 
ALU1b uA5( dataA[4], dataB[4], Signal, temp[4], reset, c4, c5 ) ; 
ALU1b uA6( dataA[5], dataB[5], Signal, temp[5], reset, c5, c6 ) ; 
ALU1b uA7( dataA[6], dataB[6], Signal, temp[6], reset, c6, c7 ) ; 
ALU1b uA8( dataA[7], dataB[7], Signal, temp[7], reset, c7, c8 ) ;
ALU1b uA9( dataA[8], dataB[8], Signal, temp[8], reset, c8, c9 ) ; 
ALU1b uA10( dataA[9], dataB[9], Signal, temp[9], reset, c9, c10 ) ; 
ALU1b uA11( dataA[10], dataB[10], Signal, temp[10], reset, c10, c11 ) ; 
ALU1b uA12( dataA[11], dataB[11], Signal, temp[11], reset, c11, c12 ) ; 
ALU1b uA13( dataA[12], dataB[12], Signal, temp[12], reset, c12, c13 ) ; 
ALU1b uA14( dataA[13], dataB[13], Signal, temp[13], reset, c13, c14 ) ;
ALU1b uA15( dataA[14], dataB[14], Signal, temp[14], reset, c14, c15 ) ; 
ALU1b uA16( dataA[15], dataB[15], Signal, temp[15], reset, c15, c16 ) ; 
ALU1b uA17( dataA[16], dataB[16], Signal, temp[16], reset, c16, c17 ) ; 
ALU1b uA18( dataA[17], dataB[17], Signal, temp[17], reset, c17, c18 ) ; 
ALU1b uA19( dataA[18], dataB[18], Signal, temp[18], reset, c18, c19 ) ; 
ALU1b uA20( dataA[19], dataB[19], Signal, temp[19], reset, c19, c20 ) ;
ALU1b uA21( dataA[20], dataB[20], Signal, temp[20], reset, c20, c21 ) ; 
ALU1b uA22( dataA[21], dataB[21], Signal, temp[21], reset, c21, c22 ) ; 
ALU1b uA23( dataA[22], dataB[22], Signal, temp[22], reset, c22, c23 ) ; 
ALU1b uA24( dataA[23], dataB[23], Signal, temp[23], reset, c23, c24 ) ; 
ALU1b uA25( dataA[24], dataB[24], Signal, temp[24], reset, c24, c25 ) ; 
ALU1b uA26( dataA[25], dataB[25], Signal, temp[25], reset, c25, c26 ) ; 
ALU1b uA27( dataA[26], dataB[26], Signal, temp[26], reset, c26, c27 ) ; 
ALU1b uA28( dataA[27], dataB[27], Signal, temp[27], reset, c27, c28 ) ; 
ALU1b uA29( dataA[28], dataB[28], Signal, temp[28], reset, c28, c29 ) ; 
ALU1b uA30( dataA[29], dataB[29], Signal, temp[29], reset, c29, c30 ) ; 
ALU1b uA31( dataA[30], dataB[30], Signal, temp[30], reset, c30, c31 ) ; 
ALU1b uA32( dataA[31], dataB[31], Signal, temp[31], reset, c31, c32 ) ; 

assign dataOut = ( Signal == SLT )? ( ( dataA < dataB )? 1 : 0 ) : temp[31:0] ;

endmodule