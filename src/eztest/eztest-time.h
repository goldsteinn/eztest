#ifndef EZTEST_D_EZTEST_D_EZTEST_TIME_H_
#define EZTEST_D_EZTEST_D_EZTEST_TIME_H_

#include "eztest-compiler.h"
#include "eztest-lang.h"
#include "eztest-libc-incs.h"
#include "eztest-system.h"

#define EZTEST_CXX_HAS_TS_                                                     \
 (EZTEST_CXX_LANG_ >= 2020 ||                                                  \
  (EZTEST_CXX_LANG_ >= 2017 && EZTEST_USING_GCC_ >= EZTEST_VERNUM_(9, 0, 0)))

#if EZTEST_CXX_HAS_TS_ || (EZTEST_C_LANG_ >= 2011) ||                          \
    (EZTEST_POSIX_VERSION_ >= 199309L)

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
# if EZTEST_CXX_LANG_
#  include <ctime>
# else
#  include <time.h>
# endif
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

# define EZTEST_TIME_IS_TIMESPEC_ 1

# if EZTEST_CXX_HAS_TS_
#  define EZTEST_TIME_T_ EZTEST_STD_NS_ timespec
# else
#  define EZTEST_TIME_T_ EZTEST_STRUCT_ timespec
# endif

#elif EZTEST_OS_LINUX_
# define EZTEST_TIME_IS_TIMESPEC_ 0

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
# include <sys/time.h>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */
# define EZTEST_TIME_T_ EZTEST_STRUCT_ timeval

#endif

#define EZTEST_TIME_T_INIT_                                                    \
 { 0, 0 }

#define EZTEST_TIME_GET_(tsp)   EZTEST_NS_ eztest_time_get(tsp)
#define EZTEST_TIME_AS_MS_(tsp) EZTEST_NS_ eztest_time_timespec_to_ms(tsp)


EZTEST_NAMESPACE_BEGIN_

#if EZTEST_CXX_HAS_TS_ || EZTEST_C_LANG_ >= 2011
EZTEST_PRIVATE_ int
eztest_time_get(EZTEST_TIME_T_ * eztest_tsp) {
    return EZTEST_CAST_(
        int, EZTEST_STD_NS_ timespec_get(eztest_tsp, TIME_UTC) != TIME_UTC);
}
#elif EZTEST_POSIX_VERSION_ >= 199309L
EZTEST_PRIVATE_ int
eztest_time_get(EZTEST_TIME_T_ * eztest_tsp) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    return clock_gettime(CLOCK_MONOTONIC, eztest_tsp);
    /* NOLINTEND(llvmlibc-callee-namespace) */
}
#elif EZTEST_OS_LINUX_
EZTEST_PRIVATE_ int
eztest_time_get(EZTEST_TIME_T_ * eztest_tsp) {
    return EZTEST_CAST_(int, gettimeofday(eztest_tsp, EZTEST_NULL_));
}
#endif

#define EZTEST_MSEC_TO_SEC_L_ EZTEST_CAST_(int64_t, 1000)
#define EZTEST_USEC_TO_SEC_L_ (EZTEST_MSEC_TO_SEC_L_ * EZTEST_MSEC_TO_SEC_L_)
EZTEST_PRIVATE_
int64_t
eztest_time_timespec_to_ms(const EZTEST_TIME_T_ * eztest_ts) {
#if EZTEST_TIME_IS_TIMESPEC_
    return EZTEST_CAST_(int64_t, eztest_ts->tv_sec) * EZTEST_MSEC_TO_SEC_L_ +
           EZTEST_CAST_(int64_t, eztest_ts->tv_nsec) / (EZTEST_USEC_TO_SEC_L_);
#else
    return EZTEST_CAST_(int64_t, eztest_ts->tv_sec) * EZTEST_MSEC_TO_SEC_L_ +
           EZTEST_CAST_(int64_t, eztest_ts->tv_usec) / (EZTEST_MSEC_TO_SEC_L_);
#endif
}
EZTEST_NAMESPACE_END_

#endif
