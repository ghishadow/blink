#ifndef COSMOPOLITAN_LIBC_BITS_ATOMIC_H_
#define COSMOPOLITAN_LIBC_BITS_ATOMIC_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)

/**
 * @fileoverview Cosmopolitan C11 Atomics Library
 *
 * - Forty-two different ways to say MOV.
 * - Fourteen different ways to say XCHG.
 * - Twenty different ways to say LOCK CMPXCHG.
 *
 * @see libc/atomic.h
 */

#if __STDC_VERSION__ + 0 < 201112
#define _Atomic(TYPE) TYPE volatile
#endif

#define atomic_bool           _Atomic(_Bool)
#define atomic_bool32         _Atomic(__INT32_TYPE__)
#define atomic_char           _Atomic(char)
#define atomic_schar          _Atomic(signed char)
#define atomic_uchar          _Atomic(unsigned char)
#define atomic_short          _Atomic(short)
#define atomic_ushort         _Atomic(unsigned short)
#define atomic_int            _Atomic(int)
#define atomic_uint           _Atomic(unsigned int)
#define atomic_long           _Atomic(long)
#define atomic_ulong          _Atomic(unsigned long)
#define atomic_llong          _Atomic(long long)
#define atomic_ullong         _Atomic(unsigned long long)
#define atomic_char16_t       _Atomic(__CHAR16_TYPE__)
#define atomic_char32_t       _Atomic(__CHAR32_TYPE__)
#define atomic_wchar_t        _Atomic(__WCHAR_TYPE__)
#define atomic_intptr_t       _Atomic(__INTPTR_TYPE__)
#define atomic_uintptr_t      _Atomic(__UINTPTR_TYPE__)
#define atomic_size_t         _Atomic(__SIZE_TYPE__)
#define atomic_ptrdiff_t      _Atomic(__PTRDIFF_TYPE__)
#define atomic_int_fast8_t    _Atomic(__INT_FAST8_TYPE__)
#define atomic_uint_fast8_t   _Atomic(__UINT_FAST8_TYPE__)
#define atomic_int_fast16_t   _Atomic(__INT_FAST16_TYPE__)
#define atomic_uint_fast16_t  _Atomic(__UINT_FAST16_TYPE__)
#define atomic_int_fast32_t   _Atomic(__INT_FAST32_TYPE__)
#define atomic_uint_fast32_t  _Atomic(__UINT_FAST32_TYPE__)
#define atomic_int_fast64_t   _Atomic(__INT_FAST64_TYPE__)
#define atomic_uint_fast64_t  _Atomic(__UINT_FAST64_TYPE__)
#define atomic_int_least8_t   _Atomic(__INT_LEAST8_TYPE__)
#define atomic_uint_least8_t  _Atomic(__UINT_LEAST8_TYPE__)
#define atomic_int_least16_t  _Atomic(__INT_LEAST16_TYPE__)
#define atomic_uint_least16_t _Atomic(__UINT_LEAST16_TYPE__)
#define atomic_int_least32_t  _Atomic(__INT_LEAST32_TYPE__)
#define atomic_uint_least32_t _Atomic(__UINT_LEAST32_TYPE__)
#define atomic_int_least64_t  _Atomic(__INT_LEAST64_TYPE__)
#define atomic_uint_least64_t _Atomic(__UINT_LEAST64_TYPE__)

