#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "code.hh"
class parser
{
public:
    // File
    std::ifstream asmfile;
    // Constructor
    parser(const char *);
    ~parser();
    // Current command
    std::string currentCommand;
    // End of file
    bool hasMoreCommands();
    // Go to next command
    void advance();
    // Get command type
    std::string comandType();
    // Get symbol
    std::string symbol();
    // Get destination, what to compute and where to go in a C instuction
    std::string dest();
    std::string comp();
    std::string jump();
};

parser::parser(const char *route)
{
    // Open file
    asmfile.open(route);
}

parser::~parser()
{
}

bool parser::hasMoreCommands()
{
    // Get if we are at the end of file
    return asmfile.eof() == 0;
}

void parser::advance()
{
    // If not eof
    if (hasMoreCommands())
    {
        // Get line
        std::getline(asmfile, currentCommand);
        // Delete whitespace
        currentCommand = std::regex_replace(currentCommand, std::regex(" "), "");  //
        currentCommand = std::regex_replace(currentCommand, std::regex("\t"), ""); //

        // Ignore comments and empty lines
        bool isComment = currentCommand[0] == '/';
        bool isNewline = currentCommand[0] == '\n';
        bool isSpace = currentCommand[0] == ' ';
        bool isTab = currentCommand[0] == '\t';
        bool isEmpty = currentCommand[0] == '\0';
        
        //delete comments
        if (currentCommand.find("//") != -1)
        {
            currentCommand = currentCommand.substr(0,currentCommand.find("//"));
        }
        
        
        // If its empty, next line
        if (isComment || isNewline || isSpace || isTab || isEmpty)
        {
            advance();
        }
        
        
    }
}

std::string parser::comandType()
{
    // Get if its an A instuction
    if (currentCommand[0] == '@')
    {
        return "A_COMMAND";
    }
    // Get if its a Label
    else if (currentCommand[0] == '(')
    {
        return "L_COMMAND";
    }
    else
    {
        // If the line is empty there is no command, so we return an empty string
        bool isComment = currentCommand[0] == '/';
        bool isNewline = currentCommand[0] == '\n';
        bool isSpace = currentCommand[0] == ' ';
        bool isTab = currentCommand[0] == '\t';
        bool isEmpty = currentCommand[0] == '\0';
        if (isComment || isNewline || isSpace || isTab || isEmpty)
        {
            return "";
        }
        else
        {
            // Else, its a C instruction
            return "C_COMMAND";
        }
    }
    return "";
}

std::string parser::symbol()
{
    // If its not C, return the symbol
    if (comandType() == "A_COMMAND")
    {
        return currentCommand.substr(1);
    }
    if (comandType() == "L_COMMAND")
    {
        return currentCommand.substr(1,currentCommand.length()-2);
    }

    return "";
}

std::string parser::dest()
{
    // Get destination
    if (comandType() == "C_COMMAND")
    {

        if (currentCommand.find("=") != -1)
        {
            return currentCommand.substr(0, currentCommand.find("="));
        }
    }
    return "";
}

std::string parser::comp()
{
    if (comandType() == "C_COMMAND")
    {
        // Get compute, ignores computes with no destination or jump
        if (currentCommand.find("=") != -1)
        {
            return currentCommand.substr(currentCommand.find("=") + 1, -1);
        }
        else if (currentCommand.find(";") != -1)
        {
            return currentCommand.substr(currentCommand.find(";") - 1, 1);
        }
    }
    return "";
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
    return "";
}
