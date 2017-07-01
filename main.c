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

    FILE *prefile = fopen("/Users/a.nabereznyi/Dev/prelamda/test/lex1.cc", "r");
    if (!prefile)
    {
        printf("cannot open files\n");
        return 0;
    }

    lex_init(prefile);
    lex_start_parse();


    int tok_len;
    tokenize_t **tok = token_get_tokens(&tok_len);

    char buf[1 KiB];
    token_snprintf(tok, tok_len, buf, sizeof(buf));
    printf("%s\n", buf);

    fclose(prefile);
    return 0;
}