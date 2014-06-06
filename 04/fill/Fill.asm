// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.


(BEGIN)

@KBD
D=M
@END1
D;JEQ

// This fills up the screen with the black pixels
@8192
D=A

@offset
M=D

@SCREEN
D=A

@2000
M=D

(LOOP)
	
	@offset
	M=M-1
	D=M
	@END
	D;JEQ

	@2000
	A=M

	M=-1
	A=A+1

	D=A

	@2000
	M=D

	@LOOP
	0;JMP
(END)
	@BEGIN
	0;JMP

//This fills up the screen with white pixels
(END1)
@8192
D=A

@offset1
M=D

@SCREEN
D=A

@2000
M=D

(LOOP1)
	
	@offset1
	M=M-1
	D=M
	@END2
	D;JEQ

	@2000
	A=M

	M=0
	A=A+1

	D=A

	@2000
	M=D

	@LOOP1
	0;JMP
(END2)

	@BEGIN
	0;JMP
