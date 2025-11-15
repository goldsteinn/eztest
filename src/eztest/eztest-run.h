#ifndef EZTEST_D_EZTEST_D_EZTEST_RUN_H_
#define EZTEST_D_EZTEST_D_EZTEST_RUN_H_

#include "eztest-algo.h"
#include "eztest-duration.h"
#include "eztest-fail.h"
#include "eztest-group-it.h"
#include "eztest-lang.h"
#include "eztest-libc.h"
#include "eztest-list.h"
#include "eztest-proc.h"
#include "eztest-results.h"
#include "eztest-status.h"
#include "eztest-test.h"
#include "eztest-time.h"


EZTEST_NAMESPACE_BEGIN_

#define EZTEST_IO_SUITE_PREFIX_    "[==========] "
#define EZTEST_IO_STATUS_PREFIX_   "[----------] "
#define EZTEST_IO_RUN_PREFIX_      "[ RUN      ] "
#define EZTEST_IO_OK_PREFIX_       "[       OK ] "
#define EZTEST_IO_FAIL_PREFIX_     "[  FAILED  ] "
#define EZTEST_IO_DISABLED_PREFIX_ "[ DISABLED ] "
#define EZTEST_IO_TIMEOUT_PREFIX_  "[  TIMEOUT ] "
#define EZTEST_IO_BAD_PREFIX_      "[  BAD     ] "
#define EZTEST_IO_PASS_PREFIX_     "[  PASSED  ] "

