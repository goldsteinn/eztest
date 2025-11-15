#ifndef EZTEST_D_EZTEST_D_EZTEST_STATUS_H_
#define EZTEST_D_EZTEST_D_EZTEST_STATUS_H_

#include "eztest-lang.h"

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#if EZTEST_CXX_LANG_
# include <climits> /* CHAR_BIT.  */
#else
# include <limits.h> /* CHAR_BIT.  */
#endif
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

EZTEST_NAMESPACE_BEGIN_

typedef unsigned eztest_status_t;
/* NOLINTBEGIN(cppcoreguidelines-use-enum-class) */
enum {
    eztest_k_status_init,
    eztest_k_status_counted,
    eztest_k_status_running,
    eztest_k_status_passed,
    eztest_k_status_disabled,
    eztest_k_status_internal_error,
    eztest_k_status_internal_fatal_error,
    eztest_k_status_fail,
    eztest_k_status_fail_sig,
    eztest_k_status_fail_unknown,
    eztest_k_status_fail_timeout,
    eztest_k_status_unknown,
    eztest_k_status_end
};
/* NOLINTEND(cppcoreguidelines-use-enum-class) */
#define EZTEST_STATUS_T_ EZTEST_NS_ eztest_status_t


EZTEST_PRIVATE_ EZTEST_STATUS_T_
eztest_status_to_mask(EZTEST_STATUS_T_ eztest_status) {

    return 1U << (eztest_status & (CHAR_BIT * sizeof(EZTEST_STATUS_T_) - 1));
}


EZTEST_PRIVATE_ EZTEST_STATUS_T_
eztest_status_fail_mask(EZTEST_VOID_ARG_) {

    return EZTEST_NS_ eztest_status_to_mask(EZTEST_NS_ eztest_k_status_fail) |
           EZTEST_NS_ eztest_status_to_mask(
               EZTEST_NS_ eztest_k_status_fail_sig) |
           EZTEST_NS_ eztest_status_to_mask(
               EZTEST_NS_ eztest_k_status_fail_unknown) |
           EZTEST_NS_ eztest_status_to_mask(
               EZTEST_NS_ eztest_k_status_fail_timeout);
}


EZTEST_PRIVATE_ int
eztest_status_is_failure(EZTEST_STATUS_T_ eztest_status) {

    return EZTEST_CAST_(int, (EZTEST_NS_ eztest_status_to_mask(eztest_status) &
                              EZTEST_NS_ eztest_status_fail_mask()) != 0);
}


EZTEST_PRIVATE_ int
eztest_status_is_init(EZTEST_STATUS_T_ eztest_status) {

    return EZTEST_CAST_(int, eztest_status == EZTEST_NS_ eztest_k_status_init);
}


EZTEST_PRIVATE_ const char *
eztest_status_failure_str(EZTEST_STATUS_T_ eztest_status) {

    switch (eztest_status) {
        case EZTEST_NS_ eztest_k_status_fail:
            return "(Assert Failure)";
        case EZTEST_NS_ eztest_k_status_fail_sig:
            return "(Signal)";
        case EZTEST_NS_ eztest_k_status_fail_unknown:
            return "(Unknown)";
        case EZTEST_NS_ eztest_k_status_fail_timeout:
            return "(Timeout)";
        default:
            return "(BAD)";
    }
}


EZTEST_NAMESPACE_END_

#endif
