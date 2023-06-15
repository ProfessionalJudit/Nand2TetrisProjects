#include "parser.hh"
#include "SymbolTable.hh"
#include <fstream>
#include <bitset>
#include <regex>
#include <ctype.h>

// Parse without symbols
void symbollessParse(parser &input);
void fisrtParse(parser &input, SymbolTable &st);
void secondParse(parser &input, SymbolTable &st);

int main(int argc, char const *argv[])
{
    // Open file
    parser *input;
    SymbolTable *symbolTable = new SymbolTable();
    if (argc > 1)
    {
        input = new parser(argv[1]);
        // symbollessParse(*input);
        fisrtParse(*input, *symbolTable);
        secondParse(*input, *symbolTable);
    }
    else
    {
        std::cout << "Error, no file;";
        return 1;
    }
    // Init Symbol table

    return 0;
}

// Parse without symbols
void symbollessParse(parser &input)
{
    // Open output file with pointer at the start
    std::ofstream output("./output.hack");

    // Iterate through file
    while (input.hasMoreCommands())
    {
        // Current line
        std::string line;
        // Next line
        input.advance();
        // Get command type
        if (input.comandType() == "C_COMMAND")
        {
            // Parse C instruction
            line.append("111");
            line.append(code::comp(input.comp()));
            line.append(code::dest(input.dest()));
            line.append(code::jump(input.jump()));
        }
        else if (input.comandType() == "A_COMMAND")
        {
            // Parse A instruction
            int value = stoi(input.symbol());
            line.append(std::bitset<16>(value).to_string());
        }
        // Input line into output file
        output << line << std::endl;
    }
    // Close file
    output.close();
}

void fisrtParse(parser &input, SymbolTable &st)
{
    int address = 0;
    while (input.hasMoreCommands())
    {
        input.advance();
        // std::cout << input.currentCommand << "\t\t " << input.symbol() << std::endl;
        if (input.comandType() == "A_COMMAND" || input.comandType() == "C_COMMAND")
        {
            address++;
        }
        //Add Labels on the st
        if (input.comandType() == "L_COMMAND")
        {
            st.addEntry(input.symbol(), address);
        }
    }
    //Add predefined symbols
    std::string registers[16] =
        {
            "R0",
            "R1",
            "R2",
            "R3",
            "R4",
            "R5",
            "R6",
            "R7",
            "R8",
            "R9",
            "R10",
            "R11",
            "R12",
            "R13",
            "R14",
            "R15",
        };
    for (size_t i = 0; i < 16; i++)
    {
        st.addEntry(registers[i], i);
    }
    st.addEntry("SP", 0);
    st.addEntry("LCL", 1);
    st.addEntry("ARG", 2);
    st.addEntry("THIS", 3);
    st.addEntry("THAT", 4);
    st.addEntry("SCREEN", 16384);
    st.addEntry("KBD", 24576);
}

void secondParse(parser &input, SymbolTable &st)
{
    //Reset file pointer
    input.asmfile.clear();
    input.asmfile.seekg(0);

    //Abaliable var addresses, starting at 0xF
    int nextAvaliable = 16;
    while (input.hasMoreCommands())
    {
        input.advance();
        //Parse A instruction
        if (input.comandType() == "A_COMMAND")
        {
            bool is_var = false;
            for (size_t i = 0; i < input.symbol().length(); i++)
            {
                if (isalpha(input.symbol()[i]))
                {
                    is_var = true;
                };
            }
            //If it's not in the table, and it's a var, append it to the table
            if (!st.contains(input.symbol()) && is_var)
            {
                st.addEntry(input.symbol(), nextAvaliable);
                nextAvaliable++;
            }
        }
    }

    //Clear file pointer again
    input.asmfile.clear();
    input.asmfile.seekg(0);

    // Open output file with pointer at the start
    std::ofstream output("./output.hack");

    // Iterate through file
    while (input.hasMoreCommands())
    {
        // Current line
        std::string line;
        // Next line
        input.advance();
        // Get command type
        if (input.comandType() == "C_COMMAND")
        {
            // Parse C instruction
            line.append("111");
            line.append(code::comp(input.comp()));
            line.append(code::dest(input.dest()));
            line.append(code::jump(input.jump()));
            output << line << std::endl;
        }
        else if (input.comandType() == "A_COMMAND")
        {
            //Parse A
            //If it's a var, translate the name into an address
            if (st.contains(input.symbol()))
            {
                int value = std::stoi(st.GetAddress(input.symbol()));
                line.append(std::bitset<16>(value).to_string());
                output << line << std::endl;
            }
            else
            {
                // Else, parse A the "old way"
                int value = stoi(input.symbol());
                line.append(std::bitset<16>(value).to_string());
                output << line << std::endl;
            }
        }
        // Input line into output file
    }
    // Close file
    output.close();
    
}