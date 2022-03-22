`timescale 1ns/1ns
module HA(a,b,cout,sum);

  input a,b;
  output cout, sum;

  assign sum = a^b;
  assign cout = a&b;
  
endmodule  