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

#ifndef __GENERIC_ARRAY_H__
#define __GENERIC_ARRAY_H__

#include "errnum.h"

/* Array struct definition */
#define array_def(type, size)       \
    struct {                        \
        type data[size];            \
        unsigned int arr_size;      \
        unsigned int count;         \
        unsigned int err_num;       \
    }

/* Extern the array to a type, so we can use the pointer in param */
#define array_extern(type, size)    \
    typedef array_def(type, size) array_##type##_##size##_t

/* Define an array type */
#define array(type, size) array_##type##_##size##_t

/* Initialize an array */
#define array_init(array, size) do {    \
    (array).count = 0;                  \
    (array).err_num = 0;                \
    (array).arr_size = size;            \
} while (0)

/* Get the specified position array item */
#define array_get(array, pos) (array).data[pos]

/* Get the array size */
#define array_size(array) (array).count

/* Get the operation result number */
#define array_err(array) (array).err_num

/* Delete all items in the array, will not affect the array size */
#define array_clear(array) do { \
    (array).count = 0;          \
    (array).err_num = ERR_OK;   \
} while (0)

/* Judge whether the array is empty */
#define array_empty(array) ((array).count == 0)

/* Add an item to array at the specified position */
#define array_insert(array, pos, item) do {                                 \
    if ((array).count >= (array).arr_size)                                  \
    {                                                                       \
        (array).err_num = ERR_ARRAY_FULL;                                   \
    }                                                                       \
    else if ((pos) >= (array).arr_size)                                     \
    {                                                                       \
        (array).err_num = ERR_INVALID_POS;                                  \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        unsigned int real = (pos) < (array).count? (pos) : (array).count;   \
        for (unsigned int i = (array).count; i > real; i--)                 \
        {                                                                   \
            (array).data[i] = (array).data[i - 1];                          \
        }                                                                   \
        (array).data[real] = item;                                          \
        (array).count++;                                                    \
        (array).err_num = ERR_OK;                                           \
    }                                                                       \
} while (0)

/* Add an item to the array at last position */
#define array_pushback(array, item) array_insert(array, (array).count, item)

/* Remove the speicified position item in array */
#define array_erase(array, pos) do {                            \
    if ((pos) >= (array).count)                                 \
    {                                                           \
        (array).err_num = ERR_INVALID_POS;                      \
    }                                                           \
    else                                                        \
    {                                                           \
        (array).count--;                                        \
        for (unsigned int i = (pos); i < (array).count; i++)    \
        {                                                       \
            (array).data[i] = (array).data[i + 1];              \
        }                                                       \
        (array).err_num = ERR_OK;                               \
    }                                                           \
} while (0)

#endif /* __GENERIC_ARRAY_H__ */
