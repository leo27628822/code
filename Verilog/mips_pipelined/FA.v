`timescale 1ns/1ns
module FA(a,b,c,cout,sum);

  input a,b,c;
  output cout, sum;

  assign sum = a ^ b ^ c ;
  assign cout = a & b | ( c & ( a ^ b ) ) ;
  
endmodule  

