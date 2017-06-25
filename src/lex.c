#include "prelamda.h"

#define CHRTOINT(chr) chr - '0'

#define DOIT_NOTHING(index)

#define IN_ARRAY(array, chr, flag, doit) do {           \
        int index0;                                     \
        flag = 0;                                       \
        FOREACH_STATIC(array, index0) {                 \
            if (*(array[index0]) == chr)                \
            {                                           \
                flag = 1;                               \
                doit(index0);                           \
            }                                           \
        }                                               \
    }                                                   \
    while (0)

/* start lex */

char *lex_spec_symbol[] = { "{", "}", "=", "+", "-", "/", "*" /* ptr or multi */, ";", "(", ")" };
int is_after_variable(int chr)
{
    if (chr == ' ')
        goto yes;
    
    int flag;
    IN_ARRAY(lex_spec_symbol, chr, flag, DOIT_NOTHING);
    if (flag)
        goto yes;
    
    return 0;
yes:
    return 1;
}

char *lex_digit[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

char *lex_spec_words[] = { "if", "else", "while", "do", "typedef", "int", "double", "char" };

/* set array for exclude elements */

#define MAX_LEX_SIZE 100
int lex_spec_words_impl[MAX_LEX_SIZE];

#define DOIT_SETFLAG(index) lex_spec_words_impl[index] = 1;

/* end lex*/

static char __buf[4 KiB];
int __buf_len;

static FILE *local_file;
lex_status_callback local_callback;

void
lex_init(FILE *file)
{
    local_file = file;
    local_callback = NULL;
}

void
lex_init_with_callback(FILE *file, lex_status_callback callback)
{
    local_file = file;
    local_callback = callback;
}

void
lex_start_parse()
{
    int c = 0, flag;
    
    tokenize_t *token;
    
    int read_token = 1, now_line = 1;
    while ((!read_token) || ((c = fgetc(local_file)) != EOF))
    {
        read_token = 1;
        /* is enter TODO work with \r\n */
        if (c == 10 || c == 13)
        {
            now_line += 1;
            continue;
        }
        
        /* is space ~ ignore */
        if (c == 32)
            continue;
        
        token = tokenize_init();
        token->line = now_line;
        
        IN_ARRAY(lex_spec_symbol, c, flag, DOIT_NOTHING);
        if (flag)
        {
            token->token_type = SPECIAL;
            token->a_chr = (char) c;
            token_add(token);
    
            continue;
        }
        
        IN_ARRAY(lex_digit, c, flag, DOIT_NOTHING);
        if (flag)
        {
            token->token_type = INT;
            int tmp = CHRTOINT(c);
            while (1)
            {
                c = fgetc(local_file);
                if ((c >= '0') && (c <= '9'))
                    tmp = tmp * 10 + CHRTOINT(c);
                else
                    break;
            }
            token_add(token);
    
            continue;
        }
        
        /* set flag in lex_spec_words_impl */
        IN_ARRAY(lex_spec_words, c, flag, DOIT_SETFLAG);

        const int NOTHING = -2;
        const int READ = -1;
        
        char new_string[1 KiB];
        /* need? */
        bzero(new_string, STATICSZ(new_string));
        
        new_string[0] = (char) c;
        
        int find_flag = NOTHING;
        int cursor = 1 /* begin find */;
        
        if (flag)
        {
            find_flag = READ;
            int is_flag;
            do
            {
                c = fgetc(local_file);
                new_string[cursor] = (char) c;
        
                xassert(c != EOF, "wrong words TODO!");
        
                is_flag = 0;
                for (int i = 0; i < STATICSZ(lex_spec_words); i++)
                {
                    /* in list */
                    if (lex_spec_words_impl[i] == 1)
                    {
                        is_flag = 1;
                        if (lex_spec_words[i][cursor] == '\0')
                            find_flag = i;
                        else if (lex_spec_words[i][cursor] != c)
                            lex_spec_words_impl[i] = 0;
                    }
                }
        
                if (!is_flag)
                    find_flag = NOTHING;
        
                ++cursor;
            } while (find_flag == READ);
        }
        
        if (find_flag == NOTHING)
        {
            while (1)
            {
                c = fgetc(local_file);
                xassert(c != EOF, "TODO this!");
                
                if (!is_after_variable(c))
                    new_string[cursor] = (char) c;
                else
                    break;
                
                ++cursor;
            }
            
            token->token_type = STRING_PTR;
            token->a_ptr = xmemdup(new_string, cursor + 1);
            token_add(token);
        }
        else
        {
            token->token_type = SPEC_WORDS;
            token->a_ptr = lex_spec_words[find_flag];
            token_add(token);
        }
        
        read_token = 0;
    }
}