#ifndef EZTEST_D_EZTEST_D_EZTEST_H_
#define EZTEST_D_EZTEST_D_EZTEST_H_

/* NOLINTBEGIN(altera-unroll-loops) */
/* NOLINTBEGIN(altera-struct-pack-align) */
/* NOLINTBEGIN(cppcoreguidelines-macro-usage) */
/* NOLINTBEGIN(modernize-use-trailing-return-type) */
/* NOLINTBEGIN(altera-id-dependent-backward-branch) */
/* NOLINTBEGIN(performance-enum-size) */
/* NOLINTBEGIN(google-runtime-int) */
/* NOLINTBEGIN(modernize-avoid-c-arrays) */
/* NOLINTBEGIN(hicpp-avoid-c-arrays) */
/* NOLINTBEGIN(cppcoreguidelines-avoid-c-arrays) */
/* NOLINTBEGIN(modernize-use-using) */
/* NOLINTBEGIN(modernize-use-auto) */
/* NOLINTBEGIN(hicpp-use-auto) */
/* Set ULP bound for FLOAT_EQ / DOUBLE_EQ checks.  */
#ifndef EZTEST_ULP_PRECISION
# define EZTEST_ULP_PRECISION 4
#endif

/* Set ULT bound for FLOAT_EQ.  */
#ifndef EZTEST_FLOAT_ULP_PRECISION
# define EZTEST_FLOAT_ULP_PRECISION EZTEST_ULP_PRECISION
#endif

/* Set ULT bound for DOUBLE_EQ.  */
#ifndef EZTEST_DOUBLE_ULP_PRECISION
# define EZTEST_DOUBLE_ULP_PRECISION EZTEST_ULP_PRECISION
#endif

/*
 * Disable warnings that are inevitable in implementation:
 * The following warnings are present / disabled:
 *
 *	 -Waggregate-returns
 *   -Wcxx98-compat
 *   -Wcxx98-compat-pedantic
 *   -Wdouble-promotion
 *   -Wfloat-equal
 *   -Wformat-nonliteral
 *   -Wglobal-constructors
 *   -Wpadded
 *   -Wunsafe-buffer-usage
 *   -Wunused-function
 *   -Wunused-member-function
 *   -Wunused-result
 *   -Wunused-template
 */
#ifndef EZTEST_DISABLE_WARNINGS
# define EZTEST_DISABLE_WARNINGS 1
#endif

/*
 * Don't define macros outside of eztest* namespace (TEST/ASSERT/EXPECT)
 */
#ifndef EZTEST_STRICT_NAMESPACE
# define EZTEST_STRICT_NAMESPACE 0
#endif

/*
 * Use relatively hacky means to try to print arguments on failure in C.
 */
#ifndef EZTEST_C_PRINT_ARGS
# define EZTEST_C_PRINT_ARGS 1
#endif

/* Verbosity for internal status from the testsuite.  Mostly useful for
 * debugging.  */
#ifndef EZTEST_VERBOSITY
# define EZTEST_VERBOSITY 0
#endif


#include "eztest-api.h"

/* NOLINTEND(hicpp-use-auto) */
/* NOLINTEND(modernize-use-auto) */
/* NOLINTEND(modernize-use-using) */
/* NOLINTEND(cppcoreguidelines-avoid-c-arrays) */
/* NOLINTEND(hicpp-avoid-c-arrays) */
/* NOLINTEND(modernize-avoid-c-arrays) */
/* NOLINTEND(google-runtime-int) */
/* NOLINTEND(performance-enum-size) */
/* NOLINTEND(altera-id-dependent-backward-branch) */
/* NOLINTEND(modernize-use-trailing-return-type) */
/* NOLINTEND(cppcoreguidelines-macro-usage) */
/* NOLINTEND(altera-struct-pack-align) */
/* NOLINTEND(altera-unroll-loops) */
#endif
