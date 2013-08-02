// node.cpp
//

#include <map>
#include <utility>
#include "node.h"

class ConvertionMap
{
public:
    static std::map<int, double>& get();
};

std::map<int, double>& ConvertionMap::get()
{
    static std::map<int, double>* m;

    if (m == NULL)
        std::map<int, double>* m = new std::map<int, double>();

    return *m;
}

double NDeclaration::convert() const
{
    double p = numeric.isDouble ? numeric.dValue : numeric.iValue;
    double converted = p * ConvertionMap::get()[unit];
    return converted;
}

void NConvertion::add() const
{
    std::pair<int, double> item = std::make_pair(l.unit, r.numeric.isDouble ? r.numeric.dValue : r.numeric.iValue);
    ConvertionMap::get().insert(item);
}

double NExpression::calculate() const
{
    return 0.0;
}

void NStatement::print() const
{
}

void NBlock::print() const
{
    Statements::const_iterator c_iter = stmts.begin();
    for (; c_iter != stmts.end(); ++c_iter)
    {
        (*c_iter)->print();
    }
}
