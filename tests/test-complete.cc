#include "test-suite-common.h"


/* Some errors in the tests... */
TS_DISABLE_WSTACK_PROTECTOR_
TS_DISABLE_WCXX98_COMPAT_
TS_DISABLE_WDOUBLE_PROMOTION_
TS_DISABLE_WFLOAT_EQUAL_
TS_DISABLE_WFLOAT_CONVERSION_
TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
/* NOLINTBEGIN(cppcoreguidelines-macro-usage) */
#ifndef EZTEST_DISABLE_WARNINGS
# define EZTEST_DISABLE_WARNINGS 1
#endif
/* NOLINTEND(cppcoreguidelines-macro-usage) */

#include "eztest/eztest.h"

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
/* NOLINTBEGIN(hicpp-deprecated-headers,modernize-deprecated-headers) */
#include <signal.h>
/* NOLINTEND(hicpp-deprecated-headers,modernize-deprecated-headers) */
#include <unistd.h>

#include <cstdint>
#include <cstring>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

/* NOLINTBEGIN(llvmlibc-implementation-in-namespace) */
/* NOLINTBEGIN(modernize-use-trailing-return-type) */
/* NOLINTBEGIN(misc-use-anonymous-namespace) */
/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
static inline uint64_t
ts_uint64_c(uint32_t hibits, uint32_t lobits) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(hicpp-use-auto,modernize-use-auto) */
    uint64_t complete = static_cast<uint64_t>(hibits);
    /* NOLINTEND(hicpp-use-auto,modernize-use-auto) */
    /* NOLINTBEGIN(*-magic-numbers) */
    complete <<= 32U;
    /* NOLINTEND(*-magic-numbers) */
    complete |= static_cast<uint64_t>(lobits);
    return complete;
}
/* NOLINTEND(misc-use-anonymous-namespace) */
/* NOLINTEND(modernize-use-trailing-return-type) */
/* NOLINTEND(llvmlibc-implementation-in-namespace) */

/* NOLINTBEGIN(altera-unroll-loops) */
TS_DISABLE_WMISSING_NORETURN_
TS_DISABLE_WSUGGEST_ATTRIBUTE_PURE_
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    ASSERT_FLOAT_EQ(fp0, fp1, "Oh no: %f vs %f\n", fp0, fp1);
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    ASSERT_FLOAT_EQ(fp0, fp1, "Yikes!\n");
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}

TEST(fpe, assert_float_eq13_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    ASSERT_FLOAT_EQ(fp0, 1.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    ASSERT_FLOAT_EQ(fp0, 2.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    ASSERT_FLOAT_EQ(1.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq16_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    ASSERT_FLOAT_EQ(2.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    ASSERT_FLOAT_EQ(fp0, 1.23);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq18_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    ASSERT_FLOAT_EQ(fp0, 2.23);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    ASSERT_FLOAT_EQ(1.23, fp0);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_float_eq20_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    ASSERT_FLOAT_EQ(2.23, fp0);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, assert_double_eq0_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeee);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeef);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq1_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeec);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq2_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeea);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq3_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbee9);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq4_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbee8);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq5_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x7ff80000, 0x00000000);
    bits1 = ts_uint64_c(0x7ff80000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq6_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq7_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x80000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}
TEST(fpe, assert_double_eq8_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x00000000, 0x00000001);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq9_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000004);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}


