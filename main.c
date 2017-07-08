#include "prelamda.h"

void print_help()
{
    printf("use program: [ \n"
           " -c - configure file \n"
           "]");
}

int main(int argc, char **argv)
{
    token_init();

    FILE *prefile = fopen("/home/alex/CLionProjects/prelamda/test/lex1.cc", "r");
    if (!prefile)
    {
        printf("cannot open files\n");
        return 0;
    }

    lex_init(prefile);
    lex_start_parse();

    char *buf;
    token_all_print_alloc(&buf);
    printf("%s\n", buf);

    fclose(prefile);
    return 0;
}