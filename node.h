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

class NBlock
{
public:
    Statements const& getStatements() const { return m_stmt; }
    Statements& getStatements() { return m_stmt; }

private:
    Statements m_stmts;
};

class NStatement
{
public:
    NStatement(Node* node);

private:
    Node* m_node;
};

class NConvertion : public ConvertionNode
{
public:
    virtual ~NConvertion() {}
    virtual std::pair<int, double> makeConvertion();
};

class NExpression : public ExpressionNode
{
public:
    virtual ~NExpression() {}
    virtual double getResult();
};

class NDeclaration : public ExpressionNode
{
public:
    virtual ~NDeclaration() {}
    virtual double getResult();
};

class NDouble
{
public:
    NDouble(std::string const& txt);
    double value() const;

private:
    std::string m_value;
};

class NInteger
{
public:
    NInteger(std::string const& txt);
    int value() const;

private:
    std::string m_value;
};

class NBinaryOperator
{
public:
};

#endif /* __CODE_H__ */
