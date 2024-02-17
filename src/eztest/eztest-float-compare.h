#ifndef EZTEST_D_EZTEST_D_EZTEST_FLOAT_COMPARE_H_
#define EZTEST_D_EZTEST_D_EZTEST_FLOAT_COMPARE_H_

#include "eztest-compiler.h"
#include "eztest-lang.h"
#include "eztest-libc.h"
#include "eztest-libm.h"


EZTEST_NAMESPACE_BEGIN_

#define EZTEST_FP_ULP_COMPARE_INVALID_ (~(EZTEST_CAST_(uint64_t, 0)))
EZTEST_DISABLE_WUNUSED_FUNCTION_
/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */

EZTEST_PRIVATE_ uint64_t
eztest_fp_bits_get_sam(uint64_t              eztest_fp_bits,
                       uint64_t              eztest_fp_signbit,
                       EZTEST_STD_NS_ size_t eztest_fp_bytes) {

    /* NOLINTEND(bugprone-easily-swappable-parameters) */

    if ((eztest_fp_bits & eztest_fp_signbit) != 0) {
        const uint64_t eztest_bits_shift =
            CHAR_BIT *
            ((sizeof(uint64_t) - eztest_fp_bytes) % sizeof(uint64_t));
        eztest_fp_bits = ~eztest_fp_bits;
        eztest_fp_bits++;
        eztest_fp_bits <<= eztest_bits_shift;
        eztest_fp_bits >>= eztest_bits_shift;
        return eztest_fp_bits;
    }
    return eztest_fp_bits | eztest_fp_signbit;
}


EZTEST_PRIVATE_ uint64_t
eztest_fp_bits_get_signmask(uint64_t eztest_fp_bits_1,
                            uint64_t eztest_fp_bits_m1) {

    eztest_fp_bits_1 ^= eztest_fp_bits_m1;
    if ((eztest_fp_bits_1 & (eztest_fp_bits_1 - 1)) != 0) {
        return 0;
    }
    return eztest_fp_bits_1;
}

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */

EZTEST_PRIVATE_ uint64_t
eztest_fp_bits_get_ulp(uint64_t              eztest_fp_bits_lhs,
                       uint64_t              eztest_fp_bits_rhs,
                       uint64_t              eztest_fp_bits_1,
                       uint64_t              eztest_fp_bits_m1,
                       EZTEST_STD_NS_ size_t eztest_fp_size) {

    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* This should portably isolate the sign bits.  */
    const uint64_t eztest_fp_bits_signmask =
        EZTEST_NS_ eztest_fp_bits_get_signmask(eztest_fp_bits_1,
                                               eztest_fp_bits_m1);
    /* If we didn't isolate the signbit, then just fallback to "==".  */
    if (eztest_fp_bits_signmask == 0) {
        return EZTEST_FP_ULP_COMPARE_INVALID_;
    }

    eztest_fp_bits_lhs = EZTEST_NS_ eztest_fp_bits_get_sam(
        eztest_fp_bits_lhs, eztest_fp_bits_signmask, eztest_fp_size);

    eztest_fp_bits_rhs = EZTEST_NS_ eztest_fp_bits_get_sam(
        eztest_fp_bits_rhs, eztest_fp_bits_signmask, eztest_fp_size);

    return (eztest_fp_bits_lhs >= eztest_fp_bits_rhs)
               ? (eztest_fp_bits_lhs - eztest_fp_bits_rhs)
               : (eztest_fp_bits_rhs - eztest_fp_bits_lhs);
}

#define EZTEST_BITCAST_FP_TO_U64_(ty_t, fp, u64_out)                           \
 /* NOLINTBEGIN(cppcoreguide*-avoid-do-while) */                               \
 do {                                                                          \
  ty_t eztest_fp_tmp_ = fp;                                                    \
  (u64_out)           = 0;                                                     \
  /* NOLINTBEGIN(clang-a*-sec*.insecureAPI.Depr*OrUnsafeBufferHandling) */     \
  EZTEST_MEMCPY_(&(u64_out), &eztest_fp_tmp_, sizeof(ty_t));                   \
  /* NOLINTEND(clang-a*-sec*.insecureAPI.Depr*OrUnsafeBufferHandling) */       \
 } while (0) /* NOLINTEND(cppcoreguide*-avoid-do-while) */


