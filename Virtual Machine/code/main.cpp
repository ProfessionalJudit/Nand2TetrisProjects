#include "parser.hh"
#include "code.hh"
#include <stack>
#include <string>

void testParse(parser &);
int main(int argc, char const *argv[])
{
    // Open file
    // argv[1] = source
    // std::vector<std::string> commands;
    // std::vector<std::string> args1;
    // std::vector<int> args2;

    parser *input;
    if (argc > 1)
    {
        input = new parser(argv[1]);
    }
    else
    {
        std::cout << "Error, no file;";
        return 1;
    }
    // Test parse
    testParse(*input);
    return 0;
}
/*
    THIS DOES NOT PRINT INTO A FILE
    Since it will be finished into the next chapter it outputs the result into the terminal
    It makes testing more confy for some reaseon :3
*/
void testParse(parser &parser)
{
    // INIT
    // Init stack
    /*
    Global stack at:        256
    Local segment at:       500
    Argument segment at:    700
    This segment at:        3000
    That segment at:        3010
    Temp at:                ---
    */
    // SP
    std::cout << "@256" << std::endl;
    std::cout << "D=A" << std::endl;
    std::cout << "@SP" << std::endl;
    std::cout << "M=D" << std::endl;
    // LCL
    std::cout << "@500" << std::endl;
    std::cout << "D=A" << std::endl;
    std::cout << "@LCL" << std::endl;
    std::cout << "M=D" << std::endl;
    // ARG
    std::cout << "@700" << std::endl;
    std::cout << "D=A" << std::endl;
    std::cout << "@ARG" << std::endl;
    std::cout << "M=D" << std::endl;
    // THIS
    std::cout << "@3000" << std::endl;
    std::cout << "D=A" << std::endl;
    std::cout << "@THIS" << std::endl;
    std::cout << "M=D" << std::endl;
    // THAT
    std::cout << "@3010" << std::endl;
    std::cout << "D=A" << std::endl;
    std::cout << "@THAT" << std::endl;
    std::cout << "M=D" << std::endl;
    int counter = 0;

    while (parser.hasMoreCommands())
    {
        parser.advance();
        // PUSH
        if (parser.comandType() == "C_PUSH")
        {
            // Constant
            if (parser.arg1() == "constant")
            {
                std::cout << "@" << parser.arg2() << std::endl; // Get Value
                std::cout << "D=A" << std::endl;                // Save value into D

                std::cout << "@SP" << std::endl;   // Select Stack Pointer
                std::cout << "A=M" << std::endl;   // Save stored address into A regsiter
                std::cout << "M=D" << std::endl;   // Save Value
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M+1" << std::endl; // Increase Stack Pointer
            }
            // Local segment
            else if (parser.arg1() == "local")
            {
                // Get selected element from segment
                // To do this we add LCL and the index into R13
                // Then we can get the element from the generated address and store it into the stack

                // Set R13 to index
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add LCL to R13
                std::cout << "@LCL" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=M+D" << std::endl;

                // Get element from R13 Address, save it into D
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;

                // Push element into the global stack
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "M=D" << std::endl;

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M+1" << std::endl;
            }
            // Argument segment
            else if (parser.arg1() == "argument")
            {
                // Get selected element from segment
                // To do this we add ARG and the index into R13
                // Then we can get the element from the generated address and store it into the stack

                // Set R13 to index
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add ARG to R13
                std::cout << "@ARG" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=M+D" << std::endl;

                // Get element from R13 Address, save it into D
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;

                // Push element into the global stack
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "M=D" << std::endl;

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M+1" << std::endl;
            }
            // This segment
            else if (parser.arg1() == "this")
            {
                // Get selected element from segment
                // To do this we add THIS and the index into R13
                // Then we can get the element from the generated address and store it into the stack

                // Set R13 to index
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add THIS to R13
                std::cout << "@THIS" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=M+D" << std::endl;

                // Get element from R13 Address, save it into D
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;

                // Push element into the global stack
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "M=D" << std::endl;

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M+1" << std::endl;
            }
            // That segment
            else if (parser.arg1() == "that")
            {
                // Get selected element from segment
                // To do this we add THAT and the index into R13
                // Then we can get the element from the generated address and store it into the stack

                // Set R13 to index
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add THAT to R13
                std::cout << "@THAT" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=M+D" << std::endl;

                // Get element from R13 Address, save it into D
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;

                // Push element into the global stack
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "M=D" << std::endl;

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M+1" << std::endl;
            }
            // Temp segment
            else if (parser.arg1() == "temp")
            {
                // Get selected element from segment
                // To do this we add R5 and the index into R13
                // Then we can get the element from the generated address and store it into the stack

                // Set R13 to index
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add Temp to R13
                std::cout << "@5" << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=M+D" << std::endl;

                // Get element from R13 Address, save it into D
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;

                // Push element into the global stack
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "M=D" << std::endl;

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M+1" << std::endl;
            }
            // Pointer segment
            else if (parser.arg1() == "pointer")
            {
                // Get selected element from segment
                // To do this we add R3 and the index into R13
                // Then we can get the element from the generated address and store it into the stack

                // Set R13 to index
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add Pointer to R13
                std::cout << "@3" << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=M+D" << std::endl;

                // Get element from R13 Address, save it into D
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;

                // Push element into the global stack
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "M=D" << std::endl;

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M+1" << std::endl;
            }
            // Static segment
            else if (parser.arg1() == "static")
            {
                // Get selected element from segment
                // To do this we add R16 and the index into R13
                // Then we can get the element from the generated address and store it into the stack

                // Set R13 to index
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add Static to R13
                std::cout << "@16" << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=M+D" << std::endl;

                // Get element from R13 Address, save it into D
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;

                // Push element into the global stack
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "M=D" << std::endl;

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M+1" << std::endl;
            }
        }
        // POP
        if (parser.comandType() == "C_POP")
        {
            // Local segment
            if (parser.arg1() == "local")
            {
                // R13 Will contain the value to pop into the segement
                // R14 Will contain the segment index, then we'll add LCL to it to get the correct address

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M-1" << std::endl;

                // Get value from the global stack, store it into R13
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Get LCL segment index, store it into R14
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add LCL To R14 to get the correct address
                std::cout << "@LCL" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=M+D" << std::endl; // Now R14 is pointing to LCL + Index

                // Get value from R13, and store it into the address marked at R14
                std::cout << "@R13" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "A=M" << std::endl; // Pointing to Segment + index
                std::cout << "M=D" << std::endl;
            }
            // Argument segment
            else if (parser.arg1() == "argument")
            {
                // R13 Will contain the value to pop into the segement
                // R14 Will contain the segment index, then we'll add ARG to it to get the correct address

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M-1" << std::endl;

                // Get value from the global stack, store it into R13
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Get ARG segment index, store it into R14
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add ARG To R14 to get the correct address
                std::cout << "@ARG" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=M+D" << std::endl; // Now R14 is pointing to ARG + Index

                // Get value from R13, and store it into the address marked at R14
                std::cout << "@R13" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "A=M" << std::endl; // Pointing to Segment + index
                std::cout << "M=D" << std::endl;
            }
            // This segment
            else if (parser.arg1() == "this")
            {
                // R13 Will contain the value to pop into the segement
                // R14 Will contain the segment index, then we'll add THIS to it to get the correct address

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M-1" << std::endl;

                // Get value from the global stack, store it into R13
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Get THIS segment index, store it into R14
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add THIS To R14 to get the correct address
                std::cout << "@THIS" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=M+D" << std::endl; // Now R14 is pointing to THIS + Index

                // Get value from R13, and store it into the address marked at R14
                std::cout << "@R13" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "A=M" << std::endl; // Pointing to Segment + index
                std::cout << "M=D" << std::endl;
            }
            // That segment
            else if (parser.arg1() == "that")
            {
                // R13 Will contain the value to pop into the segement
                // R14 Will contain the segment index, then we'll add THAT to it to get the correct address

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M-1" << std::endl;

                // Get value from the global stack, store it into R13
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Get THAT segment index, store it into R14
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add THAT To R14 to get the correct address
                std::cout << "@THAT" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=M+D" << std::endl; // Now R14 is pointing to that + Index

                // Get value from R13, and store it into the address marked at R14
                std::cout << "@R13" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "A=M" << std::endl; // Pointing to Segment + index
                std::cout << "M=D" << std::endl;
            }
            // Temp segment
            else if (parser.arg1() == "temp")
            {
                // R13 Will contain the value to pop into the segement
                // R14 Will contain the segment index, then we'll add Temp to it to get the correct address

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M-1" << std::endl;

                // Get value from the global stack, store it into R13
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Get Temp segment index, store it into R14
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add Temp To R14 to get the correct address
                std::cout << "@5" << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=M+D" << std::endl; // Now R14 is pointing to Temp + Index

                // Get value from R13, and store it into the address marked at R14
                std::cout << "@R13" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "A=M" << std::endl; // Pointing to Segment + index
                std::cout << "M=D" << std::endl;
            }
            // Pointer segment
            else if (parser.arg1() == "pointer")
            {
                // R13 Will contain the value to pop into the segement
                // R14 Will contain the segment index, then we'll add Pointer to it to get the correct address

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M-1" << std::endl;

                // Get value from the global stack, store it into R13
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Get Pointer segment index, store it into R14
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add Pointer To R14 to get the correct address
                std::cout << "@3" << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=M+D" << std::endl; // Now R14 is pointing to Pointer + Index

                // Get value from R13, and store it into the address marked at R14
                std::cout << "@R13" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "A=M" << std::endl; // Pointing to Segment + index
                std::cout << "M=D" << std::endl;
            }
            // Static segment
            else if (parser.arg1() == "static")
            {
                // R13 Will contain the value to pop into the segement
                // R14 Will contain the segment index, then we'll add Static to it to get the correct address

                // Decrement SP
                std::cout << "@SP" << std::endl;
                std::cout << "M=M-1" << std::endl;

                // Get value from the global stack, store it into R13
                std::cout << "@SP" << std::endl;
                std::cout << "A=M" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R13" << std::endl;
                std::cout << "M=D" << std::endl;

                // Get Static segment index, store it into R14
                std::cout << "@" << parser.arg2() << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=D" << std::endl;

                // Add Static To R14 to get the correct address
                std::cout << "@16" << std::endl;
                std::cout << "D=A" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "M=M+D" << std::endl; // Now R14 is pointing to Static + Index

                // Get value from R13, and store it into the address marked at R14
                std::cout << "@R13" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "@R14" << std::endl;
                std::cout << "A=M" << std::endl; // Pointing to Segment + index
                std::cout << "M=D" << std::endl;
            }
        }
        // ARITHMETIC
        if (parser.comandType() == "C_ARITHMETIC")
        {
            // ADD
            if (parser.arg1() == "add")
            {
                // Select and Save topmost element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R13" << std::endl; // Select R13
                std::cout << "M=D" << std::endl;  // Save value into R13

                // Do it again to save topmost -1 element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R14" << std::endl; // Select R14
                std::cout << "M=D" << std::endl;  // Save value into R14
                std::cout << "D=M" << std::endl;  // Save value into D

                // Add stored numbers and store the result into the stack
                std::cout << "@R13" << std::endl;  // Select R13
                std::cout << "M=M+D" << std::endl; // Add D(R14) to R13
                std::cout << "D=M" << std::endl;   // Store value into D
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "A=M" << std::endl;   // Get value from SP address, and load it into A
                std::cout << "M=D" << std::endl;   // Store the result

                // Increase Stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M+1" << std::endl; // Increase Stack Pointer
            }
            // SUB
            else if (parser.arg1() == "sub")
            {
                // Select and Save topmost element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R13" << std::endl; // Select R13
                std::cout << "M=D" << std::endl;  // Save value into R13

                // Do it again to save topmost -1 element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R14" << std::endl; // Select R14
                std::cout << "M=D" << std::endl;  // Save value into R14
                std::cout << "D=M" << std::endl;  // Save value into D

                // Sub stored numbers and store the result into the stack
                std::cout << "@R15" << std::endl; // Select R15
                std::cout << "M=D" << std::endl;  // R15 = D(R14)
                std::cout << "@R13" << std::endl; // Select R13
                std::cout << "D=M" << std::endl;
                std::cout << "@R15" << std::endl; // Select R15
                std::cout << "M=M-D" << std::endl;
                std::cout << "D=M" << std::endl;
                std::cout << "D=M" << std::endl; // Store value into D
                std::cout << "@SP" << std::endl; // Select SP
                std::cout << "A=M" << std::endl; // Get value from SP address, and load it into A
                std::cout << "M=D" << std::endl; // Store the result

                // Increase Stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M+1" << std::endl; // Increase Stack Pointer
            }
            // NEG
            else if (parser.arg1() == "neg")
            {
                // Select and Save topmost element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R13" << std::endl; // Select R13
                std::cout << "M=D" << std::endl;  // Save value into R13

                // Neg stored number and store the result into the stack
                std::cout << "@R13" << std::endl;  // Select R13
                std::cout << "D=M" << std::endl;   // Store value into D
                std::cout << "M=M-D" << std::endl; // Store value into D
                std::cout << "M=M-D" << std::endl; // Store value into D
                std::cout << "D=M" << std::endl;   // Store value into D
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "A=M" << std::endl;   // Get value from SP address, and load it into A
                std::cout << "M=D" << std::endl;   // Store the result

                // Increase Stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M+1" << std::endl; // Increase Stack Pointer
            }
            // EQ
            else if (parser.arg1() == "eq")
            {
                // Select and Save topmost element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R13" << std::endl; // Select R13
                std::cout << "M=D" << std::endl;  // Save value into R13

                // Do it again to save topmost -1 element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R14" << std::endl; // Select R14
                std::cout << "M=D" << std::endl;  // Save value into R14
                std::cout << "D=M" << std::endl;  // Save value into D

                // Compare stored numbers and store the result into the stack
                // True = 0xFFFF
                // False = 0x0000
                std::cout << "@R13" << std::endl;  // Select R13
                std::cout << "M=M-D" << std::endl; // Sub D(R14) to R13
                std::cout << "D=M" << std::endl;   // Store value into D

                // Compare and Jump
                std::cout << "@TRUE" << counter << std::endl;
                std::cout << "D;JEQ" << std::endl;
                std::cout << "@FALSE" << counter << std::endl;
                std::cout << "0;JMP" << std::endl;

                std::cout << "(TRUE" << counter << ")" << std::endl;
                std::cout << "@SP" << std::endl; // Select Topmost stack element +1
                std::cout << "A=M" << std::endl;
                std::cout << "M=-1" << std::endl;
                std::cout << "@ENDIF" << counter << std::endl;
                std::cout << "0;JMP" << std::endl;

                std::cout << "(FALSE" << counter << ")" << std::endl;
                std::cout << "@SP" << std::endl; // Select Topmost stack element +1
                std::cout << "A=M" << std::endl;
                std::cout << "M=0" << std::endl;

                std::cout << "(ENDIF" << counter << ")" << std::endl;
                // Increase Stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M+1" << std::endl; // Increase Stack Pointer
            }
            // GT
            else if (parser.arg1() == "lt")
            {
                // Select and Save topmost element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R13" << std::endl; // Select R13
                std::cout << "M=D" << std::endl;  // Save value into R13

                // Do it again to save topmost -1 element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R14" << std::endl; // Select R14
                std::cout << "M=D" << std::endl;  // Save value into R14
                std::cout << "D=M" << std::endl;  // Save value into D

                // Compare stored numbers and store the result into the stack
                // True = 0xFFFF
                // False = 0x0000
                std::cout << "@R13" << std::endl;  // Select R13
                std::cout << "M=M-D" << std::endl; // Sub D(R14) to R13
                std::cout << "D=M" << std::endl;   // Store value into D

                // Compare and Jump
                std::cout << "@TRUE" << counter << std::endl;
                std::cout << "D;JGT" << std::endl;
                std::cout << "@FALSE" << counter << std::endl;
                std::cout << "0;JMP" << std::endl;

                std::cout << "(TRUE" << counter << ")" << std::endl;
                std::cout << "@SP" << std::endl; // Select Topmost stack element +1
                std::cout << "A=M" << std::endl;
                std::cout << "M=-1" << std::endl;
                std::cout << "@ENDIF" << counter << std::endl;
                std::cout << "0;JMP" << std::endl;

                std::cout << "(FALSE" << counter << ")" << std::endl;
                std::cout << "@SP" << std::endl; // Select Topmost stack element +1
                std::cout << "A=M" << std::endl;
                std::cout << "M=0" << std::endl;

                std::cout << "(ENDIF" << counter << ")" << std::endl;
                // Increase Stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M+1" << std::endl; // Increase Stack Pointer
            }
            // LT
            else if (parser.arg1() == "gt")
            {
                // Select and Save topmost element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R13" << std::endl; // Select R13
                std::cout << "M=D" << std::endl;  // Save value into R13

                // Do it again to save topmost -1 element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R14" << std::endl; // Select R14
                std::cout << "M=D" << std::endl;  // Save value into R14
                std::cout << "D=M" << std::endl;  // Save value into D

                // Compare stored numbers and store the result into the stack
                // True = 0xFFFF
                // False = 0x0000
                std::cout << "@R13" << std::endl;  // Select R13
                std::cout << "M=M-D" << std::endl; // Sub D(R14) to R13
                std::cout << "D=M" << std::endl;   // Store value into D

                // Compare and Jump
                std::cout << "@TRUE" << counter << std::endl;
                std::cout << "D;JLT" << std::endl;
                std::cout << "@FALSE" << counter << std::endl;
                std::cout << "0;JMP" << std::endl;

                std::cout << "(TRUE" << counter << ")" << std::endl;
                std::cout << "@SP" << std::endl; // Select Topmost stack element +1
                std::cout << "A=M" << std::endl;
                std::cout << "M=-1" << std::endl;
                std::cout << "@ENDIF" << counter << std::endl;
                std::cout << "0;JMP" << std::endl;

                std::cout << "(FALSE" << counter << ")" << std::endl;
                std::cout << "@SP" << std::endl; // Select Topmost stack element +1
                std::cout << "A=M" << std::endl;
                std::cout << "M=0" << std::endl;

                std::cout << "(ENDIF" << counter << ")" << std::endl;
                // Increase Stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M+1" << std::endl; // Increase Stack Pointer
            }
            // AND
            else if (parser.arg1() == "and")
            {
                // Select and Save topmost element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R13" << std::endl; // Select R13
                std::cout << "M=D" << std::endl;  // Save value into R13

                // Do it again to save topmost -1 element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R14" << std::endl; // Select R14
                std::cout << "M=D" << std::endl;  // Save value into R14
                std::cout << "D=M" << std::endl;  // Save value into D

                // And elements
                std::cout << "@R13" << std::endl;  // Select R13
                std::cout << "M=M&D" << std::endl; // And elements
                std::cout << "D=M" << std::endl;

                std::cout << "@SP" << std::endl; // Select Stack and store value
                std::cout << "A=M" << std::endl;
                std::cout << "M=D" << std::endl;

                // Increase Stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M+1" << std::endl; // Increase Stack Pointer
            }
            // OR
            else if (parser.arg1() == "or")
            {
                // Select and Save topmost element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R13" << std::endl; // Select R13
                std::cout << "M=D" << std::endl;  // Save value into R13

                // Do it again to save topmost -1 element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R14" << std::endl; // Select R14
                std::cout << "M=D" << std::endl;  // Save value into R14
                std::cout << "D=M" << std::endl;  // Save value into D

                // And elements
                std::cout << "@R13" << std::endl;  // Select R13
                std::cout << "M=M|D" << std::endl; // And elements
                std::cout << "D=M" << std::endl;

                std::cout << "@SP" << std::endl; // Select Stack and store value
                std::cout << "A=M" << std::endl;
                std::cout << "M=D" << std::endl;

                // Increase Stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M+1" << std::endl; // Increase Stack Pointer
            }
            // NOT
            else if (parser.arg1() == "not")
            {
                // Select and Save topmost element, decrease stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M-1" << std::endl; // Decrease value From SP

                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "D=M" << std::endl;  // Store value from SP address into D
                std::cout << "@R13" << std::endl; // Select R13
                std::cout << "M=D" << std::endl;  // Save value into R13

                // Neg stored number and store the result into the stack
                std::cout << "@R13" << std::endl; // Select R13
                std::cout << "M=!M" << std::endl; // Add D(R14) to R13
                std::cout << "D=M" << std::endl;  // Store value into D
                std::cout << "@SP" << std::endl;  // Select SP
                std::cout << "A=M" << std::endl;  // Get value from SP address, and load it into A
                std::cout << "M=D" << std::endl;  // Store the result

                // Increase Stack pointer
                std::cout << "@SP" << std::endl;   // Select SP
                std::cout << "M=M+1" << std::endl; // Increase Stack Pointer
            }
        }
        counter++;
    }
}