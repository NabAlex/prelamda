#include "prelamda.h"

#define TOKEN_MULTI_COEF 2.7

tokenize_t **buffer_tok;
size_t buffer_tok_len;

int32_t tok_cur;

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

void
token_debug_print()
{
    for (int i = 0; i < tok_cur; i++)
    {
        printf("%d\n", buffer_tok[i]->token_type);
    }
}