#ifdef __CLANG_ATOMIC_BOOL_LOCK_FREE
#define ATOMIC_BOOL_LOCK_FREE     __CLANG_ATOMIC_BOOL_LOCK_FREE
#define ATOMIC_CHAR_LOCK_FREE     __CLANG_ATOMIC_CHAR_LOCK_FREE
#define ATOMIC_CHAR16_T_LOCK_FREE __CLANG_ATOMIC_CHAR16_T_LOCK_FREE
#define ATOMIC_CHAR32_T_LOCK_FREE __CLANG_ATOMIC_CHAR32_T_LOCK_FREE
#define ATOMIC_WCHAR_T_LOCK_FREE  __CLANG_ATOMIC_WCHAR_T_LOCK_FREE
#define ATOMIC_SHORT_LOCK_FREE    __CLANG_ATOMIC_SHORT_LOCK_FREE
#define ATOMIC_INT_LOCK_FREE      __CLANG_ATOMIC_INT_LOCK_FREE
#define ATOMIC_LONG_LOCK_FREE     __CLANG_ATOMIC_LONG_LOCK_FREE
#define ATOMIC_LLONG_LOCK_FREE    __CLANG_ATOMIC_LLONG_LOCK_FREE
#define ATOMIC_POINTER_LOCK_FREE  __CLANG_ATOMIC_POINTER_LOCK_FREE
#else
#define ATOMIC_BOOL_LOCK_FREE     __GCC_ATOMIC_BOOL_LOCK_FREE
#define ATOMIC_CHAR_LOCK_FREE     __GCC_ATOMIC_CHAR_LOCK_FREE
#define ATOMIC_CHAR16_T_LOCK_FREE __GCC_ATOMIC_CHAR16_T_LOCK_FREE
#define ATOMIC_CHAR32_T_LOCK_FREE __GCC_ATOMIC_CHAR32_T_LOCK_FREE
#define ATOMIC_WCHAR_T_LOCK_FREE  __GCC_ATOMIC_WCHAR_T_LOCK_FREE
#define ATOMIC_SHORT_LOCK_FREE    __GCC_ATOMIC_SHORT_LOCK_FREE
#define ATOMIC_INT_LOCK_FREE      __GCC_ATOMIC_INT_LOCK_FREE
#define ATOMIC_LONG_LOCK_FREE     __GCC_ATOMIC_LONG_LOCK_FREE
#define ATOMIC_LLONG_LOCK_FREE    __GCC_ATOMIC_LLONG_LOCK_FREE
#define ATOMIC_POINTER_LOCK_FREE  __GCC_ATOMIC_POINTER_LOCK_FREE
#endif

#define memory_order         int
#define memory_order_relaxed 0
#define memory_order_consume 1
#define memory_order_acquire 2
#define memory_order_release 3
#define memory_order_acq_rel 4
#define memory_order_seq_cst 5

#define ATOMIC_VAR_INIT(...)     __VA_ARGS__
#define atomic_is_lock_free(obj) ((void)(obj), sizeof(obj) <= sizeof(void *))

#define atomic_flag      atomic_bool
#define ATOMIC_FLAG_INIT ATOMIC_VAR_INIT(0)
#define atomic_flag_test_and_set_explicit(x, order) \
  atomic_exchange_explicit(x, 1, order)
#define atomic_flag_clear_explicit(x, order) atomic_store_explicit(x, 0, order)

#define atomic_compare_exchange_strong(pObject, pExpected, desired) \
  atomic_compare_exchange_strong_explicit(                          \
      pObject, pExpected, desired, memory_order_seq_cst, memory_order_seq_cst)
#define atomic_compare_exchange_weak(pObject, pExpected, desired) \
  atomic_compare_exchange_weak_explicit(                          \
      pObject, pExpected, desired, memory_order_seq_cst, memory_order_seq_cst)
#define atomic_exchange(pObject, desired) \
  atomic_exchange_explicit(pObject, desired, memory_order_seq_cst)
#define atomic_fetch_add(pObject, operand) \
  atomic_fetch_add_explicit(pObject, operand, memory_order_seq_cst)
#define atomic_fetch_and(pObject, operand) \
  atomic_fetch_and_explicit(pObject, operand, memory_order_seq_cst)
#define atomic_fetch_or(pObject, operand) \
  atomic_fetch_or_explicit(pObject, operand, memory_order_seq_cst)
#define atomic_fetch_sub(pObject, operand) \
  atomic_fetch_sub_explicit(pObject, operand, memory_order_seq_cst)
#define atomic_fetch_xor(pObject, operand) \
  atomic_fetch_xor_explicit(pObject, operand, memory_order_seq_cst)
#define atomic_load(pObject) atomic_load_explicit(pObject, memory_order_seq_cst)
#define atomic_store(pObject, desired) \
  atomic_store_explicit(pObject, desired, memory_order_seq_cst)
#define atomic_flag_test_and_set(x) \
  atomic_flag_test_and_set_explicit(x, memory_order_seq_cst)
#define atomic_flag_clear(x) atomic_flag_clear_explicit(x, memory_order_seq_cst)

#if defined(__CLANG_ATOMIC_BOOL_LOCK_FREE)

