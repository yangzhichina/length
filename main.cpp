// main.cpp
//

#include <iostream>
#include "node.h"

extern NBlock* programBlock;
extern int yydebug;
extern int yyparse();

int main(int argc, char* argv[])
{
    //yydebug = 1;
    yyparse();
    programBlock->print();
    return 0;
}
