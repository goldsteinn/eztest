#ifndef EZTEST_D_EZTEST_D_EZTEST_DURATION_H_
#define EZTEST_D_EZTEST_D_EZTEST_DURATION_H_

#include "eztest-lang.h"
#include "eztest-libc-incs.h"
#include "eztest-time.h"

EZTEST_NAMESPACE_BEGIN_
/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
struct eztest_duration_t {
    EZTEST_TIME_T_ eztest_duration_start_;
    EZTEST_TIME_T_ eztest_duration_end_;

    long eztest_duration_failure_;
};
/* NOLINTEND(llvmlibc-inline-function-decl) */
#define EZTEST_DURATION_T_INIT_                                                \
 { EZTEST_TIME_T_INIT_, EZTEST_TIME_T_INIT_, -1L }
#define EZTEST_DURATION_T_ EZTEST_STRUCT_NS_ eztest_duration_t


EZTEST_PRIVATE_ int64_t
eztest_duration_timer_to_ms(const EZTEST_TIME_T_ * eztest_ts) {
    return EZTEST_TIME_AS_MS_(eztest_ts);
}

EZTEST_PRIVATE_ long
eztest_duration_timer_gettime(EZTEST_TIME_T_ * eztest_ts) {
    return EZTEST_CAST_(long, EZTEST_TIME_GET_(eztest_ts));
}


EZTEST_PRIVATE_ void
eztest_duration_start(EZTEST_DURATION_T_ * eztest_duration) {
    eztest_duration->eztest_duration_failure_ =
        EZTEST_NS_ eztest_duration_timer_gettime(
            &(eztest_duration->eztest_duration_start_));
}
EZTEST_PRIVATE_ void
eztest_duration_end(EZTEST_DURATION_T_ * eztest_duration) {
    unsigned long eztest_duration_result =
        EZTEST_CAST_(unsigned long, eztest_duration->eztest_duration_failure_);
    eztest_duration_result |= EZTEST_CAST_(
        unsigned long, EZTEST_NS_ eztest_duration_timer_gettime(
                           &(eztest_duration->eztest_duration_end_)));

    eztest_duration->eztest_duration_failure_ =
        EZTEST_CAST_(long, eztest_duration_result);
}


EZTEST_PRIVATE_ long
eztest_duration_ms(const EZTEST_DURATION_T_ * eztest_duration) {
    int64_t eztest_duration_complete = 0;
    if (eztest_duration->eztest_duration_failure_ != 0) {
        return -1L;
    }


    eztest_duration_complete = EZTEST_NS_ eztest_duration_timer_to_ms(
                                   &(eztest_duration->eztest_duration_end_)) -
                               EZTEST_NS_ eztest_duration_timer_to_ms(
                                   &(eztest_duration->eztest_duration_start_));

    EZTEST_DISABLE_WUSELESS_CAST_
    return EZTEST_CAST_(long, eztest_duration_complete);
    EZTEST_REENABLE_WUSELESS_CAST_
}


EZTEST_NAMESPACE_END_


#endif
