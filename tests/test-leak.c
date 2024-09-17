#include "test-suite-common.h"

#ifndef EZTEST_DISABLE_WARNINGS
# define EZTEST_DISABLE_WARNINGS 1
#endif
#include "eztest/eztest.h"

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#include <stdlib.h>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

/* NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables) */
extern void * global_p;
void *        global_p = TS_NULL_;
/* NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables) */
TEST(leaks, leaks_alsan_leakfailsan) {
    /* NOLINTBEGIN(*-magic-numbers) */
    global_p = malloc(10);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(concurrency-mt-unsafe) */
    ASSERT_NE(global_p, TS_NULL_);
    /* NOLINTEND(concurrency-mt-unsafe) */
    global_p = TS_NULL_;
}


TEST(leaks, leaks_assert_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    global_p = malloc(10);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(concurrency-mt-unsafe) */
    ASSERT_EQ(global_p, TS_NULL_);
    /* NOLINTEND(concurrency-mt-unsafe) */
    global_p = TS_NULL_;
}

TEST(leaks, leaks_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    global_p = malloc(10);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(concurrency-mt-unsafe) */
    ASSERT_NE(global_p, TS_NULL_);
    /* NOLINTEND(concurrency-mt-unsafe) */
    free(global_p);
    global_p = TS_NULL_;
}
