#include "prelamda.h"

acc_t *
acc_init(size_t init_size)
{
    acc_t *tmp = xmalloc( sizeof(acc_t) );
    tmp->data = xmalloc(init_size);
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
accf(acc_t *acc, char *format, ...)
{
    
}

int inc;
void
gen_init()
{
    inc = 0; // TODO in config
}

static void gen_func()
{
    
}