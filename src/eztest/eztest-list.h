#ifndef EZTEST_D_EZTEST_D_EZTEST_LIST_H_
#define EZTEST_D_EZTEST_D_EZTEST_LIST_H_

#include "eztest-lang.h"
#include "eztest-struct-padding.h"
#include "eztest-test.h"

EZTEST_NAMESPACE_BEGIN_

struct eztest_list_t {
    EZTEST_TEST_T_ * eztest_tests_begin_;
    unsigned         eztest_ntests_;
    EZTEST_STRUCT_INTT_PADDING_
};
#define EZTEST_LIST_T_ EZTEST_STRUCT_NS_ eztest_list_t
#define EZTEST_LIST_T_INIT_                                                    \
    { EZTEST_NULL_, 0, EZTEST_STRUCT_INTT_PADDING_INIT_ }


/*
 * TODO: Just sort this before running tests with merge sort. This is O(n^2)
 * insert in sorted order.
 */


EZTEST_DISABLE_WUNUSED_FUNCTION_
EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_
EZTEST_PRIVATE_ int
eztest_list_insert_test(EZTEST_LIST_T_ * eztest_list,
                        EZTEST_TEST_T_ * eztest_newest_test) {

    EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_
    EZTEST_TEST_T_ * eztest_cur         = EZTEST_NULL_;
    EZTEST_TEST_T_ * eztest_prev        = EZTEST_NULL_;
    unsigned         eztest_ntests      = eztest_list->eztest_ntests_;
    const char *     eztest_new_group   = eztest_newest_test->eztest_group_;
    int              eztest_found_group = 0;

    eztest_list->eztest_ntests_ = eztest_ntests + 1U;
    eztest_prev                 = EZTEST_NULL_;
    for (eztest_cur = eztest_list->eztest_tests_begin_; eztest_ntests != 0;
         --eztest_ntests, eztest_cur = eztest_cur->eztest_next_) {
        /* TODO: Move these pragmas to EZTEST_STRCMP_ (clang doesn't seem to be
         * picking them up) */
        EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
        int eztest_at_new_group = EZTEST_CAST_(
            int,
            EZTEST_STRCMP_(eztest_cur->eztest_group_, eztest_new_group) != 0);
        EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
        if (eztest_at_new_group == eztest_found_group) {
            if (eztest_found_group == 0) {
                eztest_found_group = 1;
            }
            else {
                break;
            }
        }
        eztest_prev = eztest_cur;
    }
    if (eztest_prev == EZTEST_NULL_) {
        eztest_list->eztest_tests_begin_ = eztest_newest_test;
    }
    else {
        eztest_prev->eztest_next_ = eztest_newest_test;
    }
    eztest_newest_test->eztest_next_ = eztest_cur;
    return 0;
}
EZTEST_REENABLE_WUNUSED_FUNCTION_

EZTEST_PRIVATE_ EZTEST_LIST_T_ *
eztest_list_get_head(EZTEST_VOID_ARG_) {
    static EZTEST_LIST_T_ eztest_S_tests_base = EZTEST_LIST_T_INIT_;
    return &eztest_S_tests_base;
}


EZTEST_NAMESPACE_END_

#endif
