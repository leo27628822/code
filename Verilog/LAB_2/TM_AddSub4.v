module TM_AddSub4() ;

reg [3:0] a, b ;
reg cin, sel ;

wire [3:0] sum ;
wire cout ;

AddSub4 AddSub4( .a(a), .b(b), .cin(cin), .cout(cout), .sum(sum), .sel(sel) ) ;

initial begin
  
  a = 4'd5 ;
  b = 4'd1 ;
  cin = 1'd0 ;
  sel = 0 ;
  
  #10 
  sel = 1 ;
  
  #10
  a = 4'd0 ;
  b = 4'd0 ;
  sel = 0 ;
  
  #10
  sel = 1 ;
  
  #10
  a = 4'd2 ;
  b = 4'd2 ;
  sel = 0 ;

  #10
  sel = 1 ;
  
  #10
  a = 4'd1 ;
  b = 4'd5 ;
  sel = 0 ;
  
  #10
  sel = 1 ;
  
  #10
  $stop ;
end

endmodule