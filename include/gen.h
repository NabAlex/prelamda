#ifndef PRELAMDA_GEN_H_H
#define PRELAMDA_GEN_H_H

#define ACCUMULATOR_BEGIN_LENGTH 100

typedef struct acc
{
    char *data;
    size_t cursor;
    
    size_t length;
} acc_t;

void
gen_init();

acc_t *
acc_init(size_t init_size);
void
acc_release(acc_t *acc);

void
accf(acc_t *acc, char *format, ...);


#endif //PRELAMDA_GEN_H_H