EZTEST_PRIVATE_ int
eztest_flt_compare(float eztest_fp_lhs, float eztest_fp_rhs) {

    uint64_t eztest_flt_ulp = 0;
    uint64_t eztest_u64_lhs = 0;
    uint64_t eztest_u64_rhs = 0;
    uint64_t eztest_u64_1f  = 0;
    uint64_t eztest_u64_m1f = 0;
    if (EZTEST_ISNAN_(eztest_fp_lhs) || EZTEST_ISNAN_(eztest_fp_rhs)) {
        return 0;
    }
    EZTEST_BITCAST_FP_TO_U64_(float, eztest_fp_lhs, eztest_u64_lhs);
    EZTEST_BITCAST_FP_TO_U64_(float, eztest_fp_rhs, eztest_u64_rhs);
    EZTEST_BITCAST_FP_TO_U64_(float, 1.0F, eztest_u64_1f);
    EZTEST_BITCAST_FP_TO_U64_(float, -1.0F, eztest_u64_m1f);


    eztest_flt_ulp = EZTEST_NS_ eztest_fp_bits_get_ulp(
        eztest_u64_lhs, eztest_u64_rhs, eztest_u64_1f, eztest_u64_m1f,
        sizeof(float));

    if (eztest_flt_ulp == EZTEST_FP_ULP_COMPARE_INVALID_) {
        EZTEST_DISABLE_WFLOAT_EQUAL_
        return EZTEST_CAST_(int, eztest_fp_lhs == eztest_fp_rhs);
        EZTEST_REENABLE_WFLOAT_EQUAL_
    }
    return EZTEST_CAST_(int, eztest_flt_ulp <= EZTEST_FLOAT_ULP_PRECISION);
}


EZTEST_PRIVATE_ int
eztest_dbl_compare(double eztest_fp_lhs, double eztest_fp_rhs) {

    uint64_t eztest_dbl_ulp = 0;
    uint64_t eztest_u64_lhs = 0;
    uint64_t eztest_u64_rhs = 0;
    uint64_t eztest_u64_1d  = 0;
    uint64_t eztest_u64_m1d = 0;
    if (EZTEST_ISNAN_(eztest_fp_lhs) || EZTEST_ISNAN_(eztest_fp_rhs)) {
        return 0;
    }
    EZTEST_BITCAST_FP_TO_U64_(double, eztest_fp_lhs, eztest_u64_lhs);
    EZTEST_BITCAST_FP_TO_U64_(double, eztest_fp_rhs, eztest_u64_rhs);
    EZTEST_DISABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
    EZTEST_BITCAST_FP_TO_U64_(double, 1.0, eztest_u64_1d);
    EZTEST_BITCAST_FP_TO_U64_(double, -1.0, eztest_u64_m1d);
    EZTEST_REENABLE_WUNSUFFIXED_FLOAT_CONSTANTS_


    eztest_dbl_ulp = EZTEST_NS_ eztest_fp_bits_get_ulp(
        eztest_u64_lhs, eztest_u64_rhs, eztest_u64_1d, eztest_u64_m1d,
        sizeof(double));

    if (eztest_dbl_ulp == EZTEST_FP_ULP_COMPARE_INVALID_) {
        EZTEST_DISABLE_WFLOAT_EQUAL_
        return EZTEST_CAST_(int, eztest_fp_lhs == eztest_fp_rhs);
        EZTEST_REENABLE_WFLOAT_EQUAL_
    }
    return EZTEST_CAST_(int, eztest_dbl_ulp <= EZTEST_DOUBLE_ULP_PRECISION);
}
EZTEST_REENABLE_WUNUSED_FUNCTION_
EZTEST_NAMESPACE_END_


#endif
