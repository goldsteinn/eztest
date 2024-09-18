#include "test-suite-common.h"

#ifndef EZTEST_DISABLE_WARNINGS
# define EZTEST_DISABLE_WARNINGS 1
#endif
#include "eztest/eztest.h"

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#include <signal.h>
/* NOLINTBEGIN(misc-include-cleaner) */
#include <stdint.h>
/* NOLINTEND(misc-include-cleaner) */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */


/* NOLINTBEGIN(altera-unroll-loops) */
TS_DISABLE_WSTACK_PROTECTOR_
TS_DISABLE_WDOUBLE_PROMOTION_
TS_DISABLE_WFLOAT_EQUAL_
TS_DISABLE_WFLOAT_CONVERSION_
TS_DISABLE_WMISSING_NORETURN_
TS_DISABLE_WLITERAL_CONVERSION_
TS_DISABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
TS_DISABLE_WSUGGEST_ATTRIBUTE_PURE_

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
static inline uint64_t
ts_uint64_c(uint32_t hibits, uint32_t lobits) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    uint64_t complete = (uint64_t)hibits;
    /* NOLINTBEGIN(*-magic-numbers) */
    complete <<= 32U;
    /* NOLINTEND(*-magic-numbers) */
    complete |= ((uint64_t)lobits);
    return complete;
}


TEST_TIMED(timeouts, 1ms_simple_timefail, 1) {
    while (1) {
        /* NOLINTBEGIN(hicpp-no-assembler) */
        __asm__ volatile("" ::: "memory");
        /* NOLINTEND(hicpp-no-assembler) */
    }
}


TEST(c, assert_strcasene00_fail) {
    ASSERT_STRCASENE("", "");
}

/* NOLINTBEGIN(misc-include-cleaner) */
TEST(fpe, assert_float_eq0_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0xdeadbeef;
    bits1 = 0xdeadbeee;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    ASSERT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, assert_float_eq1_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0xdeadbeed;
    bits1 = 0xdeadbeef;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, assert_float_eq2_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0xdeadbeef;
    bits1 = 0xdeadbeec;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1);
}


TEST(fpe, assert_float_eq3_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0xdeadbeeb;
    bits1 = 0xdeadbeef;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, assert_float_eq4_fail) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0xdeadbeef;
    bits1 = 0x5eadbeef;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, assert_float_eq5_fail) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x7fc00000;
    bits1 = 0x7fc00000;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1, "Oh not: %f, %f\n", fp0, fp1);
}

TEST(fpe, assert_float_eq6_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000000;
    bits1 = 0x00000000;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1, "oh yeah: %f, %u\n", fp0, bits0);
}

TEST(fpe, assert_float_eq7_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000000;
    bits1 = 0x80000000;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1);
}
TEST(fpe, assert_float_eq8_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000000;
    bits1 = 0x00000001;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, assert_float_eq9_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000004;
    bits1 = 0x00000000;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1);
}


TEST(fpe, assert_float_eq10_fail) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000005;
    bits1 = 0x00000000;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, assert_float_eq11_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000002;
    bits1 = 0x80000002;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, assert_float_eq12_fail) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000003;
    bits1 = 0x80000002;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    ASSERT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, assert_float_eq13_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    ASSERT_FLOAT_EQ(fp0, 1.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    ASSERT_FLOAT_EQ(fp0, 2.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    ASSERT_FLOAT_EQ(1.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq16_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    ASSERT_FLOAT_EQ(2.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    ASSERT_FLOAT_EQ(fp0, 1.23);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq18_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    ASSERT_FLOAT_EQ(fp0, 2.23);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    ASSERT_FLOAT_EQ(1.23, fp0);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq20_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    ASSERT_FLOAT_EQ(2.23, fp0);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq21_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    ASSERT_FLOAT_EQ(fp0, 2.23L);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq22_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    ASSERT_FLOAT_EQ(2.23L, fp0);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, assert_double_eq0_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeee);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeef);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq1_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeec);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq2_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeea);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq3_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbee9);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq4_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbee8);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq5_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x7ff80000, 0x00000000);
    bits1 = ts_uint64_c(0x7ff80000, 0x00000000);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq6_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq7_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x80000000, 0x00000000);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}
TEST(fpe, assert_double_eq8_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x00000000, 0x00000001);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq9_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000004);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}


