module Stimulate() ;

reg[3:0] A,B ;

wire A_gt_B, A_eq_B, A_lt_B ;

Comparator cmp( A, B, A_gt_B, A_eq_B, A_lt_B );

initial
begin

// design your test case here
	A = 4'd0 ;
	B = 4'd0 ;
	#10 A = 4'd1  ; B = 4'd15 ;
	#10 A = 4'd2  ; B = 4'd14 ;
	#10 A = 4'd3  ; B = 4'd13 ;
	#10 A = 4'd4  ; B = 4'd12 ;
	#10 A = 4'd5  ; B = 4'd11 ;
	#10 A = 4'd6  ; B = 4'd10 ;
	#10 A = 4'd7  ; B = 4'd9  ;
	#10 A = 4'd8  ; B = 4'd8  ;
	#10 A = 4'd9  ; B = 4'd7  ;
	#10 A = 4'd10 ; B = 4'd6  ;
	#10 A = 4'd11 ; B = 4'd5  ;
	#10 A = 4'd12 ; B = 4'd4  ;
	#10 A = 4'd13 ; B = 4'd3  ;
	#10 A = 4'd14 ; B = 4'd2  ;
	#10 A = 4'd15 ; B = 4'd1  ;
	#10 A = 4'd0  ; B = 4'd0  ;
	#10 $stop ;
	
end

endmodule