EZTEST_PRIVATE_ int
eztest_run_user_test_function(const EZTEST_TEST_T_ * eztest_test) {
    EZTEST_NS_ eztest_cur_test_set_success();
    /* Run test in the child.  */
    eztest_test->eztest_func_();
    return EZTEST_NS_ eztest_cur_test_result();
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
EZTEST_PRIVATE_ unsigned
eztest_run_test(const EZTEST_TEST_T_ * eztest_test) {
    /* NOLINTEND(readability-function-cognitive-complexity) */

    EZTEST_STATUS_T_ eztest_test_ret = EZTEST_NS_ eztest_k_status_unknown;
    EZTEST_PROC_RESULT_T_ eztest_proc_result = EZTEST_PROC_RESULT_T_INIT_;
    if (EZTEST_NS_ eztest_proc_run(&EZTEST_NS_ eztest_run_user_test_function,
                                   eztest_test, eztest_test->eztest_timeout_ms_,
                                   &eztest_proc_result) != 0) {
        eztest_test_ret = EZTEST_NS_ eztest_k_status_internal_error;
    }
    else if (EZTEST_NS_ eztest_proc_returned(&eztest_proc_result) != 0) {
        if (EZTEST_NS_ eztest_proc_return_value(&eztest_proc_result) == 0) {
            eztest_test_ret = EZTEST_NS_ eztest_k_status_passed;
        }
        else {
            eztest_test_ret = EZTEST_NS_ eztest_k_status_fail;
        }
    }
    else if (EZTEST_NS_ eztest_proc_signalled(&eztest_proc_result) != 0) {
        (void)EZTEST_PRINTF_(
            "Test died with signal: [%d] -> %s\n",
            EZTEST_NS_ eztest_proc_signal_num(&eztest_proc_result),
            EZTEST_NS_ eztest_proc_signal_str(&eztest_proc_result));
        eztest_test_ret = EZTEST_NS_ eztest_k_status_fail_sig;
    }
    else if (EZTEST_NS_ eztest_proc_timed_out(&eztest_proc_result) != 0) {
        eztest_test_ret = EZTEST_NS_ eztest_k_status_fail_timeout;
    }
    else if (EZTEST_NS_ eztest_proc_unknown_result(&eztest_proc_result) != 0) {
        eztest_test_ret = EZTEST_NS_ eztest_k_status_fail_unknown;
    }

    switch (eztest_test_ret) {
        case EZTEST_NS_ eztest_k_status_passed:
            (void)EZTEST_PRINTF_(EZTEST_IO_OK_PREFIX_ "%s.%s",
                                 eztest_test->eztest_group_,
                                 eztest_test->eztest_name_);
            break;
        case EZTEST_NS_ eztest_k_status_internal_error:
        case EZTEST_NS_ eztest_k_status_internal_fatal_error:
            (void)EZTEST_PRINTF_(EZTEST_IO_BAD_PREFIX_ "%s.%s",
                                 eztest_test->eztest_group_,
                                 eztest_test->eztest_name_);
            break;
        case EZTEST_NS_ eztest_k_status_fail:
        case EZTEST_NS_ eztest_k_status_fail_sig:
        case EZTEST_NS_ eztest_k_status_fail_unknown:
            (void)EZTEST_PRINTF_(EZTEST_IO_FAIL_PREFIX_ "%s.%s",
                                 eztest_test->eztest_group_,
                                 eztest_test->eztest_name_);
            break;
        case EZTEST_NS_ eztest_k_status_fail_timeout:
            (void)EZTEST_PRINTF_(
                EZTEST_IO_TIMEOUT_PREFIX_ "%s.%s (After %d ms)\n",
                eztest_test->eztest_group_, eztest_test->eztest_name_,
                eztest_test->eztest_timeout_ms_);
            break;
        default:
            (void)EZTEST_PRINTF_(
                "Internal Error -- "
                "Unknown test result\n");
            (void)EZTEST_PRINTF_(EZTEST_IO_BAD_PREFIX_ "%s.%s",
                                 eztest_test->eztest_group_,
                                 eztest_test->eztest_name_);
            break;
    }
    if (eztest_test_ret != EZTEST_NS_ eztest_k_status_fail_timeout) {
        (void)EZTEST_PRINTF_(" (%ld ms)\n", EZTEST_NS_ eztest_proc_duration_ms(
                                                &eztest_proc_result));
    }


    return eztest_test_ret;
}


EZTEST_PRIVATE_ int
eztest_run_tests(const EZTEST_LIST_T_ * eztest_tests_base,
                 EZTEST_RESULTS_T_ *    eztest_results) {

    EZTEST_TEST_T_ *   eztest_test           = EZTEST_NULL_;
    int                eztest_new_group      = 1;
    const char *       eztest_new_group_str  = EZTEST_NULL_;
    const char *       eztest_last_group_str = EZTEST_NULL_;
    EZTEST_GROUP_IT_T_ eztest_group_it       = EZTEST_GROUP_IT_T_INIT_;
    EZTEST_DURATION_T_ eztest_group_time     = EZTEST_DURATION_T_INIT_;
    EZTEST_NS_ eztest_group_it_init(&eztest_group_it, eztest_tests_base);

    /* TODO: "Running <NTESTS Total>  from <NGROUPS Total> test suites.". */
    (void)EZTEST_PRINTF_(
        EZTEST_IO_SUITE_PREFIX_ "Running %lu tests\n",
        EZTEST_CAST_(unsigned long, eztest_tests_base->eztest_ntests_));
    (void)EZTEST_PRINTF_(EZTEST_IO_STATUS_PREFIX_
                         "Global test environment set-up.\n");
    EZTEST_NS_ eztest_duration_start(&(eztest_results->eztest_suite_duration_));
    for (eztest_test = EZTEST_NS_ eztest_group_it_begin(&eztest_group_it);;
         eztest_test = EZTEST_NS_ eztest_group_it_next(&eztest_group_it,
                                                       &eztest_new_group)) {
        unsigned eztest_run_result = 0;
        if (eztest_test == EZTEST_NULL_ || eztest_new_group != 0) {
            if (eztest_last_group_str != EZTEST_NULL_) {
                EZTEST_NS_ eztest_duration_end(&eztest_group_time);
                /* TODO: "<NTESTS PGroup> tests from <PGroup> (\d ms total). */
                (void)EZTEST_PRINTF_(
                    EZTEST_IO_STATUS_PREFIX_
                    "Ran tests from %s (%ld ms total)\n\n",
                    eztest_last_group_str,
                    EZTEST_NS_ eztest_duration_ms(&eztest_group_time));
                eztest_last_group_str = EZTEST_NULL_;
            }
            if (eztest_test == EZTEST_NULL_) {
                break;
            }
            eztest_new_group_str = eztest_test->eztest_group_;
        }
        if (!EZTEST_NS_ eztest_test_is_init(eztest_test)) {
            continue;
        }
        if (EZTEST_STARTSWITH_("DISABLED_", eztest_test->eztest_name_)) {
            eztest_run_result = EZTEST_NS_ eztest_k_status_disabled;
        }
        else {
            if (eztest_new_group_str != EZTEST_NULL_) {
                /* TODO: "<NTESTS Group> tests from <Group>".  */
                (void)EZTEST_PRINTF_(EZTEST_IO_STATUS_PREFIX_
                                     "Running tests from %s\n",
                                     eztest_new_group_str);
                eztest_last_group_str = eztest_new_group_str;
                eztest_new_group_str  = EZTEST_NULL_;
                ++eztest_results->eztest_num_groups_;
                EZTEST_NS_ eztest_duration_start(&eztest_group_time);
            }

            (void)EZTEST_PRINTF_(EZTEST_IO_RUN_PREFIX_ "%s.%s\n",
                                 eztest_test->eztest_group_,
                                 eztest_test->eztest_name_);
            (void)EZTEST_FFLUSH_(stdout);
            eztest_run_result = EZTEST_NS_ eztest_run_test(eztest_test);
            (void)EZTEST_FFLUSH_(stdout);
            /* Fatal error in test suite occurred.  */
            if (eztest_run_result ==
                EZTEST_NS_ eztest_k_status_internal_fatal_error) {
                (void)EZTEST_PRINTF_(
                    "\n[----------] Global test environment tear-down\n");
                return 1;
            }
        }
        /* Clamp return value.  */
        eztest_run_result = EZTEST_MIN_(
            eztest_run_result,
            EZTEST_CAST_(unsigned, EZTEST_NS_ eztest_k_status_unknown));

        eztest_test->eztest_status_ = eztest_run_result;
        EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
        /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index) */
        /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
         */
        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        ++eztest_results->eztest_stats_[eztest_run_result];
        /* NOLINTEND(llvmlibc-callee-namespace) */
        /* NOLINTEND(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
         */
        /* NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index) */
        EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    }
    EZTEST_NS_ eztest_duration_end(&(eztest_results->eztest_suite_duration_));
    EZTEST_NS_ eztest_group_it_deinit(&eztest_group_it);
    (void)EZTEST_PRINTF_("[----------] Global test environment tear-down\n");
    return 0;
}


