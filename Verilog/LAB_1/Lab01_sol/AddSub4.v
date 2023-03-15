`timescale 1ns/1ns


module AddSub4 (a, b, sel, s, cout);

   
    input 	[3:0]	a, b;
    input		 	sel;
    output	[3:0]	s;
    output			cout;
       
    wire	[3:0]	bx;
	wire    [2:0]   c;
    
    xor (bx[0], b[0], sel);
    xor (bx[1], b[1], sel);
    xor (bx[2], b[2], sel);
    xor (bx[3], b[3], sel);
    
    FA		tfa0(.a(a[0]), .b(bx[0]), .c(sel ), .cout(c[0]), .sum(s[0]));
    FA		tfa1(.a(a[1]), .b(bx[1]), .c(c[0]), .cout(c[1]), .sum(s[1]));
    FA		tfa2(.a(a[2]), .b(bx[2]), .c(c[1]), .cout(c[2]), .sum(s[2]));
    FA		tfa3(.a(a[3]), .b(bx[3]), .c(c[2]), .cout(cout), .sum(s[3]));

endmodule

