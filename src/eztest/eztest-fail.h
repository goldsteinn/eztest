#ifndef EZTEST_D_EZTEST_D_EZTEST_FAIL_H_
#define EZTEST_D_EZTEST_D_EZTEST_FAIL_H_

#include "eztest-lang.h"


EZTEST_NAMESPACE_BEGIN_

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ int
eztest_cur_test_getmod_failed(int eztest_set, int eztest_val) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    static int eztest_S_cur_test_failed = 0;
    if (eztest_set == 0) {
        return eztest_S_cur_test_failed;
    }
    eztest_S_cur_test_failed = eztest_val;
    return 0;
}

EZTEST_DISABLE_WUNUSED_FUNCTION_
EZTEST_PRIVATE_ void
eztest_cur_test_set_failed(EZTEST_VOID_ARG_) {
    (void)EZTEST_NS_ eztest_cur_test_getmod_failed(1, 1);
}
EZTEST_REENABLE_WUNUSED_FUNCTION_

EZTEST_PRIVATE_ void
eztest_cur_test_set_success(EZTEST_VOID_ARG_) {
    (void)EZTEST_NS_ eztest_cur_test_getmod_failed(1, 0);
}

EZTEST_PRIVATE_ int
eztest_cur_test_result(EZTEST_VOID_ARG_) {
    return EZTEST_NS_ eztest_cur_test_getmod_failed(0, 0);
}

EZTEST_NAMESPACE_END_

#endif
