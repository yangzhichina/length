// node.h
//

#ifndef __CODE_H__
#define __CODE_H__

#include <string>
#include <map>
#include <vector>
#include <util>

class NStatement;
class NExpression;
class NDeclaration

typedef std::vector<NStatement*> Statements;

class Node
{
public:
    virtual ~Node() {}
    virtual bool isCalculable() const = 0;
};

class ConvertionNode : public Node
{
public:
    virtual ~ConvertionNode() {}
    virtual bool isCalculable() const { return false; }
    virtual std::pair<int, double> makeConvertion() = 0;
};

class ExpressionNode : public Node
{
public:
    virtual ~ExpressionNode() {}
    virtual bool isCalculable() const { return true; }
    virtual double getResult() = 0;
};

struct NBlock
{
    Statements stmts;
};

struct NStatement
{
    NStatement(): isCalculable(false), convertion(), expression() {}
    bool isCalculable;
    NConvertion convertion;
    NExpression expression;
};

struct NConvertion
{
    NConvertion(): l(), r() {}

    NDeclaration l;
    NDeclaration r;
};

struct NExpression
{
    NExpression(): expr(NULL), calc(0), decl() {}

    NExpression* expr;
    int calc;
    NDeclaration decl;
};

struct NDeclaration
{
    NDeclaration() {}

    Numeric numeric;
    int unit;
};

struct Numeric
{
    Numeric(): isDouble(false), dValue(0.0), iValue(0) {}

    bool isDouble;
    double dValue;
    long iValue;
};

#endif /* __CODE_H__ */
