#ifndef PRELAMDA_TOKEN_H
#define PRELAMDA_TOKEN_H

#define TOKEN_MAX_SPEC_WORD 16

typedef enum tokenize_type
{
    SPECIAL,
    INT,
    SPEC_WORDS,
    STRING_PTR
} tokenize_type_t;

typedef struct tokenize
{
    tokenize_type_t token_type;
    
    union {
        int a_int;
        char a_chr;
        
        char *a_ptr;
    };
    
    int line;
} tokenize_t;

void
token_init();

void
token_add(tokenize_t *tok);

/* init token */
tokenize_t *
tokenize_init();
void
tokenize_release(tokenize_t *tok);

void
token_debug_print();

#endif //PRELAMDA_TOKEN_H
