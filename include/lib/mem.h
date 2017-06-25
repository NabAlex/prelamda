#ifndef PRELAMDA_MEM_H
#define PRELAMDA_MEM_H

#define STRSZ(str) str, sizeof(str) - 1
#define STRLN(str) str, strlen(str)

#define SZ(str) sizeof(str) - 1

#define KiB * 1024

#define STATICSZ(array) sizeof(array) / sizeof(*array)
#define FOREACH_STATIC(array, index) for (index = 0; index < STATICSZ(array); index++)

#define MEM_ERROR_P "[MEM ERROR]"
#define xassert(expr, text) do {                                        \
        if(!(expr))                                                     \
        {                                                               \
            printf(MEM_ERROR_P" %s line: %d", text, __LINE__);    \
            assert(0);                                                  \
        }                                                               \
    } while(0);

void *
xmemdup(void *src, size_t size);

void
xmemmove(void *dst, void *src, size_t size);

void *
xmalloc(size_t size);

#endif //PRELAMDA_MEM_H
