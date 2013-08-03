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
    FILE* f = fopen("input.txt", "r");
    if (!f)
    {
        std::cout << "No file found." << std::endl;
        // Don't delete programBlock here, it's not created.
        // By the way, it is created after yyparse().
        return -1;
    }

    yyin = f;

    yyparse();

    programBlock->print();

    fclose(f);

    delete programBlock; // It's right position for deletion.

    return 0;
}