#define atomic_init(obj, value)    __c11_atomic_init(obj, value)
#define atomic_thread_fence(order) __c11_atomic_thread_fence(order)
#define atomic_signal_fence(order) __c11_atomic_signal_fence(order)
#define atomic_compare_exchange_strong_explicit(object, expected, desired, \
                                                success, failure)          \
  __c11_atomic_compare_exchange_strong(object, expected, desired, success, \
                                       failure)
#define atomic_compare_exchange_weak_explicit(object, expected, desired, \
                                              success, failure)          \
  __c11_atomic_compare_exchange_weak(object, expected, desired, success, \
                                     failure)
#define atomic_exchange_explicit(object, desired, order) \
  __c11_atomic_exchange(object, desired, order)
#define atomic_fetch_add_explicit(object, operand, order) \
  __c11_atomic_fetch_add(object, operand, order)
#define atomic_fetch_and_explicit(object, operand, order) \
  __c11_atomic_fetch_and(object, operand, order)
#define atomic_fetch_or_explicit(object, operand, order) \
  __c11_atomic_fetch_or(object, operand, order)
#define atomic_fetch_sub_explicit(object, operand, order) \
  __c11_atomic_fetch_sub(object, operand, order)
#define atomic_fetch_xor_explicit(object, operand, order) \
  __c11_atomic_fetch_xor(object, operand, order)
#define atomic_load_explicit(object, order) __c11_atomic_load(object, order)
#define atomic_store_explicit(object, desired, order) \
  __c11_atomic_store(object, desired, order)

#elif (__GNUC__ + 0) * 100 + (__GNUC_MINOR__ + 0) >= 407

#define atomic_init(obj, value)    ((void)(*(obj) = (value)))
#define atomic_thread_fence(order) __atomic_thread_fence(order)
#define atomic_signal_fence(order) __atomic_signal_fence(order)
#define atomic_compare_exchange_strong_explicit(pObject, pExpected, desired, \
                                                success, failure)            \
  __atomic_compare_exchange_n(pObject, pExpected, desired, 0, success, failure)
#define atomic_compare_exchange_weak_explicit(pObject, pExpected, desired, \
                                              success, failure)            \
  __atomic_compare_exchange_n(pObject, pExpected, desired, 1, success, failure)
#define atomic_exchange_explicit(pObject, desired, order) \
  __atomic_exchange_n(pObject, desired, order)
#define atomic_fetch_add_explicit(pObject, operand, order) \
  __atomic_fetch_add(pObject, operand, order)
#define atomic_fetch_and_explicit(pObject, operand, order) \
  __atomic_fetch_and(pObject, operand, order)
#define atomic_fetch_or_explicit(pObject, operand, order) \
  __atomic_fetch_or(pObject, operand, order)
#define atomic_fetch_sub_explicit(pObject, operand, order) \
  __atomic_fetch_sub(pObject, operand, order)
#define atomic_fetch_xor_explicit(pObject, operand, order) \
  __atomic_fetch_xor(pObject, operand, order)
#define atomic_load_explicit(pObject, order) __atomic_load_n(pObject, order)
#define atomic_store_explicit(pObject, desired, order) \
  __atomic_store_n(pObject, desired, order)

#elif (__GNUC__ + 0) * 100 + (__GNUC_MINOR__ + 0) >= 401

#define atomic_init(obj, value)    ((void)(*(obj) = (value)))
#define atomic_thread_fence(order) __sync_synchronize()
#define atomic_signal_fence(order) __asm__ volatile("" ::: "memory")
#define __atomic_apply_stride(object, operand) \
  (((__typeof__(*(object)))0) + (operand))
#define atomic_compare_exchange_strong_explicit(object, expected, desired,    \
                                                success_order, failure_order) \
  __extension__({                                                             \
    __typeof__(expected) __ep = (expected);                                   \
    __typeof__(*__ep) __e = *__ep;                                            \
    (void)(success_order);                                                    \
    (void)(failure_order);                                                    \
    (*__ep = __sync_val_compare_and_swap(object, __e, desired)) == __e;       \
  })
#define atomic_compare_exchange_weak_explicit(object, expected, desired,    \
                                              success_order, failure_order) \
  atomic_compare_exchange_strong_explicit(object, expected, desired,        \
                                          success_order, failure_order)
