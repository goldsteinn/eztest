#ifndef EZTEST_D_EZTEST_D_EZTEST_GROUP_IT_H_
#define EZTEST_D_EZTEST_D_EZTEST_GROUP_IT_H_

#include "eztest-lang.h"
#include "eztest-test.h"

EZTEST_NAMESPACE_BEGIN_
struct eztest_group_it_t {
    EZTEST_TEST_T_ * eztest_cur_test_;
};
#define EZTEST_GROUP_IT_T_INIT_ { EZTEST_NULL_ }
#define EZTEST_GROUP_IT_T_      EZTEST_STRUCT_NS_ eztest_group_it_t


EZTEST_PRIVATE_ void
eztest_group_it_deinit(EZTEST_GROUP_IT_T_ * eztest_group_it) {
    (void)eztest_group_it;
}


EZTEST_PRIVATE_ void
eztest_group_it_init(EZTEST_GROUP_IT_T_ *   eztest_group_it,
                     const EZTEST_LIST_T_ * eztest_tests_base) {
    if (eztest_tests_base == EZTEST_NULL_) {
        eztest_group_it->eztest_cur_test_ = EZTEST_NULL_;
    }
    else {
        eztest_group_it->eztest_cur_test_ =
            eztest_tests_base->eztest_tests_begin_;
    }
}


EZTEST_PRIVATE_ EZTEST_TEST_T_ *
eztest_group_it_next(EZTEST_GROUP_IT_T_ * eztest_group_it,
                     int *                eztest_new_group_out) {

    EZTEST_TEST_T_ * eztest_cur_test  = EZTEST_NULL_;
    const char *     eztest_cur_group = EZTEST_NULL_;
    eztest_cur_test                   = eztest_group_it->eztest_cur_test_;
    if (eztest_cur_test == EZTEST_NULL_) {
        *eztest_new_group_out = 0;
        return EZTEST_NULL_;
    }

    eztest_cur_group = eztest_cur_test->eztest_group_;
    eztest_cur_test  = eztest_cur_test->eztest_next_;
    if (eztest_cur_test == EZTEST_NULL_) {
        *eztest_new_group_out = 0;
    }
    else {
        /* TODO: Move these pragmas to EZTEST_STRCMP_ (clang doesn't seem to be
         * picking them up) */
        EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
        *eztest_new_group_out = EZTEST_CAST_(
            int, EZTEST_STRCMP_(eztest_cur_group,
                                eztest_cur_test->eztest_group_) != 0);
        EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    }

    eztest_group_it->eztest_cur_test_ = eztest_cur_test;
    return eztest_cur_test;
}


EZTEST_PRIVATE_ EZTEST_TEST_T_ *
eztest_group_it_begin(EZTEST_GROUP_IT_T_ * eztest_group_it) {

    return eztest_group_it->eztest_cur_test_;
}

EZTEST_NAMESPACE_END_

#endif
