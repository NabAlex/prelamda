#include "prelamda.h"

void print_help()
{
    printf("Use program: [ \n"
           " -c - configure file \n"
           "]");
}

int main(int argc, char **argv)
{
    token_init();
    
    lex_init(fopen("/home/alex/CLionProjects/prelamda/test/lex1.txt", "r"));
    lex_start_parse();
    
    token_debug_print();
    
    return 0;
}