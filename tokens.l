%{

#include <string>
#include "node.h"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng);
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() {}

%}

%%

[ \t\n]                 ;
[0-9]+\.[0-9]*          SAVE_TOKEN; return T_DOUBLE;
[0-9]+                  SAVE_TOKEN; return T_INTEGER;
"="                     return TOKEN(T_EQUAL);
"+"                     return TOKEN(T_PLUS);
"-"                     return TOKEN(T_MINUS);
"*"                     return TOKEN(T_MUL);
"/"                     return TOKEN(T_DIV);
"m"                     return TOKEN(T_M);
"mile"                  return TOKEN(T_MILE);
"miles"                 return TOKEN(T_MILES);
"yard"                  return TOKEN(T_YARD);
"yards"                 return TOKEN(T_YARDS);
"inch"                  return TOKEN(T_INCH);
"inches"                return TOKEN(T_INCHES);
"foot"                  return TOKEN(T_FOOT);
"feet"                  return TOKEN(T_FEET);
"fath"                  return TOKEN(T_FATH);
"faths"                 return TOKEN(T_FATHS);
"furlong"               return TOKEN(T_FURLONG);
.                       printf("Unknown token!\n"); yyterminate();

%%

