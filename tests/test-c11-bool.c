
#include "test-suite-common.h"

/* NOLINTBEGIN(misc-include-cleaner) */
/* NOLINTBEGIN(cppcoreguidelines-macro-usage) */
#ifndef EZTEST_DISABLE_WARNINGS
# define EZTEST_DISABLE_WARNINGS 1
#endif
/* NOLINTEND(cppcoreguidelines-macro-usage) */
#include "eztest/eztest.h"
/* NOLINTEND(misc-include-cleaner) */

#if TS_C_LANG_ >= 2011

# define TS_TRUE_  ((_Bool)1)
# define TS_FALSE_ ((_Bool)0)

/* NOLINTBEGIN(altera-unroll-loops) */
TS_DISABLE_WSUGGEST_ATTRIBUTE_PURE_
TEST(assert_true, is_okay) {
    _Bool val = TS_TRUE_;
    ASSERT_TRUE(val);
}

TEST(assert_true, is_fail) {
    _Bool val = TS_FALSE_;
    ASSERT_TRUE(val);
}

TEST(assert_false, is_okay) {
    _Bool val = TS_FALSE_;
    ASSERT_FALSE(val);
}

TEST(assert_false, is_fail) {
    _Bool val = TS_TRUE_;
    ASSERT_FALSE(val);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(assert_eq, is_okay) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_TRUE_;
    ASSERT_EQ(lhs, rhs);
    lhs = TS_FALSE_;
    rhs = TS_FALSE_;
    ASSERT_EQ(lhs, rhs);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(assert_eq, is0_fail) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_FALSE_;
    ASSERT_EQ(lhs, rhs);
}

TEST(assert_eq, is1_fail) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_TRUE_;
    ASSERT_EQ(lhs, rhs);
}

TEST(assert_ne, is0_fail) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_TRUE_;
    ASSERT_NE(lhs, rhs);
}

TEST(assert_ne, is1_fail) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_FALSE_;
    ASSERT_NE(lhs, rhs);
}

TEST(assert_ne, is_okay) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_FALSE_;
    ASSERT_NE(lhs, rhs);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(assert_ge, is_okay) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_TRUE_;
    ASSERT_GE(lhs, rhs);
    lhs = TS_FALSE_;
    rhs = TS_FALSE_;
    ASSERT_GE(lhs, rhs);
    lhs = TS_TRUE_;
    rhs = TS_FALSE_;
    ASSERT_GE(lhs, rhs);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(assert_ge, is_fail) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_TRUE_;
    ASSERT_GE(lhs, rhs);
}


TEST(assert_gt, is_okay) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_FALSE_;
    ASSERT_GT(lhs, rhs);
}

TEST(assert_gt, is0_fail) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_FALSE_;
    ASSERT_GT(lhs, rhs);
}

TEST(assert_gt, is1_fail) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_TRUE_;
    ASSERT_GT(lhs, rhs);
}

TEST(assert_gt, is2_fail) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_TRUE_;
    ASSERT_GT(lhs, rhs);
}


TEST(assert_lt, is_okay) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_TRUE_;
    ASSERT_LT(lhs, rhs);
}

TEST(assert_lt, is0_fail) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_FALSE_;
    ASSERT_LT(lhs, rhs);
}

TEST(assert_lt, is1_fail) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_TRUE_;
    ASSERT_LT(lhs, rhs);
}

TEST(assert_lt, is2_fail) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_FALSE_;
    ASSERT_LT(lhs, rhs);
}


/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(assert_le, is_okay) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_TRUE_;
    ASSERT_LE(lhs, rhs);
    lhs = TS_FALSE_;
    rhs = TS_FALSE_;
    ASSERT_LE(lhs, rhs);
    lhs = TS_TRUE_;
    rhs = TS_TRUE_;
    ASSERT_LE(lhs, rhs);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(assert_le, is_fail) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_FALSE_;
    ASSERT_LE(lhs, rhs);
}

TEST(expect_true, is_okay) {
    _Bool val = TS_TRUE_;
    EXPECT_TRUE(val);
}

TEST(expect_true, is_fail) {
    _Bool val = TS_FALSE_;
    EXPECT_TRUE(val);
}

TEST(expect_false, is_okay) {
    _Bool val = TS_FALSE_;
    EXPECT_FALSE(val);
}

TEST(expect_false, is_fail) {
    _Bool val = TS_TRUE_;
    EXPECT_FALSE(val);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(expect_eq, is_okay) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_TRUE_;
    EXPECT_EQ(lhs, rhs);
    lhs = TS_FALSE_;
    rhs = TS_FALSE_;
    EXPECT_EQ(lhs, rhs);
}

TEST(expect_eq, is_fail) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_FALSE_;
    EXPECT_EQ(lhs, rhs);
    lhs = TS_FALSE_;
    rhs = TS_TRUE_;
    EXPECT_EQ(lhs, rhs);
}

TEST(expect_ne, is_fail) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_TRUE_;
    EXPECT_NE(lhs, rhs);
    lhs = TS_FALSE_;
    rhs = TS_FALSE_;
    EXPECT_NE(lhs, rhs);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(expect_ne, is_okay) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_FALSE_;
    EXPECT_NE(lhs, rhs);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(expect_ge, is_okay) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_TRUE_;
    EXPECT_GE(lhs, rhs);
    lhs = TS_FALSE_;
    rhs = TS_FALSE_;
    EXPECT_GE(lhs, rhs);
    lhs = TS_TRUE_;
    rhs = TS_FALSE_;
    EXPECT_GE(lhs, rhs);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(expect_ge, is_fail) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_TRUE_;
    EXPECT_GE(lhs, rhs);
}


TEST(expect_gt, is_okay) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_FALSE_;
    EXPECT_GT(lhs, rhs);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(expect_gt, is_fail) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_FALSE_;
    EXPECT_GT(lhs, rhs);
    lhs = TS_FALSE_;
    rhs = TS_TRUE_;
    EXPECT_GT(lhs, rhs);
    lhs = TS_TRUE_;
    rhs = TS_TRUE_;
    EXPECT_GT(lhs, rhs);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(expect_lt, is_okay) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_TRUE_;
    EXPECT_LT(lhs, rhs);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(expect_lt, is_fail) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_TRUE_;
    EXPECT_LT(lhs, rhs);
    lhs = TS_TRUE_;
    rhs = TS_FALSE_;
    EXPECT_LT(lhs, rhs);
    lhs = TS_FALSE_;
    rhs = TS_FALSE_;
    EXPECT_LT(lhs, rhs);
}

TEST(expect_le, is_okay) {
    _Bool lhs = TS_FALSE_;
    _Bool rhs = TS_TRUE_;
    EXPECT_LE(lhs, rhs);
    lhs = TS_FALSE_;
    rhs = TS_FALSE_;
    EXPECT_LE(lhs, rhs);
    lhs = TS_TRUE_;
    rhs = TS_TRUE_;
    EXPECT_LE(lhs, rhs);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(expect_le, is_fail) {
    _Bool lhs = TS_TRUE_;
    _Bool rhs = TS_FALSE_;
    EXPECT_LE(lhs, rhs);
}
TS_REENABLE_WSUGGEST_ATTRIBUTE_PURE_
/* NOLINTEND(altera-unroll-loops) */

#endif
