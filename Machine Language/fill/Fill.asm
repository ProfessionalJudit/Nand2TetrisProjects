// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
//Num o pixel registers 8192
(INIT)
@8192 //Start from the bottom left
D=A //Dregister = num of pixel groups
@I  //Index var
M=D //Index = D = 8192


(NOTPRESSED)
@SCREEN //Screen poiter
D=A     //D reg = 0x4000
@I
A=D+M 
M=0  //.. = 1111111111111111
@I
M=M-1 

@KBD
D=M
@INIT2
D;JNE
@NOTPRESSED
0;JMP

(INIT2)
@8192 //Start from the bottom left
D=A //Dregister = num of pixel groups
@I  //Index var
M=D //Index = D = 8192

(PRESSED)
@SCREEN //Screen poiter
D=A     //D reg = 0x4000
@I
A=D+M //Adress pointer "0x4000 + index" ..  0x4000 is the screen address, is stored in the d register
//                                          Index is stored in M
M=-1  //.. = 1111111111111111
@I
M=M-1 
D=M

@KBD
D=M
@INIT
D;JEQ
@PRESSED
D;JNE

(END)
@END
0;JMP