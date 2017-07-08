#include "prelamda.h"

int inc_counter;

acc_t *
acc_init(size_t init_size)
{
    acc_t *tmp = xmalloc( sizeof(acc_t) );
    tmp->data = xmalloc(init_size * sizeof(tmp->data));
    tmp->cursor = 0;
    
    tmp->length = init_size;
    return tmp;
}

void
acc_release(acc_t *acc)
{
    free(acc->data);
    free(acc);
}

void
acc_concat(acc_t *acc, acc_t *add_part)
{
    // snprinf
}

void
accf(acc_t *acc, char *format, ...)
{
    
}

int inc_counter;
void
gen_init()
{
    inc_counter = 0;
}

static acc_t *
gen_func_alloc(acc_t *body)
{
    acc_t *tmp = acc_init(ACCUMULATOR_BEGIN_LENGTH);
    
}