// main.cpp
//

#include <stdio.h>
#include <iostream>
#include "node.h"

extern NBlock* programBlock;
extern int yydebug;
extern int yyparse();
extern "C" FILE *yyin;

int main(int argc, char* argv[])
{
    //yydebug = 1;

    FILE* f = fopen("input.txt", "r");
    if (!f)
    {
        std::cout << "No file found." << std::endl;
        return -1;
    }

    yyin = f;

    yyparse();

    programBlock->print();

    fclose(f);

    delete programBlock;

    return 0;
}
