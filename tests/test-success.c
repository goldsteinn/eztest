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
TS_DISABLE_WSUGGEST_ATTRIBUTE_PURE_
TEST(assert_true, assert_int_true_okay) {
    ASSERT_TRUE(1);
}

TEST(assert_true, assert_int_true_once_okay) {
    ASSERT_TRUE(!eval_once_int());
}

#if !EZTEST_ARCH_IS_X86_32_ || TS_USING_CLANG_
TEST(assert_true, assert_fp_true_okay) {
    TS_DISABLE_WLITERAL_CONVERSION_
    TS_DISABLE_WFLOAT_OVERFLOW_CONVERSION_
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_TRUE(1.5);
    /* NOLINTEND(*-magic-numbers) */
    TS_REENABLE_WFLOAT_OVERFLOW_CONVERSION_
    TS_REENABLE_WLITERAL_CONVERSION_
}
#endif

TEST(assert_true, assert_ptr_true_okay) {
    ASSERT_TRUE((void *)1UL);
}


TEST(assert_false, assert_int_false_okay) {
    ASSERT_FALSE(0);
}

TEST(assert_false, assert_int_false_once_okay) {
    ASSERT_FALSE(eval_once_int());
}

#if !EZTEST_ARCH_IS_X86_32_ || TS_USING_CLANG_
TEST(assert_false, assert_fp_false_okay) {
    TS_DISABLE_WFLOAT_CONVERSION_
    ASSERT_FALSE(0.0);
    TS_REENABLE_WFLOAT_CONVERSION_
}
#endif

TEST(assert_false, assert_ptr_false_okay) {
    ASSERT_FALSE(NULL);
}

TEST(assert_eq, assert_int_eq_okay) {
    ASSERT_EQ(1, 1);
}


TEST(assert_eq, assert_int_eq_once_lhs_okay) {
    ASSERT_EQ(eval_once_int(), 0);
}

TEST(assert_eq, assert_int_eq_once_rhs_okay) {
    ASSERT_EQ(0, eval_once_int());
}