TEST(fpe, assert_double_eq10_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000005);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq11_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000002);
    bits1 = ts_uint64_c(0x80000000, 0x00000002);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq12_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000003);
    bits1 = ts_uint64_c(0x80000000, 0x00000002);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    ASSERT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq13_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(fp0, 1.23);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(fp0, 2.23);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(1.23, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq16_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(2.23, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq17_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(fp0, 1.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq18_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(fp0, 2.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq19_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(1.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_eq20_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    ASSERT_DOUBLE_EQ(2.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near0_okay) {
    const double fp0 = 1.1;
    const double fp1 = 1.2;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(fp0, fp1, .1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near1_fail) {
    const double fp0 = 1.1;
    const double fp1 = 1.2;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(fp0, fp1, .0999);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near2_okay) {
    const double fp0 = 1.1;
    const double fp1 = 1.1000001;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near3_okay) {
    const double fp0 = 1.1000001;
    const double fp1 = 1.1;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near4_okay) {
    const double fp0 = 1.10001;
    const double fp1 = 1.1;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}
TEST(fpe, assert_double_near5_fail) {
    const double fp0 = 1.10001;
    const double fp1 = 1.1;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NEAR(fp0, fp1, .000001);
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, assert_double_near6_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    const double fp1 = 1.1;
    ASSERT_NEAR(fp0, fp1, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near7_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    ASSERT_NEAR(fp0, 1.1, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near8_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    ASSERT_NEAR(fp0, 1.1F, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near9_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    ASSERT_NEAR(1.1F, fp0, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near10_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    ASSERT_NEAR(1.1F, fp0, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near11_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
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
    ASSERT_NEAR(1.1, 1.10001F, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float  fp0 = 1.10001F;
    const double fp1 = 1.1;
    ASSERT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near16_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    const float fp1 = 1.1F;
    ASSERT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    const float fp1 = 1.1F;
    ASSERT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, assert_double_near18_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float  fp0 = 1.10001F;
    const double fp1 = 1.1;
    ASSERT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    const float  fp1 = 1.1F;
    ASSERT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near20_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    ASSERT_NEAR(fp0, 1.1, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near21_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    ASSERT_NEAR(fp0, 1.1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near22_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    ASSERT_NEAR(1.1, fp0, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near23_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    ASSERT_NEAR(1.1, fp0, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

//
TEST(fpe, assert_long_double_near0_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.1L;
    const long double fp1 = 1.2L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, fp1, .1);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near1_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.2L;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, fp1, .0999);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near2_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.1L;
    const long double fp1 = 1.1000001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, fp1, .0001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near3_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.1000001L;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, fp1, .0001);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near4_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}
TEST(fpe, assert_long_double_near5_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, fp1, .000001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, assert_long_double_near6_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, fp1, .000001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near7_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, 1.1, .000001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near8_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, 1.1, .000001);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near9_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(1.1F, fp0, .000001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near10_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(1.1F, fp0, .000001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near11_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(1.1, fp0, .000001);
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
    const float       fp0 = 1.10001F;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near16_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    const float fp1 = 1.1F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    ASSERT_NEAR(fp0, fp1, .0001);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    const float fp1 = 1.1F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, assert_long_double_near18_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float       fp0 = 1.10001F;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, fp1, .0001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    const float       fp1 = 1.1F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near20_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, 1.1L, .0001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near21_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(fp0, 1.1, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near22_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(1.1L, fp0, .0001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_long_double_near23_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    ASSERT_NEAR(1.1L, fp0, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    EXPECT_FLOAT_EQ(fp0, fp1, "Oh no: %f vs %f\n", fp0, fp1);
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    EXPECT_FLOAT_EQ(fp0, fp1, "Yikes!\n");
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}

TEST(fpe, expect_float_eq13_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    EXPECT_FLOAT_EQ(fp0, 1.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    EXPECT_FLOAT_EQ(fp0, 2.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    EXPECT_FLOAT_EQ(1.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq16_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    EXPECT_FLOAT_EQ(2.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    EXPECT_FLOAT_EQ(fp0, 1.23);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq18_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    EXPECT_FLOAT_EQ(fp0, 2.23);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    EXPECT_FLOAT_EQ(1.23, fp0);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_float_eq20_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.23F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    EXPECT_FLOAT_EQ(2.23, fp0);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, expect_double_eq0_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeee);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeef);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq1_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeec);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq2_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeea);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq3_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbee9);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq4_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbee8);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq5_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x7ff80000, 0x00000000);
    bits1 = ts_uint64_c(0x7ff80000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq6_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq7_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x80000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}
TEST(fpe, expect_double_eq8_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x00000000, 0x00000001);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq9_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000004);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}


TEST(fpe, expect_double_eq10_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000005);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq11_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000002);
    bits1 = ts_uint64_c(0x80000000, 0x00000002);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq12_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000003);
    bits1 = ts_uint64_c(0x80000000, 0x00000002);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, expect_double_eq13_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(fp0, 1.23);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq14_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(fp0, 2.23);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq15_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(1.23, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq16_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(2.23, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq17_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(fp0, 1.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq18_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(fp0, 2.23F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq19_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(1.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_eq20_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.23;
    EXPECT_DOUBLE_EQ(2.23F, fp0);
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, expect_double_near0_okay) {
    const double fp0 = 1.1;
    const double fp1 = 1.2;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near1_fail) {
    const double fp0 = 1.1;
    const double fp1 = 1.2;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .0999);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near2_okay) {
    const double fp0 = 1.1;
    const double fp1 = 1.1000001;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near3_okay) {
    const double fp0 = 1.1000001;
    const double fp1 = 1.1;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near4_okay) {
    const double fp0 = 1.10001;
    const double fp1 = 1.1;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}
TEST(fpe, expect_double_near5_fail) {
    const double fp0 = 1.10001;
    const double fp1 = 1.1;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near6_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    const double fp1 = 1.1;
    EXPECT_NEAR(fp0, fp1, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near7_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    EXPECT_NEAR(fp0, 1.1, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near8_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    EXPECT_NEAR(fp0, 1.1F, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near9_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    EXPECT_NEAR(1.1F, fp0, .000001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near10_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    EXPECT_NEAR(1.1F, fp0, .000001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near11_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
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
    const float  fp0 = 1.10001F;
    const double fp1 = 1.1;
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near16_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    const float fp1 = 1.1F;
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    const float fp1 = 1.1F;
    EXPECT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, expect_double_near18_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float  fp0 = 1.10001F;
    const double fp1 = 1.1;
    EXPECT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const double fp0 = 1.10001;
    const float  fp1 = 1.1F;
    EXPECT_NEAR(fp0, fp1, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near20_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    EXPECT_NEAR(fp0, 1.1, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near21_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    EXPECT_NEAR(fp0, 1.1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near22_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    EXPECT_NEAR(1.1, fp0, .0001F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_double_near23_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    EXPECT_NEAR(1.1, fp0, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

//
TEST(fpe, expect_long_double_near0_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.1L;
    const long double fp1 = 1.2L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, fp1, .1);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near1_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.2L;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, fp1, .0999);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near2_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.1L;
    const long double fp1 = 1.1000001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, fp1, .0001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near3_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.1000001L;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, fp1, .0001);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near4_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}
TEST(fpe, expect_long_double_near5_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, fp1, .000001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, expect_long_double_near6_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, fp1, .000001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near7_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, 1.1, .000001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near8_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, 1.1, .000001);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near9_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(1.1F, fp0, .000001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near10_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(1.1F, fp0, .000001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near11_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(1.1, fp0, .000001);
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
    const float       fp0 = 1.10001F;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near16_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    const float fp1 = 1.1F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    EXPECT_NEAR(fp0, fp1, .0001);
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near17_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    const float fp1 = 1.1F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


TEST(fpe, expect_long_double_near18_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float       fp0 = 1.10001F;
    const long double fp1 = 1.1L;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, fp1, .0001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near19_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const long double fp0 = 1.10001L;
    const float       fp1 = 1.1F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, fp1, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near20_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, 1.1L, .0001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near21_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(fp0, 1.1, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near22_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(1.1L, fp0, .0001F);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, expect_long_double_near23_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    const float fp0 = 1.10001F;
    TS_DISABLE_WIMPLICIT_FLOAT_CONVERSION_
    TS_DISABLE_WABSOLUTE_VALUE_
    EXPECT_NEAR(1.1L, fp0, .0001L);
    TS_REENABLE_WABSOLUTE_VALUE_
    TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
    /* NOLINTEND(*-magic-numbers) */
}


/* NOLINTBEGIN(llvmlibc-implementation-in-namespace) */
/* NOLINTBEGIN(modernize-use-trailing-return-type) */
/* NOLINTBEGIN(misc-use-anonymous-namespace) */
TS_DISABLE_WTEMPLATES_
template<typename T>
static inline T
get_type() {
#if (__cplusplus >= 201103L)
    T val{};
#else
    T val(0);
#endif
    return val;
}
TS_REENABLE_WTEMPLATES_
/* NOLINTEND(misc-use-anonymous-namespace) */
/* NOLINTEND(modernize-use-trailing-return-type) */
/* NOLINTEND(llvmlibc-implementation-in-namespace) */

TEST(cxx, assert_true0_okay) {
    ASSERT_TRUE(true);
}

TEST(acxx, assert_true1_fail) {
    ASSERT_TRUE(false);
}

TEST(cxx, assert_true2_skip_okay) {
    /* TODO: ASSERT_TRUE(TS_NULL_); */
}

TEST(cxx, assert_true3_fail) {
    ASSERT_TRUE(0);
}

TEST(cxx, assert_true4_okay) {
    ASSERT_TRUE(1);
}

TEST(cxx, assert_true5_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_TRUE(0.9);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, assert_true6_okay) {
    const int foo = 1;
    ASSERT_TRUE(foo);
}


TEST(cxx, assert_true7_fail) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    ASSERT_TRUE(get_type<long>());
    /* NOLINTEND(llvmlibc-callee-namespace) */
}

TEST(cxx, assert_true8_okay) {
    bool val = false;
    ASSERT_TRUE(val ^= true);
}

TEST(cxx, assert_true9_fail) {
    bool val = true;
    ASSERT_TRUE(val ^= true);
}


TEST(cxx, assert_false0_okay) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    ASSERT_FALSE(get_type<double>());
    /* NOLINTEND(llvmlibc-callee-namespace) */
}

TEST(cxx, assert_false1_okay) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    ASSERT_FALSE(get_type<void *>());
    /* NOLINTEND(llvmlibc-callee-namespace) */
}

TEST(cxx, assert_false2_skip_okay) {
    /* TODO: ASSERT_FALSE(TS_NULL_); */
}

TEST(cxx, assert_false3_fail) {
    const char foo = 'a';
    ASSERT_FALSE(foo);
}

TEST(cxx, assert_false4_fail) {
    ASSERT_FALSE(true);
}

TEST(cxx, assert_false5_fail) {
    ASSERT_FALSE(123);
}

TEST(cxx, assert_false6_fail) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_FALSE(reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, assert_false7_fail) {
    bool val = false;
    ASSERT_FALSE(val ^= true);
}

TEST(cxx, assert_false8_okay) {
    bool val = true;
    ASSERT_FALSE(val ^= true);
}


TEST(cxx, assert_eq0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_EQ(reinterpret_cast<void *>(1UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, assert_eq1_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_EQ(reinterpret_cast<char *>(1UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

#if EZTEST_WORD_SIZE_ == 64
TEST(cxx, assert_eq2_okay) {
    TS_DISABLE_WUSELESS_CAST_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_EQ(reinterpret_cast<uintptr_t>(1UL), 1UL);
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WUSELESS_CAST_
}
#endif

TEST(cxx, assert_eq3_fail) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_EQ(TS_NULL_, reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, assert_eq4_fail) {
    const int abc = 1;
    const int def = 2;
    ASSERT_EQ(abc, def);
}

TEST(cxx, assert_eq5_fail) {
    const int abc = 1;
    ASSERT_EQ(abc, 10 + 11);
}

TEST(cxx, assert_eq6_okay) {
    ASSERT_EQ(21, 10 + 11);
}

TEST(cxx, assert_eq7_okay) {
    int abc = 1;
    ASSERT_EQ(abc++, 1);
    ASSERT_EQ(2, abc++);
    ASSERT_EQ(abc++, 3);
    ASSERT_EQ(5, ++abc);
}


TEST(cxx, assert_eq8_fail) {
    int abc = 1;
    ASSERT_EQ(abc++, 1);
    ASSERT_EQ(abc++, 2);
    ASSERT_EQ(3, abc++);
    ASSERT_EQ(++abc, 4);
}

TEST(cxx, assert_eq9_okay) {
    TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_EQ(TS_NULL_, reinterpret_cast<void *>(0));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_
}

TEST(cxx, assert_ne0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_NE(reinterpret_cast<void *>(1UL), reinterpret_cast<void *>(2UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, assert_ne1_okay) {
    TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_NE(reinterpret_cast<char *>(0UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_
}

TEST(cxx, assert_ne2_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_NE(TS_NULL_, reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, assert_ne3_fail) {
    TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_NE(TS_NULL_, reinterpret_cast<void *>(0UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_
}
TEST(cxx, assert_ne4_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NE(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, assert_ne5_okay) {
    const double dbl(0);
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_NE(dbl, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, assert_ne6_okay) {
    ASSERT_NE(20 + 0, 10 + 11);
}

TEST(cxx, assert_ne7_okay) {
    int abc = 1;
    ASSERT_NE(abc++, 2);
    ASSERT_NE(abc++, 3);
    ASSERT_NE(abc++, 4);
    ASSERT_NE(++abc, 6);
}


TEST(cxx, assert_ne8_fail) {
    int abc = 1;
    ASSERT_NE(abc++, 2);
    ASSERT_NE(abc++, 3);
    ASSERT_NE(abc++, 4);
    ASSERT_NE(++abc, 5);
}

TEST(cxx, assert_le0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_LE(reinterpret_cast<void *>(1UL), reinterpret_cast<void *>(2UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, assert_le1_fail) {
    TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_LE(reinterpret_cast<char *>(1UL), reinterpret_cast<void *>(0UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_
}

TEST(cxx, assert_le2_skip_okay) {
    /* TODO: ASSERT_LE(TS_NULL_, reinterpret_cast<void *>(1UL)); */
}

TEST(cxx, assert_le3_skip_okay) {
    /* TODO: ASSERT_LE(TS_NULL_, reinterpret_cast<void *>(0UL)); */
}
TEST(cxx, assert_le4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LE(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, assert_le5_okay) {
    const double dbl(0);
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LE(dbl, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, assert_le6_okay) {
    ASSERT_LE(20 + 0, 10 + 11);
}

TEST(cxx, assert_le7_okay) {
    int abc = 1;
    ASSERT_LE(abc++, 1);
    ASSERT_LE(abc++, 2);
    ASSERT_LE(abc++, 3);
    ASSERT_LE(++abc, 5);
}


TEST(cxx, assert_le8_fail) {
    int abc = 1;
    ASSERT_LE(++abc, 2);
    ASSERT_LE(++abc, 3);
    ASSERT_LE(++abc, 4);
    ASSERT_LE(++abc, 4);
}

TEST(cxx, assert_gt0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_GT(reinterpret_cast<void *>(2UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, assert_gt1_fail) {
    TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_GT(reinterpret_cast<void *>(0UL), reinterpret_cast<char *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_
}

TEST(cxx, assert_gt2_skip_okay) {
    /* TODO: ASSERT_GT( reinterpret_cast<void *>(1UL),TS_NULL_); */
}

TEST(cxx, assert_gt3_skip_okay) {
    /* TODO: ASSERT_GT( reinterpret_cast<void *>(0UL),TS_NULL_); */
}
TEST(cxx, assert_gt4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GT(10, 20.1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, assert_gt5_okay) {
    const double dbl(0);
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GT(10.5F, dbl);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, assert_gt6_okay) {
    ASSERT_GT(10 + 11, 20 + 0);
}

TEST(cxx, assert_gt7_okay) {
    int abc = 1;
    ASSERT_GT(++abc, 1);
    ASSERT_GT(++abc, 2);
    ASSERT_GT(++abc, 3);
    ASSERT_GT(++abc, 4);
}


TEST(cxx, assert_gt8_fail) {
    int abc = 1;
    ASSERT_GT(++abc, 1);
    ASSERT_GT(++abc, 2);
    ASSERT_GT(++abc, 3);
    ASSERT_GT(abc++, 4);
}


TEST(cxx, assert_lt0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_LT(reinterpret_cast<void *>(1UL), reinterpret_cast<void *>(2UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, assert_lt1_fail) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_LT(reinterpret_cast<char *>(1UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, assert_lt2_skip_okay) {
    /* TODO: ASSERT_LT(TS_NULL_, reinterpret_cast<void *>(1UL)); */
}

TEST(cxx, assert_lt3_skip_okay) {
    /* TODO: ASSERT_LT(TS_NULL_, reinterpret_cast<void *>(0UL)); */
}
TEST(cxx, assert_lt4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LT(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, assert_lt5_okay) {
    const float flt = 0;
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_LT(flt, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, assert_lt6_okay) {
    ASSERT_LT(20 + 0, 10 + 11);
}

TEST(cxx, assert_lt7_okay) {
    int abc = 1;
    ASSERT_LT(abc++, 2);
    ASSERT_LT(abc++, 3);
    ASSERT_LT(abc++, 4);
    ASSERT_LT(++abc, 6);
}


TEST(cxx, assert_lt8_fail) {
    int abc = 1;
    ASSERT_LT(abc++, 2);
    ASSERT_LT(abc++, 3);
    ASSERT_LT(abc++, 4);
    ASSERT_LT(++abc, 5);
}

TEST(cxx, assert_lt9_okay) {
    int abc = 1;
    ASSERT_LT(abc++, 2);
    ASSERT_LT(abc++, 3);
    ASSERT_LT(abc++, 4);
    ASSERT_LT(4, ++abc);
}


TEST(cxx, assert_ge0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_GE(reinterpret_cast<void *>(2UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, assert_ge1_fail) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    ASSERT_GE(reinterpret_cast<void *>(1UL), reinterpret_cast<char *>(2UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, assert_ge2_skip_okay) {
    /* TODO: ASSERT_GE( reinterpret_cast<void *>(1UL),TS_NULL_); */
}

TEST(cxx, assert_ge3_skip_okay) {
    /* TODO: ASSERT_GE( reinterpret_cast<void *>(0UL),TS_NULL_); */
}
TEST(cxx, assert_ge4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GE(10, 20.1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, assert_ge5_okay) {
    const float flt(0);
    /* NOLINTBEGIN(*-magic-numbers) */
    ASSERT_GE(10.5F, flt);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, assert_ge6_okay) {
    ASSERT_GE(char(10 + 11), 20 + 1);
}

TEST(cxx, assert_ge7_okay) {
    int abc = 1;
    ASSERT_GE(2, abc++);
    ASSERT_GE(3, abc++);
    ASSERT_GE(4, abc++);
    ASSERT_GE(6, ++abc);
}


TEST(cxx, assert_ge8_fail) {
    int abc = 1;
    ASSERT_GE(2, abc++);
    ASSERT_GE(3, abc++);
    ASSERT_GE(4, abc++);
    ASSERT_GE(4, ++abc);
}

TEST(cxx, assert_ge9_okay) {
    int abc = 1;
    ASSERT_GE(2, abc++);
    ASSERT_GE(3, abc++);
    ASSERT_GE(4, abc++);
    ASSERT_GE(++abc, 4);
}

TEST(cxx, assert_streq0_okay) {
    ASSERT_STREQ("", "");
}

TEST(cxx, assert_streq1_fail) {
    ASSERT_STREQ("abc", "abcd");
}

TEST(cxx, assert_streq2_fail) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STREQ("abc", buf);
}

TEST(cxx, assert_streq3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STREQ(buf0, buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STREQ(buf0, buf1);
}

TEST(cxx, assert_streq4_fail) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STREQ(buf0, "abcd");
    ASSERT_STREQ("abcd", buf0);
    ASSERT_STREQ("abCd", buf0);
}

TEST(cxx, assert_streq5_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STREQ(buf0, "");
}


TEST(cxx, assert_strne0_fail) {
    ASSERT_STRNE("", "");
}

TEST(cxx, assert_strne1_okay) {
    ASSERT_STRNE("abc", "abcd");
}

TEST(cxx, assert_strne2_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STRNE("abc", buf);
}

TEST(cxx, assert_strne3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 2;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRNE(buf0, buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRNE(buf0, buf1);
}

TEST(cxx, assert_strne4_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STRNE(buf0, "bcd");
    ASSERT_STRNE("abc", buf0);
    ASSERT_STRNE("abCd", buf0);
}

TEST(cxx, assert_strne5_fail) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STRNE(buf0, "");
}

TEST(cxx, assert_strcaseeq0_okay) {
    ASSERT_STRCASEEQ("", "");
}

TEST(cxx, assert_strcaseeq1_fail) {
    ASSERT_STRCASEEQ("abc", "abCd");
}

TEST(cxx, assert_strcaseeq2_fail) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STRCASEEQ("abc", buf);
}

TEST(cxx, assert_strcaseeq3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASEEQ(buf0, buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASEEQ(buf0, buf1);
}

TEST(cxx, assert_strcaseeq4_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { 'A', 'b', 'c', 'D', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STRCASEEQ(buf0, "abcd");
    ASSERT_STRCASEEQ("abcd", buf0);
    ASSERT_STRCASEEQ("abCd", buf0);
}

TEST(cxx, assert_strcaseeq5_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STRCASEEQ(buf0, "");
}

TEST(cxx, assert_strcaseeq6_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { '0', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STRCASEEQ(buf0, "0BcD");
}


TEST(cxx, assert_strcasene0_fail) {
    ASSERT_STRCASENE("", "");
}

TEST(cxx, assert_strcasene1_okay) {
    ASSERT_STRCASENE("abc", "abcd");
}

TEST(cxx, assert_strcasene2_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf[] = { 1, 2, 'C', 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STRCASENE("abC", buf);
}

TEST(cxx, assert_strcasene3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    char       buf0[] = { 'a', 2, 3, 4, 0 };
    const char buf1[] = { 'A', 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASENE(buf0, buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 2;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    ASSERT_STRCASENE(buf0, buf1);
}

TEST(cxx, assert_strcasene4_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STRCASENE(buf0, "ABCCD");
    ASSERT_STRCASENE("abc", buf0);
    ASSERT_STRCASENE("ab0d", buf0);
}

TEST(cxx, assert_strcasene5_fail) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    ASSERT_STRCASENE(buf0, "");
}
TEST(cxx, assert_strcasene6_fail) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    ASSERT_STRCASENE("ABc", "abc", "They be eq: %s/%s (%d)\n", "hello", "world",
                     0);
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}
TEST(d, assert_strcasene7_fail) {
    ASSERT_STRCASENE("ABc1", "abc1");
}
TEST(c, assert_strcasene8_okay) {
    ASSERT_STRCASENE("ABc0", "abc1");
}


TEST(cxx, DISABLED_foo_okay) {
    ASSERT_TRUE(false);
}
TEST(cxx, DISABLED_bar_okay) {
    ASSERT_FALSE(false);
}
TEST(cxx, DISABLED_buz_okay) {
    ASSERT_FALSE(true);
}

TEST(dxx, DISABLED_baz_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    ASSERT_FALSE(true, "I OBVIOUSLY FAILED!");
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}
TEST(a_way_to_overly_long_group_name_that_make_it_not_nice_to_fmt,
     assert_true1_fail) {
    ASSERT_TRUE(false);
}

TEST_TIMED(a_moderately_long_group_name, assert_true1_fail, 50000) {
    ASSERT_TRUE(false);
}

TEST(a_modestly_long_group_name, assert_true1_fail) {
    ASSERT_TRUE(false);
}
TEST(a_mid_long_group_name, assert_true1_fail) {
    ASSERT_TRUE(false);
}

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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_FLOAT_EQ(fp0, fp1);
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
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    EXPECT_FLOAT_EQ(fp0, fp1);
}


TEST(fpe, assert_double_eq0_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeee);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeef);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq1_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeec);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq2_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbeea);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq3_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbee9);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq4_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0xdeadbeef, 0xdeadbeed);
    bits1 = ts_uint64_c(0xdeadbeef, 0xdeadbee8);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq5_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x7ff80000, 0x00000000);
    bits1 = ts_uint64_c(0x7ff80000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq6_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq7_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x80000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}
TEST(fpe, assert_double_eq8_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000000);
    bits1 = ts_uint64_c(0x00000000, 0x00000001);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq9_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000004);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}


TEST(fpe, assert_double_eq10_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000005);
    bits1 = ts_uint64_c(0x00000000, 0x00000000);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq11_okay) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000002);
    bits1 = ts_uint64_c(0x80000000, 0x00000002);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    /* NOLINTBEGIN(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    /* NOLINTEND(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
     */

    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_eq12_fail) {
    uint64_t bits0 = 0;
    uint64_t bits1 = 0;
    double   fp0   = 0.0F;
    double   fp1   = 0.0F;
    /* NOLINTBEGIN(*-magic-numbers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    bits0 = ts_uint64_c(0x00000000, 0x00000003);
    bits1 = ts_uint64_c(0x80000000, 0x00000002);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTEND(*-magic-numbers) */
    std::memcpy(&fp0, &bits0, sizeof(bits0));
    std::memcpy(&fp1, &bits1, sizeof(bits1));
    EXPECT_DOUBLE_EQ(fp0, fp1);
}

TEST(fpe, assert_double_near0_okay) {
    const double fp0 = 1.1;
    const double fp1 = 1.2;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near1_fail) {
    const double fp0 = 1.1;
    const double fp1 = 1.2;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .0999);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near2_okay) {
    const double fp0 = 1.1;
    const double fp1 = 1.1000001;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near3_okay) {
    const double fp0 = 1.1000001;
    const double fp1 = 1.1;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(fpe, assert_double_near4_okay) {
    const double fp0 = 1.10001;
    const double fp1 = 1.1;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .0001);
    /* NOLINTEND(*-magic-numbers) */
}
TEST(fpe, assert_double_near5_fail) {
    const double fp0 = 1.10001;
    const double fp1 = 1.1;
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NEAR(fp0, fp1, .000001);
    /* NOLINTEND(*-magic-numbers) */
}


TEST(cxx, expect_true0_okay) {
    EXPECT_TRUE(true);
}

TEST(acxx, expect_true1_fail) {
    EXPECT_TRUE(false);
}

TEST(cxx, expect_true2_skip_okay) {
    /* TODO EXPECT_TRUE(TS_NULL_); */
}

TEST(cxx, expect_true3_fail) {
    EXPECT_TRUE(0);
}

TEST(cxx, expect_true4_okay) {
    EXPECT_TRUE(1);
}

TEST(cxx, expect_true5_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_TRUE(0.9);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, expect_true6_okay) {
    const int foo = 1;
    EXPECT_TRUE(foo);
}


TEST(cxx, expect_true7_fail) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    EXPECT_TRUE(get_type<long>());
    /* NOLINTEND(llvmlibc-callee-namespace) */
}

TEST(cxx, expect_true8_okay) {
    bool val = false;
    EXPECT_TRUE(val ^= true);
}

TEST(cxx, expect_true9_fail) {
    bool val = true;
    EXPECT_TRUE(val ^= true);
}


TEST(cxx, expect_false0_okay) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    EXPECT_FALSE(get_type<double>());
    /* NOLINTEND(llvmlibc-callee-namespace) */
}

TEST(cxx, expect_false1_okay) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    EXPECT_FALSE(get_type<void *>());
    /* NOLINTEND(llvmlibc-callee-namespace) */
}

TEST(cxx, expect_false2_skip_okay) {
    /* TODO: EXPECT_FALSE(TS_NULL_); */
}

TEST(cxx, expect_false3_fail) {
    const char foo = 'a';
    EXPECT_FALSE(foo);
}

TEST(cxx, expect_false4_fail) {
    EXPECT_FALSE(true);
}

TEST(cxx, expect_false5_fail) {
    EXPECT_FALSE(123);
}

TEST(cxx, expect_false6_fail) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_FALSE(reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, expect_false7_fail) {
    bool val = false;
    EXPECT_FALSE(val ^= true);
}

TEST(cxx, expect_false8_okay) {
    bool val = true;
    EXPECT_FALSE(val ^= true);
}


TEST(cxx, expect_eq0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_EQ(reinterpret_cast<void *>(1UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, expect_eq1_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_EQ(reinterpret_cast<char *>(1UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}
#if EZTEST_WORD_SIZE_ == 64
TEST(cxx, expect_eq2_okay) {
    TS_DISABLE_WUSELESS_CAST_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_EQ(reinterpret_cast<uintptr_t>(1UL), 1UL);
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WUSELESS_CAST_
}
#endif

TEST(cxx, expect_eq3_fail) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_EQ(TS_NULL_, reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, expect_eq4_fail) {
    const int abc = 1;
    const int def = 2;
    EXPECT_EQ(abc, def);
}

TEST(cxx, expect_eq5_fail) {
    const int abc = 1;
    EXPECT_EQ(abc, 10 + 11);
}

TEST(cxx, expect_eq6_okay) {
    EXPECT_EQ(21, 10 + 11);
}

TEST(cxx, expect_eq7_okay) {
    int abc = 1;
    EXPECT_EQ(abc++, 1);
    EXPECT_EQ(2, abc++);
    EXPECT_EQ(abc++, 3);
    EXPECT_EQ(5, ++abc);
}


TEST(cxx, expect_eq8_fail) {
    int abc = 1;
    EXPECT_EQ(abc++, 1);
    EXPECT_EQ(abc++, 2);
    EXPECT_EQ(3, abc++);
    EXPECT_EQ(++abc, 4);
}

TEST(cxx, expect_eq9_okay) {
    TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_EQ(TS_NULL_, reinterpret_cast<void *>(0));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_
}

TEST(cxx, expect_ne0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_NE(reinterpret_cast<void *>(1UL), reinterpret_cast<void *>(2UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, expect_ne1_okay) {
    TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_NE(reinterpret_cast<char *>(0UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_
}

TEST(cxx, expect_ne2_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_NE(TS_NULL_, reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, expect_ne3_fail) {
    TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_NE(TS_NULL_, reinterpret_cast<void *>(0UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_
}
TEST(cxx, expect_ne4_okay) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NE(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, expect_ne5_okay) {
    const double dbl(0);
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_NE(dbl, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, expect_ne6_okay) {
    EXPECT_NE(20 + 0, 10 + 11);
}

TEST(cxx, expect_ne7_okay) {
    int abc = 1;
    EXPECT_NE(abc++, 2);
    EXPECT_NE(abc++, 3);
    EXPECT_NE(abc++, 4);
    EXPECT_NE(++abc, 6);
}


TEST(cxx, expect_ne8_fail) {
    int abc = 1;
    EXPECT_NE(abc++, 2);
    EXPECT_NE(abc++, 3);
    EXPECT_NE(abc++, 4);
    EXPECT_NE(++abc, 5);
}

TEST(cxx, expect_le0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_LE(reinterpret_cast<void *>(1UL), reinterpret_cast<void *>(2UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, expect_le1_fail) {
    TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_LE(reinterpret_cast<char *>(1UL), reinterpret_cast<void *>(0UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_
}

TEST(cxx, expect_le2_skip_okay) {
    /* TODO: EXPECT_LE(TS_NULL_, reinterpret_cast<void *>(1UL)); */
}

TEST(cxx, expect_le3_skip_okay) {
    /* TODO: EXPECT_LE(TS_NULL_, reinterpret_cast<void *>(0UL)); */
}
TEST(cxx, expect_le4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LE(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, expect_le5_okay) {
    const double dbl(0);
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LE(dbl, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, expect_le6_okay) {
    EXPECT_LE(20 + 0, 10 + 11);
}

TEST(cxx, expect_le7_okay) {
    int abc = 1;
    EXPECT_LE(abc++, 1);
    EXPECT_LE(abc++, 2);
    EXPECT_LE(abc++, 3);
    EXPECT_LE(++abc, 5);
}


TEST(cxx, expect_le8_fail) {
    int abc = 1;
    EXPECT_LE(++abc, 2);
    EXPECT_LE(++abc, 3);
    EXPECT_LE(++abc, 4);
    EXPECT_LE(++abc, 4);
}

TEST(cxx, expect_gt0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_GT(reinterpret_cast<void *>(2UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, expect_gt1_fail) {
    TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_GT(reinterpret_cast<void *>(0UL), reinterpret_cast<char *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
    TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_
}

TEST(cxx, expect_gt2_skip_okay) {
    /* TODO: EXPECT_GT( reinterpret_cast<void *>(1UL),TS_NULL_); */
}

TEST(cxx, expect_gt3_skip_okay) {
    /* TODO: EXPECT_GT( reinterpret_cast<void *>(0UL),TS_NULL_); */
}
TEST(cxx, expect_gt4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GT(10, 20.1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, expect_gt5_okay) {
    const double dbl(0);
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GT(10.5F, dbl);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, expect_gt6_okay) {
    EXPECT_GT(10 + 11, 20 + 0);
}

TEST(cxx, expect_gt7_okay) {
    int abc = 1;
    EXPECT_GT(++abc, 1);
    EXPECT_GT(++abc, 2);
    EXPECT_GT(++abc, 3);
    EXPECT_GT(++abc, 4);
}


TEST(cxx, expect_gt8_fail) {
    int abc = 1;
    EXPECT_GT(++abc, 1);
    EXPECT_GT(++abc, 2);
    EXPECT_GT(++abc, 3);
    EXPECT_GT(abc++, 4);
}


TEST(cxx, expect_lt0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_LT(reinterpret_cast<void *>(1UL), reinterpret_cast<void *>(2UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, expect_lt1_fail) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_LT(reinterpret_cast<char *>(1UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, expect_lt2_skip_okay) {
    /* TODO: EXPECT_LT(TS_NULL_, reinterpret_cast<void *>(1UL)); */
}

TEST(cxx, expect_lt3_skip_okay) {
    /* TODO: EXPECT_LT(TS_NULL_, reinterpret_cast<void *>(0UL)); */
}
TEST(cxx, expect_lt4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LT(20.1, 10);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, expect_lt5_okay) {
    const float flt(0);
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_LT(flt, 10.5F);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, expect_lt6_okay) {
    EXPECT_LT(20 + 0, 10 + 11);
}

TEST(cxx, expect_lt7_okay) {
    int abc = 1;
    EXPECT_LT(abc++, 2);
    EXPECT_LT(abc++, 3);
    EXPECT_LT(abc++, 4);
    EXPECT_LT(++abc, 6);
}


TEST(cxx, expect_lt8_fail) {
    int abc = 1;
    EXPECT_LT(abc++, 2);
    EXPECT_LT(abc++, 3);
    EXPECT_LT(abc++, 4);
    EXPECT_LT(++abc, 5);
}

TEST(cxx, expect_lt9_okay) {
    int abc = 1;
    EXPECT_LT(abc++, 2);
    EXPECT_LT(abc++, 3);
    EXPECT_LT(abc++, 4);
    EXPECT_LT(4, ++abc);
}


TEST(cxx, expect_ge0_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_GE(reinterpret_cast<void *>(2UL), reinterpret_cast<void *>(1UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, expect_ge1_fail) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    EXPECT_GE(reinterpret_cast<void *>(1UL), reinterpret_cast<char *>(2UL));
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
}

TEST(cxx, expect_ge2_skip_okay) {
    /* TODO: EXPECT_GE( reinterpret_cast<void *>(1UL),TS_NULL_); */
}

TEST(cxx, expect_ge3_skip_okay) {
    /* TODO: EXPECT_GE( reinterpret_cast<void *>(0UL),TS_NULL_); */
}
TEST(cxx, expect_ge4_fail) {
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GE(10, 20.1);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, expect_ge5_okay) {
    const float flt(0);
    /* NOLINTBEGIN(*-magic-numbers) */
    EXPECT_GE(10.5F, flt);
    /* NOLINTEND(*-magic-numbers) */
}

TEST(cxx, expect_ge6_okay) {
    EXPECT_GE(char(10 + 11), 20 + 1);
}

TEST(cxx, expect_ge7_okay) {
    int abc = 1;
    EXPECT_GE(2, abc++);
    EXPECT_GE(3, abc++);
    EXPECT_GE(4, abc++);
    EXPECT_GE(6, ++abc);
}


TEST(cxx, expect_ge8_fail) {
    int abc = 1;
    EXPECT_GE(2, abc++);
    EXPECT_GE(3, abc++);
    EXPECT_GE(4, abc++);
    EXPECT_GE(4, ++abc);
}

TEST(cxx, expect_ge9_okay) {
    int abc = 1;
    EXPECT_GE(2, abc++);
    EXPECT_GE(3, abc++);
    EXPECT_GE(4, abc++);
    EXPECT_GE(++abc, 4);
}

TEST(cxx, expect_streq0_okay) {
    EXPECT_STREQ("", "");
}

TEST(cxx, expect_streq1_fail) {
    EXPECT_STREQ("abc", "abcd");
}

TEST(cxx, expect_streq2_fail) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STREQ("abc", buf);
}

TEST(cxx, expect_streq3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STREQ(buf0, buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STREQ(buf0, buf1);
}

TEST(cxx, expect_streq4_fail) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STREQ(buf0, "abcd");
    EXPECT_STREQ("abcd", buf0);
    EXPECT_STREQ("abCd", buf0);
}

TEST(cxx, expect_streq5_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STREQ(buf0, "");
}


TEST(cxx, expect_strne0_fail) {
    EXPECT_STRNE("", "");
}

TEST(cxx, expect_strne1_okay) {
    EXPECT_STRNE("abc", "abcd");
}

TEST(cxx, expect_strne2_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STRNE("abc", buf);
}

TEST(cxx, expect_strne3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 2;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRNE(buf0, buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRNE(buf0, buf1);
}

TEST(cxx, expect_strne4_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STRNE(buf0, "bcd");
    EXPECT_STRNE("abc", buf0);
    EXPECT_STRNE("abCd", buf0);
}

TEST(cxx, expect_strne5_fail) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STRNE(buf0, "");
}

TEST(cxx, expect_strcaseeq0_okay) {
    EXPECT_STRCASEEQ("", "");
}

TEST(cxx, expect_strcaseeq1_fail) {
    EXPECT_STRCASEEQ("abc", "abCd");
}

TEST(cxx, expect_strcaseeq2_fail) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STRCASEEQ("abc", buf);
}

TEST(cxx, expect_strcaseeq3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    char       buf0[] = { 1, 2, 3, 4, 0 };
    const char buf1[] = { 1, 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRCASEEQ(buf0, buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRCASEEQ(buf0, buf1);
}

TEST(cxx, expect_strcaseeq4_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { 'A', 'b', 'c', 'D', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STRCASEEQ(buf0, "abcd");
    EXPECT_STRCASEEQ("abcd", buf0);
    EXPECT_STRCASEEQ("abCd", buf0);
}

TEST(cxx, expect_strcaseeq5_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STRCASEEQ(buf0, "");
}

TEST(cxx, expect_strcaseeq6_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { '0', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STRCASEEQ(buf0, "0BcD");
}


TEST(cxx, expect_strcasene0_fail) {
    EXPECT_STRCASENE("", "");
}

TEST(cxx, expect_strcasene1_okay) {
    EXPECT_STRCASENE("abc", "abcd");
}

TEST(cxx, expect_strcasene2_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf[] = { 1, 2, 'C', 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STRCASENE("abC", buf);
}

TEST(cxx, expect_strcasene3_fail) {
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    char       buf0[] = { 'a', 2, 3, 4, 0 };
    const char buf1[] = { 'A', 2, 3, 4, 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 1;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRCASENE(buf0, buf1);
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    buf0[1] = 2;
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    EXPECT_STRCASENE(buf0, buf1);
}

TEST(cxx, expect_strcasene4_okay) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { 'a', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STRCASENE(buf0, "ABCCD");
    EXPECT_STRCASENE("abc", buf0);
    EXPECT_STRCASENE("ab0d", buf0);
}

TEST(cxx, expect_strcasene5_fail) {
    /* NOLINTBEGIN(*-avoid-c-arrays) */
    const char buf0[] = { '\0', 'b', 'c', 'd', 0 };
    /* NOLINTEND(*-avoid-c-arrays) */
    EXPECT_STRCASENE(buf0, "");
}
TEST(cxx, expect_strcasene6_fail) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    EXPECT_STRCASENE("ABc", "abc", "They be eq: %s/%s (%d)\n", "hello", "world",
                     0);
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}
TEST(d, expect_strcasene7_fail) {
    EXPECT_STRCASENE("ABc1", "abc1");
}
TEST(c, expect_strcasene8_okay) {
    EXPECT_STRCASENE("ABc0", "abc1");
}


TEST(cxx, DISABLED_foo_okay) {
    EXPECT_TRUE(false);
}
TEST(cxx, DISABLED_bar_okay) {
    EXPECT_FALSE(false);
}
TEST(cxx, DISABLED_buz_okay) {
    EXPECT_FALSE(true);
}

TEST(dxx, DISABLED_baz_okay) {
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    EXPECT_FALSE(true, "I OBVIOUSLY FAILED!");
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}
TEST(a_way_to_overly_long_group_name_that_make_it_not_nice_to_fmt,
     expect_true1_fail) {
    EXPECT_TRUE(false);
}

TEST(a_moderately_long_group_name, expect_true1_fail) {
    EXPECT_TRUE(false);
}
TEST(a_modestly_long_group_name, expect_true1_fail) {
    EXPECT_TRUE(false);
}
TEST(a_mid_long_group_name, expect_true1_fail) {
    EXPECT_TRUE(false);
}

TEST_TIMED(timeouts, 10ms_timefail, 10) {
    while (true) {
        /* NOLINTBEGIN(hicpp-no-assembler) */
        __asm__ volatile("" ::: "memory");
        /* NOLINTEND(hicpp-no-assembler) */
    }
}

TEST_TIMED(timeouts, 50ms_timefail, 50) {
    while (true) {
        /* NOLINTBEGIN(hicpp-no-assembler) */
        __asm__ volatile("" ::: "memory");
        /* NOLINTEND(hicpp-no-assembler) */
    }
}


TEST_TIMED(timeouts, 1000ms_timefail, 1000) {
    while (true) {
        /* NOLINTBEGIN(hicpp-no-assembler) */
        __asm__ volatile("" ::: "memory");
        /* NOLINTEND(hicpp-no-assembler) */
    }
}

TEST_TIMED(timeouts, 1ms_timefail, 1) {
    while (true) {
        /* NOLINTBEGIN(hicpp-no-assembler) */
        __asm__ volatile("" ::: "memory");
        /* NOLINTEND(hicpp-no-assembler) */
    }
}

TEST_TIMED(timeouts, 100ms_okay, 50000) {
    ASSERT_TRUE(true);
}

TEST_TIMED(timeouts, 100ms_bad0_fail, 50000) {
    ASSERT_TRUE(false);
}

TEST_TIMED(timeouts, 100ms_okay_fail, 50000) {
    EXPECT_TRUE(false);
    EXPECT_TRUE(false);
    EXPECT_TRUE(true);
}

TEST_TIMED(timeouts, 100ms_bad_sig_sigfail, 50000) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    TS_KILL_(getpid(), SIGKILL);
    /* NOLINTEND(llvmlibc-callee-namespace) */
}

TEST(sigs, sigkill_self_sigfail) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    TS_KILL_(getpid(), SIGKILL);
    /* NOLINTEND(llvmlibc-callee-namespace) */
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
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    int * ptr = reinterpret_cast<int *>(1UL);
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */
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
    EXPECT_TRUE(false);
    /* NOLINTBEGIN(google-runtime-int) */
    long val = 0;
    /* NOLINTEND(google-runtime-int) */
    /* NOLINTBEGIN(hicpp-no-assembler) */
    __asm__ volatile("" : "+r"(val) : : "memory");
    /* NOLINTEND(hicpp-no-assembler) */
    /* NOLINTBEGIN(*-magic-numbers) */
    val = 1231L / val;
    /* NOLINTEND(*-magic-numbers) */
    ASSERT_TRUE(val);
}
#elif EZTEST_ARCH_IS_AARCH64_
TEST(sigs, fpe_self_fail) {
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
TS_REENABLE_WSUGGEST_ATTRIBUTE_PURE_
TS_REENABLE_WCXX98_COMPAT_
TS_REENABLE_WDOUBLE_PROMOTION_
TS_REENABLE_WFLOAT_EQUAL_
TS_REENABLE_WFLOAT_CONVERSION_
TS_REENABLE_WMISSING_NORETURN_
TS_REENABLE_WSTACK_PROTECTOR_
TS_REENABLE_WIMPLICIT_FLOAT_CONVERSION_
/* NOLINTEND(altera-unroll-loops) */
