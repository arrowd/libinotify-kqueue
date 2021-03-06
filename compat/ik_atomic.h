/*******************************************************************************
  Copyright (c) 2015 Vladimir Kondratyev <vladimir@kondratyev.su>
  SPDX-License-Identifier: MIT

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*******************************************************************************/

#include <pthread.h>

extern pthread_mutex_t ik_atomic_mutex;

#define	_Atomic(T)		T volatile
typedef	_Atomic(unsigned int)		atomic_uint;
#define	atomic_init(object, value)	(*(object) = (value))
#define atomic_load(object) ({ \
    pthread_mutex_lock (&ik_atomic_mutex); \
    typeof (*(object)) ret_ = *(object); \
    pthread_mutex_unlock (&ik_atomic_mutex); \
    ret_; \
})
#define atomic_fetch_add(object, operand) ({ \
    pthread_mutex_lock (&ik_atomic_mutex); \
    typeof (*(object)) ret_ = *(object); \
    *(object) += (operand); \
    pthread_mutex_unlock (&ik_atomic_mutex); \
    ret_; \
})
#define atomic_fetch_sub(object, operand) ({ \
    pthread_mutex_lock (&ik_atomic_mutex); \
    typeof (*(object)) ret_ = *(object); \
    *(object) -= (operand); \
    pthread_mutex_unlock (&ik_atomic_mutex); \
    ret_; \
})
