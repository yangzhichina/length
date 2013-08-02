// node.cpp
//

#include <iostream>
#include <map>
#include <utility>

#include "node.h"
#include "parser.hpp" // It must be this position.

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
    double sum = 0.0; // m

    if (expr)
    {
        switch (calc)
        {
            case T_PLUS:
                sum = expr->calculate() + decl.convert();
                break;
            case T_MINUS:
                sum = expr->calculate() - decl.convert();
                break;
            case T_MUL:
                sum = expr->calculate() * decl.convert();
                break;
            case T_DIV:
                sum = expr->calculate() / decl.convert();
                break;

            default:
                break;
        }
    }
    else
    {
        sum = decl.convert();
    }

    return sum;
}

void NStatement::print() const
{
    if (isCalculable)
    {
        std::cout << expression.calculate() << " m" << std::endl;
    }
    else
    {
        convertion.add();
    }
}

void NBlock::print() const
{
    Statements::const_iterator c_iter = stmts.begin();
    for (; c_iter != stmts.end(); ++c_iter)
    {
        std::cout << "How\n";
        (*c_iter)->print();
    }
}
