#ifndef SMELLCODE_STRING_H
#define SMELLCODE_STRING_H

#include <stddef.h>

static inline size_t strlen(const char *s)
{
    size_t n = 0;
    while (s[n]) n++;
    return n;
}

#endif