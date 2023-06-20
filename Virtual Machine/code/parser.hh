#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

class parser
{
public:
    // File
    std::ifstream sourcefile;
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
    // Get command type
    std::string arg1();
    int arg2();
};

parser::parser(const char *route)
{
    // Open file
    sourcefile.open(route);
}

parser::~parser()
{
}

bool parser::hasMoreCommands()
{
    // Get if we are at the end of file
    return sourcefile.eof() == 0;
}

void parser::advance()
{
    // If not eof
    if (hasMoreCommands())
    {
        // Get line
        std::getline(sourcefile, currentCommand);
        // Delete whitespace
        // currentCommand = std::regex_replace(currentCommand, std::regex(" "), "");  //
        // currentCommand = std::regex_replace(currentCommand, std::regex("\t"), ""); //

        // Ignore comments and empty lines
        bool isComment = currentCommand[0] == '/';
        bool isNewline = currentCommand[0] == '\n';
        bool isSpace = currentCommand[0] == ' ';
        bool isTab = currentCommand[0] == '\t';
        bool isEmpty = currentCommand[0] == '\0';

        // delete comments
        if (currentCommand.find("//") != -1)
        {
            currentCommand = currentCommand.substr(0, currentCommand.find("//"));
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
    std::string arithmetic[] =
        {"add", "sub", "neg", "eq", "gt", "lt", "and", "or", "not"};
    // Exsists in array, arithmetic
    bool existsInMath = std::find(std::begin(arithmetic), std::end(arithmetic), currentCommand) != std::end(arithmetic);
    if (existsInMath)
    {
        return "C_ARITHMETIC";
    }
    // If push
    else if (currentCommand.substr(0, currentCommand.find(" ")) == "push")
    {
        return "C_PUSH";
    }
    // If pop
    else if (currentCommand.substr(0, currentCommand.find(" ")) == "pop")
    {
        return "C_POP";
    }
    return "";
}
std::string parser::arg1()
{
    if (comandType() == "C_ARITHMETIC")
    {
        return currentCommand;
    }
    else if (comandType() == "C_PUSH" ||
             comandType() == "C_POP")
    {
        std::string segment;
        segment = currentCommand.substr(currentCommand.find(" "));
        segment = segment.substr(0, segment.find(" "));
        return segment;
    }
}
int parser::arg2()
{
    if (comandType() == "C_ARITHMETIC")
    {
        return -1;
    }
    else if (comandType() == "C_PUSH" ||
             comandType() == "C_POP")
    {
        std::string segment;
        segment = currentCommand.substr(currentCommand.find(" ")+1);
        segment = segment.substr(segment.find(" "));
        return std::stoi(segment);
    }
}