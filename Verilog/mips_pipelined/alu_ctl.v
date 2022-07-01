/*
	Title:	ALU Control Unit
	Author: Garfield (Computer System and Architecture Lab, ICE, CYCU)
	Input Port
		1. ALUOp: 控制alu是要用+還是-或是其他指令
		2. Funct: 如果是其他指令則用這邊6碼判斷
	Output Port
		1. ALUOperation: 最後解碼完成之指令
*/
`timescale 1ns/1ns
module alu_ctl(ALUOp, Funct, ALUOperation, Divu, sel);
    input [1:0] ALUOp;
    input [5:0] Funct;
    output Divu;
    output [1:0] sel;
    output [2:0] ALUOperation;
    reg    Divu;
    reg    [1:0] sel;
    reg    [2:0] ALUOperation;

    // symbolic constants for instruction function code
    parameter F_add = 6'd32;
    parameter F_sub = 6'd34;
    parameter F_and = 6'd36;
    parameter F_or  = 6'd37;
    parameter F_slt = 6'd42;
    parameter F_sll = 6'd0;
    parameter F_div = 6'd27;
    parameter F_mfhi = 6'd10;
    parameter F_mflo = 6'd12;

    // symbolic constants for ALU Operations
    parameter ALU_add = 3'b010;
    parameter ALU_sub = 3'b110;
    parameter ALU_and = 3'b000;
    parameter ALU_or  = 3'b001;
    parameter ALU_slt = 3'b111;
	
    parameter ALU_sll = 3'b011; 
    parameter ALU_div = 3'b100; 

	
    always @(ALUOp or Funct)
    begin
	Divu = 1'b0;
	sel = 2'b0;
        case (ALUOp) 
            2'b00 : ALUOperation = ALU_add;
            2'b01 : ALUOperation = ALU_sub;
            2'b10 : case (Funct) 
                        F_add : ALUOperation = ALU_add;
                        F_sub : ALUOperation = ALU_sub;
                        F_and : ALUOperation = ALU_and;
                        F_or  : ALUOperation = ALU_or;
                        F_slt : ALUOperation = ALU_slt;
			F_sll : ALUOperation = ALU_sll;
			F_div : Divu = 1'b1;
			F_mfhi : sel = 2'b01;
			F_mflo : sel = 2'b10;
                        default ALUOperation = 3'bxxx;
                    endcase
            default ALUOperation = 3'bxxx;
        endcase
    end
endmodule

