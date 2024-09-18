#ifndef EZTEST_D_EZTEST_D_EZTEST_ALGO_H_
#define EZTEST_D_EZTEST_D_EZTEST_ALGO_H_

#include "eztest-lang.h"

#if EZTEST_CXX_LANG_
/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
# include <algorithm>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */
# define EZTEST_MIN_(eztest_lhs, eztest_rhs)                                   \
     EZTEST_STD_NS_ min(eztest_lhs, eztest_rhs)
#else
# define EZTEST_MIN_(eztest_lhs, eztest_rhs)                                   \
     ((eztest_lhs) < (eztest_rhs) ? (eztest_lhs) : (eztest_rhs))
#endif

#endif
