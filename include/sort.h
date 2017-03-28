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

#ifndef __GENERIC_SORT_H__
#define __GENERIC_SORT_H__

#include "errnum.h"
#include "utils.h"

/*******************************************************************************
* Macro:        sort_selection
* Description:  The simple selection sort algorithm.
* Input:        container:  The container object, e.g. vector, array.
*               compare_ptr(type *, type *):  Object comparing function.
* Notice:       The selection sort is an UNSTABLE algorithm.
*               It's time complexity is as following:
*                - AVG / MAX / MIN TIME: O(n^2)
*******************************************************************************/
#define sort_selection(container, compare_ptr) do { \
    for (int i = 0; i < (container).count - 1; i++)                 \
    {                                                               \
        int sort_index = i;                                         \
        for (int j = i + 1; j < (container).count; j++)             \
        {                                                           \
            if (compare_ptr((container).get(&(container), i),       \
                            (container).get(&(container), j)) > 0)  \
            {                                                       \
                sort_index = j;                                     \
            }                                                       \
        }                                                           \
        if (sort_index != i)                                        \
        {                                                           \
            swap(*(container).get(&(container), i),                 \
                 *(container).get(&(container), j));                \
        }                                                           \
    }                                                               \
} while (0)

/*******************************************************************************
* Macro:        sort_bubble
* Description:  The bubble sort algorithm.
* Input:        container:  The container object, e.g. vector, array.
*               compare_ptr(type *, type *):  Object comparing function.
* Notice:       The bubble sort is a STABLE algorithm.
*               It's time complexity is as following:
*                - AVG / MAX TIME: O(n^2)
*                - MIN TIME: O(n)
*******************************************************************************/
#define sort_bubble(container, compare_ptr) do { \
    for (int i = (container).count - 1; i >= 0; i--)                    \
    {                                                                   \
        for (int j = 0; j < i; j++)                                     \
        {                                                               \
            if (compare_ptr((container).get(&(container), j),           \
                            (container).get(&(container), j + 1)) > 0)  \
            {                                                           \
                swap(*(container).get(&(container), j),                 \
                     *(container).get(&(container), j + 1));            \
            }                                                           \
        }                                                               \
    }                                                                   \
} while (0)

/*******************************************************************************
* Macro:        sort_quick_internal
* Description:  The quick sort algorithm internal macro.
*******************************************************************************/
#define sort_quick_internal(qindex, container, compare, left, right) do { \
    int left_i = left, right_i = right, mv_dir = 0;                 \
    while (left_i != right_i)                                       \
    {                                                               \
        if (compare((container).get(&(container), left_i),          \
                    (container).get(&(container), right_i)) > 0)    \
        {                                                           \
            swap(*(container).get(&(container), left_i),            \
                 *(container).get(&(container), right_i));          \
            mv_dir = (mv_dir + 1) % 2;                              \
        }                                                           \
        left_i += (mv_dir == 0)? 1 : 0;                             \
        right_i -= (mv_dir == 1)? 1 : 0;                            \
    }                                                               \
    if (left_i - 1 > left)                                          \
    {                                                               \
        vector_pushback(qindex, left);                              \
        vector_pushback(qindex, left_i - 1);                        \
    }                                                               \
    if (right > right_i + 1)                                        \
    {                                                               \
        vector_pushback(qindex, right_i + 1);                       \
        vector_pushback(qindex, right);                             \
    }                                                               \
} while (0)

/*******************************************************************************
* Macro:        sort_quick
* Description:  The quick sort algorithm.
* Input:        container:  The container object, e.g. vector, array.
*               compare_ptr(type *, type *):  Object comparing function.
* Notice:       The quick sort is an UNSTABLE algorithm.
*               It's time complexity is as following:
*                - AVG / MIN TIME: O(n * log n)
*                - MAX TIME: O(n^2)
*******************************************************************************/
#define sort_quick(container, compare_ptr) do { \
    vector(int) qsort_index;                                    \
    vector_init(qsort_index);                                   \
    vector_pushback(qsort_index, 0);                            \
    vector_pushback(qsort_index, (container).count - 1);        \
    while (!vector_empty(qsort_index))                          \
    {                                                           \
        int left_idx = vector_get(qsort_index, 0);              \
        int right_idx = vector_get(qsort_index, 1);             \
        vector_erase(qsort_index, 1);                           \
        vector_erase(qsort_index, 0);                           \
        sort_quick_internal(qsort_index, container,             \
                            compare_ptr, left_idx, right_idx);  \
    }                                                           \
    vector_destroy(qsort_index);                                \
} while (0)

