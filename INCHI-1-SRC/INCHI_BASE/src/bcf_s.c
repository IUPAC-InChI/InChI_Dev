/* djb-rwth: implementation of missing bounds - checking functions */  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "bcf_s.h"

#ifndef _WIN32
#define EINVAL 22
#endif

#define RSIZE_MAX_C (0xffffffffffffffffull >> 1)

#if USE_BCF
errno_t memset_ssc(void* v, rsize_t smax, int c, rsize_t n)
{
    if (v == NULL) return EINVAL;
    if (smax > RSIZE_MAX_C) return EINVAL;
    if (n > smax) return EINVAL;

    volatile unsigned char* p = (volatile unsigned char*)v;
    while (smax-- && n--)
    {
        *p++ = c;
    }

    return 0;
}
#endif


/* ANOTHER SOLUTION ?

errno_t memset_s(void* s, rsize_t smax, int c, rsize_t n)
{
    if (!s || (smax > RSIZE_MAX_C))
        return EINVAL;

    if (n > smax)
    {
        memset_s(s, smax, c, smax);
        return EINVAL;
    }

    volatile unsigned char* v = (volatile unsigned char*)s;
    for (rsize_t i = 0u; i < n; ++i)
        *v++ = (unsigned char)c;

    return 0;
}

*/

/* djb-rwth: Linux version */
int memset_usc(void* v, size_t smax, int c, size_t n)
{
    if (v == NULL) return EINVAL;
    if (smax > RSIZE_MAX_C) return EINVAL;
    if (n > smax) return EINVAL;

    volatile unsigned char* p = (volatile unsigned char*)v;
    while (smax-- && n--)
    {
        *p++ = c;
    }

    return 0;
}