TEST(assert_eq, assert_fp_eq_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_EQ(1.5, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_eq, assert_null_eq_okay) {
    ASSERT_EQ(NULL, NULL);
}

TEST(assert_eq, assert_ptr_eq_okay) {
    ASSERT_EQ((void *)1UL, (void *)1UL);
}


TEST(assert_ne, assert_int_ne_okay) {
    ASSERT_NE(1, 0);
}

TEST(assert_ne, assert_int_ne_lhs_once_okay) {
    ASSERT_NE(eval_once_int(), 1);
}

TEST(assert_ne, assert_int_ne_once_rhs_okay) {
    ASSERT_NE(1, eval_once_int());
}

TEST(assert_ne, assert_float_ne_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NE(1.5, 0.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_ne, assert_null_ne_okay) {
    ASSERT_NE(NULL, (void *)1UL);
}

TEST(assert_ne, assert_ptr_eq_okay) {
    ASSERT_NE((void *)2UL, (void *)1UL);
}


TEST(assert_gt, assert_int_gt_once_lhs_okay) {
    ASSERT_GT(eval_once_int(), -1);
}

TEST(assert_gt, assert_int_gt_once_rhs_okay) {
    ASSERT_GT(1, eval_once_int());
}

TEST(assert_gt, assert_fp_gt_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GT(1.8, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_gt, assert_null_gt_okay) {
    TS_DISABLE_WEXTRA_
    ASSERT_GT((void *)1UL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(assert_gt, assert_ptr_gt_okay) {
    ASSERT_GT((void *)2UL, (void *)1UL);
}


TEST(assert_ge, assert_int_ge_once_lhs_okay) {
    ASSERT_GE(eval_once_int(), -1);
}

TEST(assert_ge, assert_int_ge_once_rhs_okay) {
    ASSERT_GE(1, eval_once_int());
}

TEST(assert_ge, assert_fp_ge_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GE(1.8, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_ge, assert_null_ge_okay) {
    TS_DISABLE_WEXTRA_
    ASSERT_GE(NULL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(assert_ge, assert_ptr_ge_okay) {
    ASSERT_GE((void *)2UL, (void *)1UL);
}


TEST(assert_lt, assert_int_lt_once_lhs_okay) {
    ASSERT_LT(eval_once_int(), 1);
}

TEST(assert_lt, assert_int_lt_once_rhs_okay) {
    ASSERT_LT(-1, eval_once_int());
}

TEST(assert_lt, assert_fp_lt_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LT(1.3, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_lt, assert_null_lt_okay) {
    TS_DISABLE_WEXTRA_
    ASSERT_LT(NULL, (void *)1UL);
    TS_REENABLE_WEXTRA_
}

TEST(assert_lt, assert_ptr_lt_okay) {
    ASSERT_LT((void *)1UL, (void *)2UL);
}


TEST(assert_le, assert_int_le_once_lhs_okay) {
    ASSERT_LE(eval_once_int(), 0);
}

TEST(assert_le, assert_int_le_once_rhs_okay) {
    ASSERT_LE(-1, eval_once_int());
}

TEST(assert_le, assert_fp_le_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LE(1.5, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_le, assert_null_le_okay) {
    TS_DISABLE_WEXTRA_
    ASSERT_LE(NULL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(assert_le, assert_ptr_le_okay) {
    ASSERT_LE((void *)2UL, (void *)5UL);
}

TEST(assert_float_eq, assert_float_eq_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_FLOAT_EQ((float)1.5, (float)1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_float_eq, assert_float_eq_once_lhs_okay) {
    ASSERT_FLOAT_EQ(eval_once_float(), (float)0);
}

TEST(assert_float_eq, assert_float_eq_once_rhs_okay) {
    ASSERT_FLOAT_EQ((float)0, eval_once_float());
}

TEST(assert_double_eq, assert_double_eq_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_DOUBLE_EQ((double)1.5, (double)1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_double_eq, assert_double_eq_once_lhs_okay) {
    ASSERT_DOUBLE_EQ(eval_once_double(), (double)0);
}

TEST(assert_double_eq, assert_double_eq_once_rhs_okay) {
    ASSERT_DOUBLE_EQ((double)0, eval_once_double());
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(assert_near, assert_double_near_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(-(double)1.0, -(double)1.5, (double)1.0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_near, assert_float_near_okay) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR((float)1.0, (float)1.5, (float)1.0);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(assert_near, assert_float_near_once_op0_okay) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(eval_once_float(), (float)0.5, -(float)1.0);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(assert_near, assert_float_near_once_op1_okay) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR((float)0.5, eval_once_float(), (float)1.0);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(assert_near, assert_float_near_once_op2_okay) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(-(float)0.5, -(float)0.5, eval_once_float());
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(assert_near, assert_double_near_once_op0_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(eval_once_double(), (double)0.5, (double)1.0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_near, assert_double_near_once_op1_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR((double)0.5, eval_once_double(), (double)1.0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(assert_near, assert_double_near_once_op2_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR((double)0.5, (double)0.5, eval_once_double());
    /* NOLINTEND(*-magic-numbers) */
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(assert_streq, assert_str_eq_okay) {
    ASSERT_STREQ("12345", "12345");
}

TEST(assert_streq, assert_str_eq_eval_once_lhs_okay) {
    ASSERT_STREQ(eval_once_str(), "abc");
}

TEST(assert_streq, assert_str_eq_eval_once_rhs_okay) {
    ASSERT_STREQ("abc", eval_once_str());
}

TEST(assert_strcaseeq, assert_str_caseeq_okay) {
    ASSERT_STRCASEEQ("a12345", "A12345");
}

TEST(assert_strcaseeq, assert_str_caseeq_eval_once_lhs_okay) {
    ASSERT_STRCASEEQ(eval_once_str(), "aBC");
}

TEST(assert_strcaseeq, assert_str_caseeq_eval_once_rhs_okay) {
    ASSERT_STRCASEEQ("ABC", eval_once_str());
}

TEST(assert_strne, assert_str_ne_okay) {
    ASSERT_STRNE("1235", "12345");
}

TEST(assert_strne, assert_str_ne_eval_once_lhs_okay) {
    ASSERT_STRNE(eval_once_str(), "bac");
}

TEST(assert_strne, assert_str_ne_eval_once_rhs_okay) {
    ASSERT_STRNE("acb", eval_once_str());
}

TEST(assert_strcasene, assert_str_casene_okay) {
    ASSERT_STRCASENE("a12345 ", "A12345");
}

TEST(assert_strcasene, assert_str_casene_eval_once_lhs_okay) {
    ASSERT_STRCASENE(eval_once_str(), "ABD");
}

TEST(assert_strcasene, assert_str_casene_eval_once_rhs_okay) {
    ASSERT_STRCASENE(" ABC", eval_once_str());
}

TEST(expect_true, expect_int_true_okay) {
    EXPECT_TRUE(1);
}

TEST(expect_true, expect_int_true_once_okay) {
    EXPECT_TRUE(!eval_once_int());
}

#if !EZTEST_ARCH_IS_X86_32_ || TS_USING_CLANG_
TEST(expect_true, expect_fp_true_okay) {
    TS_DISABLE_WLITERAL_CONVERSION_
    TS_DISABLE_WFLOAT_OVERFLOW_CONVERSION_
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_TRUE(1.5);
    /* NOLINTEND(*-magic-numbers) */
    TS_REENABLE_WFLOAT_OVERFLOW_CONVERSION_
    TS_REENABLE_WLITERAL_CONVERSION_
}
#endif

TEST(expect_true, expect_ptr_true_okay) {
    EXPECT_TRUE((void *)1UL);
}


TEST(expect_false, expect_int_false_okay) {
    EXPECT_FALSE(0);
}

TEST(expect_false, expect_int_false_once_okay) {
    EXPECT_FALSE(eval_once_int());
}

#if !EZTEST_ARCH_IS_X86_32_ || TS_USING_CLANG_
TEST(expect_false, expect_fp_false_okay) {
    TS_DISABLE_WFLOAT_CONVERSION_
    EXPECT_FALSE(0.0);
    TS_REENABLE_WFLOAT_CONVERSION_
}
#endif

TEST(expect_false, expect_ptr_false_okay) {
    EXPECT_FALSE(NULL);
}

TEST(expect_eq, expect_int_eq_okay) {
    EXPECT_EQ(1, 1);
}


TEST(expect_eq, expect_int_eq_once_lhs_okay) {
    EXPECT_EQ(eval_once_int(), 0);
}

TEST(expect_eq, expect_int_eq_once_rhs_okay) {
    EXPECT_EQ(0, eval_once_int());
}

TEST(expect_eq, expect_fp_eq_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_EQ(1.5, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_eq, expect_null_eq_okay) {
    EXPECT_EQ(NULL, NULL);
}

TEST(expect_eq, expect_ptr_eq_okay) {
    EXPECT_EQ((void *)1UL, (void *)1UL);
}


TEST(expect_ne, expect_int_ne_okay) {
    EXPECT_NE(1, 0);
}

TEST(expect_ne, expect_int_ne_lhs_once_okay) {
    EXPECT_NE(eval_once_int(), 1);
}

TEST(expect_ne, expect_int_ne_once_rhs_okay) {
    EXPECT_NE(1, eval_once_int());
}

TEST(expect_ne, expect_float_ne_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NE(1.5, 0.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_ne, expect_null_ne_okay) {
    EXPECT_NE(NULL, (void *)1UL);
}

TEST(expect_ne, expect_ptr_eq_okay) {
    EXPECT_NE((void *)2UL, (void *)1UL);
}


TEST(expect_gt, expect_int_gt_once_lhs_okay) {
    EXPECT_GT(eval_once_int(), -1);
}

TEST(expect_gt, expect_int_gt_once_rhs_okay) {
    EXPECT_GT(1, eval_once_int());
}

TEST(expect_gt, expect_fp_gt_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GT(1.8, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_gt, expect_null_gt_okay) {
    TS_DISABLE_WEXTRA_
    EXPECT_GT((void *)1UL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(expect_gt, expect_ptr_gt_okay) {
    EXPECT_GT((void *)2UL, (void *)1UL);
}


TEST(expect_ge, expect_int_ge_once_lhs_okay) {
    EXPECT_GE(eval_once_int(), -1);
}

TEST(expect_ge, expect_int_ge_once_rhs_okay) {
    EXPECT_GE(1, eval_once_int());
}

TEST(expect_ge, expect_fp_ge_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GE(1.8, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_ge, expect_null_ge_okay) {
    TS_DISABLE_WEXTRA_
    EXPECT_GE(NULL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(expect_ge, expect_ptr_ge_okay) {
    EXPECT_GE((void *)2UL, (void *)1UL);
}


TEST(expect_lt, expect_int_lt_once_lhs_okay) {
    EXPECT_LT(eval_once_int(), 1);
}

TEST(expect_lt, expect_int_lt_once_rhs_okay) {
    EXPECT_LT(-1, eval_once_int());
}

TEST(expect_lt, expect_fp_lt_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LT(1.3, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_lt, expect_null_lt_okay) {
    TS_DISABLE_WEXTRA_
    EXPECT_LT(NULL, (void *)1UL);
    TS_REENABLE_WEXTRA_
}

TEST(expect_lt, expect_ptr_lt_okay) {
    EXPECT_LT((void *)1UL, (void *)2UL);
}


TEST(expect_le, expect_int_le_once_lhs_okay) {
    EXPECT_LE(eval_once_int(), 0);
}

TEST(expect_le, expect_int_le_once_rhs_okay) {
    EXPECT_LE(-1, eval_once_int());
}

TEST(expect_le, expect_fp_le_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LE(1.5, 1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_le, expect_null_le_okay) {
    TS_DISABLE_WEXTRA_
    EXPECT_LE(NULL, NULL);
    TS_REENABLE_WEXTRA_
}

TEST(expect_le, expect_ptr_le_okay) {
    EXPECT_LE((void *)2UL, (void *)5UL);
}

TEST(expect_float_eq, expect_float_eq_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_FLOAT_EQ((float)1.5, (float)1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_float_eq, expect_float_eq_once_lhs_okay) {
    EXPECT_FLOAT_EQ(eval_once_float(), (float)0);
}

TEST(expect_float_eq, expect_float_eq_once_rhs_okay) {
    EXPECT_FLOAT_EQ((float)0, eval_once_float());
}

TEST(expect_double_eq, expect_double_eq_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_DOUBLE_EQ((double)1.5, (double)1.5);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_double_eq, expect_double_eq_once_lhs_okay) {
    EXPECT_DOUBLE_EQ(eval_once_double(), (double)0);
}

TEST(expect_double_eq, expect_double_eq_once_rhs_okay) {
    EXPECT_DOUBLE_EQ((double)0, eval_once_double());
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(expect_near, expect_double_near_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((double)1.0, (double)1.5, (double)1.0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_near, expect_float_near_okay) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((float)1.0, (float)1.5, (float)1.0);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(expect_near, expect_float_near_once_op0_okay) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(eval_once_float(), (float)0.5, (float)1.0);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(expect_near, expect_float_near_once_op1_okay) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((float)0.5, eval_once_float(), (float)1.0);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(expect_near, expect_float_near_once_op2_okay) {
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((float)0.5, (float)0.5, eval_once_float());
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
}

TEST(expect_near, expect_double_near_once_op0_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(eval_once_double(), (double)0.5, (double)1.0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_near, expect_double_near_once_op1_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((double)0.5, eval_once_double(), (double)1.0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(expect_near, expect_double_near_once_op2_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR((double)0.5, (double)0.5, eval_once_double());
    /* NOLINTEND(*-magic-numbers) */
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(expect_streq, expect_str_eq_okay) {
    EXPECT_STREQ("12345", "12345");
}

TEST(expect_streq, expect_str_eq_eval_once_lhs_okay) {
    EXPECT_STREQ(eval_once_str(), "abc");
}

TEST(expect_streq, expect_str_eq_eval_once_rhs_okay) {
    EXPECT_STREQ("abc", eval_once_str());
}

TEST(expect_strcaseeq, expect_str_caseeq_okay) {
    EXPECT_STRCASEEQ("a12345", "A12345");
}

TEST(expect_strcaseeq, expect_str_caseeq_eval_once_lhs_okay) {
    EXPECT_STRCASEEQ(eval_once_str(), "aBC");
}

TEST(expect_strcaseeq, expect_str_caseeq_eval_once_rhs_okay) {
    EXPECT_STRCASEEQ("ABC", eval_once_str());
}

TEST(expect_strne, expect_str_ne_okay) {
    EXPECT_STRNE("1235", "12345");
}

TEST(expect_strne, expect_str_ne_eval_once_lhs_okay) {
    EXPECT_STRNE(eval_once_str(), "bac");
}

TEST(expect_strne, expect_str_ne_eval_once_rhs_okay) {
    EXPECT_STRNE("acb", eval_once_str());
}

TEST(expect_strcasene, expect_str_casene_okay) {
    EXPECT_STRCASENE("a12345 ", "A12345");
}

TEST(expect_strcasene, expect_str_casene_eval_once_lhs_okay) {
    EXPECT_STRCASENE(eval_once_str(), "ABD");
}

TEST(expect_strcasene, expect_str_casene_eval_once_rhs_okay) {
    EXPECT_STRCASENE(" ABC", eval_once_str());
}
TS_REENABLE_WSUGGEST_ATTRIBUTE_PURE_
TS_REENABLE_WDOUBLE_PROMOTION_
TS_REENABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
TS_REENABLE_WFLOAT_EQUAL_
TS_REENABLE_WSTACK_PROTECTOR_
/* NOLINTEND(altera-unroll-loops) */
