#ifndef EZTEST_D_EZTEST_D_EZTEST_LIST_H_
#define EZTEST_D_EZTEST_D_EZTEST_LIST_H_ 1

#include "eztest-lang.h"
#include "eztest-test.h"

EZTEST_NAMESPACE_BEGIN_
EZTEST_DISABLE_WPADDED_
typedef struct eztest_list {
    EZTEST_NS_ eztest_test_t * eztest_tests_begin_;
    EZTEST_NS_ eztest_test_t * eztest_tests_end_;
    unsigned                   eztest_ntests_;
} eztest_list_t;
EZTEST_REENABLE_WPADDED_

#if EZTEST_INSERT_SORTED_
static int
eztest_list_insert_test(EZTEST_NS_ eztest_list_t * eztest_list,
                        EZTEST_NS_ eztest_test_t * eztest_newest_test) {
    EZTEST_NS_ eztest_test_t *eztest_cur, *eztest_prev;
    const char * eztest_new_group   = eztest_newest_test->eztest_group_;
    int          eztest_found_group = 0;
    ++eztest_list->eztest_ntests_;
    if (eztest_list->eztest_tests_begin_ == EZTEST_NULL_) {
        eztest_list->eztest_tests_begin_ = eztest_newest_test;
        //        eztest_list->eztest_tests_end_   = eztest_newest_test;
        eztest_newest_test->eztest_next_ = EZTEST_NULL_;
        return 0;
    }

    eztest_prev = EZTEST_NULL_;
    for (eztest_cur = eztest_list->eztest_tests_begin_;
         eztest_cur != EZTEST_NULL_; eztest_cur = eztest_cur->eztest_next_) {
        if (!!EZTEST_STRCMP_(eztest_cur->eztest_group_, eztest_new_group) ==
            eztest_found_group) {
            if (eztest_found_group == 0) {
                eztest_found_group = 1;
            }
            else {
                break;
            }
        }
        eztest_prev = eztest_cur;
    }


    eztest_newest_test->eztest_next_ = eztest_cur;
    eztest_prev->eztest_next_        = eztest_newest_test;
    if (eztest_prev == eztest_list->eztest_tests_end_) {
        eztest_list->eztest_tests_end_ = eztest_newest_test;
    }

    return 0;
}
#else
static int
eztest_list_insert_test(EZTEST_NS_ eztest_list_t * eztest_list,
                        EZTEST_NS_ eztest_test_t * eztest_newest_test) {
    if (eztest_list->eztest_tests_begin_ == EZTEST_NULL_) {
        eztest_list->eztest_tests_begin_ = eztest_newest_test;
    }
    else if (eztest_list->eztest_tests_end_ != EZTEST_NULL_) {
        eztest_list->eztest_tests_end_->eztest_next_ = eztest_newest_test;
    }
    eztest_list->eztest_tests_end_ = eztest_newest_test;
    ++eztest_list->eztest_ntests_;
    return 0;
}
#endif


EZTEST_NAMESPACE_END_

#endif
