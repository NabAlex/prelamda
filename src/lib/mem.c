#include "prelamda.h"

void *
xmemdup(void *src, size_t size)
{
    xassert(src, "error src");
    void *dst = malloc(size);
    xassert(dst, "cannot allocate memory");
    memmove(dst, src, size);
    return dst;
}

void
xmemmove(void *dst, void *src, size_t size)
{
    xassert(dst, "error dst");
    xassert(src, "error src");
    memmove(dst, src, size);
}

void *
xmalloc(size_t size)
{
    xassert(size > 0, "error size");
    char *data = malloc(size);
    xassert(data, "cannot allocate memory");
    
    return data;
}