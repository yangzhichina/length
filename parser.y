%{

#include "node.h"
NBlock* programBlock;
extern int yylex();
void yyerror(const char* s) { printf("ERROR: %s\n", s); }

%}

%union {
    NBlock* block;
    NStatement* stmt;
    NConvertion* convertion;
    NDeclaration* decl;
    NExpression* expr;
    Numeric* numeric;
    std::string* string;
    int token;
}

%token <string> T_INTEGER T_DOUBLE
%token <token> T_PLUS T_MINUS T_MUL T_DIV T_EQUAL
%token <token> T_M T_KM T_MILE T_YARD T_INCH T_FOOT T_FATH T_FURLONG

%type <convertion> convertion
%type <decl> decl
%type <stmt> stmt
%type <expr> expr
%type <numeric> numeric
%type <block> program stmts
%type <token> calc unit

%left T_PLUS T_MINUS
%left T_MUL T_DIV

%start program

%%

program
: stmts {
    programBlock = $1;
}
;

stmts
: stmt {
    $$ = new NBlock();
    $$->stmts.push_back($1);
}
| stmts stmt {
    $1->stmts.push_back($2);
}
;

stmt
: convertion {
    $$ = new NStatement();
    $$->isCalculable = false;
    $$->convertion = *$1;

    delete $1;
}
| expr {
    $$ = new NStatement();
    $$->isCalculable = true;
    $$->expression = *$1;

    delete $1;
}
;

convertion
: decl T_EQUAL decl {
    $$ = new NConvertion();
    $$->l = *$1;
    $$->r = *$3;

    delete $1;
    delete $3;
}
;

expr
: decl {
    $$ = new NExpression();
    $$->decl = *$1;
    delete $1;
}
| expr calc decl {
    $$ = new NExpression();
    $$->expr.reset($1);
    $$->calc = $2;
    $$->decl = *$3;

    delete $3;
}
;

calc : T_PLUS
     | T_MINUS
     | T_MUL
     | T_DIV
     ;

decl
: numeric unit {
    $$ = new NDeclaration();
    $$->numeric = *$1;
    $$->unit = $2;
    delete $1;
}
;

numeric
: T_DOUBLE {
    $$ = new Numeric();
    $$->isDouble = true;
    $$->dValue = atof($1->c_str());
    delete $1;
}
| T_INTEGER {
    $$ = new Numeric();
    $$->isDouble = false;
    $$->iValue = atol($1->c_str());
    delete $1;
}
;

unit : T_M | T_KM
     | T_MILE 
     | T_YARD 
     | T_INCH
     | T_FOOT 
     | T_FATH 
     | T_FURLONG
     ;

%%