EZTEST_PRIVATE_ int
eztest_summarize_and_get_result(const EZTEST_LIST_T_ *    eztest_tests_base,
                                const EZTEST_RESULTS_T_ * eztest_results) {
    unsigned eztest_fail_count     = 0;
    unsigned eztest_etc_count      = 0;
    unsigned eztest_disabled_count = 0;
    int      eztest_extra_nl       = 0;
    eztest_disabled_count =
        EZTEST_NS_ eztest_results_count_disabled(eztest_results);
    (void)EZTEST_PRINTF_(
        EZTEST_IO_SUITE_PREFIX_ "%u tests from %u suites ran. (%ld ms total)\n",
        eztest_tests_base->eztest_ntests_ - eztest_disabled_count,
        eztest_results->eztest_num_groups_,
        EZTEST_NS_ eztest_duration_ms(
            &(eztest_results->eztest_suite_duration_)));

    (void)EZTEST_PRINTF_(
        EZTEST_IO_PASS_PREFIX_ "%u tests.\n",
        EZTEST_NS_ eztest_results_count_passed(eztest_results));

    eztest_fail_count = EZTEST_NS_ eztest_results_count_failed(eztest_results);
    if (eztest_fail_count != 0) {
        int                eztest_name_fmt_len = 0;
        EZTEST_TEST_T_ *   eztest_test         = EZTEST_NULL_;
        int                eztest_new_group    = 1;
        EZTEST_GROUP_IT_T_ eztest_group_it     = EZTEST_GROUP_IT_T_INIT_;
        EZTEST_NS_ eztest_group_it_init(&eztest_group_it, eztest_tests_base);

        (void)EZTEST_PRINTF_(
            EZTEST_IO_FAIL_PREFIX_ "%u tests.\n",
            EZTEST_NS_ eztest_results_count_failed(eztest_results));
        for (eztest_test = EZTEST_NS_ eztest_group_it_begin(&eztest_group_it);
             eztest_test != EZTEST_NULL_;
             eztest_test = EZTEST_NS_ eztest_group_it_next(&eztest_group_it,
                                                           &eztest_new_group)) {
            if (eztest_new_group != 0) {
                static const size_t eztest_k_name_padding = 40;
                const size_t        eztest_group_len      = EZTEST_STRNLEN_(
                    eztest_test->eztest_group_, eztest_k_name_padding);
                eztest_name_fmt_len =
                    EZTEST_CAST_(int, eztest_k_name_padding - eztest_group_len);
            }
            if (EZTEST_NS_ eztest_test_failed(eztest_test)) {
                (void)EZTEST_PRINTF_(
                    EZTEST_IO_FAIL_PREFIX_ "%s.%-*s: %s\n",
                    eztest_test->eztest_group_, eztest_name_fmt_len,
                    eztest_test->eztest_name_,
                    EZTEST_NS_ eztest_test_failure_str(eztest_test));
                eztest_test->eztest_status_ =
                    EZTEST_NS_ eztest_k_status_counted;
            }
        }
        EZTEST_NS_ eztest_group_it_deinit(&eztest_group_it);
        (void)EZTEST_PRINTF_("\n%u FAILED TESTS\n", eztest_fail_count);
    }
    eztest_extra_nl = 0;
    if (eztest_disabled_count != 0) {
        eztest_extra_nl = 1;
        (void)EZTEST_PRINTF_("  YOU HAVE %u DISABLED TESTS\n",
                             eztest_disabled_count);
    }
    eztest_etc_count =
        EZTEST_NS_ eztest_results_count_internal_errors(eztest_results);
    if (eztest_etc_count != 0) {
        eztest_extra_nl = 1;
        (void)EZTEST_PRINTF_("  %u TESTS DIDN'T RUN DUE TO INTERNAL ERRORS\n",
                             eztest_etc_count);
    }
    eztest_etc_count = EZTEST_NS_ eztest_results_count_unknown(eztest_results);
    if (eztest_etc_count != 0) {
        eztest_extra_nl = 1;
        (void)EZTEST_PRINTF_("  %u TESTS HAD UNKNOWN RESULT\n",
                             eztest_etc_count);
    }
    if (eztest_extra_nl != 0) {
        (void)EZTEST_PRINTF_("\n");
    }
    return EZTEST_CAST_(int, eztest_fail_count != 0);
}

EZTEST_NAMESPACE_END_

#endif
