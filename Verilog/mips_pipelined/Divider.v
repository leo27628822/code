`timescale 1ns/1ns
module Divider( clk, dataA, dataB, dataOut, Divu, reset );
input clk ;
input reset ;
input Divu;
input [31:0] dataA ;
input [31:0] dataB ;
output [63:0] dataOut ;

//   Signal ( 6-bits)?
//   DIVU  : 27

reg [63:0] temp ;
parameter DIVU = 6'b011011;
parameter OUT = 6'b111111;
/*
�w�q�U�ذT��
*/
/*
=====================================================
�U���������d�ҡA�{�����g�п�ӦѮv�W�һ�������k�Ӽg
=====================================================
*/
always@( posedge clk or reset )
begin
        if ( reset )
        begin
                temp = 32'b0 ;
        end
/*
reset�T�� �p�G�Oreset�N���k0
*/
        else
        begin
		if ( Divu )
		begin
			temp = dataA ;
			temp = temp << 1 ;
			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] - dataB ;

			if ( temp >= 0 )
			begin
				temp = temp << 1 ;
				temp[0] = 1 ;
			end
			else
			begin
				temp[63:32] = temp[63:32] + dataB ;
				temp = temp << 1 ;
			end

			temp[63:32] = temp[63:32] >> 1 ;
			// assign temp[63:32] = {1'b0, temp[63:33] } ;
		end
  		

        end
/*
���k�B��
OUT�������O�n��control���A���O�A�~����⵪�׿�X��HILO�Ȧs��
*/

end
assign dataOut = temp ;

/*
=====================================================
�W���������d�ҡA�{�����g�п�ӦѮv�W�һ�������k�Ӽg
=====================================================
*/
endmodule