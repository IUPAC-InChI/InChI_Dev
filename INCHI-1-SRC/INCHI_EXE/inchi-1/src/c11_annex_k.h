/* djb-rwth: custom defined C11 Annex K functions */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

#define RSIZE_MAX_C (0xffffffffffffffffull >> 1)

errno_t memset_sc(void* v, rsize_t smax, int c, rsize_t n) 
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



/* VARIANT 1

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
