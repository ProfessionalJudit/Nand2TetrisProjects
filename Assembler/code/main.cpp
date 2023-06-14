#include "parser.hh"
int main(int argc, char const *argv[])
{
    parser parser("../max/MaxL.asm");

    std::cout << "\t\t" << "comandType\tsymbol\tdest\tcomp\tjump\n";

    while (parser.hasMoreCommands())
    {
        parser.advance();
    }

    std::cout << parser.bin;

    return 0;
}
