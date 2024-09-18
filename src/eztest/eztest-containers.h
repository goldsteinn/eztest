#ifndef EZTEST_D_EZTEST_D_EZTEST_CONTAINERS_H_
#define EZTEST_D_EZTEST_D_EZTEST_CONTAINERS_H_

#include "eztest-lang.h"
#include "eztest-libc.h"


#if EZTEST_CXX_LANG_ >= 2011
/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
# include <array>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */
# define EZTEST_ARR_BUILDER_(name, T, k_n) EZTEST_STD_NS_ array<T, k_n> name
# define EZTEST_ARR_T_INIT_                                                    \
     {                                                                         \
         { 0 }                                                                 \
     }
#else
# define EZTEST_ARR_BUILDER_(name, T, k_n) T name[k_n]
# define EZTEST_ARR_T_INIT_                { 0 }
#endif

#endif
