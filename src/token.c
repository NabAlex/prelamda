#include "prelamda.h"

#define TOKEN_MULTI_COEF 2.7

#define MAX_TOKEN_STR_SIZE 1 KiB

tokenize_t **buffer_tok;
size_t buffer_tok_len;

int32_t tok_cur;

tokenize_t **
token_get_tokens(int *size)
{
    *size = tok_cur;
    return buffer_tok;
}

tokenize_t *
tokenize_init()
{
    tokenize_t *tmp = (tokenize_t*) xmalloc(sizeof(tokenize_t));
    bzero(tmp, sizeof(tokenize_t));
    return tmp;
}

static void
tokenize_delete(tokenize_t *tok)
{
    if (tok->token_type == STRING_PTR)
    {
        free(tok->a_ptr);
    }
}

void
tokenize_release(tokenize_t *tok)
{
    tokenize_delete(tok);
    free(tok);
}

void
token_init()
{
    const unsigned int DEFAULT_BUFFER_SIZE = 40;
    const unsigned int BUFFER_SIZE = DEFAULT_BUFFER_SIZE * sizeof(tokenize_t*);
    
    buffer_tok = (tokenize_t**) xmalloc(BUFFER_SIZE);
    buffer_tok_len = DEFAULT_BUFFER_SIZE;
        
    bzero(buffer_tok, BUFFER_SIZE);
    
    tok_cur = 0;
}

void
token_add(tokenize_t *tok)
{
    if (tok_cur >= buffer_tok_len)
    {
        buffer_tok_len *= TOKEN_MULTI_COEF;
        buffer_tok = (tokenize_t**) realloc(buffer_tok, buffer_tok_len);
        
        xassert(buffer_tok != NULL, "cannot memory for token");
    }
    
    buffer_tok[tok_cur] = tok;
    ++tok_cur;
}

int
token_snprintf(tokenize_t **tokens, int tokens_len, char *buf, int buf_size)
{
    int buf_len = 0;
    for (int i = 0; i < tokens_len; i++)
    {
        tokenize_t *t = tokens[i];
        switch (tokens[i]->token_type)
        {
            case (SPECIAL):
                buf_len += snprintf(buf + buf_len, buf_size - buf_len, "%c ", tokens[i]->a_chr);
                break;
            case (SPEC_WORDS):
                buf_len += snprintf(buf + buf_len, buf_size - buf_len, "%s ", tokens[i]->a_ptr);
                break;
            case (INT):
                buf_len += snprintf(buf + buf_len, buf_size - buf_len, "%d ", tokens[i]->a_int);
                break;
            case (STRING_PTR):
                buf_len += snprintf(buf + buf_len, buf_size - buf_len, "%s ", tokens[i]->a_ptr);
                break;
        }
    }

    buf[buf_len] = '\0';
    return buf_len;
}

int
token_all_print_alloc(char **result_buf)
{
    const unsigned int STR_SIZE = MAX_TOKEN_STR_SIZE;
    
    *result_buf = (char*) xmalloc(STR_SIZE * sizeof(char));
    return token_snprintf(buffer_tok, tok_cur, *result_buf, STR_SIZE);
}

void
token_debug_print()
{
    for (int i = 0; i < tok_cur; i++)
    {
        printf("%d\n", buffer_tok[i]->token_type);
    }
}