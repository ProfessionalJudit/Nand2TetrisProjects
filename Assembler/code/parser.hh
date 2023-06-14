#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "code.hh"
#include <bitset>
class parser
{
public:
    std::ifstream asmfile;
    parser(const char *);
    ~parser();
    std::string currentCommand;
    bool hasMoreCommands();
    void advance();
    std::string comandType();
    std::string symbol();
    std::string dest();
    std::string comp();
    std::string jump();
    std::string bin = "";
};

parser::parser(const char *route)
{
    asmfile.open(route);
    std::cout << "File opened: " << route << "\n\n";
}

parser::~parser()
{
    std::cout << "\nParser Closed";
}

bool parser::hasMoreCommands()
{

    return asmfile.eof() == 0;
}

void parser::advance()
{
    if (hasMoreCommands())
    {
        // Get line
        std::getline(asmfile, currentCommand);

        // Delete whitespace
        currentCommand = std::regex_replace(currentCommand, std::regex(" "), "");  // replace 'def' -> 'klm'
        currentCommand = std::regex_replace(currentCommand, std::regex("\t"), ""); // replace 'def' -> 'klm'

        // Ignore comments and empty lines
        bool isComment = currentCommand[0] == '/';
        bool isNewline = currentCommand[0] == '\n';
        bool isSpace = currentCommand[0] == ' ';
        bool isTab = currentCommand[0] == '\t';
        bool isEmpty = currentCommand[0] == '\0';

        if (isComment || isNewline || isSpace || isTab || isEmpty)
        {
            advance();
        }
        else
        {
            // Print
            std::cout << currentCommand << "\t\t" << comandType() << "\t" << symbol()
                      << "\t" << dest() << "\t" << comp() << "\t" << jump() << "\t";

            // Parse A to binary
            if (comandType() == "A_COMMAND")
            {
                // Turn decimal symbol into binary
                int value = stoi(symbol());
                bin.append(std::bitset<16>(value).to_string());
            }
            else
                // Parse C To binary
                if (comandType() == "C_COMMAND")
                {
                    bin.append("100");
                    bin.append(code::comp(comp()));
                    bin.append(code::dest(dest()));
                    bin.append(code::jump(jump()));
                }

            bin.append("\n");
            std::cout << bin;
        }
    }
}

std::string parser::comandType()
{
    if (currentCommand[0] == '@')
    {
        return "A_COMMAND";
    }
    else if (currentCommand[0] == '(')
    {
        return "L_COMMAND";
    }
    else
    {
        return "C_COMMAND";
    }
    return "";
}

std::string parser::symbol()
{
    if (comandType() == "A_COMMAND" || comandType() == "L_COMMAND")
    {
        return currentCommand.substr(1);
    }
    return "-";
}

std::string parser::dest()
{
    if (comandType() == "C_COMMAND")
    {

        if (currentCommand.find("=") != -1)
        {
            return currentCommand.substr(0, currentCommand.find("="));
        }
    }
    return "-";
}

std::string parser::comp()
{
    if (comandType() == "C_COMMAND")
    {
        if (currentCommand.find("=") != -1)
        {
            return currentCommand.substr(currentCommand.find("=") + 1, -1);
        }
        else
        {
            return currentCommand;
        }
    }
    return "-";
}

std::string parser::jump()
{
    if (comandType() == "C_COMMAND")
    {
        if (currentCommand.find(";") != -1)
        {
            return currentCommand.substr(currentCommand.find(";") + 1, -1);
        }
    }
    return "-";
}
