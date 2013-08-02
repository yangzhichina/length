// node.h
//

#ifndef __CODE_H__
#define __CODE_H__

#include <stdio.h>
#include <string>
#include <vector>

class NStatement;

typedef std::vector<NStatement*> Statements;

struct Numeric
{
    Numeric(): isDouble(false), dValue(0.0), iValue(0) {}

    bool isDouble;
    double dValue;
    int iValue;
};

struct NDeclaration
{
    NDeclaration() {}

    Numeric numeric;
    int unit;

    double convert() const;
};

struct NConvertion
{
    NConvertion(): l(), r() {}

    NDeclaration l;
    NDeclaration r;

    void add() const;
};

struct NExpression
{
    NExpression(): expr(NULL), calc(0), decl() {}

    NExpression* expr;
    int calc;
    NDeclaration decl;

    double calculate() const;
};

struct NStatement
{
    NStatement(): isCalculable(false), convertion(), expression() {}

    bool isCalculable;
    NConvertion convertion;
    NExpression expression;

    void print() const;
};

struct NBlock
{
    Statements stmts;
    void print() const;
};

#endif /* __CODE_H__ */
