#ifndef EZTEST_D_EZTEST_D_EZTEST_MAIN_H_
#define EZTEST_D_EZTEST_D_EZTEST_MAIN_H_

#include "eztest-lang.h"
#include "eztest-list.h"
#include "eztest-reqs.h"
#include "eztest-results.h"
#include "eztest-run.h"

EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_
/* NOLINTBEGIN(misc-definitions-in-headers) */
int
main(int argc, char ** argv) {
    /* NOLINTEND(misc-definitions-in-headers) */
    EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_
    int               eztest_had_err = 0;
    EZTEST_RESULTS_T_ eztest_results = EZTEST_RESULTS_T_INIT_;
    (void)argc;
    (void)argv;
    (void)EZTEST_PRINTF_("Running main() from %s\n", __FILE__);

    (void)EZTEST_FFLUSH_(stdout);
    eztest_had_err = EZTEST_NS_ eztest_run_tests(
        EZTEST_NS_ eztest_list_get_head(), &eztest_results);

    (void)EZTEST_FFLUSH_(EZTEST_STDOUT_);
    if (eztest_had_err != 0) {
        return -1;
    }

    eztest_had_err = EZTEST_NS_ eztest_summarize_and_get_result(
        EZTEST_NS_ eztest_list_get_head(), &eztest_results);
    (void)EZTEST_FFLUSH_(stdout);
    return eztest_had_err;
}


#endif
