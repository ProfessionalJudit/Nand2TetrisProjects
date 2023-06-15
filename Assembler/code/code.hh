#include <string>
class code
{
private:
    /* data */
public:
    // Convert compute part from C instruction
    static std::string comp(std::string comp)
    {
        // Bits
        std::string bits = "";
        // Mark 12th bit
        if (comp.find("M") != -1)
        {
            bits.append("1");
        }
        else
        {
            bits.append("0");
        }
        // Yes, i put everything into and if statement, don't judge
        if (comp == "0")
        {
            bits.append("101010");
        }
        else if (comp == "1")
        {
            bits.append("111111");
        }
        else if (comp == "-1")
        {
            bits.append("111010");
        }
        else if (comp == "D")
        {
            bits.append("001100");
        }
        else if (comp == "A" || comp == "M")
        {
            bits.append("110000");
        }
        else if (comp == "!D")
        {
            bits.append("001101");
        }
        else if (comp == "!A" || comp == "!M")
        {
            bits.append("110001");
        }
        else if (comp == "-D")
        {
            bits.append("001111");
        }
        else if (comp == "-A" || comp == "-M")
        {
            bits.append("110011");
        }
        else if (comp == "D+1")
        {
            bits.append("011111");
        }
        else if (comp == "A+1" || comp == "M+1")
        {
            bits.append("110111");
        }
        else if (comp == "D-1")
        {
            bits.append("001110");
        }
        else if (comp == "A-1" || comp == "M-1")
        {
            bits.append("110010");
        }
        else if (comp == "D+A" || comp == "D+M")
        {
            bits.append("000010");
        }
        else if (comp == "D-A" || comp == "D-M")
        {
            bits.append("010011");
        }
        else if (comp == "A-D" || comp == "M-D")
        {
            bits.append("000111");
        }
        else if (comp == "D&A" || comp == "D&M")
        {
            bits.append("000000");
        }
        else if (comp == "D|A" || comp == "D|M")
        {
            bits.append("010101");
        }
        else
        {
            return "0000000";
        }

        return bits;
    }
    // Convert dest part from C instruction
    static std::string dest(std::string dest)
    {
        // Bits
        std::string bits = "";
        // Set each bit depending of ocurrence
        if (dest.find("A") != -1)
        {
            bits.append("1");
        }
        else
        {
            bits.append("0");
        }
        if (dest.find("D") != -1)
        {
            bits.append("1");
        }
        else
        {
            bits.append("0");
        }
        if (dest.find("M") != -1)
        {
            bits.append("1");
        }
        else
        {
            bits.append("0");
        }
        return bits;
    }
    // Convert jump part from C instruction
    static std::string jump(std::string jump)
    {
        if (jump == "JGT")
        {
            return "001";
        }
        if (jump == "JEQ")
        {
            return "010";
        }
        if (jump == "JGE")
        {
            return "011";
        }
        if (jump == "JLT")
        {
            return "100";
        }
        if (jump == "JLE")
        {
            return "110";
        }
        if (jump == "JMP")
        {
            return "111";
        }
        if (jump == "JNE")
        {
            return "101";
        }
        return "000";
    }
};
