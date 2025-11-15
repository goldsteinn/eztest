#ifndef EZTEST_D_EZTEST_D_EZTEST_RESULTS_H_
#define EZTEST_D_EZTEST_D_EZTEST_RESULTS_H_

#include "eztest-containers.h"
#include "eztest-duration.h"
#include "eztest-lang.h"
#include "eztest-libc.h"
#include "eztest-status.h"
EZTEST_NAMESPACE_BEGIN_

EZTEST_DISABLE_WPADDED_
struct eztest_results_t {
    EZTEST_DURATION_T_ eztest_suite_duration_;
    EZTEST_ARR_BUILDER_(eztest_stats_,
                        unsigned,
                        EZTEST_NS_ eztest_k_status_end);
    unsigned eztest_num_groups_;
};
EZTEST_REENABLE_WPADDED_
#define EZTEST_RESULTS_T_ EZTEST_STRUCT_NS_ eztest_results_t
#define EZTEST_RESULTS_T_INIT_                                                 \
    { EZTEST_DURATION_T_INIT_, EZTEST_ARR_T_INIT_, 0 }


EZTEST_PRIVATE_ unsigned
eztest_results_count_failed(const EZTEST_RESULTS_T_ * eztest_results) {

    unsigned eztest_cnt = 0;
    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
     */
    eztest_cnt +=
        eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_fail];
    eztest_cnt +=
        eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_fail_sig];
    eztest_cnt +=
        eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_fail_unknown];
    eztest_cnt +=
        eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_fail_timeout];
    /* NOLINTEND(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
     */
    /* NOLINTEND(llvmlibc-callee-namespace) */
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    return eztest_cnt;
}


EZTEST_PRIVATE_ unsigned
eztest_results_count_passed(const EZTEST_RESULTS_T_ * eztest_results) {

    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
     */
    return eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_passed];
    /* NOLINTEND(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
     */
    /* NOLINTEND(llvmlibc-callee-namespace) */
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
}


EZTEST_PRIVATE_ unsigned
eztest_results_count_disabled(const EZTEST_RESULTS_T_ * eztest_results) {

    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
     */
    return eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_disabled];
    /* NOLINTEND(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
     */
    /* NOLINTEND(llvmlibc-callee-namespace) */
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
}


EZTEST_PRIVATE_ unsigned
eztest_results_count_unknown(const EZTEST_RESULTS_T_ * eztest_results) {

    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
     */
    return eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_unknown];
    /* NOLINTEND(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
     */
    /* NOLINTEND(llvmlibc-callee-namespace) */
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
}


EZTEST_PRIVATE_ unsigned
eztest_results_count_internal_errors(const EZTEST_RESULTS_T_ * eztest_results) {

    unsigned eztest_cnt = 0;
    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
     */
    eztest_cnt +=
        eztest_results
            ->eztest_stats_[EZTEST_NS_ eztest_k_status_internal_error];
    eztest_cnt +=
        eztest_results
            ->eztest_stats_[EZTEST_NS_ eztest_k_status_internal_fatal_error];
    /* NOLINTEND(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
     */
    /* NOLINTEND(llvmlibc-callee-namespace) */
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    return eztest_cnt;
}

EZTEST_NAMESPACE_END_
#endif
