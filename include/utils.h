/*
 * Copyright (c) 2014 Leo <leo@nullptr.com.cn>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef __GENERIC_UTILS_H__
#define __GENERIC_UTILS_H__

#include "errnum.h"

/* Get the max number from two numbers */
#define max(a, b)  ((a) > (b) ? (a) : (b))

/* Get the min number from two numbers */
#define min(a, b)  ((a) < (b) ? (a) : (b))

/* Array element number calculating macro */
#define     NUM_ELEMS(x)    (sizeof(x) / sizeof(x[0]))

/* Swap macro definition */
#define swap(x, y) do { \
    uint32 swp_size = min(sizeof(x), sizeof(y));    \
    char *ptr1 = (char *)&(x);                      \
    char *ptr2 = (char *)&(y);                      \
    for (int i = 0; i < swp_size; i++)              \
    {                                               \
        ptr1[i] ^= ptr2[i];                         \
        ptr2[i] ^= ptr1[i];                         \
        ptr1[i] ^= ptr2[i];                         \
    }                                               \
} while (0)

/* Branch predict optimize macro definitions */
#define likely(x)   __builtin_expect (!!(x), 1)
#define unlikely(x) __builtin_expect (!!(x), 0)

#endif /* __GENERIC_UTILS_H__ */
