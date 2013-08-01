%{
#include "node.h"
NBlock* programBlock;
extern int yylex();
void yyerror(const char* s) { printf("ERROR: %s\n", s); }
%}

%union {
    Node* node;
    NBlock* block;
    NStatement* stmt;
    NConvertion* convertion;
    NDeclaration* decl;
    NExpression* expr;
    std::vector<NConvertion*>* convertion_vec;
    std::vector<NExpression*>* expr_vec;
    std::string* string;
    int token;
}

%token <string> T_INTEGER T_DOUBLE
%token <token> T_PLUS T_MINUS T_MUL T_DIV T_EQUAL
%token <token> T_M T_MILE T_MILES T_YARD T_YARDS T_INCH T_INCHES T_FOOT T_FEET T_FATH T_FATHS T_FURLONG

%type <convertion> convertion
%type <decl> decl
%type <stmt> stmt
%type <expr> expr
%type <string> numeric
%type <block> program stmts
%type <token> calc unit

%left T_PLUS T_MINUS
%left T_MUL T_DIV

%start program

%%

program : stmts { programBlock = $1; }
        ;

stmts : stmt { $$ = new NBlock(); $$->getStatements().push_back($<stmt>1); }
      | stmts stmt { $1->statements.push_back($<stmt>2);  }
      ;

stmt : convertion { $$ = new NStatement($<convertion>1); }
     | expr { $$ = new NStatement($<expr>1); }
     ;

convertion : decl T_EQUAL decl { $$ = new NConvertion($<decl>1, $<decl>3);  }
           ;

expr : expr calc decl { $$ = new NBinaryOperator($<expr>1, $<calc>2, $<decl>3); }
     | decl { $$ = $<decl>1; }
     ;


calc : T_PLUS
     | T_MINUS
     | T_MUL
     | T_DIV
     ;

decl : numeric unit { $$ = new NDeclaration(*$1, $2); delete $1; }
     ;

numeric : T_DOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; }
        | T_INTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
        ;

unit : T_M
     | T_MILE | T_MILES
     | T_YARD | T_YARDS
     | T_INCH | T_INCHES
     | T_FOOT | T_FEET
     | T_FATH | T_FATHS
     | T_FURLONG
     ;

%%

