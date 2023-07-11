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
void testParse(parser &parser)
{
    // INIT
    // Init stack
    /*
    @256
    D=A
    @SP
    M=D
    */
    std::cout << "@256" << std::endl;
    std::cout << "D=A" << std::endl;
    std::cout << "@SP" << std::endl;
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