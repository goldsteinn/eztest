#include "test-suite-common.h"


#ifndef EZTEST_DISABLE_WARNINGS
# define EZTEST_DISABLE_WARNINGS 1
#endif
#include "eztest/eztest.h"

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#include <stdio.h>
#include <stdlib.h>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */


/* NOLINTBEGIN(altera-unroll-loops) */
TS_DISABLE_WSTACK_PROTECTOR_
TS_DISABLE_WDISABLED_MACRO_EXPANSION_
static int
eval_once_int(void) {
    static int first = 0;
    if (first) {
        /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
         */
        (void)fprintf(stderr, "Evaluated Twice!");
        /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
         */
        abort();
    }
    first = 1;
    return 0;
}

static float
eval_once_float(void) {
    static int first = 0;
    if (first) {
        /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
         */
        (void)fprintf(stderr, "Evaluated Twice!");
        /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
         */
        abort();
    }
    first = 1;
    return 0.0F;
}

static double
eval_once_double(void) {
    static int first = 0;
    if (first) {
        /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
         */
        (void)fprintf(stderr, "Evaluated Twice!");
        /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
         */
        abort();
    }
    first = 1;
    TS_DISABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
    return 0.0;
    TS_REENABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
}

static const char *
eval_once_str(void) {
    static int first = 0;
    if (first) {
        /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
         */
        (void)fprintf(stderr, "Evaluated Twice!");
        /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
         */
        abort();
    }
    first = 1;
    return "abc";
}
TS_REENABLE_WDISABLED_MACRO_EXPANSION_

TS_DISABLE_WFLOAT_EQUAL_
TS_DISABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
TS_DISABLE_WDOUBLE_PROMOTION_
TS_DISABLE_WMISSING_NORETURN_
TS_DISABLE_WSUGGEST_ATTRIBUTE_PURE_
TEST(assert_false, assert_int_true_fail) {
    ASSERT_FALSE(1);
}

TEST(assert_false, assert_int_true_once_fail) {
    ASSERT_FALSE(!eval_once_int());
}


#if !EZTEST_ARCH_IS_X86_32_ || TS_USING_CLANG_
TEST(assert_false, assert_fp_true_fail) {
    TS_DISABLE_WLITERAL_CONVERSION_
    TS_DISABLE_WFLOAT_OVERFLOW_CONVERSION_
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_FALSE(1.5);
    /* NOLINTEND(*-magic-numbers) */
    TS_REENABLE_WFLOAT_OVERFLOW_CONVERSION_
    TS_REENABLE_WLITERAL_CONVERSION_
}
#endif

TEST(assert_false, assert_ptr_true_fail) {
    ASSERT_FALSE((void *)1UL);
}


TEST(assert_true, assert_int_false_fail) {
    ASSERT_TRUE(0);
}

TEST(assert_true, assert_int_false_once_fail) {
    ASSERT_TRUE(eval_once_int());
}

#if !EZTEST_ARCH_IS_X86_32_ || TS_USING_CLANG_
TEST(assert_true, assert_fp_false_fail) {
    TS_DISABLE_WFLOAT_CONVERSION_
    ASSERT_TRUE(0.0);
    TS_REENABLE_WFLOAT_CONVERSION_
}
#endif

TEST(assert_true, assert_ptr_false_fail) {
    ASSERT_TRUE(NULL);
}

TEST(assert_ne, assert_int_eq_fail) {
    ASSERT_NE(1, 1);
}


TEST(assert_ne, assert_int_eq_once_lhs_fail) {
    ASSERT_NE(eval_once_int(), 0);
}

TEST(assert_ne, assert_int_eq_once_rhs_fail) {
    ASSERT_NE(0, eval_once_int());
}

