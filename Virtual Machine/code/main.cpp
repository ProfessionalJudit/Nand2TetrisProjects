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
    
}