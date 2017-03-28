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

#ifndef __GENERIC_SEARCH_H__
#define __GENERIC_SEARCH_H__

#include "errnum.h"
#include "utils.h"

/*******************************************************************************
* Macro:        search_binary
* Description:  The binary search algorithm.
* Input:        container:  The container object, e.g. vector, array.
*               compare(type *, type *):  Object comparing function.
*               type *obj_ptr:  The pointer to object for searching.
* Output:       int pos_out:  The position, or -1 if not found.
* Notice:       It's time complexity is: O(log n).
*******************************************************************************/
#define search_binary(container, compare, obj_ptr, pos_out) do { \
    int left_idx = 0, right_idx = (container).count - 1;                    \
    while (1)                                                               \
    {                                                                       \
        int m_idx = (left_idx + right_idx) / 2;                             \
        int cmp_r = compare(obj_ptr, (container).get(&(container), m_idx)); \
        if (cmp_r == 0)                                                     \
        {                                                                   \
            pos_out = m_idx;                                                \
            break;                                                          \
        }                                                                   \
        else if (left_idx == right_idx)                                     \
        {                                                                   \
            pos_out = -1;                                                   \
            break;                                                          \
        }                                                                   \
        else if (cmp_r > 0)                                                 \
        {                                                                   \
            left_idx = m_idx + ((m_idx == left_idx)? 1 : 0);                \
        }                                                                   \
        else if (cmp_r < 0)                                                 \
        {                                                                   \
            right_idx = m_idx - ((m_idx == right_idx)? 1 : 0);              \
        }                                                                   \
    }                                                                       \
} while (0)

#endif /* __GENERIC_SEARCH_H__ */