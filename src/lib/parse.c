#include "prelamda.h"

#define PARSE_MAX_DATA 10
#define PARSE_MAX_LEN 10

static char *name[PARSE_MAX_DATA];
static char *values[PARSE_MAX_DATA];

static void
parse_file(FILE *f)
{
    const unsigned int COUNT_KV = 2;
    
    int err = COUNT_KV, i = 0;
    while (err == COUNT_KV)
    {
        err = fscanf(f, "%s%s", name[i], values[i]);
        ++i;
    }
}

void
parse_init(FILE *file)
{
    for (int i = 0; i < PARSE_MAX_DATA; i++)
    {
        name[i] = (char*) xmalloc(PARSE_MAX_LEN);
        values[i] = (char*) xmalloc(PARSE_MAX_LEN);
    }
    
    parse_file(file);
}

char *
get_config_elem(char *data)
{
    for (int i = 0; i < PARSE_MAX_DATA; i++)
    {
        if (strcmp(name[i], data) == 0)
            return values[i];
    }
    
    return NULL;
}