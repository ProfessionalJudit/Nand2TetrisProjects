#include <string>
#include <fstream>
class code
{
private:
    /* data */
public:
    std::ofstream output;
    code(){
        output.open("output.vm");
    }
    // Convert compute part from C instruction
    std::string writeArithmetic(std::string command){
        
    }
};
