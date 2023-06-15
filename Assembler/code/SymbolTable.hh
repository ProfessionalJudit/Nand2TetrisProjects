#include <map>
#include <string>
class SymbolTable
{
private:
    /* data */
public:
    SymbolTable(/* args */);
    ~SymbolTable();
    void addEntry(std::string symbol, int address);
    bool contains(std::string symbol);
    std::string GetAddress(std::string symbol);
    std::map<std::string, int> symbols;
};

SymbolTable::SymbolTable(/* args */)
{
}

SymbolTable::~SymbolTable()
{
}

bool SymbolTable::contains(std::string symbol)
{
    // Get an iterator pointing to the first element in the map
    std::map<std::string, int>::iterator it = symbols.begin();
    bool containsSymbol = false;
    // Iterate through the map and
    while (it != symbols.end())
    {
        if (it->first == symbol)
        {
            containsSymbol = true;
        }

        ++it;
    }
    return containsSymbol;
}

void SymbolTable::addEntry(std::string symbol, int address)
{
    if (!contains(symbol))
    {
        symbols.insert(std::pair<std::string, int>(symbol, address));
    }
}

std::string SymbolTable::GetAddress(std::string symbol)
{
    return std::to_string(symbols.find(symbol)->second);
}