#if __has_builtin(__sync_swap)
#define atomic_exchange_explicit(object, desired, order) \
  ((void)(order), __sync_swap(object, desired))
#else
#define atomic_exchange_explicit(object, desired, order) \
  __extension__({                                        \
    __typeof__(object) __o = (object);                   \
    __typeof__(desired) __d = (desired);                 \
    (void)(order);                                       \
    __sync_synchronize();                                \
    __sync_lock_test_and_set(__o, __d);                  \
  })
#endif
#define atomic_fetch_add_explicit(object, operand, order) \
  ((void)(order),                                         \
   __sync_fetch_and_add(object, __atomic_apply_stride(object, operand)))
#define atomic_fetch_and_explicit(object, operand, order) \
  ((void)(order), __sync_fetch_and_and(object, operand))
#define atomic_fetch_or_explicit(object, operand, order) \
  ((void)(order), __sync_fetch_and_or(object, operand))
#define atomic_fetch_sub_explicit(object, operand, order) \
  ((void)(order),                                         \
   __sync_fetch_and_sub(object, __atomic_apply_stride(object, operand)))
#define atomic_fetch_xor_explicit(object, operand, order) \
  ((void)(order), __sync_fetch_and_xor(object, operand))
#define atomic_load_explicit(object, order) \
  ((void)(order), __sync_fetch_and_add(object, 0))
#define atomic_store_explicit(object, desired, order) \
  ((void)atomic_exchange_explicit(object, desired, order))

#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))

#define atomic_init(obj, value)    ((void)(*(obj) = (value)))
#define atomic_thread_fence(order) __asm__ volatile("mfence" ::: "memory")
#define atomic_signal_fence(order) __asm__ volatile("" ::: "memory")
#define atomic_compare_exchange_strong_explicit(object, expected, desired,    \
                                                success_order, failure_order) \
  __extension__({                                                             \
    char DidIt;                                                               \
    __typeof__(object) IfThing = (object);                                    \
    __typeof__(IfThing) IsEqualToMe = (expected);                             \
    __typeof__(*IfThing) ReplaceItWithMe = (desired), ax;                     \
    (void)(success_order);                                                    \
    (void)(failure_order);                                                    \
    __asm__ volatile("lock cmpxchg\t%3,(%1)\n\t"                              \
                     "setz\t%b0"                                              \
                     : "=q"(DidIt), "=r"(IfThing), "+a"(ax)                   \
                     : "r"(ReplaceItWithMe), "2"(*IsEqualToMe)                \
                     : "memory", "cc");                                       \
    *IsEqualToMe = ax;                                                        \
    DidIt;                                                                    \
  })
#define atomic_compare_exchange_weak_explicit(object, expected, desired,    \
                                              success_order, failure_order) \
  atomic_compare_exchange_strong_explicit(object, expected, desired,        \
                                          success_order, failure_order)
#define atomic_exchange_explicit(object, desired, order)                \
  __extension__({                                                       \
    __typeof__(object) __o = (object);                                  \
    __typeof__(*__o) __d = (desired);                                   \
    (void)(order);                                                      \
    __asm__ volatile("xchg\t%0,%1" : "=r"(__d), "+m"(*__o) : "0"(__d)); \
    __d;                                                                \
  })
#define atomic_fetch_add_explicit(object, operand, order)                    \
  __extension__({                                                            \
    __typeof__(object) __o = (object);                                       \
    __typeof__(*__o) __d = (desired);                                        \
    (void)(order);                                                           \
    __asm__ volatile("lock xadd\t%0,%1" : "=r"(__d), "+m"(*__o) : "0"(__d)); \
    __d;                                                                     \
  })
#define atomic_fetch_sub_explicit(object, operand, order) \
  atomic_fetch_add_explicit(object, -(operand), order)
#define atomic_load_explicit(object, order) \
  atomic_fetch_add_explicit(object, 0, order)
#define atomic_store_explicit(object, desired, order) \
  ((void)atomic_exchange_explicit(object, desired, order))

#else /* non-gcc or old gcc w/o x86 */
#error "atomic operations not supported with this compiler and/or architecture"
#endif

#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_BITS_ATOMIC_H_ */