/*******************************************************************************
* Macro:        sort_insert
* Description:  The quick sort algorithm.
* Input:        container:  The container object, e.g. vector, array.
*               compare_ptr(type *, type *):  Object comparing function.
* Notice:       The quick sort is a STABLE algorithm.
*               It's time complexity is as following:
*                - AVG / MAX TIME: O(n^2)
*                - MIN TIME: O(n)
*******************************************************************************/
#define sort_insert(container, compare_ptr) do { \
    void *store_ptr = malloc(sizeof(*(container).get(&(container), 0)));    \
    for (int i = 1; i < (container).count; i++)                             \
    {                                                                       \
        int left_idx = 0, right_idx = i - 1;                                \
        while (left_idx != right_idx)                                       \
        {                                                                   \
            int mid_idx = (left_idx + right_idx) / 2;                       \
            if (compare_ptr((container).get(&(container), i),               \
                            (container).get(&(container), mid_idx)) > 0)    \
            {                                                               \
                left_idx = mid_idx + ((mid_idx == left_idx)? 1 : 0);        \
            }                                                               \
            else                                                            \
            {                                                               \
                right_idx = mid_idx - ((mid_idx == right_idx)? 1 : 0);      \
            }                                                               \
        }                                                                   \
        if (right_idx != i - 1)                                             \
        {                                                                   \
            memcpy(store_ptr, (container).get(&(container), i),             \
                   sizeof(*(container).get(&(container), 0)));              \
            for (int j = i - 1; j >= left_idx; j--)                         \
            {                                                               \
                *(container).get(&(container), j + 1) =                     \
                                    *(container).get(&(container), j);      \
            }                                                               \
            memcpy((container).get(&(container), left_idx), store_ptr,      \
                   sizeof(*(container).get(&(container), 0)));              \
        }                                                                   \
        else if (compare_ptr((container).get(&(container), right_idx),      \
                             (container).get(&(container), i)) > 0)         \
        {                                                                   \
            swap(*(container).get(&(container), right_idx),                 \
                 *(container).get(&(container), i));                        \
        }                                                                   \
    }                                                                       \
    free(store_ptr);                                                        \
} while (0)

/*******************************************************************************
* Macro:        sort_merge
* Description:  The merge sort algorithm.
* Input:        container:  The container object, e.g. vector, array.
*               compare_ptr(type *, type *):  Object comparing function.
* Notice:       The merge sort is a STABLE algorithm.
*               It's time complexity is as following:
*                - AVG / MAX / MIN TIME: O(n * log n)
*******************************************************************************/
#define sort_merge(container, compare_ptr) do { \
    int elem_size = sizeof(*(container).get(&(container), 0));                 \
    /* Allocate memory buffer in heap to avoid stack crash */                  \
    void *store_ptr = malloc((container).count * elem_size);                   \
    /* Memory allocation successful, sort */                                   \
    int step, l_min, l_max, r_min, r_max, nps, len = (container).count;        \
    for (step = 1; step < len; step *= 2)                                      \
    {                                                                          \
        for (l_min = 0; l_min < len - step; l_min = r_max)                     \
        {                                                                      \
            /* Initialize position variables */                                \
            r_min = l_max = l_min + step;                                      \
            r_max = l_max + step;                                              \
            r_max = (r_max > len)? len : r_max;                                \
            /* Start merge copy */                                             \
            nps = 0;                                                           \
            while (l_min < l_max && r_min < r_max)                             \
            {                                                                  \
                if (compare_ptr((container).get(&(container), l_min),          \
                                 (container).get(&(container), r_min)) > 0)    \
                {                                                              \
                    memcpy(store_ptr + (nps * elem_size),                      \
                           (container).get(&(container), r_min), elem_size);   \
                    r_min = r_min + 1;                                         \
                }                                                              \
                else                                                           \
                {                                                              \
                    memcpy(store_ptr + (nps * elem_size),                      \
                           (container).get(&(container), r_min), elem_size);   \
                    l_min = l_min + 1;                                         \
                }                                                              \
                nps++;                                                         \
            }                                                                  \
            /* Merge reserved items */                                         \
            while (l_min < l_max)                                              \
            {                                                                  \
                r_min = r_min - 1;                                             \
                l_max = l_max - 1;                                             \
                memcpy((container).get(&(container), r_min),                   \
                       (container).get(&(container), l_max), elem_size);       \
            }                                                                  \
            while (nps > 0)                                                    \
            {                                                                  \
                r_min = r_min - 1;                                             \
                nps = nps - 1;                                                 \
                memcpy((container).get(&(container), r_min),                   \
                       (container).get(&(container), nps), elem_size);         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    /* Release the memory buffer */                                            \
    free(store_ptr);                                                           \
} while (0)

#endif /* __GENERIC_SORT_H__ */