TEST(fpe, assert_double_eq10_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000005);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq11_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000002);
    bits1 = ts_uint64_c(0x80000000, 0x00000002);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq12_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000003);
    bits1 = ts_uint64_c(0x80000000, 0x00000002);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq13_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(fp0, 1.23);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(fp0, 2.23);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(1.23, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq16_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(2.23, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq17_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(fp0, 1.93L);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq18_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(fp0, 2.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq19_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(1.93L, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq20_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(2.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}


/* NOLINTEND(misc-include-cleaner) */

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(fpe, assert_double_near0_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.1;
    double fp1 = 1.2;
    ASSERT_NEAR(fp0, fp1, .1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near1_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.1;
    double fp1 = 1.2;
    ASSERT_NEAR(fp0, fp1, .0999);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near2_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.1;
    double fp1 = 1.1000001;
    ASSERT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near3_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.1000001;
    double fp1 = 1.1;
    ASSERT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near4_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    double fp1 = 1.1;
    ASSERT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}
TEST(fpe, assert_double_near5_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    double fp1 = 1.1;
    ASSERT_NEAR(fp0, fp1, .000001);
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, assert_double_near6_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    double fp1 = 1.1;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, fp1, .000001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near7_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, 1.1, .000001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near8_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, 1.1F, .000001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near9_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(1.1F, fp0, .000001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near10_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    ASSERT_NEAR(1.1F, fp0, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near11_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    ASSERT_NEAR(1.1, fp0, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near12_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(1.1, 1.10001, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near13_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(1.1, 1.10001F, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(1.1, 1.10001F, .000001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float  fp0 = 1.10001F;
    double fp1 = 1.1;
    ASSERT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near16_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    float fp1 = 1.1F;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    float fp1 = 1.1F;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, assert_double_near18_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float  fp0 = 1.10001F;
    double fp1 = 1.1;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    float  fp1 = 1.1F;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near20_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, 1.1, .0001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near21_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    ASSERT_NEAR(fp0, 1.1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near22_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(1.1, fp0, .0001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near23_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    ASSERT_NEAR(1.1, fp0, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

//
TEST(fpe, assert_long_double_near0_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.1L;
    long double fp1 = 1.2L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(fp0, fp1, .1);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near1_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.2L;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(fp0, fp1, .0999);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near2_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.1L;
    long double fp1 = 1.1000001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near3_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.1000001L;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(fp0, fp1, .0001);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near4_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}
TEST(fpe, assert_long_double_near5_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(fp0, fp1, .000001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, assert_long_double_near6_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, fp1, .000001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near7_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(fp0, 1.1, .000001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near8_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(fp0, 1.1, .000001);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near9_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(1.1F, fp0, .000001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near10_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(1.1F, fp0, .000001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near11_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(1.1, fp0, .000001);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near12_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(1.1, 1.10001, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near13_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(1.1, 1.10001F, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(1.1, 1.10001F, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float       fp0 = 1.10001F;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near16_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    float fp1 = 1.1F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    float fp1 = 1.1F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, fp1, .0001L);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, assert_long_double_near18_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float       fp0 = 1.10001F;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    float       fp1 = 1.1F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near20_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(fp0, 1.1L, .0001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near21_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(fp0, 1.1, .0001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near22_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    ASSERT_NEAR(1.1L, fp0, .0001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near23_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    ASSERT_NEAR(1.1L, fp0, .0001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

/* NOLINTEND(readability-function-cognitive-complexity) */

/* NOLINTBEGIN(misc-include-cleaner) */
TEST(fpe, expect_float_eq0_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0xdeadbeef;
    bits1 = 0xdeadbeee;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    EXPECT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, expect_float_eq1_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0xdeadbeed;
    bits1 = 0xdeadbeef;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, expect_float_eq2_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0xdeadbeef;
    bits1 = 0xdeadbeec;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, expect_float_eq3_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0xdeadbeeb;
    bits1 = 0xdeadbeef;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, expect_float_eq4_fail) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0xdeadbeef;
    bits1 = 0x5eadbeef;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, expect_float_eq5_fail) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x7fc00000;
    bits1 = 0x7fc00000;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1, "Oh not: %f, %f\n", fp0, fp1);
}

TEST(fpe, expect_float_eq6_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000000;
    bits1 = 0x00000000;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1, "oh yeah: %f, %u\n", fp0, bits0);
}

TEST(fpe, expect_float_eq7_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000000;
    bits1 = 0x80000000;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
}
TEST(fpe, expect_float_eq8_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000000;
    bits1 = 0x00000001;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, expect_float_eq9_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000004;
    bits1 = 0x00000000;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
}


TEST(fpe, expect_float_eq10_fail) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000005;
    bits1 = 0x00000000;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, expect_float_eq11_okay) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000002;
    bits1 = 0x80000002;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, expect_float_eq12_fail) {
    uint32_t bits0 = 0;
    uint32_t bits1 = 0;
    float    fp0   = 0.0F;
    float    fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = 0x00000003;
    bits1 = 0x80000002;
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    EXPECT_FLOAT_EQ(fp0, fp1);
}

TEST(fpe, expect_float_eq13_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    EXPECT_FLOAT_EQ(fp0, 1.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    EXPECT_FLOAT_EQ(fp0, 2.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    EXPECT_FLOAT_EQ(1.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq16_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    EXPECT_FLOAT_EQ(2.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    EXPECT_FLOAT_EQ(fp0, 1.23);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq18_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    EXPECT_FLOAT_EQ(fp0, 2.23);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    EXPECT_FLOAT_EQ(1.23, fp0);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq20_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    EXPECT_FLOAT_EQ(2.23, fp0);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq21_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    EXPECT_FLOAT_EQ(fp0, 2.23L);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq22_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    EXPECT_FLOAT_EQ(2.23L, fp0);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq0_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeee);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeef);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq1_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeec);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq2_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeea);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq3_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbee9);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq4_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbee8);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq5_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x7ff80000, 0x00000000);
    bits1 = ts_uint64_c(0x7ff80000, 0x00000000);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq6_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq7_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x80000000, 0x00000000);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}
TEST(fpe, expect_double_eq8_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x00000000, 0x00000001);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq9_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000004);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}


TEST(fpe, expect_double_eq10_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000005);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq11_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000002);
    bits1 = ts_uint64_c(0x80000000, 0x00000002);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq12_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0;
    double   fp1   = 0.0;
    /* NOLINTBEGIN(*-magic-numbers) */
    bits0 = ts_uint64_c(0x00000000, 0x00000003);
    bits1 = ts_uint64_c(0x80000000, 0x00000002);
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    memcpy(&fp0, &bits0, sizeof(bits0));
    memcpy(&fp1, &bits1, sizeof(bits1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    EXPECT_DOUBLE_EQ(fp0, fp1);
}
/* NOLINTEND(misc-include-cleaner) */


TEST(fpe, expect_double_eq13_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(fp0, 1.23);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(fp0, 2.23);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(1.23, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq16_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(2.23, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq17_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(fp0, 1.93L);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq18_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(fp0, 2.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq19_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(1.93L, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq20_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(2.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}


/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(fpe, expect_double_near0_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.1;
    double fp1 = 1.2;
    EXPECT_NEAR(fp0, fp1, .1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near1_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.1;
    double fp1 = 1.2;
    EXPECT_NEAR(fp0, fp1, .0999);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near2_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.1;
    double fp1 = 1.1000001;
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near3_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.1000001;
    double fp1 = 1.1;
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near4_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    double fp1 = 1.1;
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}
TEST(fpe, expect_double_near5_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    double fp1 = 1.1;
    EXPECT_NEAR(fp0, fp1, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near6_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    double fp1 = 1.1;
    EXPECT_NEAR(fp0, fp1, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near7_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    EXPECT_NEAR(fp0, 1.1, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near8_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    EXPECT_NEAR(fp0, 1.1F, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near9_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    EXPECT_NEAR(1.1F, fp0, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near10_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    EXPECT_NEAR(1.1F, fp0, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near11_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    EXPECT_NEAR(1.1, fp0, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near12_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(1.1, 1.10001, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near13_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(1.1, 1.10001F, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(1.1, 1.10001F, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float  fp0 = 1.10001F;
    double fp1 = 1.1;
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near16_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    float fp1 = 1.1F;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    float fp1 = 1.1F;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    EXPECT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, expect_double_near18_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float  fp0 = 1.10001F;
    double fp1 = 1.1;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    EXPECT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    double fp0 = 1.10001;
    float  fp1 = 1.1F;
    EXPECT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near20_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    EXPECT_NEAR(fp0, 1.1, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near21_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    EXPECT_NEAR(fp0, 1.1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near22_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    EXPECT_NEAR(1.1, fp0, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near23_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    EXPECT_NEAR(1.1, fp0, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near0_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.1L;
    long double fp1 = 1.2L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, fp1, .1);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near1_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.1L;
    long double fp1 = 1.2L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, fp1, .0999);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near2_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.1L;
    long double fp1 = 1.1000001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, fp1, .0001F);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near3_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.1000001L;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, fp1, .0001);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near4_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}
TEST(fpe, expect_long_double_near5_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, fp1, .000001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, expect_long_double_near6_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, fp1, .000001F);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near7_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, 1.1, .000001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near8_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, 1.1, .000001);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near9_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(1.1F, fp0, .000001F);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near10_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(1.1F, fp0, .000001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near11_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(1.1, fp0, .000001);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near12_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(1.1, 1.10001, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near13_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(1.1, 1.10001F, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(1.1, 1.10001F, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float       fp0 = 1.10001F;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near16_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    float fp1 = 1.1F;
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    float fp1 = 1.1F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    /* NOLINTBEGIN(performance-type-promotion-in-math-fn) */
    EXPECT_NEAR(fp0, fp1, .0001L);
    /* NOLINTEND(performance-type-promotion-in-math-fn) */
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, expect_long_double_near18_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float       fp0 = 1.10001F;
    long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, fp1, .0001F);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    long double fp0 = 1.10001L;
    float       fp1 = 1.1F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near20_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, 1.1L, .0001F);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near21_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(fp0, 1.1, .0001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near22_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(1.1L, fp0, .0001F);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near23_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    TS_DISABLE_WCONVERSION_
    EXPECT_NEAR(1.1L, fp0, .0001L);
    TS_REENABLE_WCONVERSION_
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, assert_true0_okay) {
    ASSERT_TRUE(1);
}


TEST(ac, assert_true1_fail) {
    ASSERT_TRUE(0);
}

TEST(c, assert_true2_skip_okay) {
    /* TODO ASSERT_TRUE(NULL); */
}


TEST(c, assert_true3_fail) {
    ASSERT_TRUE(0);
}

TEST(c, assert_true4_okay) {
    ASSERT_TRUE(1);
}

#if !EZTEST_ARCH_IS_X86_32_ || TS_USING_CLANG_
TEST(c, assert_true5_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_TRUE(0.9);
    /* NOLINTEND(*-magic-numbers) */
}
#endif


TEST(c, assert_true6_okay) {
    int foo = 1;
    ASSERT_TRUE(foo);
}


TEST(c, assert_true7_fail) {
    ASSERT_TRUE((long)0L);
}

TEST(c, assert_true8_okay) {
    unsigned val = 0;
    /* NOLINTBEGIN(bugprone-assignment-in-if-condition) */
    ASSERT_TRUE(val ^= 1U);
    /* NOLINTEND(bugprone-assignment-in-if-condition) */
}

TEST(c, assert_true9_fail) {
    unsigned val = 1;
    /* NOLINTBEGIN(bugprone-assignment-in-if-condition) */
    ASSERT_TRUE(val ^= 1U);
    /* NOLINTEND(bugprone-assignment-in-if-condition) */
}


TEST(c, assert_false0_okay) {
    ASSERT_FALSE((double)0);
}

TEST(c, assert_false1_okay) {
    ASSERT_FALSE((void *)0);
}

TEST(c, assert_false2_skip_okay) {
    /* TODO: ASSERT_FALSE(NULL); */
}

TEST(c, assert_false3_fail) {
    char foo = 'a';
    ASSERT_FALSE(foo);
}


TEST(c, assert_false4_fail) {
    ASSERT_FALSE(1);
}


TEST(c, assert_false5_fail) {
    ASSERT_FALSE(123);
}


TEST(c, assert_false6_fail) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_FALSE((void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, assert_false7_fail) {
    unsigned val = 0;
    /* NOLINTBEGIN(bugprone-assignment-in-if-condition) */
    ASSERT_FALSE(val ^= 1U);
    /* NOLINTEND(bugprone-assignment-in-if-condition) */
}

TEST(c, assert_false8_okay) {
    unsigned val = 1;
    /* NOLINTBEGIN(bugprone-assignment-in-if-condition) */
    ASSERT_FALSE(val ^= 1U);
    /* NOLINTEND(bugprone-assignment-in-if-condition) */
}


TEST(c, assert_eq0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_EQ((void *)(1UL), (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, assert_eq1_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_EQ((char *)(1UL), (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, assert_eq2_okay) {
    ASSERT_EQ((uintptr_t)(1UL), 1UL);
}


TEST(c, assert_eq3_fail) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_EQ(NULL, (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, assert_eq4_fail) {
    int abc = 1;
    int def = 2;
    ASSERT_EQ(abc, def);
}

TEST(c, assert_eq5_fail) {
    int abc = 1;
    ASSERT_EQ(abc, 10 + 11);
}

TEST(c, assert_eq6_okay) {
    ASSERT_EQ(21, 10 + 11);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, assert_eq7_okay) {
    int abc = 1;
    ASSERT_EQ(abc++, 1);
    ASSERT_EQ(2, abc++);
    ASSERT_EQ(abc++, 3);
    ASSERT_EQ(5, ++abc);
}

TEST(c, assert_eq8_fail) {
    int abc = 1;
    ASSERT_EQ(abc++, 1);
    ASSERT_EQ(abc++, 2);
    ASSERT_EQ(3, abc++);
    ASSERT_EQ(++abc, 4);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, assert_eq9_okay) {
    ASSERT_EQ(NULL, (void *)(0));
}

TEST(c, assert_ne0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_NE((void *)(1UL), (void *)(2UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, assert_ne1_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_NE((char *)(0UL), (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, assert_ne2_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_NE(NULL, (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}


TEST(c, assert_ne3_fail) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_NE(NULL, (void *)(0UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, assert_ne4_fail) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_NE(NULL, NULL);
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, assert_ne5_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    void * ptr0 = malloc(10);
    void * ptr1 = malloc(11);
    /* NOLINTEND(*-magic-numbers) */
    ASSERT_NE(ptr0, ptr1);
    free(ptr0);
    free(ptr1);
}

TEST(c, assert_ne4_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NE(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, assert_ne5_okay) {
    double dbl = 0;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NE(dbl, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, assert_ne6_okay) {
    ASSERT_NE(20 + 0, 10 + 11);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, assert_ne7_okay) {
    int abc = 1;
    ASSERT_NE(abc++, 2);
    ASSERT_NE(abc++, 3);
    ASSERT_NE(abc++, 4);
    ASSERT_NE(++abc, 6);
}

TEST(c, assert_ne8_fail) {
    int abc = 1;
    ASSERT_NE(abc++, 2);
    ASSERT_NE(abc++, 3);
    ASSERT_NE(abc++, 4);
    ASSERT_NE(++abc, 5);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, assert_le0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_LE((void *)(1UL), (void *)(2UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}


TEST(c, assert_le2_skip_okay) {
    /* TODO: ASSERT_LE(NULL, (void *)(1UL)); */
}

TEST(c, assert_le3_skip_okay) {
    /* TODO: ASSERT_LE(NULL, (void *)(0UL)); */
}

TEST(c, assert_le4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LE(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, assert_le5_okay) {
    double dbl = 0;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LE(dbl, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, assert_le6_okay) {
    ASSERT_LE(20 + 0, 10 + 11);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, assert_le7_okay) {
    int abc = 1;
    ASSERT_LE(abc++, 1);
    ASSERT_LE(abc++, 2);
    ASSERT_LE(abc++, 3);
    ASSERT_LE(++abc, 5);
}


TEST(c, assert_le8_fail) {
    int abc = 1;
    ASSERT_LE(++abc, 2);
    ASSERT_LE(++abc, 3);
    ASSERT_LE(++abc, 4);
    ASSERT_LE(++abc, 4);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, assert_gt0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_GT((void *)(2UL), (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}


TEST(c, assert_gt2_skip_okay) {
    /* TODO: ASSERT_GT( (void *)(1UL),NULL); */
}

TEST(c, assert_gt3_skip_okay) {
    /* TODO: ASSERT_GT( (void *)(0UL),NULL); */
}

TEST(c, assert_gt4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GT(10, 20.1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, assert_gt5_okay) {
    double dbl = 0;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GT(10.5F, dbl);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, assert_gt6_okay) {
    ASSERT_GT(10 + 11, 20 + 0);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, assert_gt7_okay) {
    int abc = 1;
    ASSERT_GT(++abc, 1);
    ASSERT_GT(++abc, 2);
    ASSERT_GT(++abc, 3);
    ASSERT_GT(++abc, 4);
}


TEST(c, assert_gt8_fail) {
    int abc = 1;
    ASSERT_GT(++abc, 1);
    ASSERT_GT(++abc, 2);
    ASSERT_GT(++abc, 3);
    ASSERT_GT(abc++, 4);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, assert_lt0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_LT((void *)(1UL), (void *)(2UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}


TEST(c, assert_lt2_skip_okay) {
    /* TODO: ASSERT_LT(NULL, (void *)(1UL)); */
}

TEST(c, assert_lt3_skip_okay) {
    /* TODO: ASSERT_LT(NULL, (void *)(0UL)); */
}

TEST(c, assert_lt4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LT(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, assert_lt5_okay) {
    float flt = 0;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LT(flt, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, assert_lt6_okay) {
    ASSERT_LT(20 + 0, 10 + 11);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, assert_lt7_okay) {
    int abc = 1;
    ASSERT_LT(abc++, 2);
    ASSERT_LT(abc++, 3);
    ASSERT_LT(abc++, 4);
    ASSERT_LT(++abc, 6);
}


TEST(c, assert_lt8_fail) {
    int abc = 1;
    ASSERT_LT(abc++, 2);
    ASSERT_LT(abc++, 3);
    ASSERT_LT(abc++, 4);
    ASSERT_LT(++abc, 5);
}

TEST(c, assert_lt9_okay) {
    int abc = 1;
    ASSERT_LT(abc++, 2);
    ASSERT_LT(abc++, 3);
    ASSERT_LT(abc++, 4);
    ASSERT_LT(4, ++abc);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, assert_ge0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    ASSERT_GE((void *)(2UL), (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, assert_ge1_okay) {
    // ASSERT_GE((void *)(1UL), (char *)(2UL));
}

TEST(c, assert_ge2_skip_okay) {
    /* TODO: ASSERT_GE( (void *)(1UL),NULL); */
}

TEST(c, assert_ge3_skip_okay) {
    /* TODO: ASSERT_GE( (void *)(0UL),NULL); */
}

TEST(c, assert_ge4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GE(10, 20.1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, assert_ge5_okay) {
    float flt = 0;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GE(10.5F, flt);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, assert_ge6_okay) {
    ASSERT_GE((char)(10 + 11), 20 + 1);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, assert_ge7_okay) {
    int abc = 1;
    ASSERT_GE(2, abc++);
    ASSERT_GE(3, abc++);
    ASSERT_GE(4, abc++);
    ASSERT_GE(6, ++abc);
}


TEST(c, assert_ge8_fail) {
    int abc = 1;
    ASSERT_GE(2, abc++);
    ASSERT_GE(3, abc++);
    ASSERT_GE(4, abc++);
    ASSERT_GE(4, ++abc);
}

TEST(c, assert_ge9_okay) {
    int abc = 1;
    ASSERT_GE(2, abc++);
    ASSERT_GE(3, abc++);
    ASSERT_GE(4, abc++);
    ASSERT_GE(++abc, 4);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, assert_streq0_okay) {
    ASSERT_STREQ("", "");
}


TEST(c, assert_streq1_fail) {
    ASSERT_STREQ("abc", "abcd");
}

TEST(c, assert_streq2_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    char buf[] = { 1, 2, 3, 4, 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STREQ("abc", (const char *)buf);
}

TEST(c, assert_streq3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STREQ((char *)buf0, (const char *)buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STREQ((char const *)buf0, (const char *)buf1);
}

TEST(c, assert_streq4_fail) {
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    ASSERT_STREQ((const char *)buf0, "abcd");
    ASSERT_STREQ("abcd", (const char *)buf0);
    ASSERT_STREQ("abCd", (const char * const)buf0);
}

TEST(c, assert_streq5_okay) {
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    ASSERT_STREQ((const char *)buf0, "");
}


TEST(c, assert_strne0_fail) {
    ASSERT_STRNE("", "");
}

TEST(c, assert_strne1_okay) {
    ASSERT_STRNE("abc", "abcd");
}

TEST(c, assert_strne2_okay) {
    char buf[] = { 1, 2, 3, 4, 0 };
    ASSERT_STRNE("abc", (char * const)buf);
}

TEST(c, assert_strne3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 2;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRNE((char * const)buf0, (const char *)buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRNE((const char *)buf0, (const char *)buf1);
}

TEST(c, assert_strne4_okay) {
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    ASSERT_STRNE((const char *)buf0, "bcd");
    ASSERT_STRNE("abc", (const char *)buf0);
    ASSERT_STRNE("abCd", (const char *)buf0);
}

TEST(c, assert_strne5_fail) {
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    ASSERT_STRNE((const char *)buf0, "");
}

TEST(c, assert_strcaseeq0_okay) {
    ASSERT_STRCASEEQ("", "");
}

TEST(c, assert_strcaseeq1_fail) {
    ASSERT_STRCASEEQ("abc", "abCd");
}

TEST(c, assert_strcaseeq2_fail) {
    char buf[] = { 1, 2, 3, 4, 0 };
    ASSERT_STRCASEEQ("abc", (const char *)buf);
}

TEST(c, assert_strcaseeq3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASEEQ((const char *)buf0, (const char *)buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASEEQ((char * const)buf0, (const char * const)buf1);
}

TEST(c, assert_strcaseeq4_okay) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    const char buf0[] = { 'A', 'b', 'c', 'D', 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASEEQ((const char *)buf0, "abcd");
    ASSERT_STRCASEEQ("abcd", (const char *)buf0);
    ASSERT_STRCASEEQ("abCd", (const char *)buf0);
}

TEST(c, assert_strcaseeq5_okay) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASEEQ((const char *)buf0, "");
}

TEST(c, assert_strcaseeq6_okay) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    const char buf0[] = { '0', 'b', 'c', 'd', 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASEEQ((const char *)buf0, "0BcD");
}


TEST(c, assert_strcasene0_fail) {
    ASSERT_STRCASENE("", "");
}

TEST(c, assert_strcasene1_okay) {
    ASSERT_STRCASENE("abc", "abcd");
}

TEST(c, assert_strcasene2_okay) {
    char buf[] = { 1, 2, 'C', 4, 0 };
    ASSERT_STRCASENE("abC", (const char *)buf);
}

TEST(c, assert_strcasene3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    char       buf0[] = { 'a', 2, 3, 4, 0 };
    const char buf1[] = { 'A', 2, 3, 4, 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASENE((const char *)buf0, (const char *)buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 2;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASENE((const char *)buf0, (const char *)buf1);
}

TEST(c, assert_strcasene4_okay) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASENE((const char *)buf0, "ABCCD");
    ASSERT_STRCASENE("abc", (const char *)buf0);
    ASSERT_STRCASENE("ab0d", (const char *)buf0);
}

TEST(c, assert_strcasene5_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASENE((const char *)buf0, "");
}
TEST(c, assert_strcasene6_fail) {
    ASSERT_STRCASENE("ABc", "abc", "They be eq: %s/%s (%d)\n", "hello", "world",
                     0);
}
TEST(d, assert_strcasene7_fail) {
    ASSERT_STRCASENE("ABc1", "abc1");
}
TEST(c, assert_strcasene8_okay) {
    ASSERT_STRCASENE("ABc0", "abc1");
}


TEST(c, DISABLED_foo_okay) {
    ASSERT_TRUE(0);
}
TEST(c, DISABLED_bar_okay) {
    ASSERT_FALSE(0);
}

TEST(c, DISABLED_buz_okay) {
    ASSERT_FALSE(1);
}


TEST(dxx, DISABLED_baz_okay) {
    ASSERT_FALSE(1, "I OBVIOUSLY FAILED!");
}

TEST(a_way_to_overly_long_group_name_that_make_it_not_nice_to_fmt,
     assert_true1_fail) {
    ASSERT_TRUE(0);
}


TEST(a_moderately_long_group_name, assert_true1_fail) {
    ASSERT_TRUE(0);
}

TEST(a_modestly_long_group_name, assert_true1_fail) {
    ASSERT_TRUE(0);
}

TEST(a_mid_long_group_name, assert_true1_fail) {
    ASSERT_TRUE(0);
}


TEST(c, expect_true0_okay) {
    EXPECT_TRUE(1);
}

TEST(ac, expect_true1_fail) {
    EXPECT_TRUE(0);
}

TEST(c, expect_true2_skip_okay) {
    /* TODO EXPECT_TRUE(NULL); */
}


TEST(c, expect_true3_fail) {
    EXPECT_TRUE(0);
}

TEST(c, expect_true4_okay) {
    EXPECT_TRUE(1);
}

#if !EZTEST_ARCH_IS_X86_32_ || TS_USING_CLANG_
TEST(c, expect_true5_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_TRUE(0.9);
    /* NOLINTEND(*-magic-numbers) */
}
#endif

TEST(c, expect_true6_okay) {
    int foo = 1;
    EXPECT_TRUE(foo);
}


TEST(c, expect_true7_fail) {
    EXPECT_TRUE((long)0L);
}

TEST(c, expect_true8_okay) {
    unsigned val = 0;
    /* NOLINTBEGIN(bugprone-assignment-in-if-condition) */
    EXPECT_TRUE(val ^= 1U);
    /* NOLINTEND(bugprone-assignment-in-if-condition) */
}

TEST(c, expect_true9_fail) {
    unsigned val = 1;
    /* NOLINTBEGIN(bugprone-assignment-in-if-condition) */
    EXPECT_TRUE(val ^= 1U);
    /* NOLINTEND(bugprone-assignment-in-if-condition) */
}


TEST(c, expect_false0_okay) {
    EXPECT_FALSE((double)0);
}

TEST(c, expect_false1_okay) {
    EXPECT_FALSE((void *)0);
}

TEST(c, expect_false2_skip_okay) {
    /* TODO: EXPECT_FALSE(NULL); */
}

TEST(c, expect_false3_fail) {
    char foo = 'a';
    EXPECT_FALSE(foo);
}


TEST(c, expect_false4_fail) {
    EXPECT_FALSE(1);
}


TEST(c, expect_false5_fail) {
    EXPECT_FALSE(123);
}


TEST(c, expect_false6_fail) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    EXPECT_FALSE((void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, expect_false7_fail) {
    unsigned val = 0;
    /* NOLINTBEGIN(bugprone-assignment-in-if-condition) */
    EXPECT_FALSE(val ^= 1U);
    /* NOLINTEND(bugprone-assignment-in-if-condition) */
}

TEST(c, expect_false8_okay) {
    unsigned val = 1;
    /* NOLINTBEGIN(bugprone-assignment-in-if-condition) */
    EXPECT_FALSE(val ^= 1U);
    /* NOLINTEND(bugprone-assignment-in-if-condition) */
}


TEST(c, expect_eq0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    EXPECT_EQ((void *)(1UL), (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, expect_eq1_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    EXPECT_EQ((char *)(1UL), (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, expect_eq2_okay) {
    EXPECT_EQ((uintptr_t)(1UL), 1UL);
}


TEST(c, expect_eq3_fail) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    EXPECT_EQ(NULL, (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, expect_eq4_fail) {
    int abc = 1;
    int def = 2;
    EXPECT_EQ(abc, def);
}

TEST(c, expect_eq5_fail) {
    int abc = 1;
    EXPECT_EQ(abc, 10 + 11);
}

TEST(c, expect_eq6_okay) {
    EXPECT_EQ(21, 10 + 11);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, expect_eq7_okay) {
    int abc = 1;
    EXPECT_EQ(abc++, 1);
    EXPECT_EQ(2, abc++);
    EXPECT_EQ(abc++, 3);
    EXPECT_EQ(5, ++abc);
}


TEST(c, expect_eq8_fail) {
    int abc = 1;
    EXPECT_EQ(abc++, 1);
    EXPECT_EQ(abc++, 2);
    EXPECT_EQ(3, abc++);
    EXPECT_EQ(++abc, 4);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, expect_eq9_okay) {
    EXPECT_EQ(NULL, (void *)(0));
}

TEST(c, expect_ne0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    EXPECT_NE((void *)(1UL), (void *)(2UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, expect_ne1_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    EXPECT_NE((char *)(0UL), (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, expect_ne2_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    EXPECT_NE(NULL, (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}


TEST(c, expect_ne3_fail) {
    EXPECT_NE(NULL, (void *)(0UL));
}
TEST(c, expect_ne4_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NE(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, expect_ne5_okay) {
    double dbl = 0;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NE(dbl, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, expect_ne6_okay) {
    EXPECT_NE(20 + 0, 10 + 11);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, expect_ne7_okay) {
    int abc = 1;
    EXPECT_NE(abc++, 2);
    EXPECT_NE(abc++, 3);
    EXPECT_NE(abc++, 4);
    EXPECT_NE(++abc, 6);
}


TEST(c, expect_ne8_fail) {
    int abc = 1;
    EXPECT_NE(abc++, 2);
    EXPECT_NE(abc++, 3);
    EXPECT_NE(abc++, 4);
    EXPECT_NE(++abc, 5);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, expect_le0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    EXPECT_LE((void *)(1UL), (void *)(2UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}


TEST(c, expect_le2_skip_okay) {
    /* TODO: EXPECT_LE(NULL, (void *)(1UL)); */
}

TEST(c, expect_le3_skip_okay) {
    /* TODO: EXPECT_LE(NULL, (void *)(0UL)); */
}

TEST(c, expect_le4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LE(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, expect_le4_float_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LE((float)20.1, (float)10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, expect_le5_okay) {
    double dbl = 0;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LE(dbl, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, expect_le6_okay) {
    EXPECT_LE(20 + 0, 10 + 11);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, expect_le7_okay) {
    int abc = 1;
    EXPECT_LE(abc++, 1);
    EXPECT_LE(abc++, 2);
    EXPECT_LE(abc++, 3);
    EXPECT_LE(++abc, 5);
}


TEST(c, expect_le8_fail) {
    int abc = 1;
    EXPECT_LE(++abc, 2);
    EXPECT_LE(++abc, 3);
    EXPECT_LE(++abc, 4);
    EXPECT_LE(++abc, 4);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, expect_gt0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    EXPECT_GT((void *)(2UL), (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}


TEST(c, expect_gt2_skip_okay) {
    /* TODO: EXPECT_GT( (void *)(1UL),NULL); */
}

TEST(c, expect_gt3_skip_okay) {
    /* TODO: EXPECT_GT( (void *)(0UL),NULL); */
}

TEST(c, expect_gt4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GT(10, 20.1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, expect_gt5_okay) {
    double dbl = 0;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GT(10.5F, dbl);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, expect_gt6_okay) {
    EXPECT_GT(10 + 11, 20 + 0);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, expect_gt7_okay) {
    int abc = 1;
    EXPECT_GT(++abc, 1);
    EXPECT_GT(++abc, 2);
    EXPECT_GT(++abc, 3);
    EXPECT_GT(++abc, 4);
}


TEST(c, expect_gt8_fail) {
    int abc = 1;
    EXPECT_GT(++abc, 1);
    EXPECT_GT(++abc, 2);
    EXPECT_GT(++abc, 3);
    EXPECT_GT(abc++, 4);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, expect_lt0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    EXPECT_LT((void *)(1UL), (void *)(2UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}


TEST(c, expect_lt2_skip_okay) {
    /* TODO: EXPECT_LT(NULL, (void *)(1UL)); */
}

TEST(c, expect_lt3_skip_okay) {
    /* TODO: EXPECT_LT(NULL, (void *)(0UL)); */
}


TEST(c, expect_lt4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LT(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, expect_lt5_okay) {
    float flt = 0;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LT(flt, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, expect_lt6_okay) {
    EXPECT_LT(20 + 0, 10 + 11);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, expect_lt7_okay) {
    int abc = 1;
    EXPECT_LT(abc++, 2);
    EXPECT_LT(abc++, 3);
    EXPECT_LT(abc++, 4);
    EXPECT_LT(++abc, 6);
}


TEST(c, expect_lt8_fail) {
    int abc = 1;
    EXPECT_LT(abc++, 2);
    EXPECT_LT(abc++, 3);
    EXPECT_LT(abc++, 4);
    EXPECT_LT(++abc, 5);
}

TEST(c, expect_lt9_okay) {
    int abc = 1;
    EXPECT_LT(abc++, 2);
    EXPECT_LT(abc++, 3);
    EXPECT_LT(abc++, 4);
    EXPECT_LT(4, ++abc);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, expect_ge0_okay) {
    /* NOLINTBEGIN(performance-no-int-to-ptr) */
    EXPECT_GE((void *)(2UL), (void *)(1UL));
    /* NOLINTEND(performance-no-int-to-ptr) */
}

TEST(c, expect_ge1_okay) {
    /* TODO: EXPECT_GE((void *)(1UL), (char *)(2UL)); */
}

TEST(c, expect_ge2_skip_okay) {
    /* TODO: EXPECT_GE( (void *)(1UL),NULL); */
}

TEST(c, expect_ge3_skip_okay) {
    /* TODO: EXPECT_GE( (void *)(0UL),NULL); */
}

TEST(c, expect_ge4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GE(10, 20.1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, expect_ge5_okay) {
    float flt = 0;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GE(10.5F, flt);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(c, expect_ge6_okay) {
    EXPECT_GE((char)(10 + 11), 20 + 1);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST(c, expect_ge7_okay) {
    int abc = 1;
    EXPECT_GE(2, abc++);
    EXPECT_GE(3, abc++);
    EXPECT_GE(4, abc++);
    EXPECT_GE(6, ++abc);
}


TEST(c, expect_ge8_fail) {
    int abc = 1;
    EXPECT_GE(2, abc++);
    EXPECT_GE(3, abc++);
    EXPECT_GE(4, abc++);
    EXPECT_GE(4, ++abc);
}

TEST(c, expect_ge9_okay) {
    int abc = 1;
    EXPECT_GE(2, abc++);
    EXPECT_GE(3, abc++);
    EXPECT_GE(4, abc++);
    EXPECT_GE(++abc, 4);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST(c, expect_streq0_okay) {
    EXPECT_STREQ("", "");
}


TEST(c, expect_streq1_fail) {
    EXPECT_STREQ("abc", "abcd");
}

TEST(c, expect_streq2_fail) {
    char buf[] = { 1, 2, 3, 4, 0 };
    EXPECT_STREQ("abc", (const char *)buf);
}

TEST(c, expect_streq3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STREQ((char *)buf0, (const char *)buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STREQ((char const *)buf0, (const char *)buf1);
}

TEST(c, expect_streq4_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STREQ((const char *)buf0, "abcd");
    EXPECT_STREQ("abcd", (const char *)buf0);
    EXPECT_STREQ("abCd", (const char * const)buf0);
}

TEST(c, expect_streq5_okay) {
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    EXPECT_STREQ((const char *)buf0, "");
}


TEST(c, expect_strne0_fail) {
    EXPECT_STRNE("", "");
}

TEST(c, expect_strne1_okay) {
    EXPECT_STRNE("abc", "abcd");
}

TEST(c, expect_strne2_okay) {
    char buf[] = { 1, 2, 3, 4, 0 };
    EXPECT_STRNE("abc", (char * const)buf);
}

TEST(c, expect_strne3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 2;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRNE((char * const)buf0, (const char *)buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRNE((const char *)buf0, (const char *)buf1);
}

TEST(c, expect_strne4_okay) {
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    EXPECT_STRNE((const char *)buf0, "bcd");
    EXPECT_STRNE("abc", (const char *)buf0);
    EXPECT_STRNE("abCd", (const char *)buf0);
}

TEST(c, expect_strne5_fail) {
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    EXPECT_STRNE((const char *)buf0, "");
}

TEST(c, expect_strcaseeq0_okay) {
    EXPECT_STRCASEEQ("", "");
}

TEST(c, expect_strcaseeq1_fail) {
    EXPECT_STRCASEEQ("abc", "abCd");
}

TEST(c, expect_strcaseeq2_fail) {
    char buf[] = { 1, 2, 3, 4, 0 };
    EXPECT_STRCASEEQ("abc", (const char *)buf);
}

TEST(c, expect_strcaseeq3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRCASEEQ((const char *)buf0, (const char *)buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRCASEEQ((char * const)buf0, (const char * const)buf1);
}

TEST(c, expect_strcaseeq4_okay) {
    const char buf0[] = { 'A', 'b', 'c', 'D', 0 };
    EXPECT_STRCASEEQ((const char *)buf0, "abcd");
    EXPECT_STRCASEEQ("abcd", (const char *)buf0);
    EXPECT_STRCASEEQ("abCd", (const char *)buf0);
}

TEST(c, expect_strcaseeq5_okay) {
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    EXPECT_STRCASEEQ((const char *)buf0, "");
}

TEST(c, expect_strcaseeq6_okay) {
    const char buf0[] = { '0', 'b', 'c', 'd', 0 };
    EXPECT_STRCASEEQ((const char *)buf0, "0BcD");
}


TEST(c, expect_strcasene0_fail) {
    EXPECT_STRCASENE("", "");
}

TEST(c, expect_strcasene1_okay) {
    EXPECT_STRCASENE("abc", "abcd");
}

TEST(c, expect_strcasene2_okay) {
    char buf[] = { 1, 2, 'C', 4, 0 };
    EXPECT_STRCASENE("abC", (const char *)buf);
}

TEST(c, expect_strcasene3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    char       buf0[] = { 'a', 2, 3, 4, 0 };
    const char buf1[] = { 'A', 2, 3, 4, 0 };
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRCASENE((const char *)buf0, (const char *)buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 2;
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRCASENE((const char *)buf0, (const char *)buf1);
}

TEST(c, expect_strcasene4_okay) {
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    EXPECT_STRCASENE((const char *)buf0, "ABCCD");
    EXPECT_STRCASENE("abc", (const char *)buf0);
    EXPECT_STRCASENE("ab0d", (const char *)buf0);
}

TEST(c, expect_strcasene5_fail) {
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    EXPECT_STRCASENE((const char *)buf0, "");
}
TEST(c, expect_strcasene6_fail) {
    EXPECT_STRCASENE("ABc", "abc", "They be eq: %s/%s (%d)\n", "hello", "world",
                     0);
}
TEST(d, expect_strcasene7_fail) {
    EXPECT_STRCASENE("ABc1", "abc1");
}
TEST(c, expect_strcasene8_okay) {
    EXPECT_STRCASENE("ABc0", "abc1");
}


TEST(c, DISABLED_foo_none_okay) {
    EXPECT_TRUE(0);
}
TEST(c, DISABLED_bar_none_okay) {
    EXPECT_FALSE(0);
}

TEST(c, DISABLED_buz_none_okay) {
    EXPECT_FALSE(1);
}


TEST(dxx, DISABLED_baz_none_okay) {
    EXPECT_FALSE(1, "I OBVIOUSLY FAILED!");
}

TEST(a_way_to_overly_long_group_name_that_make_it_not_nice_to_fmt,
     expect_true1_fail) {
    EXPECT_TRUE(0);
}


TEST(a_moderately_long_group_name, expect_true1_fail) {
    EXPECT_TRUE(0);
}

TEST(a_modestly_long_group_name, expect_true1_fail) {
    EXPECT_TRUE(0);
}

TEST(a_mid_long_group_name, expect_true1_fail) {
    EXPECT_TRUE(0);
}


TEST_TIMED(timeouts, 10ms_timefail, 10) {
    while (1) {
        /* NOLINTBEGIN(hicpp-no-assembler) */
        __asm__ volatile("" ::: "memory");
        /* NOLINTEND(hicpp-no-assembler) */
    }
}

TEST_TIMED(timeouts, 50ms_timefail, 50) {
    while (1) {
        /* NOLINTBEGIN(hicpp-no-assembler) */
        __asm__ volatile("" ::: "memory");
        /* NOLINTEND(hicpp-no-assembler) */
    }
}

TEST_TIMED(timeouts, 1000ms_timefail, 1000) {
    while (1) {
        /* NOLINTBEGIN(hicpp-no-assembler) */
        __asm__ volatile("" ::: "memory");
        /* NOLINTEND(hicpp-no-assembler) */
    }
}

TEST_TIMED(timeouts, 1ms_timefail, 1) {
    while (1) {
        /* NOLINTBEGIN(hicpp-no-assembler) */
        __asm__ volatile("" ::: "memory");
        /* NOLINTEND(hicpp-no-assembler) */
    }
}

TEST_TIMED(timeouts, 1ms_double_timefail, 1) {
    EXPECT_TRUE(0);
    while (1) {
        /* NOLINTBEGIN(hicpp-no-assembler) */
        __asm__ volatile("" ::: "memory");
        /* NOLINTEND(hicpp-no-assembler) */
    }
}

TEST_TIMED(timeouts, 100ms_okay, 50000) {
    ASSERT_TRUE(1);
}

/* NOLINTBEGIN(readability-function-cognitive-complexity) */
TEST_TIMED(timeouts, 100ms_okay_fail, 50000) {
    EXPECT_TRUE(0);
    EXPECT_TRUE(0);
    EXPECT_TRUE(1);
}
/* NOLINTEND(readability-function-cognitive-complexity) */

TEST_TIMED(timeouts, 100ms_bad0_fail, 50000) {
    ASSERT_TRUE(0);
}

TEST_TIMED(timeouts, 100ms_bad_sig_sigfail, 50000) {
    TS_KILL_(getpid(), SIGKILL);
}

TEST(sigs, sigkill_self_sigfail) {
    TS_KILL_(getpid(), SIGKILL);
}

TEST(sigs, illegal_instruction_self_sigfail) {
/* NOLINTBEGIN(hicpp-no-assembler) */
#if EZTEST_ARCH_IS_ANY_X86_
    __asm__ volatile("ud2" : : :);
#elif EZTEST_ARCH_IS_AARCH64_
    __asm__ volatile("brk\t#1000" : : :);
#elif EZTEST_ARCH_IS_RISCV64_
    __asm__ volatile("ebreak" : : :);
#else
    TS_KILL_(getpid(), SIGKILL);
#endif
    /* NOLINTEND(hicpp-no-assembler) */
}

#if TS_USING_GCC_ || TS_HAS_CLANG_VER_(14, 0, 0) || !EZTEST_ARCH_IS_ANY_RISCV_
TEST(sigs, fault_self_Uultamsan_sigfail) {
    int * ptr = TS_NULL_;
    /* NOLINTBEGIN(hicpp-no-assembler) */
    __asm__ volatile("" : [ptr] "+r"(ptr) : : "memory");
    /* NOLINTEND(hicpp-no-assembler) */
    *ptr = 2;
    /* NOLINTBEGIN(hicpp-no-assembler) */
    __asm__ volatile("" : [ptr] "+r"(ptr) : : "memory");
    /* NOLINTEND(hicpp-no-assembler) */
    ASSERT_EQ(*ptr, 1);
}
#endif

#if EZTEST_ARCH_IS_ANY_X86_
TEST(sigs, fpe_self_Uultamsan_sigfail) {
    long val = 0;
    /* NOLINTBEGIN(hicpp-no-assembler) */
    __asm__ volatile("" : "+r"(val) : : "memory");
    /* NOLINTEND(hicpp-no-assembler) */
    /* NOLINTBEGIN(*-magic-numbers) */
    val = 1231L / val;
    /* NOLINTEND(*-magic-numbers) */
    ASSERT_TRUE(val);
}
#elif EZTEST_ARCH_IS_AARCH64_
TEST(sigs, fpe_self_Uusan_fail) {
    long val = 0;
    /* NOLINTBEGIN(hicpp-no-assembler) */
    __asm__ volatile("" : "+r"(val) : : "memory");
    /* NOLINTEND(hicpp-no-assembler) */
    /* NOLINTBEGIN(*-magic-numbers) */
    val = 1231L / val;
    /* NOLINTEND(*-magic-numbers) */
    ASSERT_TRUE(val);
}
#endif

TEST(dxx, baz_none_fail) {
    EXPECT_FALSE(1, "I OBVIOUSLY FAILED!\n");
}
TS_REENABLE_WSUGGEST_ATTRIBUTE_PURE_
TS_REENABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
TS_REENABLE_WLITERAL_CONVERSION_
TS_REENABLE_WDOUBLE_PROMOTION_
TS_REENABLE_WFLOAT_EQUAL_
TS_REENABLE_WFLOAT_CONVERSION_
TS_REENABLE_WMISSING_NORETURN_
TS_REENABLE_WSTACK_PROTECTOR_
/* NOLINTEND(altera-unroll-loops) */
