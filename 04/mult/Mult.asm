// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[3], respectively.)

// Put your code here.

@R2
M=0


@R0
D=M
@END
D;JEQ


@R1
D=M
@END
D;JEQ


(LOOP)

	@R0
	D=M

	@R2
	M=M+D //R2= R2+R0

	@R1   //Refer to R1
	M=M-1 // R1=R1-1
	D=M    
	@END
	D;JEQ // If R1 becomes 0 , jump to end

	@LOOP
	0;JMP
(END)
	@END
	0;JMP