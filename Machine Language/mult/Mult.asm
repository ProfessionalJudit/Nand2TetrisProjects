// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.
// D = dest, I = iterations
@R0
M=0
@R1
M=0
@R2
M=0
@I
M=0
A=0
D=0
//Get iterations
@R1
D=M
@I
M=D

(MULT)
    @R0
    D=M
    @R2
    M=M+D
    
    @I
    D=M

    D=D-1
    @I
    M=D
    @MULT
    D;JGT
 
(END)
    @END
    0;JMP