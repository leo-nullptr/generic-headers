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

#ifndef __GENERIC_RULES_H__
#define __GENERIC_RULES_H__

#ifdef __GNUC__

/* Disable the danger macro */
#undef alloca

/* String handling functions */
#pragma GCC poison strcpy wcscpy stpcpy wcpcpy
#pragma GCC poison gets puts
#pragma GCC poison strcat wcscat
#pragma GCC poison wcrtomb wctob
#pragma GCC poison sprintf vsprintf vfprintf
#pragma GCC poison asprintf vasprintf
#pragma GCC poison strncpy wcsncpy
#pragma GCC poison strtok wcstok
#pragma GCC poison strdupa strndupa

/* Signal related */
#pragma GCC poison longjmp siglongjmp
#pragma GCC poison setjmp sigsetjmp

/* Memory allocation */
#pragma GCC poison alloca
#pragma GCC poison mallopt

/* File API's */
#pragma GCC poison remove
#pragma GCC poison mktemp tmpnam tempnam
#pragma GCC poison getwd

/* Misc */
#pragma GCC poison getlogin getpass cuserid
#pragma GCC poison rexec rexec_af

#endif /* __GNUC */

#endif /* __GENERIC_RULES_H__ */
