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

#ifndef __GENERIC_VECTOR_H__
#define __GENERIC_VECTOR_H__

#include "errnum.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

/* Vector struct definition */
#define vector_def(type)            \
    struct {                        \
        type *data_ptr;             \
        unsigned int size;          \
        unsigned int count;         \
        unsigned int err_num;       \
        pthread_mutex_t mutex;      \
        pthread_cond_t cond;        \
        type* (*get)(void *, int);  \
    }

/* Extern the vector to a type, so we can use the pointer in param */
#define vector_extern(type) \
    typedef vector_def(type) vector_##type##_t;             \
    type* __attribute__((weak))                             \
        vector_get_##type(vector_##type##_t *vec, int pos)  \
    {                                                       \
        return &vector_get(*vec, pos);                      \
    }

#define vector_vtable(type, vector) do {    \
    (vector).get = vector_get_##type;       \
} while (0)

/* Define a vector type */
#define vector(type) vector_##type##_t

/* Initialize */
#define vector_init(vector) do {                            \
    (vector).data_ptr = NULL;                               \
    (vector).size = 0;                                      \
    (vector).count = 0;                                     \
    (vector).err_num = 0;                                   \
    if (pthread_mutex_init(&(vector).mutex, NULL) != 0)     \
    {                                                       \
        (vector).err_num = ERR_INIT_FAILURE;                \
    }                                                       \
    if (pthread_cond_init(&(vector).cond, NULL) != 0)       \
    {                                                       \
        (vector).err_num = ERR_INIT_FAILURE;                \
    }                                                       \
} while (0)

/* Uninitialize */
#define vector_destroy(vector) do { \
    free((vector).data_ptr);        \
    (vector).data_ptr = NULL;       \
    (vector).size = 0;              \
    (vector).count = 0;             \
    (vector).err_num = 0;           \
} while (0)

/* Get the operation number */
#define vector_err(vector) (vector).err_num

/* Get the specified item */
#define vector_get(vector, pos) (*((vector).data_ptr + pos))

/* Get the front (first) item */
#define vector_front(vector) vector_get(vector, 0)

/* Get the back (last) item */
#define vector_back(vector) vector_get(vector, (vector).count - 1)

/* Get the vector number size */
#define vector_size(vector) (vector).count

/* Get the vector capacity size */
#define vector_capacity(vector) (vector).size

/* Delete all items in the vector */
#define vector_clear(vector) do {   \
    (vector).count = 0;             \
    (vector).err_num = ERR_OK;      \
} while (0)

/* Judge whether the vector is empty */
#define vector_empty(vector) ((vector).count == 0)

/* Resize the vector size */
#define vector_resize(vector, new_size) do {                                \
    if ((new_size) <= (vector).size)                                        \
    {                                                                       \
        (vector).count = new_size;                                          \
        (vector).err_num = ERR_OK;                                          \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        void *ptr = malloc(sizeof(*(vector).data_ptr) * new_size);          \
        if (ptr == NULL)                                                    \
        {                                                                   \
            (vector).err_num = ERR_MEMORY_FAILURE;                          \
        }                                                                   \
        else                                                                \
        {                                                                   \
            unsigned int copy_size =                                        \
                sizeof(*(vector).data_ptr) * (vector).count;                \
            /*lint -e(1415) Copy without copy constructor */                \
            memcpy(ptr, (vector).data_ptr, copy_size);                      \
            free((vector).data_ptr);                                        \
            (vector).data_ptr = ptr;                                        \
            (vector).size = new_size;                                       \
            (vector).err_num = ERR_OK;                                      \
        }                                                                   \
    }                                                                       \
} while (0)

/* Add an item to vector at the specified position */
#define vector_insert(vector, pos, item) do {                               \
    (vector).err_num = ERR_OK;                                              \
    if ((vector).count >= (vector).size)                                    \
    {                                                                       \
        unsigned int n_size = (vector).size == 0? 4 : ((vector).size * 2);  \
        vector_resize(vector, n_size);                                      \
    }                                                                       \
    if ((vector).err_num == ERR_OK)                                         \
    {                                                                       \
        unsigned int real = (pos) < (vector).count? (pos) : (vector).count; \
        for (unsigned int vi = (vector).count; vi > real; vi--)             \
        {                                                                   \
            *((vector).data_ptr + vi) = *((vector).data_ptr + vi - 1);      \
        }                                                                   \
        *((vector).data_ptr + real) = item;                                 \
        (vector).count++;                                                   \
    }                                                                       \
} while (0)

/* Add an item to the last position of vector */
#define vector_pushback(vector, item) \
    vector_insert(vector, (vector).count, item)

/* Remove the speicified item */
#define vector_erase(vector, pos) do {                                  \
    unsigned int pos_uint = (unsigned int)(pos);                        \
    if (pos_uint >= (vector).count)                                     \
    {                                                                   \
        (vector).err_num = ERR_INVALID_POS;                             \
    }                                                                   \
    else                                                                \
    {                                                                   \
        (vector).count--;                                               \
        for (unsigned int vi = pos_uint; vi < (vector).count; vi++)     \
        {                                                               \
            *((vector).data_ptr + vi) = *((vector).data_ptr + vi + 1);  \
        }                                                               \
        (vector).err_num = ERR_OK;                                      \
    }                                                                   \
} while (0)

/* Lock the vector for multi-thread operations */
#define vector_lock(vector) \
    pthread_mutex_lock(&(vector).mutex);

/* Unock the vector for multi-thread operations */
#define vector_unlock(vector) \
    pthread_mutex_unlock(&(vector).mutex);

/* Sleep thread for multi-thread operations */
#define vector_wait(vector) \
    pthread_cond_wait(&(vector).cond, &(vector).mutex);

/* Wakeup thread for multi-thread operations */
#define vector_signal(vector) \
    pthread_cond_signal(&(vector).cond);

#endif /* __GENERIC_VECTOR_H__ */
