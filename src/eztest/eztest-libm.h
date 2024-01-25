#ifndef EZTEST_D_EZTEST_D_EZTEST_LIBM_H_
#define EZTEST_D_EZTEST_D_EZTEST_LIBM_H_

#include "eztest-lang.h"

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#if EZTEST_CXX_LANG_
# include <cmath> /* abs */
#else
# include <math.h> /* fabs */
#endif
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

#if EZTEST_CXX_LANG_
# define EZTEST_ABS_(x) EZTEST_STD_NS_ abs(x)
#else
# define EZTEST_ABS_(x) EZTEST_STD_NS_ fabs(x)
#endif

#define EZTEST_ISNAN_(x) EZTEST_STD_NS_ isnan(x)
#endif
