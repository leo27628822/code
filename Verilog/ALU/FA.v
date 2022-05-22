`timescale 1ns/1ns
module FA(a,b,cin,cout,sum);

  input a,b,cin;
  output cout, sum;

  assign s = a ^ b ^ cin ;
  assign cout = a & b | ( cin & ( a ^ b ) ) ;
  
endmodule  