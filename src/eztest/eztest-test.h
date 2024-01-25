#ifndef EZTEST_D_EZTEST_D_EZTEST_TEST_H_
#define EZTEST_D_EZTEST_D_EZTEST_TEST_H_

#include "eztest-compiler.h"
#include "eztest-lang.h"
#include "eztest-libc.h"
#include "eztest-status.h"
#include "eztest-struct-padding.h"
EZTEST_NAMESPACE_BEGIN_


typedef void (*eztest_test_func)(EZTEST_VOID_ARG_);


/* Struct with info setup by the EZTEST*(...) macro.  */
/* NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) */
struct eztest_test_t {
    /* Next test.  */
    EZTEST_STRUCT_ eztest_test_t * eztest_next_;
    /* Function to test.  */
    EZTEST_NS_ eztest_test_func eztest_func_;
    /* Group this test is a part of.  */
    const char * const eztest_group_;
    /* Name of this test.  */
    const char * const eztest_name_;
    /* Line number this test is defined at (determines order).  */
    const unsigned eztest_lineno_;
    /* Test timeout.  */
    const int eztest_timeout_ms_;
    /* Status of this test (mutable).  */
    EZTEST_STATUS_T_ eztest_status_;
    /* Padding.  */
    EZTEST_STRUCT_INTT_PADDING_
};
#define EZTEST_TEST_T_ EZTEST_STRUCT_NS_ eztest_test_t
/* NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) */


EZTEST_PRIVATE_ int
eztest_test_failed(const EZTEST_TEST_T_ * eztest_test) {
    
    return EZTEST_NS_ eztest_status_is_failure(eztest_test->eztest_status_);
}


EZTEST_PRIVATE_ int
eztest_test_is_init(const EZTEST_TEST_T_ * eztest_test) {
    
    return EZTEST_NS_ eztest_status_is_init(eztest_test->eztest_status_);
}


EZTEST_PRIVATE_ const char *
eztest_test_failure_str(const EZTEST_TEST_T_ * eztest_test) {
    
    return EZTEST_NS_ eztest_status_failure_str(eztest_test->eztest_status_);
}


EZTEST_NAMESPACE_END_

#endif