TEST(assert_ne, assert_fp_eq_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NE(1.5, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_ne, assert_null_eq_fail) {
    ASSERT_NE(NULL, NULL);
}

TEST(assert_ne, assert_ptr_eq_fail) {
    ASSERT_NE((void *)1UL, (void *)1UL);
}


TEST(assert_eq, assert_int_ne_fail) {
    ASSERT_EQ(1, 0);
}

TEST(assert_eq, assert_int_ne_lhs_once_fail) {
    ASSERT_EQ(eval_once_int(), 1);
}

TEST(assert_eq, assert_int_ne_once_rhs_fail) {
    ASSERT_EQ(1, eval_once_int());
}

TEST(assert_eq, assert_float_ne_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_EQ(1.5, 0.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_eq, assert_null_ne_fail) {
    ASSERT_EQ(NULL, (void *)1UL);
}

TEST(assert_eq, assert_ptr_eq_fail) {
    ASSERT_EQ((void *)2UL, (void *)1UL);
}


TEST(assert_le, assert_int_gt_once_lhs_fail) {
    ASSERT_LE(eval_once_int(), -1);
}

TEST(assert_le, assert_int_gt_once_rhs_fail) {
    ASSERT_LE(1, eval_once_int());
}

TEST(assert_le, assert_fp_gt_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LE(1.8, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_le, assert_null_gt_fail) {
    TS_DISABLE_WEXTRA_
    ASSERT_LE((void *)1UL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(assert_le, assert_ptr_gt_fail) {
    ASSERT_LE((void *)2UL, (void *)1UL);
}


TEST(assert_lt, assert_int_ge_once_lhs_fail) {
    ASSERT_LT(eval_once_int(), -1);
}

TEST(assert_lt, assert_int_ge_once_rhs_fail) {
    ASSERT_LT(1, eval_once_int());
}

TEST(assert_lt, assert_fp_ge_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LT(1.8, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_lt, assert_null_ge_fail) {
    TS_DISABLE_WEXTRA_
    ASSERT_LT(NULL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(assert_lt, assert_ptr_ge_fail) {
    ASSERT_LT((void *)2UL, (void *)1UL);
}


TEST(assert_ge, assert_int_lt_once_lhs_fail) {
    ASSERT_GE(eval_once_int(), 1);
}

TEST(assert_ge, assert_int_lt_once_rhs_fail) {
    ASSERT_GE(-1, eval_once_int());
}

TEST(assert_ge, assert_fp_lt_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GE(1.3, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_ge, assert_null_lt_fail) {
    TS_DISABLE_WEXTRA_
    ASSERT_GE(NULL, (void *)1UL);
    TS_REENABLE_WEXTRA_
}

TEST(assert_ge, assert_ptr_lt_fail) {
    ASSERT_GE((void *)1UL, (void *)2UL);
}


TEST(assert_gt, assert_int_le_once_lhs_fail) {
    ASSERT_GT(eval_once_int(), 0);
}

TEST(assert_gt, assert_int_le_once_rhs_fail) {
    ASSERT_GT(-1, eval_once_int());
}

TEST(assert_gt, assert_fp_le_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GT(1.5, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_gt, assert_null_le_fail) {
    TS_DISABLE_WEXTRA_
    ASSERT_GT(NULL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(assert_gt, assert_ptr_le_fail) {
    ASSERT_GT((void *)2UL, (void *)5UL);
}

TEST(assert_float_eq, assert_float_eq_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_FLOAT_EQ((float)1.6, (float)1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_float_eq, assert_float_eq_once_lhs_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_FLOAT_EQ(eval_once_float(), (float)0.1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_float_eq, assert_float_eq_once_rhs_fail) {
    ASSERT_FLOAT_EQ((float)1.0, eval_once_float());
}

TEST(assert_double_eq, assert_double_eq_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_DOUBLE_EQ((double)2.5, (double)1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_double_eq, assert_double_eq_once_lhs_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_DOUBLE_EQ(eval_once_double(), (double)0.9);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_double_eq, assert_double_eq_once_rhs_fail) {
    ASSERT_DOUBLE_EQ((double)2, eval_once_double());
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(assert_near, assert_double_near_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR((double)1.0, (double)1.5, (double)0.3);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_near, assert_float_near_fail) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR((float)1.0, (float)1.5, (float)0.49);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(assert_near, assert_float_near_once_op0_fail) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(eval_once_float(), (float)0.5, (float)0.25);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(assert_near, assert_float_near_once_op1_fail) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR((float)0.5, eval_once_float(), (float)0.45);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(assert_near, assert_float_near_once_op2_fail) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR((float)0.5, (float)0.51, eval_once_float());
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(assert_near, assert_double_near_once_op0_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(eval_once_double(), (double)3.5, (double)1.0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_near, assert_double_near_once_op1_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR((double)0.5, eval_once_double(), (double)0.0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_near, assert_double_near_once_op2_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR((double)0.2, (double)0.5, eval_once_double());
    /* NOLINTEND(*-magic-numbers) */
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(assert_strne, assert_str_eq_fail) {
    ASSERT_STRNE("12345", "12345");
}

TEST(assert_strne, assert_str_eq_eval_once_lhs_fail) {
    ASSERT_STRNE(eval_once_str(), "abc");
}

TEST(assert_strne, assert_str_eq_eval_once_rhs_fail) {
    ASSERT_STRNE("abc", eval_once_str());
}

TEST(assert_strcasene, assert_str_caseeq_fail) {
    ASSERT_STRCASENE("a12345", "A12345");
}

TEST(assert_strcasene, assert_str_caseeq_eval_once_lhs_fail) {
    ASSERT_STRCASENE(eval_once_str(), "aBC");
}

TEST(assert_strcasene, assert_str_caseeq_eval_once_rhs_fail) {
    ASSERT_STRCASENE("ABC", eval_once_str());
}

TEST(assert_streq, assert_str_ne_fail) {
    ASSERT_STREQ("1235", "12345");
}

TEST(assert_streq, assert_str_ne_eval_once_lhs_fail) {
    ASSERT_STREQ(eval_once_str(), "bac");
}

TEST(assert_streq, assert_str_ne_eval_once_rhs_fail) {
    ASSERT_STREQ("acb", eval_once_str());
}

TEST(assert_strcaseeq, assert_str_casene_fail) {
    ASSERT_STRCASEEQ("a12345 ", "A12345");
}

TEST(assert_strcaseeq, assert_str_casene_eval_once_lhs_fail) {
    ASSERT_STRCASEEQ(eval_once_str(), "ABD");
}

TEST(assert_strcaseeq, assert_str_casene_eval_once_rhs_fail) {
    ASSERT_STRCASEEQ(" ABC", eval_once_str());
}

TEST(expect_false, expect_int_true_fail) {
    EXPECT_FALSE(1);
}

TEST(expect_false, expect_int_true_once_fail) {
    EXPECT_FALSE(!eval_once_int());
}

#if !EZTEST_ARCH_IS_X86_32_ || TS_USING_CLANG_
TEST(expect_false, expect_fp_true_fail) {
    TS_DISABLE_WLITERAL_CONVERSION_
    TS_DISABLE_WFLOAT_OVERFLOW_CONVERSION_
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_FALSE(1.5);
    /* NOLINTEND(*-magic-numbers) */
    TS_REENABLE_WFLOAT_OVERFLOW_CONVERSION_
    TS_REENABLE_WLITERAL_CONVERSION_
}
#endif

TEST(expect_false, expect_ptr_true_fail) {
    EXPECT_FALSE((void *)1UL);
}


TEST(expect_true, expect_int_false_fail) {
    EXPECT_TRUE(0);
}

TEST(expect_true, expect_int_false_once_fail) {
    EXPECT_TRUE(eval_once_int());
}

#if !EZTEST_ARCH_IS_X86_32_ || TS_USING_CLANG_
TEST(expect_true, expect_fp_false_fail) {
    TS_DISABLE_WFLOAT_CONVERSION_
    EXPECT_TRUE(0.0);
    TS_REENABLE_WFLOAT_CONVERSION_
}
#endif

TEST(expect_true, expect_ptr_false_fail) {
    EXPECT_TRUE(NULL);
}

TEST(expect_ne, expect_int_eq_fail) {
    EXPECT_NE(1, 1);
}


TEST(expect_ne, expect_int_eq_once_lhs_fail) {
    EXPECT_NE(eval_once_int(), 0);
}

TEST(expect_ne, expect_int_eq_once_rhs_fail) {
    EXPECT_NE(0, eval_once_int());
}

TEST(expect_ne, expect_fp_eq_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NE(1.5, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_ne, expect_null_eq_fail) {
    EXPECT_NE(NULL, NULL);
}

TEST(expect_ne, expect_ptr_eq_fail) {
    EXPECT_NE((void *)1UL, (void *)1UL);
}


TEST(expect_eq, expect_int_ne_fail) {
    EXPECT_EQ(1, 0);
}

TEST(expect_eq, expect_int_ne_lhs_once_fail) {
    EXPECT_EQ(eval_once_int(), 1);
}

TEST(expect_eq, expect_int_ne_once_rhs_fail) {
    EXPECT_EQ(1, eval_once_int());
}

TEST(expect_eq, expect_float_ne_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_EQ(1.5, 0.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_eq, expect_null_ne_fail) {
    EXPECT_EQ(NULL, (void *)1UL);
}

TEST(expect_eq, expect_ptr_eq_fail) {
    EXPECT_EQ((void *)2UL, (void *)1UL);
}


TEST(expect_le, expect_int_gt_once_lhs_fail) {
    EXPECT_LE(eval_once_int(), -1);
}

TEST(expect_le, expect_int_gt_once_rhs_fail) {
    EXPECT_LE(1, eval_once_int());
}

TEST(expect_le, expect_fp_gt_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LE(1.8, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_le, expect_null_gt_fail) {
    TS_DISABLE_WEXTRA_
    EXPECT_LE((void *)1UL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(expect_le, expect_ptr_gt_fail) {
    EXPECT_LE((void *)2UL, (void *)1UL);
}


TEST(expect_lt, expect_int_ge_once_lhs_fail) {
    EXPECT_LT(eval_once_int(), -1);
}

TEST(expect_lt, expect_int_ge_once_rhs_fail) {
    EXPECT_LT(1, eval_once_int());
}

TEST(expect_lt, expect_fp_ge_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LT(1.8, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_lt, expect_null_ge_fail) {
    TS_DISABLE_WEXTRA_
    EXPECT_LT(NULL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(expect_lt, expect_ptr_ge_fail) {
    EXPECT_LT((void *)2UL, (void *)1UL);
}


TEST(expect_ge, expect_int_lt_once_lhs_fail) {
    EXPECT_GE(eval_once_int(), 1);
}

TEST(expect_ge, expect_int_lt_once_rhs_fail) {
    EXPECT_GE(-1, eval_once_int());
}

TEST(expect_ge, expect_fp_lt_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GE(1.3, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_ge, expect_null_lt_fail) {
    TS_DISABLE_WEXTRA_
    EXPECT_GE(NULL, (void *)1UL);
    TS_REENABLE_WEXTRA_
}

TEST(expect_ge, expect_ptr_lt_fail) {
    EXPECT_GE((void *)1UL, (void *)2UL);
}


TEST(expect_gt, expect_int_le_once_lhs_fail) {
    EXPECT_GT(eval_once_int(), 0);
}

TEST(expect_gt, expect_int_le_once_rhs_fail) {
    EXPECT_GT(-1, eval_once_int());
}

TEST(expect_gt, expect_fp_le_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GT(1.5, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_gt, expect_null_le_fail) {
    TS_DISABLE_WEXTRA_
    EXPECT_GT(NULL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(expect_gt, expect_ptr_le_fail) {
    EXPECT_GT((void *)2UL, (void *)5UL);
}

TEST(expect_float_eq, expect_float_eq_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_FLOAT_EQ((float)1.6, (float)1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_float_eq, expect_float_eq_once_lhs_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_FLOAT_EQ(eval_once_float(), (float)0.1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_float_eq, expect_float_eq_once_rhs_fail) {
    EXPECT_FLOAT_EQ((float)1.0, eval_once_float());
}

TEST(expect_double_eq, expect_double_eq_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_DOUBLE_EQ((double)2.5, (double)1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_double_eq, expect_double_eq_once_lhs_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_DOUBLE_EQ(eval_once_double(), (double)0.9);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_double_eq, expect_double_eq_once_rhs_fail) {
    EXPECT_DOUBLE_EQ((double)2, eval_once_double());
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(expect_near, expect_double_near_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((double)1.0, (double)1.5, (double)0.3);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_near, expect_float_near_fail) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((float)1.0, (float)1.5, (float)0.49);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(expect_near, expect_float_near_once_op0_fail) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(eval_once_float(), (float)0.5, (float)0.25);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(expect_near, expect_float_near_once_op1_fail) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((float)0.5, eval_once_float(), (float)0.45);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(expect_near, expect_float_near_once_op2_fail) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((float)0.5, (float)0.51, eval_once_float());
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(expect_near, expect_double_near_once_op0_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(eval_once_double(), (double)3.5, (double)1.0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_near, expect_double_near_once_op1_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((double)0.5, eval_once_double(), (double)0.0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_near, expect_double_near_once_op2_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((double)0.2, (double)0.5, eval_once_double());
    /* NOLINTEND(*-magic-numbers) */
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(expect_strne, expect_str_eq_fail) {
    EXPECT_STRNE("12345", "12345");
}

TEST(expect_strne, expect_str_eq_eval_once_lhs_fail) {
    EXPECT_STRNE(eval_once_str(), "abc");
}

TEST(expect_strne, expect_str_eq_eval_once_rhs_fail) {
    EXPECT_STRNE("abc", eval_once_str());
}

TEST(expect_strcasene, expect_str_caseeq_fail) {
    EXPECT_STRCASENE("a12345", "A12345");
}

TEST(expect_strcasene, expect_str_caseeq_eval_once_lhs_fail) {
    EXPECT_STRCASENE(eval_once_str(), "aBC");
}

TEST(expect_strcasene, expect_str_caseeq_eval_once_rhs_fail) {
    EXPECT_STRCASENE("ABC", eval_once_str());
}

TEST(expect_streq, expect_str_ne_fail) {
    EXPECT_STREQ("1235", "12345");
}

TEST(expect_streq, expect_str_ne_eval_once_lhs_fail) {
    EXPECT_STREQ(eval_once_str(), "bac");
}

TEST(expect_streq, expect_str_ne_eval_once_rhs_fail) {
    EXPECT_STREQ("acb", eval_once_str());
}

TEST(expect_strcaseeq, expect_str_casene_fail) {
    EXPECT_STRCASEEQ("a12345 ", "A12345");
}

TEST(expect_strcaseeq, expect_str_casene_eval_once_lhs_fail) {
    EXPECT_STRCASEEQ("a12345", "A12345");
    EXPECT_STRCASEEQ(eval_once_str(), "ABD");
    EXPECT_STRCASEEQ("a123456", "A123456");
}

TEST(expect_strcaseeq, expect_str_casene_eval_once_rhs_fail) {
    EXPECT_STRCASEEQ(" ABC", eval_once_str());
}
TS_REENABLE_WSUGGEST_ATTRIBUTE_PURE_
TS_REENABLE_WMISSING_NORETURN_
TS_REENABLE_WDOUBLE_PROMOTION_
TS_REENABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
TS_REENABLE_WFLOAT_EQUAL_
TS_REENABLE_WSTACK_PROTECTOR_
/* NOLINTEND(altera-unroll-loops) */
