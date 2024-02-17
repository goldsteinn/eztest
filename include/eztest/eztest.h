#ifndef EZTEST_EZTEST_H_
#define EZTEST_EZTEST_H_
/*
 * Single header of entire eztest suite.
 * Generated: 2024-02-17 16:36:48.423677
 */
/* Begin include of: eztest.h  */

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


/* Begin include of: eztest-api.h  */

/* Begin include of: eztest-compiler.h  */

/* Begin include of: eztest-pre-processor.h  */

#define EZTEST_STRINGIFY_IMPL_(eztest_expr) #eztest_expr
#define EZTEST_STRINGIFY_(eztest_expr)      EZTEST_STRINGIFY_IMPL_(eztest_expr)

#define EZTEST_CAT_IMPL_(eztest_expr0, eztest_expr1) eztest_expr0##eztest_expr1
#define EZTEST_CAT_(eztest_expr0, eztest_expr1)                                \
    EZTEST_CAT_IMPL_(eztest_expr0, eztest_expr1)

#define EZTEST_SNAKE_CAT_IMPL_(eztest_expr0, eztest_expr1)                     \
    eztest_expr0##_##eztest_expr1
#define EZTEST_SNAKE_CAT_(eztest_expr0, eztest_expr1)                          \
    EZTEST_SNAKE_CAT_IMPL_(eztest_expr0, eztest_expr1)

#ifdef __COUNTER__
# define EZTEST_COUNTER_ __COUNTER__
#else
# define EZTEST_COUNTER_ 0
#endif

#ifdef __LINE__
# define EZTEST_LINE_ __LINE__
#else
# define EZTEST_LINE_ 0
#endif

#ifdef __FILE__
# define EZTEST_FILE_ __FILE__
#else
# define EZTEST_FILE_ ""
#endif

#define EZTEST_UID_ EZTEST_SNAKE_CAT_(EZTEST_LINE_, EZTEST_COUNTER_)

#define EZTEST_UNIQUE_NAME_(eztest_var)                                        \
    EZTEST_SNAKE_CAT_(eztest_var, EZTEST_UID_)

/* End include of: eztest-pre-processor.h  */

#define EZTEST_VERNUM_(eztest_major, eztest_minor, eztest_patch)               \
    (((eztest_major) * 100 * 100) + ((eztest_minor) * 100) + (eztest_patch))

#ifdef __clang__
# ifdef __clang_major__
#  define EZTEST_CLANG_MAJOR_ __clang_major__
# else
#  define EZTEST_CLANG_MAJOR_ 0
# endif
# ifdef __clang_minor__
#  define EZTEST_CLANG_MINOR_ __clang_minor__
# else
#  define EZTEST_CLANG_MINOR_ 0
# endif

# ifdef __clang_patchlevel__
#  define EZTEST_CLANG_PATCHLEVEL_ __clang_patchlevel__
# else
#  define EZTEST_CLANG_PATCHLEVEL_ 0
# endif

# define EZTEST_USING_CLANG_                                                   \
     EZTEST_VERNUM_(EZTEST_CLANG_MAJOR_, EZTEST_CLANG_MINOR_,                  \
                    EZTEST_CLANG_PATCHLEVEL_)

# define EZTEST_DISABLE_WARNING_(eztest_warning)                               \
     _Pragma("clang diagnostic push")                                          \
         _Pragma(EZTEST_STRINGIFY_(clang diagnostic ignored eztest_warning))

# define EZTEST_REENABLE_WARNING_ _Pragma("clang diagnostic pop")
#endif
#if !(defined __clang__) && (defined __GNUC__)

# define EZTEST_GCC_MAJOR_ __GNUC__
# ifdef __GNUC_MINOR__
#  define EZTEST_GCC_MINOR_ __GNUC_MINOR__
# else
#  define EZTEST_GCC_MINOR_ 0
# endif

# ifdef __GNUC_PATCHLEVEL__
#  define EZTEST_GCC_PATCHLEVEL_ __GNUC_PATCHLEVEL__
# else
#  define EZTEST_GCC_PATCHLEVEL_ 0
# endif

# define EZTEST_USING_GCC_                                                     \
     EZTEST_VERNUM_(EZTEST_GCC_MAJOR_, EZTEST_GCC_MINOR_,                      \
                    EZTEST_GCC_PATCHLEVEL_)

# define EZTEST_DISABLE_WARNING_(eztest_warning)                               \
     _Pragma("GCC diagnostic push")                                            \
         _Pragma(EZTEST_STRINGIFY_(GCC diagnostic ignored eztest_warning))
# define EZTEST_REENABLE_WARNING_ _Pragma("GCC diagnostic pop")
#endif

#ifndef EZTEST_DISABLE_WARNING_
# define EZTEST_DISABLE_WARNING_(eztest_warning)
# define EZTEST_REENABLE_WARNING_
#endif

#ifndef EZTEST_USING_CLANG_
# define EZTEST_USING_CLANG_ 0
#endif

#ifndef EZTEST_USING_GCC_
# define EZTEST_USING_GCC_ 0
#endif

#define EZTEST_IN_COMPILER_HDR_ 1
/* Begin include of: eztest-compiler-warnings.h  */

/* Begin include of: eztest-lang-bits.h  */


#ifdef __cplusplus
# define EZTEST_C_VER_DEF_ 0
# if __cplusplus != 0
#  define EZTEST_CXX_VER_DEF_ (__cplusplus)
# else
#  define EZTEST_CXX_VER_DEF_ 1
# endif
# define EZTEST_C_LANG_ 0

#else
# define EZTEST_CXX_VER_DEF_ 0
# if (defined __STDC_VERSION__) && (__STDC_VERSION__ != 0)
#  define EZTEST_C_VER_DEF_ (__STDC_VERSION__)
# else
#  define EZTEST_C_VER_DEF_ 1
# endif
# define EZTEST_CXX_LANG_ 0
#endif

#if EZTEST_CXX_VER_DEF_ >= 202101L
# define EZTEST_CXX_LANG_ 2023
#endif
#if EZTEST_CXX_VER_DEF_ == 202002L
# define EZTEST_CXX_LANG_ 2020
#endif
#if EZTEST_CXX_VER_DEF_ == 201703L
# define EZTEST_CXX_LANG_ 2017
#endif
#if EZTEST_CXX_VER_DEF_ == 201402L
# define EZTEST_CXX_LANG_ 2014
#endif
#if EZTEST_CXX_VER_DEF_ == 201103L
# define EZTEST_CXX_LANG_ 2011
#endif
#if (!defined EZTEST_CXX_LANG_) && EZTEST_CXX_VER_DEF_ >= 201103L
# define EZTEST_CXX_LANG_ 2011
#endif
#if EZTEST_CXX_VER_DEF_ == 199711L
# define EZTEST_CXX_LANG_ 1998
#endif
#if EZTEST_CXX_VER_DEF_ > 0 && EZTEST_CXX_VER_DEF_ < 199711L
# define EZTEST_CXX_LANG_ 1
#endif
#if EZTEST_C_VER_DEF_ >= 202311L
# define EZTEST_C_LANG_ 2023
#endif
#if EZTEST_C_VER_DEF_ == 201710L
# define EZTEST_C_LANG_ 2017
#endif
#if EZTEST_C_VER_DEF_ == 201112L
# define EZTEST_C_LANG_ 2011
#endif
#if EZTEST_C_VER_DEF_ == 199901L
# define EZTEST_C_LANG_ 1999
#endif
#if (!defined EZTEST_C_LANG_) && EZTEST_C_VER_DEF_ >= 199901L
# define EZTEST_C_LANG_ 1999
#endif

#if EZTEST_C_VER_DEF_ == 199409L
# define EZTEST_C_LANG_ 1994
#endif
#if EZTEST_C_VER_DEF_ > 0 && EZTEST_C_VER_DEF_ < 199409L
# define EZTEST_C_LANG_ 1
#endif


#if !EZTEST_C_LANG_ && !EZTEST_CXX_LANG_
# error "Unable to determing C/CXX standard"
#endif
#if EZTEST_C_LANG_ && EZTEST_CXX_LANG_
# error "Somehow found both C/CXX enabled"
#endif

/* End include of: eztest-lang-bits.h  */

#ifndef EZTEST_IN_COMPILER_HDR_
# error "Never include compiler-warnings.h directly. Always include compiler.h"
#endif

#if (EZTEST_DISABLE_WARNINGS)
# define EZTEST_HAS_CLANG_VER_(major, minor, patch)                            \
     (EZTEST_USING_CLANG_ >= EZTEST_VERNUM_(major, minor, patch))
# define EZTEST_HAS_GCC_VER_(major, minor, patch)                              \
     (EZTEST_USING_GCC_ >= EZTEST_VERNUM_(major, minor, patch))
#else
# define EZTEST_HAS_CLANG_VER_(major, minor, patch) 0
# define EZTEST_HAS_GCC_VER_(major, minor, patch)   0
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0) || EZTEST_HAS_GCC_VER_(4, 4, 7))
# define EZTEST_DISABLE_WPADDED_  EZTEST_DISABLE_WARNING_("-Wpadded")
# define EZTEST_REENABLE_WPADDED_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WPADDED_
# define EZTEST_REENABLE_WPADDED_
#endif

#if EZTEST_HAS_GCC_VER_(7, 0, 0) && !EZTEST_HAS_GCC_VER_(9, 0, 0)
# define EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_  EZTEST_DISABLE_WPADDED_
# define EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_ EZTEST_REENABLE_WPADDED_
#else
# define EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_
# define EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0))
# define EZTEST_DISABLE_WGLOBAL_CONSTRUCTORS_                                  \
     EZTEST_DISABLE_WARNING_("-Wglobal-constructors")
# define EZTEST_REENABLE_WGLOBAL_CONSTRUCTORS_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WGLOBAL_CONSTRUCTORS_
# define EZTEST_REENABLE_WGLOBAL_CONSTRUCTORS_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0) || EZTEST_HAS_GCC_VER_(4, 4, 7))
# define EZTEST_DISABLE_WFLOAT_EQUAL_  EZTEST_DISABLE_WARNING_("-Wfloat-equal")
# define EZTEST_REENABLE_WFLOAT_EQUAL_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WFLOAT_EQUAL_
# define EZTEST_REENABLE_WFLOAT_EQUAL_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0) || EZTEST_HAS_GCC_VER_(4, 4, 7))
# define EZTEST_DISABLE_WUNUSED_FUNCTION_                                      \
     EZTEST_DISABLE_WARNING_("-Wunused-function")
# define EZTEST_REENABLE_WUNUSED_FUNCTION_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WUNUSED_FUNCTION_
# define EZTEST_REENABLE_WUNUSED_FUNCTION_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0))
# define EZTEST_DISABLE_WC99_COMPAT_  EZTEST_DISABLE_WARNING_("-Wc99-compat")
# define EZTEST_REENABLE_WC99_COMPAT_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WC99_COMPAT_
# define EZTEST_REENABLE_WC99_COMPAT_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0) || EZTEST_HAS_GCC_VER_(4, 4, 7))
# define EZTEST_DISABLE_WVARIADIC_MACROS_                                      \
     EZTEST_DISABLE_WARNING_("-Wvariadic-macros")
# define EZTEST_REENABLE_WVARIADIC_MACROS_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WVARIADIC_MACROS_
# define EZTEST_REENABLE_WVARIADIC_MACROS_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0) || EZTEST_HAS_GCC_VER_(4, 6, 4))
# define EZTEST_DISABLE_WDOUBLE_PROMOTION_                                     \
     EZTEST_DISABLE_WARNING_("-Wdouble-promotion")
# define EZTEST_REENABLE_WDOUBLE_PROMOTION_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WDOUBLE_PROMOTION_
# define EZTEST_REENABLE_WDOUBLE_PROMOTION_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0) || EZTEST_HAS_GCC_VER_(4, 4, 7))
# define EZTEST_DISABLE_WFORMAT_NONLITERAL_                                    \
     EZTEST_DISABLE_WARNING_("-Wformat-nonliteral")
# define EZTEST_REENABLE_WFORMAT_NONLITERAL_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WFORMAT_NONLITERAL_
# define EZTEST_REENABLE_WFORMAT_NONLITERAL_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0))
# define EZTEST_DISABLE_WDISABLED_MACRO_EXPANSION_                             \
     EZTEST_DISABLE_WARNING_("-Wdisabled-macro-expansion")
# define EZTEST_REENABLE_WDISABLED_MACRO_EXPANSION_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WDISABLED_MACRO_EXPANSION_
# define EZTEST_REENABLE_WDISABLED_MACRO_EXPANSION_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0))
# define EZTEST_DISABLE_WUNUSED_MEMBER_FUNCTION_                               \
     EZTEST_DISABLE_WARNING_("-Wunused-member-function")
# define EZTEST_REENABLE_WUNUSED_MEMBER_FUNCTION_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WUNUSED_MEMBER_FUNCTION_
# define EZTEST_REENABLE_WUNUSED_MEMBER_FUNCTION_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0))
# define EZTEST_DISABLE_WCXX98_COMPAT_  EZTEST_DISABLE_WARNING_("-Wc++98-compat")
# define EZTEST_REENABLE_WCXX98_COMPAT_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WCXX98_COMPAT_
# define EZTEST_REENABLE_WCXX98_COMPAT_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0))
# define EZTEST_DISABLE_WCXX98_COMPAT_PEDANTIC_                                \
     EZTEST_DISABLE_WARNING_("-Wc++98-compat-pedantic")
# define EZTEST_REENABLE_WCXX98_COMPAT_PEDANTIC_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WCXX98_COMPAT_PEDANTIC_
# define EZTEST_REENABLE_WCXX98_COMPAT_PEDANTIC_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0))
# define EZTEST_DISABLE_WC11_EXTENSIONS_                                       \
     EZTEST_DISABLE_WARNING_("-Wc11-extensions")
# define EZTEST_REENABLE_WC11_EXTENSIONS_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WC11_EXTENSIONS_
# define EZTEST_REENABLE_WC11_EXTENSIONS_
#endif


#if (EZTEST_HAS_CLANG_VER_(4, 0, 0) || EZTEST_HAS_GCC_VER_(4, 4, 7))
# define EZTEST_DISABLE_WLONG_LONG_  EZTEST_DISABLE_WARNING_("-Wlong-long")
# define EZTEST_REENABLE_WLONG_LONG_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WLONG_LONG_
# define EZTEST_REENABLE_WLONG_LONG_
#endif


#if (EZTEST_HAS_CLANG_VER_(5, 0, 0))
# define EZTEST_DISABLE_WUNUSED_TEMPLATE_                                      \
     EZTEST_DISABLE_WARNING_("-Wunused-template")
# define EZTEST_REENABLE_WUNUSED_TEMPLATE_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WUNUSED_TEMPLATE_
# define EZTEST_REENABLE_WUNUSED_TEMPLATE_
#endif


#if (EZTEST_HAS_CLANG_VER_(13, 0, 0))
# define EZTEST_DISABLE_WRESERVED_IDENTIFIER_                                  \
     EZTEST_DISABLE_WARNING_("-Wreserved-identifier")
# define EZTEST_REENABLE_WRESERVED_IDENTIFIER_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WRESERVED_IDENTIFIER_
# define EZTEST_REENABLE_WRESERVED_IDENTIFIER_
#endif


#if (EZTEST_HAS_CLANG_VER_(16, 0, 0))
# define EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_                                  \
     EZTEST_DISABLE_WARNING_("-Wunsafe-buffer-usage")
# define EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
# define EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
#endif


#if (EZTEST_HAS_GCC_VER_(4, 4, 7))
# define EZTEST_DISABLE_WSYSTEM_HEADERS_                                       \
     EZTEST_DISABLE_WARNING_("-Wsystem-headers")
# define EZTEST_REENABLE_WSYSTEM_HEADERS_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WSYSTEM_HEADERS_
# define EZTEST_REENABLE_WSYSTEM_HEADERS_
#endif


#if ((EZTEST_HAS_GCC_VER_(4, 4, 7)) && EZTEST_C_LANG_)
# define EZTEST_DISABLE_WTRADITIONAL_  EZTEST_DISABLE_WARNING_("-Wtraditional")
# define EZTEST_REENABLE_WTRADITIONAL_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WTRADITIONAL_
# define EZTEST_REENABLE_WTRADITIONAL_
#endif
#if ((EZTEST_HAS_GCC_VER_(4, 5, 3)) && EZTEST_C_LANG_)
# define EZTEST_DISABLE_WUNSUFFIXED_FLOAT_CONSTANTS_                           \
     EZTEST_DISABLE_WARNING_("-Wunsuffixed-float-constants")
# define EZTEST_REENABLE_WUNSUFFIXED_FLOAT_CONSTANTS_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
# define EZTEST_REENABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
#endif


#if ((EZTEST_HAS_GCC_VER_(5, 1, 0)) && EZTEST_C_LANG_)
# define EZTEST_DISABLE_WC90_C99_COMPAT_                                       \
     EZTEST_DISABLE_WARNING_("-Wc90-c99-compat")
# define EZTEST_REENABLE_WC90_C99_COMPAT_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WC90_C99_COMPAT_
# define EZTEST_REENABLE_WC90_C99_COMPAT_
#endif
#if ((EZTEST_HAS_GCC_VER_(5, 1, 0)) && EZTEST_C_LANG_)
# define EZTEST_DISABLE_WC99_C11_COMPAT_                                       \
     EZTEST_DISABLE_WARNING_("-Wc99-c11-compat")
# define EZTEST_REENABLE_WC99_C11_COMPAT_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WC99_C11_COMPAT_
# define EZTEST_REENABLE_WC99_C11_COMPAT_
#endif


#if ((EZTEST_HAS_GCC_VER_(4, 8, 1)) && EZTEST_CXX_LANG_)
# define EZTEST_DISABLE_WUSELESS_CAST_  EZTEST_DISABLE_WARNING_("-Wuseless-cast")
# define EZTEST_REENABLE_WUSELESS_CAST_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WUSELESS_CAST_
# define EZTEST_REENABLE_WUSELESS_CAST_
#endif


#if ((EZTEST_HAS_GCC_VER_(6, 1, 0)) && EZTEST_CXX_LANG_)
# define EZTEST_DISABLE_WNAMESPACES_  EZTEST_DISABLE_WARNING_("-Wnamespaces")
# define EZTEST_REENABLE_WNAMESPACES_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WNAMESPACES_
# define EZTEST_REENABLE_WNAMESPACES_
#endif
#if ((EZTEST_HAS_GCC_VER_(6, 1, 0)) && EZTEST_CXX_LANG_)
# define EZTEST_DISABLE_WTEMPLATES_  EZTEST_DISABLE_WARNING_("-Wtemplates")
# define EZTEST_REENABLE_WTEMPLATES_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WTEMPLATES_
# define EZTEST_REENABLE_WTEMPLATES_
#endif


#if (EZTEST_HAS_CLANG_VER_(19, 0, 0) && EZTEST_C_LANG_)
# define EZTEST_DISABLE_WPRE_C11_COMPAT_                                       \
     EZTEST_DISABLE_WARNING_("-Wpre-c11-compat")
# define EZTEST_REENABLE_WPRE_C11_COMPAT_ EZTEST_REENABLE_WARNING_
#else
# define EZTEST_DISABLE_WPRE_C11_COMPAT_
# define EZTEST_REENABLE_WPRE_C11_COMPAT_
#endif
/* End include of: eztest-compiler-warnings.h  */
#undef EZTEST_IN_COMPILER_HDR_

#ifdef __has_attribute
# define EZTEST_HAS_ATTRIBUTE_(eztest_attribute)                               \
     __has_attribute(eztest_attribute)
#else
# define EZTEST_HAS_ATTRIBUTE_(eztest_attribute) 0
#endif


#if EZTEST_HAS_ATTRIBUTE_(constructor)
# define EZTEST_ATTR_CONSTRUCTOR_ __attribute__((constructor))
#else
# define EZTEST_ATTR_CONSTRUCTOR_
#endif


#if EZTEST_HAS_ATTRIBUTE_(format)
EZTEST_DISABLE_WCXX98_COMPAT_PEDANTIC_
# define EZTEST_ATTR_FMT_(fmt, varargs)                                        \
     __attribute__((format(printf, fmt, varargs)))
EZTEST_REENABLE_WCXX98_COMPAT_PEDANTIC_
#else
# define EZTEST_ATTR_FMT_(fmt, varargs)
#endif

#if EZTEST_HAS_ATTRIBUTE_(pure)
# define EZTEST_ATTR_PURE_ __attribute__((pure))
#else
# define EZTEST_ATTR_PURE_
#endif


/* End include of: eztest-compiler.h  */
EZTEST_DISABLE_WTRADITIONAL_
EZTEST_DISABLE_WSYSTEM_HEADERS_

/* Begin include of: eztest-asserts-impl.h  */

/* Begin include of: eztest-containers.h  */

/* Begin include of: eztest-lang.h  */


#if EZTEST_CXX_LANG_
# define EZTEST_STRUCT_

# define EZTEST_NAMESPACE_BEGIN_                                               \
     EZTEST_DISABLE_WNAMESPACES_                                               \
     namespace eztest {

# define EZTEST_NAMESPACE_END_                                                 \
     }                                                                         \
     EZTEST_REENABLE_WNAMESPACES_

# define EZTEST_NS_                                                            \
     /* NOLINTBEGIN(llvmlibc-callee-namespace) */                              \
     eztest::/* NOLINTEND(llvmlibc-callee-namespace) */

# define EZTEST_STD_NS_                                                        \
     /* NOLINTBEGIN(llvmlibc-callee-namespace) */                              \
     std::/* NOLINTEND(llvmlibc-callee-namespace) */

# define EZTEST_VOID_ARG_

# if EZTEST_CXX_LANG_ >= 1998
#  define EZTEST_INLINE_ inline
# endif

# define EZTEST_PRIVATE_CXX_INL_ /* NOLINTBEGIN(llvmlibc-inl*-func*-decl) */   \
     static EZTEST_INLINE_       /* NOLINTEND(llvmlibc-inl*-func*-decl) */


# define EZTEST_PRIVATE_                                                       \
     /* NOLINTBEGIN(llvmlibc-inl*-func*-decl) */                               \
     static /* NOLINTEND(llvmlibc-inl*-func*-decl) */


# if EZTEST_CXX_LANG_ >= 2011
#  define EZTEST_NULL_                                                         \
      EZTEST_DISABLE_WCXX98_COMPAT_ nullptr EZTEST_REENABLE_WCXX98_COMPAT_
# else
#  include <cstddef> /* NULL.  */
#  define EZTEST_NULL_ NULL
# endif

# define EZTEST_CAST_(type, expr) static_cast<type>(expr)
# define EZTEST_REINTERPRET_CAST_(type, var)                                   \
     /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */            \
     reinterpret_cast<type>(                                                   \
         var) /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */

# if EZTEST_CXX_LANG_ >= 2011
#  define EZTEST_STATIC_ASSERT_MSG_(cond, msg)                                 \
      EZTEST_DISABLE_WCXX98_COMPAT_ static_assert(cond, msg)                   \
          EZTEST_REENABLE_WCXX98_COMPAT_
#  define EZTEST_AUTO_(eztest_unused_A0)                                       \
      EZTEST_DISABLE_WCXX98_COMPAT_ auto EZTEST_REENABLE_WCXX98_COMPAT_
# endif


#else
# define EZTEST_STRUCT_ struct

# define EZTEST_NAMESPACE_BEGIN_
# define EZTEST_NAMESPACE_END_

# define EZTEST_NS_
# define EZTEST_STD_NS_

# define EZTEST_VOID_ARG_ void

# if EZTEST_C_LANG_ >= 1999
#  define EZTEST_INLINE_ inline
# endif

# define EZTEST_PRIVATE_ /* NOLINTBEGIN(llvmlibc-inline-function-decl) */      \
     static              /* NOLINTEND(llvmlibc-inline-function-decl) */
# define EZTEST_PRIVATE_CXX_INL_ EZTEST_PRIVATE_


# define EZTEST_NULL_                        NULL
# define EZTEST_CAST_(type, expr)            ((type)(expr))
# define EZTEST_REINTERPRET_CAST_(type, var) ((type)(expr))

# if EZTEST_C_LANG_ >= 2023
#  define EZTEST_STATIC_ASSERT_MSG_(cond, msg) static_assert(cond, msg)
# elif EZTEST_C_LANG_ >= 2011
#  define EZTEST_STATIC_ASSERT_MSG_(cond, msg) _Static_assert(cond, msg)
# endif
#endif

#ifndef EZTEST_AUTO_
# if EZTEST_USING_CLANG_ || EZTEST_USING_GCC_
#  define EZTEST_AUTO_(x) __typeof__(x)
# endif
#endif

#ifndef EZTEST_STATIC_ASSERT_MSG_
# define EZTEST_STATIC_ASSERT_MSG_(cond, msg)                                  \
     struct EZTEST_UNIQUE_NAME_(eztest_static_assertion) {                     \
         char EZTEST_UNIQUE_NAME_(eztest_x_)[(cond) ? 1 : -1];                 \
     }

#endif

#ifndef EZTEST_INLINE_
# define EZTEST_INLINE_
#endif


#define EZTEST_STRUCT_NS_ EZTEST_STRUCT_ EZTEST_NS_

#define EZTEST_UNIMPLEMENTED_(name)                                            \
    EZTEST_STATIC_ASSERT_MSG_(0, name " is unimplemented")
#define EZTEST_STATIC_ASSERT_(cond)                                            \
    EZTEST_STATIC_ASSERT_MSG_(cond, EZTEST_STRINGIFY_(cond))


/* End include of: eztest-lang.h  */
/* Begin include of: eztest-libc.h  */


/* Begin include of: eztest-libc-incs.h  */

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#if EZTEST_CXX_LANG_
# include <cctype>
# include <climits>
# include <cstddef>
# include <cstdio>
# include <cstdlib>
# include <cstring>
#else
# include <ctype.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#endif
#if EZTEST_CXX_LANG_ >= 2011
# include <cstdint>
#else
# include <stdint.h>
#endif

#include <errno.h>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

#ifdef _POSIX_C_SOURCE
# define EZTEST_POSIX_VERSION_ (_POSIX_C_SOURCE)
#else
# define EZTEST_POSIX_VERSION_ 0
#endif

#ifdef _XOPEN_SOURCE
# define EZTEST_XOPEN_VERSION_ (_XOPEN_SOURCE)
#else
# define EZTEST_XOPEN_VERSION_ 0
#endif

#ifdef _GNU_SOURCE
# define EZTEST_GNU_SOURCE_ 1
#else
# define EZTEST_GNU_SOURCE_ 0
#endif


#if (defined _DEFAULT_SOURCE) || (defined _BSD_SOURCE) || (defined _SVID_SOURCE)
# define EZTEST_DEFAULT_SOURCE_ 1
#else
# define EZTEST_DEFAULT_SOURCE_ 0
#endif


/* End include of: eztest-libc-incs.h  */


#define EZTEST_EXIT_ EZTEST_STD_NS_ _Exit
EZTEST_DISABLE_WCXX98_COMPAT_PEDANTIC_

#define EZTEST_PRINTF_(...)                                                                                      \
    /* NOLINTBEGIN(clang-ana*-sec*.insecureAPI.Depr*OrUnsafeBufferHandling) */                                   \
    /* NOLINTBEGIN(cppcoreguide*-pro-type-vararg,hicpp-vararg) */                                                \
    EZTEST_STD_NS_ fprintf(EZTEST_STDOUT_, __VA_ARGS__) /* NOLINTEND(cppcoreguide*-pro-type-vararg,hicpp-vararg) \
                                                         */                                                      \
                                                                                                                 \
        /* NOLINTEND(clang-ana*-sec*.insecureAPI.Depr*OrUnsafeBufferHandling)                                    \
         */

EZTEST_REENABLE_WCXX98_COMPAT_PEDANTIC_

#define EZTEST_VFPRINTF_ EZTEST_STD_NS_ vfprintf
#define EZTEST_FFLUSH_   EZTEST_STD_NS_ fflush
#define EZTEST_ERRNO_    errno
#define EZTEST_STDOUT_                                                         \
    EZTEST_DISABLE_WDISABLED_MACRO_EXPANSION_ stdout                           \
        EZTEST_REENABLE_WDISABLED_MACRO_EXPANSION_

/* strerror is safe here. We have complete control of the threads
   and know in the parent proc there will only be 1 thread (the
   forked test has a seperate address space so no concern about race
   conditions from user code).  */
#if (EZTEST_POSIX_VERSION_ >= 200112L || EZTEST_XOPEN_VERSION_ >= 600)
# if EZTEST_GNU_SOURCE_
#  define EZTEST_STRERROR_R_(errnum, buf, bufsz) strerror_r(errnum, buf, bufsz)
# else
#  define EZTEST_STRERROR_R_(errnum, buf, bufsz)                               \
      (strerror_r(errnum, buf, bufsz) == 0 ? &((buf)[0]) : "Unknown error")
# endif
#else
# if EZTEST_CXX_LANG_
#  define EZTEST_STRERROR_R_(errnum, buf, bufsz)                               \
      /* NOLINTBEGIN(concurrency-mt-unsafe) */                                 \
      std::strerror(errnum) /* NOLINTEND(concurrency-mt-unsafe) */
# else
#  define EZTEST_STRERROR_R_(errnum, buf, bufsz)                               \
      /* NOLINTBEGIN(concurrency-mt-unsafe) */                                 \
      strerror(errnum) /* NOLINTEND(concurrency-mt-unsafe) */
# endif
#endif

EZTEST_NAMESPACE_BEGIN_
EZTEST_PRIVATE_ void
eztest_perr(const char * eztest_usr_msg) {
    enum { eztest_k_errbuf_size = 512 };
    char eztest_errbuf[eztest_k_errbuf_size];
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(hicpp-no-array-decay) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay) */
    (void)EZTEST_PRINTF_(
        "%s[%d] -> %s\n", eztest_usr_msg, EZTEST_ERRNO_,
        EZTEST_STRERROR_R_(
            EZTEST_ERRNO_, eztest_errbuf,
            EZTEST_CAST_(EZTEST_STD_NS_ size_t, eztest_k_errbuf_size)));
    /* NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay) */
    /* NOLINTEND(hicpp-no-array-decay) */
    /* NOLINTEND(llvmlibc-callee-namespace) */
    (void)eztest_errbuf;
}
EZTEST_PRIVATE_ void
eztest_pwarn(const char * eztest_usr_msg, int eztest_vlvl) {
    if (eztest_vlvl <= (EZTEST_VERBOSITY)) {
        EZTEST_NS_ eztest_perr(eztest_usr_msg);
    }
}

EZTEST_NAMESPACE_END_
#define EZTEST_PERR_(msg)    EZTEST_NS_ eztest_perr(msg)
#define EZTEST_PWARN_V_(msg) EZTEST_NS_ eztest_pwarn(msg, 1)


#define EZTEST_STRLEN_(str) EZTEST_STD_NS_ strlen(str)

#define EZTEST_STRCMP_(lhs, rhs) EZTEST_STD_NS_ strcmp(lhs, rhs)
#define EZTEST_STARTSWITH_(prefix, str)                                        \
    (EZTEST_STD_NS_ strncmp(prefix, str, EZTEST_STD_NS_ strlen(prefix)) == 0)

#define EZTEST_MEMCPY_(dst, src, sz) EZTEST_STD_NS_ memcpy(dst, src, sz)
#define EZTEST_MEMSET_(dst, val, sz) EZTEST_STD_NS_ memset(dst, val, sz)
#define EZTEST_MEMCMP_(s0, s1, sz)   EZTEST_STD_NS_ memcmp(s0, s1, sz)

#if EZTEST_POSIX_VERSION_ >= 200809L || EZTEST_GNU_SOURCE_ != 0
# define EZTEST_STRNLEN_(str, maxlen)                                          \
     /* NOLINTBEGIN(llvmlibc-callee-namespace) */                              \
     strnlen(str, maxlen) /* NOLINTEND(llvmlibc-callee-namespace) */

#else
EZTEST_NAMESPACE_BEGIN_
EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
EZTEST_PRIVATE_ EZTEST_STD_NS_ size_t
eztest_strnlen(const char * eztest_str, EZTEST_STD_NS_ size_t eztest_maxlen) {
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EZTEST_STD_NS_ size_t eztest_len = 0;

    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
    for (; eztest_len < eztest_maxlen && eztest_str[eztest_len] != '\0';
         ++eztest_len) {
    }
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    return eztest_len;
}

EZTEST_NAMESPACE_END_
# define EZTEST_STRNLEN_(str, maxlen) EZTEST_NS_ eztest_strnlen(str, maxlen)
#endif


#if EZTEST_GNU_SOURCE_ != 0
# define EZTEST_STRCASECMP_(lhs, rhs)                                          \
     /* NOLINTBEGIN(llvmlibc-callee-namespace) */ strcasecmp(                  \
         lhs, rhs) /* NOLINTEND(llvmlibc-callee-namespace) */
# define EZTEST_STRNCASECMP_(lhs, rhs, len)                                    \
     /* NOLINTBEGIN(llvmlibc-callee-namespace) */ strncasecmp(                 \
         lhs, rhs, len) /* NOLINTEND(llvmlibc-callee-namespace) */

#else
EZTEST_NAMESPACE_BEGIN_
EZTEST_DISABLE_WUNUSED_FUNCTION_
EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_
/* NOLINTBEGIN(readability-function-cognitive-complexity,bugprone-easily-swappable-parameters)
 */
EZTEST_PRIVATE_ EZTEST_ATTR_PURE_ int
eztest_strcasecmp(const char * eztest_lhs_str, const char * eztest_rhs_str) {
    EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EZTEST_STD_NS_ size_t eztest_len = 0;
    int                   eztest_ret = 0;
    for (;;) {
        EZTEST_DISABLE_WDISABLED_MACRO_EXPANSION_
        EZTEST_DISABLE_WRESERVED_IDENTIFIER_
        EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
        char eztest_lhs_c = EZTEST_CAST_(
            char, EZTEST_STD_NS_ tolower(eztest_lhs_str[eztest_len]));
        char eztest_rhs_c = EZTEST_CAST_(
            char, EZTEST_STD_NS_ tolower(eztest_rhs_str[eztest_len]));
        EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
        EZTEST_REENABLE_WRESERVED_IDENTIFIER_
        EZTEST_REENABLE_WDISABLED_MACRO_EXPANSION_
        eztest_ret = EZTEST_CAST_(int, eztest_lhs_c - eztest_rhs_c);
        if (eztest_ret != 0 || eztest_lhs_c == '\0') {
            break;
        }
        ++eztest_len;
    }
    return eztest_ret;
}
EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
EZTEST_PRIVATE_ EZTEST_ATTR_PURE_ int
eztest_strncasecmp(const char *          eztest_lhs_str,
                   const char *          eztest_rhs_str,
                   EZTEST_STD_NS_ size_t eztest_maxlen) {
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    EZTEST_STD_NS_ size_t eztest_len = 0;
    int                   eztest_ret = 0;
    for (; eztest_len < eztest_maxlen;) {
        EZTEST_DISABLE_WDISABLED_MACRO_EXPANSION_
        EZTEST_DISABLE_WRESERVED_IDENTIFIER_
        EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
        char eztest_lhs_c = EZTEST_CAST_(
            char, EZTEST_STD_NS_ tolower(eztest_lhs_str[eztest_len]));
        char eztest_rhs_c = EZTEST_CAST_(
            char, EZTEST_STD_NS_ tolower(eztest_rhs_str[eztest_len]));
        EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
        EZTEST_REENABLE_WRESERVED_IDENTIFIER_
        EZTEST_REENABLE_WDISABLED_MACRO_EXPANSION_
        eztest_ret = EZTEST_CAST_(int, eztest_lhs_c - eztest_rhs_c);
        if (eztest_ret != 0 || eztest_lhs_c == '\0') {
            break;
        }
        ++eztest_len;
    }
    return eztest_ret;
}
/* NOLINTEND(readability-function-cognitive-complexity,bugprone-easily-swappable-parameters)
 */
EZTEST_REENABLE_WUNUSED_FUNCTION_
EZTEST_NAMESPACE_END_
# define EZTEST_STRCASECMP_(lhs, rhs) EZTEST_NS_ eztest_strcasecmp(lhs, rhs)
# define EZTEST_STRNCASECMP_(lhs, rhs, len)                                    \
     EZTEST_NS_ eztest_strncasecmp(lhs, rhs, len)

#endif
/* End include of: eztest-libc.h  */


#if EZTEST_CXX_LANG_ >= 2011
# include <array>
# define EZTEST_ARR_BUILDER_(name, T, k_n) EZTEST_STD_NS_ array<T, k_n> name
# define EZTEST_ARR_T_INIT_                                                    \
     {                                                                         \
         { 0 }                                                                 \
     }
#else
# define EZTEST_ARR_BUILDER_(name, T, k_n) T name[k_n]
# define EZTEST_ARR_T_INIT_                                                    \
     { 0 }
#endif

/* End include of: eztest-containers.h  */
/* Begin include of: eztest-fail.h  */


EZTEST_NAMESPACE_BEGIN_

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ int
eztest_cur_test_getmod_failed(int eztest_set, int eztest_val) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    static int eztest_S_cur_test_failed = 0;
    if (eztest_set == 0) {
        return eztest_S_cur_test_failed;
    }
    eztest_S_cur_test_failed = eztest_val;
    return 0;
}

EZTEST_DISABLE_WUNUSED_FUNCTION_
EZTEST_PRIVATE_ void
eztest_cur_test_set_failed(EZTEST_VOID_ARG_) {
    (void)EZTEST_NS_ eztest_cur_test_getmod_failed(1, 1);
}
EZTEST_REENABLE_WUNUSED_FUNCTION_

EZTEST_PRIVATE_ void
eztest_cur_test_set_success(EZTEST_VOID_ARG_) {
    (void)EZTEST_NS_ eztest_cur_test_getmod_failed(1, 0);
}

EZTEST_PRIVATE_ int
eztest_cur_test_result(EZTEST_VOID_ARG_) {
    return EZTEST_NS_ eztest_cur_test_getmod_failed(0, 0);
}

EZTEST_NAMESPACE_END_

/* End include of: eztest-fail.h  */
/* Begin include of: eztest-float-compare.h  */

/* Begin include of: eztest-libm.h  */


/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#if EZTEST_CXX_LANG_
# include <cmath> /* abs */
#else
# include <math.h> /* fabs */
#endif
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

#if EZTEST_CXX_LANG_ && EZTEST_CXX_LANG_ < 2023
# define EZTEST_ABS_(x) EZTEST_STD_NS_ abs(x)
#else
# define EZTEST_ABS_(x) EZTEST_STD_NS_ fabs(x)
#endif

#define EZTEST_ISNAN_(x) EZTEST_STD_NS_ isnan(x)
/* End include of: eztest-libm.h  */


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
    /* NOLINTBEGIN(cppcoreguide*-avoid-do-while) */                            \
    do {                                                                       \
        ty_t eztest_fp_tmp_ = fp;                                              \
        (u64_out)           = 0;                                               \
        /* NOLINTBEGIN(clang-a*-sec*.insecureAPI.Depr*OrUnsafeBufferHandling)  \
         */                                                                    \
        EZTEST_MEMCPY_(&(u64_out), &eztest_fp_tmp_, sizeof(ty_t));             \
        /* NOLINTEND(clang-a*-sec*.insecureAPI.Depr*OrUnsafeBufferHandling) */ \
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


/* End include of: eztest-float-compare.h  */
/* Begin include of: eztest-hex-var-printer.h  */


#if EZTEST_CXX_LANG_ || EZTEST_C_LANG_ >= 2011
EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
EZTEST_NAMESPACE_BEGIN_

EZTEST_PRIVATE_CXX_INL_ int
eztest_hex_print_var(const uint8_t *       eztest_op,
                     EZTEST_STD_NS_ size_t eztest_op_size) {
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    static const EZTEST_STD_NS_ size_t eztest_k_hexstr_max_bytes = 40;
    EZTEST_STD_NS_ size_t              eztest_op_cur_idx         = 0;
    int                                eztest_truncated          = 0;
    int                                eztest_ret                = 0;
    if (eztest_op_size > eztest_k_hexstr_max_bytes) {
        eztest_op_size   = eztest_k_hexstr_max_bytes;
        eztest_truncated = 1;
    }
    eztest_ret += EZTEST_PRINTF_("[");
    for (; eztest_op_cur_idx < eztest_op_size; ++eztest_op_cur_idx) {
        if (eztest_op_cur_idx != 0) {
            eztest_ret += EZTEST_PRINTF_(", ");
        }
        EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
        eztest_ret += EZTEST_PRINTF_(
            "%hhx",
            /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
            EZTEST_CAST_(uint8_t, eztest_op[eztest_op_cur_idx] & 0xffU)
            /* NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
        );
        EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    }
    if (eztest_truncated != 0) {
        eztest_ret += EZTEST_PRINTF_(", ...");
    }
    eztest_ret += EZTEST_PRINTF_("]");
    return eztest_ret;
}
EZTEST_NAMESPACE_END_
#endif

/* End include of: eztest-hex-var-printer.h  */

#if EZTEST_CXX_LANG_
/* Begin include of: eztest-cxx-asserts-impl.h  */

# if !EZTEST_CXX_LANG_
#  error "CXX implementation included without CXX!"
# endif

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
# if EZTEST_CXX_LANG_ >= 2017
#  include <string_view>
# endif

# include <cstdarg>
# include <string>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

EZTEST_NAMESPACE_BEGIN_

EZTEST_DISABLE_WTEMPLATES_
EZTEST_DISABLE_WUNUSED_TEMPLATE_
EZTEST_DISABLE_WUNUSED_MEMBER_FUNCTION_

class eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t & eztest_var) {
        return EZTEST_NS_ eztest_hex_print_var(
            EZTEST_REINTERPRET_CAST_(const uint8_t *, &eztest_var),
            /* NOLINTNEXTLINE(bugprone-sizeof-container) */
            sizeof(eztest_T_t));
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(bool eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var ? "true" : "false");
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(unsigned char eztest_var) {
        return EZTEST_PRINTF_("%hhu", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(unsigned short eztest_var) {
        return EZTEST_PRINTF_("%hu", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(unsigned int eztest_var) {
        return EZTEST_PRINTF_("%u", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(unsigned long eztest_var) {
        return EZTEST_PRINTF_("%lu", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(signed char eztest_var) {
        return EZTEST_PRINTF_("%hhd", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(signed short eztest_var) {
        return EZTEST_PRINTF_("%hd", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(signed int eztest_var) {
        return EZTEST_PRINTF_("%d", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(signed long eztest_var) {
        return EZTEST_PRINTF_("%ld", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(char eztest_var) {
        return EZTEST_PRINTF_("%c", eztest_var);
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(float eztest_var) {
        EZTEST_DISABLE_WDOUBLE_PROMOTION_
        return EZTEST_PRINTF_("%f", eztest_var);
        EZTEST_REENABLE_WDOUBLE_PROMOTION_
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(double eztest_var) {
        return EZTEST_PRINTF_("%lf", eztest_var);
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(long double eztest_var) {
        return EZTEST_PRINTF_("%Lf", eztest_var);
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(eztest_T_t * eztest_var) {
        return EZTEST_PRINTF_("%p", EZTEST_CAST_(void *, eztest_var));
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t * eztest_var) {
        return EZTEST_PRINTF_("%p", EZTEST_CAST_(const void *, eztest_var));
    }


    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const EZTEST_STD_NS_ string & eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var.c_str());
    }


# if EZTEST_CXX_LANG_ >= 2011
    EZTEST_DISABLE_WCXX98_COMPAT_
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(EZTEST_STD_NS_ nullptr_t) {
        return EZTEST_PRINTF_("%p", EZTEST_CAST_(void *, EZTEST_NULL_));
    }
    EZTEST_REENABLE_WCXX98_COMPAT_
    EZTEST_DISABLE_WCXX98_COMPAT_PEDANTIC_
    EZTEST_DISABLE_WLONG_LONG_

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(unsigned long long eztest_var) {
        return EZTEST_PRINTF_("%llu", eztest_var);
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(signed long long eztest_var) {
        return EZTEST_PRINTF_("%lld", eztest_var);
    }

    EZTEST_REENABLE_WLONG_LONG_
    EZTEST_REENABLE_WCXX98_COMPAT_PEDANTIC_

# endif

# if EZTEST_CXX_LANG_ >= 2017
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(EZTEST_STD_NS_ string_view eztest_var) {
        if (eztest_var.length() >= INT_MAX) {
            return EZTEST_NS_ eztest_hex_print_var(
                EZTEST_REINTERPRET_CAST_(const uint8_t *, &eztest_var),
                /* NOLINTNEXTLINE(bugprone-sizeof-container) */
                sizeof(eztest_var));
        }
        return EZTEST_PRINTF_("%.*s", static_cast<int>(eztest_var.length()),
                              eztest_var.data());
    }
# endif
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_eq_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) == (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return eztest_op0 == eztest_op1;
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_ne_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) != (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return !EZTEST_NS_ eztest_cxx_binop_eq_t::eztest_cxx_run(eztest_op0,
                                                                 eztest_op1);
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};


class eztest_cxx_binop_gt_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) > (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return eztest_op0 > eztest_op1;
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};


class eztest_cxx_binop_lt_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) < (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return eztest_op0 < eztest_op1;
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_ge_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) >= (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return !EZTEST_NS_ eztest_cxx_binop_lt_t::eztest_cxx_run(eztest_op0,
                                                                 eztest_op1);
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};


class eztest_cxx_binop_le_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) <= (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return !EZTEST_NS_ eztest_cxx_binop_gt_t::eztest_cxx_run(eztest_op0,
                                                                 eztest_op1);
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_streq_t : public EZTEST_NS_ eztest_cxx_print_var_t {

    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run_with_1length(const char *          eztest_op0,
                                EZTEST_STD_NS_ size_t eztest_op0_len,
                                const char *          eztest_op1) {
        if (eztest_op1 == EZTEST_NULL_) {
            return eztest_op0_len == 0;
        }
        if (EZTEST_STRLEN_(eztest_op1) != eztest_op0_len) {
            return false;
        }
        return EZTEST_MEMCMP_(eztest_op0, eztest_op1, eztest_op0_len) == 0;
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */

   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t & eztest_var) {
        return EZTEST_NS_ eztest_cxx_print_var_t::eztest_cxx_print_var(
            eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) eq (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char * eztest_op0, const char * eztest_op1) {
        if (eztest_op0 == EZTEST_NULL_) {
            return eztest_op1 == EZTEST_NULL_;
        }
        if (eztest_op1 == EZTEST_NULL_) {
            return false;
        }
        return EZTEST_STRCMP_(eztest_op0, eztest_op1) == 0;
    }
# if EZTEST_CXX_LANG_ >= 2017
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const char *                       eztest_op1) {
        return EZTEST_NS_ eztest_cxx_binop_streq_t::eztest_cxx_run_with_1length(
            eztest_op0.data(), eztest_op0.length(), eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char *                       eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_NS_ eztest_cxx_binop_streq_t::eztest_cxx_run_with_1length(
            eztest_op1.data(), eztest_op1.length(), eztest_op0);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_STD_NS_ operator==(eztest_op0, eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string &      eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_STD_NS_ operator==(EZTEST_STD_NS_ string_view(eztest_op0),
                                         eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const EZTEST_STD_NS_ string &      eztest_op1) {
        return EZTEST_STD_NS_ operator==(
            eztest_op0, EZTEST_STD_NS_ string_view(eztest_op1));
    }
# endif

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string & eztest_op0,
                   const char *                  eztest_op1) {
        return EZTEST_NS_ eztest_cxx_binop_streq_t::eztest_cxx_run_with_1length(
            eztest_op0.c_str(), eztest_op0.length(), eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char *                  eztest_op0,
                   const EZTEST_STD_NS_ string & eztest_op1) {
        return EZTEST_NS_ eztest_cxx_binop_streq_t::eztest_cxx_run_with_1length(
            eztest_op1.c_str(), eztest_op1.length(), eztest_op0);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string & eztest_op0,
                   const EZTEST_STD_NS_ string & eztest_op1) {
        return EZTEST_STD_NS_ operator==(eztest_op0, eztest_op1);
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_strne_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t & eztest_var) {
        return EZTEST_NS_ eztest_cxx_print_var_t::eztest_cxx_print_var(
            eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) ne (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
         */
        return !EZTEST_NS_ eztest_cxx_binop_streq_t ::eztest_cxx_run(
            eztest_op0, eztest_op1);
        /* NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
         */
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_strcaseeq_t : public EZTEST_NS_ eztest_cxx_print_var_t {

    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run_with_2length(const char *          eztest_op0,
                                EZTEST_STD_NS_ size_t eztest_op0_len,
                                const char *          eztest_op1,
                                EZTEST_STD_NS_ size_t eztest_op1_len) {
        if (eztest_op1_len != eztest_op0_len) {
            return false;
        }
        return EZTEST_STRNCASECMP_(eztest_op0, eztest_op1, eztest_op0_len) == 0;
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run_with_1length(const char *          eztest_op0,
                                EZTEST_STD_NS_ size_t eztest_op0_len,
                                const char *          eztest_op1) {
        if (eztest_op1 == EZTEST_NULL_) {
            return eztest_op0_len == 0;
        }

        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_2length(
                eztest_op0, eztest_op0_len, eztest_op1,
                EZTEST_STRLEN_(eztest_op1));
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */

   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t & eztest_var) {
        return EZTEST_NS_ eztest_cxx_print_var_t::eztest_cxx_print_var(
            eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) case-eq (%s)", eztest_op0_expr,
                              eztest_op1_expr);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char * eztest_op0, const char * eztest_op1) {
        if (eztest_op0 == EZTEST_NULL_) {
            return eztest_op1 == EZTEST_NULL_;
        }
        if (eztest_op1 == EZTEST_NULL_) {
            return false;
        }
        return EZTEST_STRCASECMP_(eztest_op0, eztest_op1) == 0;
    }
# if EZTEST_CXX_LANG_ >= 2017
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const char *                       eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_1length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char *                       eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_1length(
                eztest_op1.data(), eztest_op1.length(), eztest_op0);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_2length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1.data(),
                eztest_op1.length());
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string &      eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_2length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1.data(),
                eztest_op1.length());
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const EZTEST_STD_NS_ string &      eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_2length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1.data(),
                eztest_op1.length());
    }
# endif

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string & eztest_op0,
                   const char *                  eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_1length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char *                  eztest_op0,
                   const EZTEST_STD_NS_ string & eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_1length(
                eztest_op1.data(), eztest_op1.length(), eztest_op0);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string & eztest_op0,
                   const EZTEST_STD_NS_ string & eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_2length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1.data(),
                eztest_op1.length());
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_strcasene_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t & eztest_var) {
        return EZTEST_NS_ eztest_cxx_print_var_t::eztest_cxx_print_var(
            eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) case-ne (%s)", eztest_op0_expr,
                              eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
         */
        return !EZTEST_NS_ eztest_cxx_binop_strcaseeq_t ::eztest_cxx_run(
            eztest_op0, eztest_op1);
        /* NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
         */
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_flt_eq_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) != (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const float & eztest_op0, const float & eztest_op1) {
        return EZTEST_NS_ eztest_flt_compare(eztest_op0, eztest_op1) != 0;
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_dbl_eq_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) != (%s)", eztest_op0_expr, eztest_op1_expr);
    }


    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const double & eztest_op0, const double & eztest_op1) {
        return EZTEST_NS_ eztest_dbl_compare(eztest_op0, eztest_op1) != 0;
    }

    /* NOLINTEND(llvmlibc-inline-function-decl) */
};


class eztest_cxx_ternop_near_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr,
                             const char * eztest_op2_expr) {
        return EZTEST_PRINTF_("abs(%s - %s) < (%s)", eztest_op0_expr,
                              eztest_op1_expr, eztest_op2_expr);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const double & eztest_op0,
                   const double & eztest_op1,
                   const double & eztest_op2) {
        return EZTEST_ABS_(eztest_op0 - eztest_op1) <= EZTEST_ABS_(eztest_op2);
    }

    template<typename eztest_T0_t, typename eztest_T1_t, typename eztest_T2_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1,
                   const eztest_T2_t & eztest_op2) {
        return EZTEST_ABS_(eztest_op0 - eztest_op1) <= EZTEST_ABS_(eztest_op2);
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

EZTEST_REENABLE_WUNUSED_MEMBER_FUNCTION_


EZTEST_PRIVATE_CXX_INL_ void
eztest_cxx_fail(int eztest_exit_on_failure) {
    EZTEST_NS_ eztest_cur_test_set_failed();
    if (eztest_exit_on_failure != 0) {
        (void)EZTEST_FFLUSH_(EZTEST_STDOUT_);
        EZTEST_EXIT_(1);
    }
}

EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_
/* NOLINTBEGIN(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_T0_t>
EZTEST_PRIVATE_
EZTEST_ATTR_FMT_(7,
                 8) void eztest_cxx_bool_assert(int eztest_exit_on_failure,
                                                int eztest_lineno,
                                                const char * eztest_file,
                                                const char * eztest_op0_expr,
                                                bool         eztest_expec,
                                                const eztest_T0_t & eztest_op0,
                                                const char *        eztest_fmt,
                                                ...) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTEND(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
    EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_
    if ((!eztest_op0) == eztest_expec) {
        (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: (%s) to be %s\n",
                             eztest_file, eztest_lineno, eztest_op0_expr,
                             eztest_expec ? "true" : "false");
        (void)EZTEST_PRINTF_("  Actual  : ");
        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        EZTEST_NS_ eztest_cxx_print_var_t::eztest_cxx_print_var(eztest_op0);
        /* NOLINTEND(llvmlibc-callee-namespace) */
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("  Expected: %s\n",
                             eztest_expec ? "true" : "false");
        if (eztest_fmt != EZTEST_NULL_) {
            /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg) */
            /* NOLINTBEGIN(hicpp-vararg) */
            /* NOLINTBEGIN(cppcoreguide*-pro-bounds-array-to-pointer-decay) */
            /* NOLINTBEGIN(hicpp-no-array-decay) */
            /* NOLINTBEGIN(cppcoreguidelines-init-variables) */
            EZTEST_STD_NS_ va_list eztest_ap;
            /* NOLINTEND(cppcoreguidelines-init-variables) */
            va_start(eztest_ap, eztest_fmt);
            (void)EZTEST_VFPRINTF_(EZTEST_STDOUT_, eztest_fmt, eztest_ap);
            va_end(eztest_ap);

            /* NOLINTEND(hicpp-no-array-decay) */
            /* NOLINTEND(cppcoreguide*-pro-bounds-array-to-pointer-decay) */
            /* NOLINTEND(hicpp-vararg) */
            /* NOLINTEND(cppcoreguidelines-pro-type-vararg) */
        }
        EZTEST_NS_ eztest_cxx_fail(eztest_exit_on_failure);
    }
}

/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_T0_t>
EZTEST_PRIVATE_CXX_INL_ void
eztest_cxx_bool_assert(int                 eztest_exit_on_failure,
                       int                 eztest_lineno,
                       const char *        eztest_file,
                       const char *        eztest_op0_expr,
                       bool                eztest_expec,
                       const eztest_T0_t & eztest_op0) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    EZTEST_NS_ eztest_cxx_bool_assert(eztest_exit_on_failure, eztest_lineno,
                                      eztest_file, eztest_op0_expr,
                                      eztest_expec, eztest_op0, EZTEST_NULL_);
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}

EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_
/* NOLINTBEGIN(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_cxx_binop_t,
         typename eztest_T0_t,
         typename eztest_T1_t>
EZTEST_PRIVATE_
EZTEST_ATTR_FMT_(8,
                 9) void eztest_cxx_binop_assert(int eztest_exit_on_failure,
                                                 int eztest_lineno,
                                                 const char * eztest_file,
                                                 const char * eztest_op0_expr,
                                                 const char * eztest_op1_expr,
                                                 const eztest_T0_t & eztest_op0,
                                                 const eztest_T1_t & eztest_op1,
                                                 const char *        eztest_fmt,
                                                 ...) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTEND(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
    EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_
    /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay) */
    /* NOLINTBEGIN(hicpp-no-array-decay) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    if (!eztest_cxx_binop_t::eztest_cxx_run(eztest_op0, eztest_op1)) {
        (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: ", eztest_file,
                             eztest_lineno);
        (void)eztest_cxx_binop_t::eztest_cxx_print_op_desc(eztest_op0_expr,
                                                           eztest_op1_expr);
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("   Op0: ");
        eztest_cxx_binop_t::eztest_cxx_print_var(eztest_op0);
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("   Op1: ");
        eztest_cxx_binop_t::eztest_cxx_print_var(eztest_op1);
        /* NOLINTEND(llvmlibc-callee-namespace) */
        (void)EZTEST_PRINTF_("\n");
        if (eztest_fmt != EZTEST_NULL_) {
            /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg) */
            /* NOLINTBEGIN(hicpp-vararg) */
            /* NOLINTBEGIN(cppcoreguidelines-init-variables) */
            EZTEST_STD_NS_ va_list eztest_ap;
            /* NOLINTEND(cppcoreguidelines-init-variables) */
            va_start(eztest_ap, eztest_fmt);
            (void)EZTEST_VFPRINTF_(EZTEST_STDOUT_, eztest_fmt, eztest_ap);
            va_end(eztest_ap);
            /* NOLINTEND(hicpp-vararg) */
            /* NOLINTEND(cppcoreguidelines-pro-type-vararg) */
        }
        EZTEST_NS_ eztest_cxx_fail(eztest_exit_on_failure);
    }
    /* NOLINTEND(hicpp-no-array-decay) */
    /* NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay) */
}
/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_cxx_binop_t,
         typename eztest_T0_t,
         typename eztest_T1_t>
EZTEST_PRIVATE_CXX_INL_ void
eztest_cxx_binop_assert(int                 eztest_exit_on_failure,
                        int                 eztest_lineno,
                        const char *        eztest_file,
                        const char *        eztest_op0_expr,
                        const char *        eztest_op1_expr,
                        const eztest_T0_t & eztest_op0,
                        const eztest_T1_t & eztest_op1) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    EZTEST_NS_ eztest_cxx_binop_assert<eztest_cxx_binop_t>(
        eztest_exit_on_failure, eztest_lineno, eztest_file, eztest_op0_expr,
        eztest_op1_expr, eztest_op0, eztest_op1, EZTEST_NULL_);
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}


EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_
/* NOLINTBEGIN(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_cxx_ternop_t,
         typename eztest_T0_t,
         typename eztest_T1_t,
         typename eztest_T2_t>
EZTEST_PRIVATE_
EZTEST_ATTR_FMT_(10, 11) void eztest_cxx_ternop_assert(
    int                 eztest_exit_on_failure,
    int                 eztest_lineno,
    const char *        eztest_file,
    const char *        eztest_op0_expr,
    const char *        eztest_op1_expr,
    const char *        eztest_op2_expr,
    const eztest_T0_t & eztest_op0,
    const eztest_T1_t & eztest_op1,
    const eztest_T2_t & eztest_op2,
    const char *        eztest_fmt,
    ...) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTEND(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
    EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_
    /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay) */
    /* NOLINTBEGIN(hicpp-no-array-decay) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    if (!eztest_cxx_ternop_t::eztest_cxx_run(eztest_op0, eztest_op1,
                                             eztest_op2)) {
        (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: ", eztest_file,
                             eztest_lineno);
        (void)eztest_cxx_ternop_t::eztest_cxx_print_op_desc(
            eztest_op0_expr, eztest_op1_expr, eztest_op2_expr);
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("   Arg0: ");
        eztest_cxx_ternop_t::eztest_cxx_print_var(eztest_op0);
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("   Arg1: ");
        eztest_cxx_ternop_t::eztest_cxx_print_var(eztest_op1);
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("   Arg2: ");
        eztest_cxx_ternop_t::eztest_cxx_print_var(eztest_op2);
        /* NOLINTEND(llvmlibc-callee-namespace) */
        (void)EZTEST_PRINTF_("\n");
        if (eztest_fmt != EZTEST_NULL_) {
            /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg) */
            /* NOLINTBEGIN(hicpp-vararg) */
            /* NOLINTBEGIN(cppcoreguidelines-init-variables) */
            EZTEST_STD_NS_ va_list eztest_ap;
            /* NOLINTEND(cppcoreguidelines-init-variables) */
            va_start(eztest_ap, eztest_fmt);
            (void)EZTEST_VFPRINTF_(EZTEST_STDOUT_, eztest_fmt, eztest_ap);
            va_end(eztest_ap);
            /* NOLINTEND(hicpp-vararg) */
            /* NOLINTEND(cppcoreguidelines-pro-type-vararg) */
        }
        EZTEST_NS_ eztest_cxx_fail(eztest_exit_on_failure);
    }
    /* NOLINTEND(hicpp-no-array-decay) */
    /* NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay) */
}

/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_cxx_ternop_t,
         typename eztest_T0_t,
         typename eztest_T1_t,
         typename eztest_T2_t>
EZTEST_PRIVATE_CXX_INL_ void
eztest_cxx_ternop_assert(int                 eztest_exit_on_failure,
                         int                 eztest_lineno,
                         const char *        eztest_file,
                         const char *        eztest_op0_expr,
                         const char *        eztest_op1_expr,
                         const char *        eztest_op2_expr,
                         const eztest_T0_t & eztest_op0,
                         const eztest_T1_t & eztest_op1,
                         const eztest_T2_t & eztest_op2) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    EZTEST_NS_ eztest_cxx_ternop_assert<eztest_cxx_ternop_t>(
        eztest_exit_on_failure, eztest_lineno, eztest_file, eztest_op0_expr,
        eztest_op1_expr, eztest_op2_expr, eztest_op0, eztest_op1, eztest_op2,
        EZTEST_NULL_);
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}


EZTEST_REENABLE_WUNUSED_TEMPLATE_
EZTEST_REENABLE_WTEMPLATES_

EZTEST_NAMESPACE_END_

EZTEST_DISABLE_WCXX98_COMPAT_PEDANTIC_
EZTEST_DISABLE_WVARIADIC_MACROS_

# define EZTEST_GET_TERNOP_EXPRESSIONS_IMPL_(expr0, expr1, expr2, ...)         \
     EZTEST_STRINGIFY_(expr0), EZTEST_STRINGIFY_(expr1),                       \
         EZTEST_STRINGIFY_(expr2)
# define EZTEST_GET_TERNOP_EXPRESSIONS_(...)                                   \
     EZTEST_GET_TERNOP_EXPRESSIONS_IMPL_(__VA_ARGS__, eztest0, eztest1,        \
                                         eztest2, eztest3)

# define EZTEST_GET_BINOP_EXPRESSIONS_IMPL_(expr0, expr1, ...)                 \
     EZTEST_STRINGIFY_(expr0), EZTEST_STRINGIFY_(expr1)
# define EZTEST_GET_BINOP_EXPRESSIONS_(...)                                    \
     EZTEST_GET_BINOP_EXPRESSIONS_IMPL_(__VA_ARGS__, eztest0, eztest1, eztest2)

# define EZTEST_GET_BOOL_EXPRESSIONS_IMPL_(expr0, ...) EZTEST_STRINGIFY_(expr0)
# define EZTEST_GET_BOOL_EXPRESSIONS_(...)                                     \
     EZTEST_GET_BOOL_EXPRESSIONS_IMPL_(__VA_ARGS__, eztest0, eztest1)

# define EZTEST_ASSERT_BOOL_IMPL_(exit_on_fail, expec, ...)                    \
     EZTEST_NS_ eztest_cxx_bool_assert(                                        \
         exit_on_fail, EZTEST_LINE_, EZTEST_FILE_,                             \
         EZTEST_GET_BOOL_EXPRESSIONS_(__VA_ARGS__), expec, __VA_ARGS__)


# define EZTEST_ASSERT_BINOP_IMPL_(exit_on_fail, binop_t, ...)                 \
     EZTEST_NS_ eztest_cxx_binop_assert<EZTEST_NS_ binop_t>(                   \
         exit_on_fail, EZTEST_LINE_, EZTEST_FILE_,                             \
         EZTEST_GET_BINOP_EXPRESSIONS_(__VA_ARGS__), __VA_ARGS__)

# define EZTEST_ASSERT_TERNOP_IMPL_(exit_on_fail, ternop_t, ...)               \
     EZTEST_NS_ eztest_cxx_ternop_assert<EZTEST_NS_ ternop_t>(                 \
         exit_on_fail, EZTEST_LINE_, EZTEST_FILE_,                             \
         EZTEST_GET_TERNOP_EXPRESSIONS_(__VA_ARGS__), __VA_ARGS__)

# define EZTEST_ASSERT_TRUE_IMPL_(...)                                         \
     EZTEST_ASSERT_BOOL_IMPL_(1, true, __VA_ARGS__)
# define EZTEST_ASSERT_FALSE_IMPL_(...)                                        \
     EZTEST_ASSERT_BOOL_IMPL_(1, false, __VA_ARGS__)
# define EZTEST_ASSERT_EQ_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_eq_t, __VA_ARGS__)
# define EZTEST_ASSERT_NE_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_ne_t, __VA_ARGS__)
# define EZTEST_ASSERT_LE_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_le_t, __VA_ARGS__)
# define EZTEST_ASSERT_LT_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_lt_t, __VA_ARGS__)
# define EZTEST_ASSERT_GE_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_ge_t, __VA_ARGS__)
# define EZTEST_ASSERT_GT_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_gt_t, __VA_ARGS__)
# define EZTEST_ASSERT_STREQ_IMPL_(...)                                        \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_streq_t, __VA_ARGS__)
# define EZTEST_ASSERT_STRNE_IMPL_(...)                                        \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_strne_t, __VA_ARGS__)
# define EZTEST_ASSERT_STRCASEEQ_IMPL_(...)                                    \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_strcaseeq_t, __VA_ARGS__)
# define EZTEST_ASSERT_STRCASENE_IMPL_(...)                                    \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_strcasene_t, __VA_ARGS__)
# define EZTEST_ASSERT_FLOAT_EQ_IMPL_(...)                                     \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_flt_eq_t, __VA_ARGS__)
# define EZTEST_ASSERT_DOUBLE_EQ_IMPL_(...)                                    \
     EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_dbl_eq_t, __VA_ARGS__)
# define EZTEST_ASSERT_NEAR_IMPL_(...)                                         \
     EZTEST_ASSERT_TERNOP_IMPL_(1, eztest_cxx_ternop_near_t, __VA_ARGS__)

# define EZTEST_EXPECT_TRUE_IMPL_(...)                                         \
     EZTEST_ASSERT_BOOL_IMPL_(0, true, __VA_ARGS__)
# define EZTEST_EXPECT_FALSE_IMPL_(...)                                        \
     EZTEST_ASSERT_BOOL_IMPL_(0, false, __VA_ARGS__)
# define EZTEST_EXPECT_EQ_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_eq_t, __VA_ARGS__)
# define EZTEST_EXPECT_NE_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_ne_t, __VA_ARGS__)
# define EZTEST_EXPECT_LE_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_le_t, __VA_ARGS__)
# define EZTEST_EXPECT_LT_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_lt_t, __VA_ARGS__)
# define EZTEST_EXPECT_GE_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_ge_t, __VA_ARGS__)
# define EZTEST_EXPECT_GT_IMPL_(...)                                           \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_gt_t, __VA_ARGS__)
# define EZTEST_EXPECT_STREQ_IMPL_(...)                                        \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_streq_t, __VA_ARGS__)
# define EZTEST_EXPECT_STRNE_IMPL_(...)                                        \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_strne_t, __VA_ARGS__)
# define EZTEST_EXPECT_STRCASEEQ_IMPL_(...)                                    \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_strcaseeq_t, __VA_ARGS__)
# define EZTEST_EXPECT_STRCASENE_IMPL_(...)                                    \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_strcasene_t, __VA_ARGS__)
# define EZTEST_EXPECT_FLOAT_EQ_IMPL_(...)                                     \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_flt_eq_t, __VA_ARGS__)
# define EZTEST_EXPECT_DOUBLE_EQ_IMPL_(...)                                    \
     EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_dbl_eq_t, __VA_ARGS__)
# define EZTEST_EXPECT_NEAR_IMPL_(...)                                         \
     EZTEST_ASSERT_TERNOP_IMPL_(0, eztest_cxx_ternop_near_t, __VA_ARGS__)


EZTEST_REENABLE_WCXX98_COMPAT_PEDANTIC_
EZTEST_REENABLE_WVARIADIC_MACROS_
/* End include of: eztest-cxx-asserts-impl.h  */
#else
/* Begin include of: eztest-c-asserts-impl.h  */

# if !EZTEST_C_LANG_
#  error "C implementation included without C!"
# endif


# if EZTEST_C_LANG_ >= 2011 && (EZTEST_C_PRINT_ARGS)
#  define EZTEST_C11_DISABLE_WLONG_LONG_      EZTEST_DISABLE_WLONG_LONG_
#  define EZTEST_C11_DISABLE_WC99_COMPAT_     EZTEST_DISABLE_WC99_COMPAT_
#  define EZTEST_C11_DISABLE_WC99_C11_COMPAT_ EZTEST_DISABLE_WC99_C11_COMPAT_
#  define EZTEST_C11_DISABLE_WC90_C99_COMPAT_ EZTEST_DISABLE_WC90_C99_COMPAT_
#  define EZTEST_C11_DISABLE_WC11_EXTENSIONS_ EZTEST_DISABLE_WC11_EXTENSIONS_
#  define EZTEST_C11_DISABLE_WPRE_C11_COMPAT_ EZTEST_DISABLE_WPRE_C11_COMPAT_

#  define EZTEST_C11_REENABLE_WLONG_LONG_      EZTEST_REENABLE_WLONG_LONG_
#  define EZTEST_C11_REENABLE_WC99_C11_COMPAT_ EZTEST_REENABLE_WC99_C11_COMPAT_
#  define EZTEST_C11_REENABLE_WC90_C99_COMPAT_ EZTEST_REENABLE_WC90_C99_COMPAT_
#  define EZTEST_C11_REENABLE_WC99_COMPAT_     EZTEST_REENABLE_WC99_COMPAT_
#  define EZTEST_C11_REENABLE_WC11_EXTENSIONS_ EZTEST_REENABLE_WC11_EXTENSIONS_
#  define EZTEST_C11_REENABLE_WPRE_C11_COMPAT_ EZTEST_REENABLE_WPRE_C11_COMPAT_

/* clang-format off */
#define EZTEST_C_GET_VAR_FMT_SPECIFIER_(var)    \
    _Generic((var),                             \
             _Bool : "%d",                      \
             unsigned char : "%hhu",            \
             unsigned short : "%hu",            \
             unsigned int : "%u",               \
             unsigned long : "%lu",             \
             unsigned long long : "%llu",       \
             signed char : "%hhd",              \
             signed short : "%hd",              \
             signed int : "%d",                 \
             signed long : "%ld",               \
             signed long long : "%lld",         \
             char : "%c",                       \
             long double : "%Lf",               \
             double : "%lf",                    \
             float : "%f",                      \
             void * :"%p",                      \
             const void * :"%p",                \
             _Bool * : "%p",                    \
             const _Bool * : "%p",              \
             unsigned char * : "%p",            \
             const unsigned char * : "%p",      \
             unsigned short * : "%p",           \
             const unsigned short * : "%p",     \
             unsigned int * : "%p",             \
             const unsigned int * : "%p",       \
             unsigned long * : "%p",            \
             const unsigned long * : "%p",      \
             unsigned long long * : "%p",       \
             const unsigned long long * : "%p", \
             signed char * : "%p",              \
             const signed char * : "%p",        \
             signed short * : "%p",             \
             const signed short * : "%p",       \
             signed int * : "%p",               \
             const signed int * : "%p",         \
             signed long * : "%p",              \
             const signed long * : "%p",        \
             signed long long * : "%p",         \
             const signed long long * : "%p",   \
             char * : "%p",                     \
             const char * : "%p",               \
             long double * : "%p",              \
             const long double * : "%p",        \
             double * : "%p",                   \
             const double * : "%p",             \
             float * : "%p",                    \
             const float * : "%p",              \
             default : EZTEST_NULL_)


#define EZTEST_C_DO_PRINT_VAR_(fmt, var)                                \
    _Generic((var),                                                     \
             default : EZTEST_PRINTF_((fmt), (var)))

/* clang-format on */
# else
#  define EZTEST_C11_DISABLE_WLONG_LONG_
#  define EZTEST_C11_REENABLE_WLONG_LONG_

#  define EZTEST_C_GET_VAR_FMT_SPECIFIER_(var) EZTEST_NULL_
#  define EZTEST_C_DO_PRINT_VAR_(fmt, var)     0
# endif

# define EZTEST_C_PRINT_VAR_IMPL_(var, tmpvar)                                 \
     do {                                                                      \
         EZTEST_C11_DISABLE_WLONG_LONG_                                        \
         EZTEST_C11_DISABLE_WC99_C11_COMPAT_                                   \
         EZTEST_C11_DISABLE_WC90_C99_COMPAT_                                   \
         EZTEST_C11_DISABLE_WPRE_C11_COMPAT_                                   \
         /* NOLINTBEGIN(bugprone-macro-parentheses) */                         \
         const char * tmpvar = EZTEST_C_GET_VAR_FMT_SPECIFIER_(var);           \
         /* NOLINTEND(bugprone-macro-parentheses) */                           \
         EZTEST_C11_REENABLE_WPRE_C11_COMPAT_                                  \
         EZTEST_C11_REENABLE_WC90_C99_COMPAT_                                  \
         EZTEST_C11_REENABLE_WC99_C11_COMPAT_                                  \
         EZTEST_C11_REENABLE_WLONG_LONG_                                       \
         if ((tmpvar) != EZTEST_NULL_) {                                       \
             EZTEST_C11_DISABLE_WC99_C11_COMPAT_                               \
             EZTEST_C11_DISABLE_WC90_C99_COMPAT_                               \
             EZTEST_C11_DISABLE_WPRE_C11_COMPAT_                               \
             EZTEST_DISABLE_WFORMAT_NONLITERAL_(void)                          \
             EZTEST_C_DO_PRINT_VAR_((tmpvar), (var));                          \
             EZTEST_REENABLE_WFORMAT_NONLITERAL_                               \
             EZTEST_C11_REENABLE_WPRE_C11_COMPAT_                              \
             EZTEST_C11_REENABLE_WC90_C99_COMPAT_                              \
             EZTEST_C11_REENABLE_WC99_C11_COMPAT_                              \
         }                                                                     \
         else {                                                                \
             (void)EZTEST_NS_ eztest_hex_print_var(                            \
                 EZTEST_CAST_(const uint8_t *, &(var)), sizeof(var));          \
         }                                                                     \
     } while (0)


# define EZTEST_C_PRINT_VAR_(var)                                              \
     EZTEST_C_PRINT_VAR_IMPL_(var, EZTEST_UNIQUE_NAME_(eztest_var_fmt_tmp_))

# define EZTEST_C_PRINT_STR_(var) (void)EZTEST_PRINTF_("%s", var);


# define EZTEST_C_ASSERT_PRINT_BOOL_HDR_(expec_str, expr_op0_str)              \
     (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: (%s) to be %s\n",          \
                          EZTEST_FILE_, EZTEST_LINE_, expr_op0_str,            \
                          expec_str);

# define EZTEST_C_ASSERT_PRINT_BINOP_HDR_(op_fmt, expr_op0_str, expr_op1_str)  \
     (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: " op_fmt "\n",             \
                          EZTEST_FILE_, EZTEST_LINE_, expr_op0_str,            \
                          expr_op1_str);

# define EZTEST_C_ASSERT_PRINT_TERNOP_HDR_(op_fmt, expr_op0_str, expr_op1_str, \
                                           expr_op2_str)                       \
     (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: " op_fmt "\n",             \
                          EZTEST_FILE_, EZTEST_LINE_, expr_op0_str,            \
                          expr_op1_str, expr_op2_str);

# define EZTEST_C_ASSERT_PRINT_BOOL_(expec_str, expr_op0_str, expr_op0_var)    \
     EZTEST_C_ASSERT_PRINT_BOOL_HDR_(expec_str, expr_op0_str);                 \
     (void)EZTEST_PRINTF_("  Actual  : ");                                     \
     EZTEST_C_PRINT_VAR_(expr_op0_var);                                        \
     (void)EZTEST_PRINTF_("\n");                                               \
     (void)EZTEST_PRINTF_("  Expected: %s", expec_str);                        \
     (void)EZTEST_PRINTF_("\n");

# define EZTEST_C_ASSERT_PRINT_BINOP_(op_fmt, expr_op0_str, expr_op1_str,      \
                                      expr_op0_var, expr_op1_var)              \
     EZTEST_C_ASSERT_PRINT_BINOP_HDR_(op_fmt, expr_op0_str, expr_op1_str);     \
     (void)EZTEST_PRINTF_("  Lhs: ");                                          \
     EZTEST_C_PRINT_VAR_(expr_op0_var);                                        \
     (void)EZTEST_PRINTF_("\n");                                               \
     (void)EZTEST_PRINTF_("  Rhs: ");                                          \
     EZTEST_C_PRINT_VAR_(expr_op1_var);                                        \
     (void)EZTEST_PRINTF_("\n");

# define EZTEST_C_ASSERT_PRINT_TERNOP_(op_fmt, expr_op0_str, expr_op1_str,     \
                                       expr_op2_str, expr_op0_var,             \
                                       expr_op1_var, expr_op2_var)             \
     EZTEST_C_ASSERT_PRINT_TERNOP_HDR_(op_fmt, expr_op0_str, expr_op1_str,     \
                                       expr_op2_str);                          \
     (void)EZTEST_PRINTF_("  Arg0: ");                                         \
     EZTEST_C_PRINT_VAR_(expr_op0_var);                                        \
     (void)EZTEST_PRINTF_("\n");                                               \
     (void)EZTEST_PRINTF_("  Arg1: ");                                         \
     EZTEST_C_PRINT_VAR_(expr_op1_var);                                        \
     (void)EZTEST_PRINTF_("\n");                                               \
     (void)EZTEST_PRINTF_("  Arg2: ");                                         \
     EZTEST_C_PRINT_VAR_(expr_op2_var);                                        \
     (void)EZTEST_PRINTF_("\n");

# define EZTEST_C_ASSERT_PRINT_STR_(op_fmt, expr_op0_str, expr_op1_str,        \
                                    expr_op0_var, expr_op1_var)                \
     EZTEST_C_ASSERT_PRINT_BINOP_HDR_(op_fmt, expr_op0_str, expr_op1_str);     \
     (void)EZTEST_PRINTF_("  Lhs: ");                                          \
     EZTEST_C_PRINT_STR_(expr_op0_var);                                        \
     (void)EZTEST_PRINTF_("\n");                                               \
     (void)EZTEST_PRINTF_("  Rhs: ");                                          \
     EZTEST_C_PRINT_STR_(expr_op1_var);                                        \
     (void)EZTEST_PRINTF_("\n");


# if (defined EZTEST_AUTO_) && EZTEST_C_LANG_ >= 2011 && (EZTEST_C_PRINT_ARGS)
#  define EZTEST_C_ASSERT_BOOL_(fail_on_err, expec, expr_op0, ...)             \
      do {                                                                     \
          const EZTEST_AUTO_(expr_op0) eztest_expr_op0_tmp_ = expr_op0;        \
          if (EZTEST_C_ASSERT_CHECK_BOOL_(expec, eztest_expr_op0_tmp_)) {      \
              EZTEST_C_ASSERT_PRINT_BOOL_((expec) ? "true" : "false",          \
                                          EZTEST_STRINGIFY_(expr_op0),         \
                                          eztest_expr_op0_tmp_);               \
              EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                 \
          }                                                                    \
      } while (0)


#  define EZTEST_C_ASSERT_BINOP_(fail_on_err, op, op_fmt, expr_op0, expr_op1,  \
                                 ...)                                          \
      do {                                                                     \
          const EZTEST_AUTO_(expr_op0) eztest_expr_op0_tmp_ = expr_op0;        \
          const EZTEST_AUTO_(expr_op1) eztest_expr_op1_tmp_ = expr_op1;        \
          if (EZTEST_C_ASSERT_CHECK_BINOP_(op, eztest_expr_op0_tmp_,           \
                                           eztest_expr_op1_tmp_)) {            \
              EZTEST_C_ASSERT_PRINT_BINOP_(                                    \
                  op_fmt, EZTEST_STRINGIFY_(expr_op0),                         \
                  EZTEST_STRINGIFY_(expr_op1), eztest_expr_op0_tmp_,           \
                  eztest_expr_op1_tmp_);                                       \
              EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                 \
          }                                                                    \
      } while (0)


#  define EZTEST_C_ASSERT_TERNOP_(fail_on_err, op, op_fmt, expr_op0, expr_op1, \
                                  expr_op2, ...)                               \
      do {                                                                     \
          const EZTEST_AUTO_(expr_op0) eztest_expr_op0_tmp_ = expr_op0;        \
          const EZTEST_AUTO_(expr_op1) eztest_expr_op1_tmp_ = expr_op1;        \
          const EZTEST_AUTO_(expr_op2) eztest_expr_op2_tmp_ = expr_op2;        \
          if (EZTEST_C_ASSERT_CHECK_TERNOP_(op, eztest_expr_op0_tmp_,          \
                                            eztest_expr_op1_tmp_,              \
                                            eztest_expr_op2_tmp_)) {           \
              EZTEST_C_ASSERT_PRINT_TERNOP_(                                   \
                  op_fmt, EZTEST_STRINGIFY_(expr_op0),                         \
                  EZTEST_STRINGIFY_(expr_op1), EZTEST_STRINGIFY_(expr_op2),    \
                  eztest_expr_op0_tmp_, eztest_expr_op1_tmp_,                  \
                  eztest_expr_op2_tmp_);                                       \
              EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                 \
          }                                                                    \
      } while (0)

#  define EZTEST_C_ASSERT_STR_(fail_on_err, op, op_fmt, expr_op0, expr_op1,    \
                               ...)                                            \
      do {                                                                     \
          const EZTEST_AUTO_(expr_op0) eztest_expr_op0_tmp_ = expr_op0;        \
          const EZTEST_AUTO_(expr_op1) eztest_expr_op1_tmp_ = expr_op1;        \
          if (EZTEST_C_ASSERT_CHECK_BINOP_(op, eztest_expr_op0_tmp_,           \
                                           eztest_expr_op1_tmp_)) {            \
              EZTEST_C_ASSERT_PRINT_STR_(op_fmt, EZTEST_STRINGIFY_(expr_op0),  \
                                         EZTEST_STRINGIFY_(expr_op1),          \
                                         eztest_expr_op0_tmp_,                 \
                                         eztest_expr_op1_tmp_);                \
              EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                 \
          }                                                                    \
      } while (0)


# else
#  define EZTEST_C_ASSERT_BOOL_(fail_on_err, expec, expr, ...)                 \
      do {                                                                     \
          if (EZTEST_C_ASSERT_CHECK_BOOL_(expec, expr)) {                      \
              EZTEST_C_ASSERT_PRINT_BOOL_HDR_((expec) ? "true" : "false",      \
                                              EZTEST_STRINGIFY_(expr));        \
              EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                 \
          }                                                                    \
      } while (0)

#  define EZTEST_C_ASSERT_BINOP_(fail_on_err, op, op_fmt, expr_op0, expr_op1,  \
                                 ...)                                          \
      do {                                                                     \
          if (EZTEST_C_ASSERT_CHECK_BINOP_(op, expr_op0, expr_op1)) {          \
              EZTEST_C_ASSERT_PRINT_BINOP_HDR_(op_fmt,                         \
                                               EZTEST_STRINGIFY_(expr_op0),    \
                                               EZTEST_STRINGIFY_(expr_op1));   \
              EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                 \
          }                                                                    \
      } while (0)


#  define EZTEST_C_ASSERT_TERNOP_(fail_on_err, op, op_fmt, expr_op0, expr_op1, \
                                  expr_op2, ...)                               \
      do {                                                                     \
          if (EZTEST_C_ASSERT_CHECK_TERNOP_(op, expr_op0, expr_op1,            \
                                            expr_op2)) {                       \
              EZTEST_C_ASSERT_PRINT_TERNOP_HDR_(                               \
                  op_fmt, EZTEST_STRINGIFY_(expr_op0),                         \
                  EZTEST_STRINGIFY_(expr_op1), EZTEST_STRINGIFY_(expr_op2));   \
              EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                 \
          }                                                                    \
      } while (0)

#  define EZTEST_C_ASSERT_STR_(fail_on_err, op, op_fmt, expr_op0, expr_op1,    \
                               ...)                                            \
      EZTEST_C_ASSERT_BINOP_(fail_on_err, op, op_fmt, expr_op0, expr_op1,      \
                             __VA_ARGS__)
# endif

# define EZTEST_C_ASSERT_FAIL_(fail_on_err, ...)                               \
     (void)EZTEST_PRINTF_(__VA_ARGS__);                                        \
     EZTEST_NS_ eztest_cur_test_set_failed();                                  \
     if (fail_on_err) {                                                        \
         (void)EZTEST_FFLUSH_(stdout);                                         \
         (void)EZTEST_FFLUSH_(stderr);                                         \
         EZTEST_EXIT_(1);                                                      \
     }

# define EZTEST_C_ASSERT_CHECK_BOOL_(expec, expr)                              \
     ((expec) ? (!(expr)) : (!!(expr)))

# define EZTEST_C_ASSERT_CHECK_BINOP_(op, expr_op0, expr_op1)                  \
     (!(op((expr_op0), (expr_op1))))

# define EZTEST_C_ASSERT_CHECK_TERNOP_(op, expr_arg0, expr_arg1, expr_arg2)    \
     (!(op((expr_arg0), (expr_arg1), (expr_arg2))))

# define EZTEST_C_BINOP_EQ_(op0, op1) ((op0) == (op1))
# define EZTEST_C_BINOP_LT_(op0, op1) ((op0) < (op1))
# define EZTEST_C_BINOP_LE_(op0, op1) ((op0) <= (op1))
# define EZTEST_C_FMT_BINOP_(op)      "(%s) " op " (%s)"
# define EZTEST_C_TERNOP_FP_NEAR_(op0, op1, abs_err)                           \
     (EZTEST_ABS_((op0) - (op1)) <= EZTEST_ABS_(abs_err))

# define EZTEST_C_FLT_COMPARE_WRAPPER_(op0, op1)                               \
     EZTEST_NS_ eztest_flt_compare(EZTEST_CAST_(float, op0),                   \
                                   EZTEST_CAST_(float, op1))
# define EZTEST_C_DBL_COMPARE_WRAPPER_(op0, op1)                               \
     EZTEST_NS_ eztest_dbl_compare(EZTEST_CAST_(double, op0),                  \
                                   EZTEST_CAST_(double, op1))

# define EZTEST_C_ASSERT_TRUE_IMPL_(fail_on_err, ...)                          \
     EZTEST_C_ASSERT_BOOL_(fail_on_err, 1, __VA_ARGS__)
# define EZTEST_C_ASSERT_FALSE_IMPL_(fail_on_err, ...)                         \
     EZTEST_C_ASSERT_BOOL_(fail_on_err, 0, __VA_ARGS__)

# define EZTEST_C_ASSERT_EQ_IMPL_(fail_on_err, ...)                            \
     EZTEST_C_ASSERT_BINOP_(fail_on_err, EZTEST_C_BINOP_EQ_,                   \
                            EZTEST_C_FMT_BINOP_("=="), __VA_ARGS__)
# define EZTEST_C_ASSERT_NE_IMPL_(fail_on_err, ...)                            \
     EZTEST_C_ASSERT_BINOP_(fail_on_err, !EZTEST_C_BINOP_EQ_,                  \
                            EZTEST_C_FMT_BINOP_("!="), __VA_ARGS__)
# define EZTEST_C_ASSERT_LE_IMPL_(fail_on_err, ...)                            \
     EZTEST_C_ASSERT_BINOP_(fail_on_err, EZTEST_C_BINOP_LE_,                   \
                            EZTEST_C_FMT_BINOP_("<="), __VA_ARGS__)
# define EZTEST_C_ASSERT_LT_IMPL_(fail_on_err, ...)                            \
     EZTEST_C_ASSERT_BINOP_(fail_on_err, EZTEST_C_BINOP_LT_,                   \
                            EZTEST_C_FMT_BINOP_("<"), __VA_ARGS__)
# define EZTEST_C_ASSERT_GE_IMPL_(fail_on_err, ...)                            \
     EZTEST_C_ASSERT_BINOP_(fail_on_err, !EZTEST_C_BINOP_LT_,                  \
                            EZTEST_C_FMT_BINOP_(">="), __VA_ARGS__)
# define EZTEST_C_ASSERT_GT_IMPL_(fail_on_err, ...)                            \
     EZTEST_C_ASSERT_BINOP_(fail_on_err, !EZTEST_C_BINOP_LE_,                  \
                            EZTEST_C_FMT_BINOP_(">"), __VA_ARGS__)

# define EZTEST_C_ASSERT_STREQ_IMPL_(fail_on_err, ...)                         \
     EZTEST_C_ASSERT_STR_(fail_on_err, !EZTEST_STRCMP_,                        \
                          EZTEST_C_FMT_BINOP_("eq"), __VA_ARGS__)
# define EZTEST_C_ASSERT_STRNE_IMPL_(fail_on_err, ...)                         \
     EZTEST_C_ASSERT_STR_(fail_on_err, EZTEST_STRCMP_,                         \
                          EZTEST_C_FMT_BINOP_("ne"), __VA_ARGS__)
# define EZTEST_C_ASSERT_STRCASEEQ_IMPL_(fail_on_err, ...)                     \
     EZTEST_C_ASSERT_STR_(fail_on_err, !EZTEST_STRCASECMP_,                    \
                          EZTEST_C_FMT_BINOP_("case-eq"), __VA_ARGS__)
# define EZTEST_C_ASSERT_STRCASENE_IMPL_(fail_on_err, ...)                     \
     EZTEST_C_ASSERT_STR_(fail_on_err, EZTEST_STRCASECMP_,                     \
                          EZTEST_C_FMT_BINOP_("case-ne"), __VA_ARGS__)

# define EZTEST_C_ASSERT_FLOAT_EQ_IMPL_(fail_on_err, ...)                      \
     EZTEST_C_ASSERT_BINOP_(fail_on_err, EZTEST_C_FLT_COMPARE_WRAPPER_,        \
                            EZTEST_C_FMT_BINOP_("=="), __VA_ARGS__)
# define EZTEST_C_ASSERT_DOUBLE_EQ_IMPL_(fail_on_err, ...)                     \
     EZTEST_C_ASSERT_BINOP_(fail_on_err, EZTEST_C_DBL_COMPARE_WRAPPER_,        \
                            EZTEST_C_FMT_BINOP_("=="), __VA_ARGS__)
# define EZTEST_C_ASSERT_NEAR_IMPL_(fail_on_err, ...)                          \
     EZTEST_C_ASSERT_TERNOP_(fail_on_err, EZTEST_C_TERNOP_FP_NEAR_,            \
                             "abs(%s - %s) <= (%s)", __VA_ARGS__)


# define EZTEST_PP_ARGS_TO_N_(...) EZTEST_PP_ARGS_TO_N_PRIM_(__VA_ARGS__)
# define EZTEST_PP_ARGS_TO_N_PRIM_(                                            \
     a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16,    \
     a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30,     \
     a31, a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44,     \
     a45, a46, a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58,     \
     a59, a60, a61, a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72,     \
     a73, a74, a75, a76, a77, a78, a79, a80, a81, a82, a83, a84, a85, a86,     \
     a87, a88, a89, a90, a91, a92, a93, a94, a95, a96, a97, a98, a99, a100,    \
     a101, a102, a103, a104, a105, a106, a107, a108, a109, a110, a111, a112,   \
     a113, a114, a115, a116, a117, a118, a119, a120, a121, a122, a123, a124,   \
     a125, a126, a127, a128, a129, a130, a131, a132, a133, a134, a135, a136,   \
     a137, a138, a139, a140, a141, a142, a143, a144, a145, a146, a147, a148,   \
     a149, a150, a151, a152, a153, a154, a155, a156, a157, a158, a159, a160,   \
     a161, a162, a163, a164, a165, a166, a167, a168, a169, a170, a171, a172,   \
     a173, a174, a175, a176, a177, a178, a179, a180, a181, a182, a183, a184,   \
     a185, a186, a187, a188, a189, a190, a191, a192, a193, a194, a195, a196,   \
     a197, a198, a199, a200, a201, a202, a203, a204, a205, a206, a207, a208,   \
     a209, a210, a211, a212, a213, a214, a215, a216, a217, a218, a219, a220,   \
     a221, a222, a223, a224, a225, a226, a227, a228, a229, a230, a231, a232,   \
     a233, a234, a235, a236, a237, a238, a239, a240, a241, a242, a243, a244,   \
     a245, a246, a247, a248, a249, a250, a251, a252, a253, a254, a255, a256,   \
     a257, aN, ...)                                                            \
     aN
# define EZTEST_PP_NARG_1N_(...)                                               \
     EZTEST_PP_ARGS_TO_N_(__VA_ARGS__, EZTEST_PP_REVERSE_SEQ_1N_())
# define EZTEST_PP_REVERSE_SEQ_1N_()                                           \
     N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,   \
         N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,  \
         N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,  \
         N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,  \
         N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,  \
         N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,  \
         N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,  \
         N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,  \
         N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,  \
         N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,  \
         N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,  \
         N, N, 1, BAD


# define EZTEST_CLEANED_VA_ARGS_1(...) __VA_ARGS__, "%s", ""
# define EZTEST_CLEANED_VA_ARGS_N(...) __VA_ARGS__
# define EZTEST_CLEAN_VA_ARGS_(...)                                            \
     EZTEST_CAT_(EZTEST_CLEANED_VA_ARGS_, EZTEST_PP_NARG_1N_(__VA_ARGS__))     \
     (__VA_ARGS__)

# define EZTEST_ASSERT_TRUE_IMPL_(...)                                         \
     EZTEST_C_ASSERT_TRUE_IMPL_(1, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_FALSE_IMPL_(...)                                        \
     EZTEST_C_ASSERT_FALSE_IMPL_(1, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_EQ_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_EQ_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_NE_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_NE_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_LE_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_LE_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_LT_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_LT_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_GE_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_GE_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_GT_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_GT_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_STREQ_IMPL_(op0, ...)                                   \
     EZTEST_C_ASSERT_STREQ_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_STRNE_IMPL_(op0, ...)                                   \
     EZTEST_C_ASSERT_STRNE_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_STRCASEEQ_IMPL_(op0, ...)                               \
     EZTEST_C_ASSERT_STRCASEEQ_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_STRCASENE_IMPL_(op0, ...)                               \
     EZTEST_C_ASSERT_STRCASENE_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_FLOAT_EQ_IMPL_(op0, ...)                                \
     EZTEST_C_ASSERT_FLOAT_EQ_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_DOUBLE_EQ_IMPL_(op0, ...)                               \
     EZTEST_C_ASSERT_DOUBLE_EQ_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_ASSERT_NEAR_IMPL_(op0, op1, ...)                               \
     EZTEST_C_ASSERT_NEAR_IMPL_(1, op0, op1, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))


# define EZTEST_EXPECT_TRUE_IMPL_(...)                                         \
     EZTEST_C_ASSERT_TRUE_IMPL_(0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_FALSE_IMPL_(...)                                        \
     EZTEST_C_ASSERT_FALSE_IMPL_(0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_EQ_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_EQ_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_NE_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_NE_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_LE_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_LE_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_LT_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_LT_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_GE_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_GE_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_GT_IMPL_(op0, ...)                                      \
     EZTEST_C_ASSERT_GT_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_STREQ_IMPL_(op0, ...)                                   \
     EZTEST_C_ASSERT_STREQ_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_STRNE_IMPL_(op0, ...)                                   \
     EZTEST_C_ASSERT_STRNE_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_STRCASEEQ_IMPL_(op0, ...)                               \
     EZTEST_C_ASSERT_STRCASEEQ_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_STRCASENE_IMPL_(op0, ...)                               \
     EZTEST_C_ASSERT_STRCASENE_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_FLOAT_EQ_IMPL_(op0, ...)                                \
     EZTEST_C_ASSERT_FLOAT_EQ_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_DOUBLE_EQ_IMPL_(op0, ...)                               \
     EZTEST_C_ASSERT_DOUBLE_EQ_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
# define EZTEST_EXPECT_NEAR_IMPL_(op0, op1, ...)                               \
     EZTEST_C_ASSERT_NEAR_IMPL_(0, op0, op1, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))


/* End include of: eztest-c-asserts-impl.h  */
#endif

/* End include of: eztest-asserts-impl.h  */
/* Begin include of: eztest-list.h  */

/* Begin include of: eztest-struct-padding.h  */


#ifdef UINTPTR_MAX
# if (UINTPTR_MAX) <= (UINT_MAX)
#  define EZTEST_STRUCT_INTT_PADDING_
#  define EZTEST_STRUCT_INTT_PADDING_INIT_
# else
#  define EZTEST_STRUCT_INTT_PADDING_                                          \
      char unused_[sizeof(void *) - sizeof(unsigned)];
#  define EZTEST_STRUCT_INTT_PADDING_INIT_                                     \
      { 0 }
# endif
#else
# define EZTEST_STRUCT_INTT_PADDING_
# define EZTEST_STRUCT_INTT_PADDING_INIT_
#endif

/* End include of: eztest-struct-padding.h  */
/* Begin include of: eztest-test.h  */

/* Begin include of: eztest-status.h  */


/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#if EZTEST_CXX_LANG_
# include <climits> /* CHAR_BIT.  */
#else
# include <limits.h> /* CHAR_BIT.  */
#endif
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

EZTEST_NAMESPACE_BEGIN_

typedef unsigned eztest_status_t;


enum {
    eztest_k_status_init,
    eztest_k_status_counted,
    eztest_k_status_running,
    eztest_k_status_passed,
    eztest_k_status_disabled,
    eztest_k_status_internal_error,
    eztest_k_status_internal_fatal_error,
    eztest_k_status_fail,
    eztest_k_status_fail_sig,
    eztest_k_status_fail_unknown,
    eztest_k_status_fail_timeout,
    eztest_k_status_unknown,
    eztest_k_status_end
};
#define EZTEST_STATUS_T_ EZTEST_NS_ eztest_status_t


EZTEST_PRIVATE_ EZTEST_STATUS_T_
eztest_status_to_mask(EZTEST_STATUS_T_ eztest_status) {

    return 1U << (eztest_status & (CHAR_BIT * sizeof(EZTEST_STATUS_T_) - 1));
}


EZTEST_PRIVATE_ EZTEST_STATUS_T_
eztest_status_fail_mask(EZTEST_VOID_ARG_) {

    return EZTEST_NS_ eztest_status_to_mask(EZTEST_NS_ eztest_k_status_fail) |
           EZTEST_NS_ eztest_status_to_mask(
               EZTEST_NS_ eztest_k_status_fail_sig) |
           EZTEST_NS_ eztest_status_to_mask(
               EZTEST_NS_ eztest_k_status_fail_unknown) |
           EZTEST_NS_ eztest_status_to_mask(
               EZTEST_NS_ eztest_k_status_fail_timeout);
}


EZTEST_PRIVATE_ int
eztest_status_is_failure(EZTEST_STATUS_T_ eztest_status) {

    return EZTEST_CAST_(int, (EZTEST_NS_ eztest_status_to_mask(eztest_status) &
                              EZTEST_NS_ eztest_status_fail_mask()) != 0);
}


EZTEST_PRIVATE_ int
eztest_status_is_init(EZTEST_STATUS_T_ eztest_status) {

    return EZTEST_CAST_(int, eztest_status == EZTEST_NS_ eztest_k_status_init);
}


EZTEST_PRIVATE_ const char *
eztest_status_failure_str(EZTEST_STATUS_T_ eztest_status) {

    switch (eztest_status) {
        case EZTEST_NS_ eztest_k_status_fail:
            return "(Assert Failure)";
        case EZTEST_NS_ eztest_k_status_fail_sig:
            return "(Signal)";
        case EZTEST_NS_ eztest_k_status_fail_unknown:
            return "(Unknown)";
        case EZTEST_NS_ eztest_k_status_fail_timeout:
            return "(Timeout)";
        default:
            return "(BAD)";
    }
}


EZTEST_NAMESPACE_END_

/* End include of: eztest-status.h  */
EZTEST_NAMESPACE_BEGIN_


typedef void (*eztest_test_func)(EZTEST_VOID_ARG_);


/* Struct with info setup by the EZTEST*(...) macro.  */
/* NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) */
struct eztest_test_t {
    /* Next test.  */
    EZTEST_STRUCT_ eztest_test_t * eztest_next_;
    /* Function to test.  */
    EZTEST_NS_ eztest_test_func eztest_func_;
    /* Group this test is a part of.  */
    const char * const eztest_group_;
    /* Name of this test.  */
    const char * const eztest_name_;
    /* Line number this test is defined at (determines order).  */
    const unsigned eztest_lineno_;
    /* Test timeout.  */
    const int eztest_timeout_ms_;
    /* Status of this test (mutable).  */
    EZTEST_STATUS_T_ eztest_status_;
    /* Padding.  */
    EZTEST_STRUCT_INTT_PADDING_
};
#define EZTEST_TEST_T_ EZTEST_STRUCT_NS_ eztest_test_t
/* NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) */


EZTEST_PRIVATE_ int
eztest_test_failed(const EZTEST_TEST_T_ * eztest_test) {

    return EZTEST_NS_ eztest_status_is_failure(eztest_test->eztest_status_);
}


EZTEST_PRIVATE_ int
eztest_test_is_init(const EZTEST_TEST_T_ * eztest_test) {

    return EZTEST_NS_ eztest_status_is_init(eztest_test->eztest_status_);
}


EZTEST_PRIVATE_ const char *
eztest_test_failure_str(const EZTEST_TEST_T_ * eztest_test) {

    return EZTEST_NS_ eztest_status_failure_str(eztest_test->eztest_status_);
}


EZTEST_NAMESPACE_END_

/* End include of: eztest-test.h  */

EZTEST_NAMESPACE_BEGIN_

struct eztest_list_t {
    EZTEST_TEST_T_ * eztest_tests_begin_;
    unsigned         eztest_ntests_;
    EZTEST_STRUCT_INTT_PADDING_
};
#define EZTEST_LIST_T_ EZTEST_STRUCT_NS_ eztest_list_t
#define EZTEST_LIST_T_INIT_                                                    \
    { EZTEST_NULL_, 0, EZTEST_STRUCT_INTT_PADDING_INIT_ }


/*
 * TODO: Just sort this before running tests with merge sort. This is O(n^2)
 * insert in sorted order.
 */


EZTEST_DISABLE_WUNUSED_FUNCTION_
EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_
EZTEST_PRIVATE_ int
eztest_list_insert_test(EZTEST_LIST_T_ * eztest_list,
                        EZTEST_TEST_T_ * eztest_newest_test) {

    EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_
    EZTEST_TEST_T_ * eztest_cur         = EZTEST_NULL_;
    EZTEST_TEST_T_ * eztest_prev        = EZTEST_NULL_;
    unsigned         eztest_ntests      = eztest_list->eztest_ntests_;
    const char *     eztest_new_group   = eztest_newest_test->eztest_group_;
    int              eztest_found_group = 0;

    eztest_list->eztest_ntests_ = eztest_ntests + 1U;
    eztest_prev                 = EZTEST_NULL_;
    for (eztest_cur = eztest_list->eztest_tests_begin_; eztest_ntests != 0;
         --eztest_ntests, eztest_cur = eztest_cur->eztest_next_) {
        if (EZTEST_CAST_(int, EZTEST_STRCMP_(eztest_cur->eztest_group_,
                                             eztest_new_group) != 0) ==
            eztest_found_group) {
            if (eztest_found_group == 0) {
                eztest_found_group = 1;
            }
            else {
                break;
            }
        }
        eztest_prev = eztest_cur;
    }
    if (eztest_prev == EZTEST_NULL_) {
        eztest_list->eztest_tests_begin_ = eztest_newest_test;
    }
    else {
        eztest_prev->eztest_next_ = eztest_newest_test;
    }
    eztest_newest_test->eztest_next_ = eztest_cur;
    return 0;
}
EZTEST_REENABLE_WUNUSED_FUNCTION_

EZTEST_PRIVATE_ EZTEST_LIST_T_ *
eztest_list_get_head(EZTEST_VOID_ARG_) {
    static EZTEST_LIST_T_ eztest_S_tests_base = EZTEST_LIST_T_INIT_;
    return &eztest_S_tests_base;
}


EZTEST_NAMESPACE_END_

/* End include of: eztest-list.h  */
/* Begin include of: eztest-main.h  */

/* Begin include of: eztest-reqs.h  */

/* Begin include of: eztest-arch.h  */

#if defined(__AMDGPU__)
# define EZTEST_ARCH_IS_AMDGPU_ 1
#else
# define EZTEST_ARCH_IS_AMDGPU_ 0
#endif

#if defined(__NVPTX__)
# define EZTEST_ARCH_IS_NVPTX_ 1
#else
# define EZTEST_ARCH_IS_NVPTX_ 0
#endif

#if EZTEST_ARCH_IS_NVPTX_ || EZTEST_ARCH_IS_AMDGPU_
# define EZTEST_ARCH_IS_GPU_ 1
#else
# define EZTEST_ARCH_IS_GPU_ 0
#endif

#if defined(__pnacl__) || defined(__CLR_VER) || EZTEST_ARCH_IS_GPU_
# define EZTEST_ARCH_IS_VM_ 1
#else
# define EZTEST_ARCH_IS_VM_ 0
#endif

#if (defined(_M_IX86) || defined(__i386__)) && !EZTEST_ARCH_IS_VM_
# define EZTEST_ARCH_IS_X86_32_ 1
#else
# define EZTEST_ARCH_IS_X86_32_ 0
#endif

#if (defined(_M_X64) || defined(__x86_64__)) && !EZTEST_ARCH_IS_VM_
# define EZTEST_ARCH_IS_X86_64_ 1
#else
# define EZTEST_ARCH_IS_X86_64_ 0
#endif

#if EZTEST_ARCH_IS_X86_32_ || EZTEST_ARCH_IS_X86_64_
# define EZTEST_ARCH_IS_ANY_X86_ 1
#else
# define EZTEST_ARCH_IS_ANY_X86_ 0
#endif

#if (defined(__arm__) || defined(_M_ARM))
# define EZTEST_ARCH_IS_ARM32_ 1
#else
# define EZTEST_ARCH_IS_ARM32_ 0
#endif

#if defined(__aarch64__) || defined(__arm64__) || defined(_M_ARM64)
# define EZTEST_ARCH_IS_AARCH64_ 1
#else
# define EZTEST_ARCH_IS_AARCH64_ 0
#endif

#if EZTEST_ARCH_IS_AARCH64_ || EZTEST_ARCH_IS_ARM32_
# define EZTEST_ARCH_IS_ANY_ARM_ 1
#else
# define EZTEST_ARCH_IS_ANY_ARM_ 0
#endif

#if defined(__riscv) && (__riscv_xlen == 64)
# define EZTEST_ARCH_IS_RISCV64_ 1
#else
# define EZTEST_ARCH_IS_RISCV64_ 0
#endif

#if defined(__riscv) && (__riscv_xlen == 32)
# define EZTEST_ARCH_IS_RISCV32_ 1
#else
# define EZTEST_ARCH_IS_RISCV32_ 0
#endif

#if EZTEST_ARCH_IS_RISCV64_ || EZTEST_ARCH_IS_RISCV32_
# define EZTEST_ARCH_IS_ANY_RISCV_ 1
#else
# define EZTEST_ARCH_IS_ANY_RISCV_ 0
#endif

#if EZTEST_ARCH_IS_RISCV32_ || EZTEST_ARCH_IS_ARM32_ || EZTEST_ARCH_IS_X86_32_
# define EZTEST_WORD_SIZE_ 32
#else
# define EZTEST_WORD_SIZE_ 64
#endif

/* End include of: eztest-arch.h  */
/* Begin include of: eztest-system.h  */

#ifdef __linux__
# define EZTEST_OS_LINUX_ 1
#else
# define EZTEST_OS_LINUX_ 0
#endif


/* End include of: eztest-system.h  */

#if !(EZTEST_USING_CLANG_) && !(EZTEST_USING_GCC_)
# error "GCC or Clang required!"
#endif


#if EZTEST_C_LANG_
# if !(EZTEST_HAS_ATTRIBUTE_(constructor))
#  error "__attribute__((constructor)) required for C mode!"
# endif
#endif


#if EZTEST_CXX_LANG_ && EZTEST_CXX_LANG_ < 2011
# error "Requires CXX11"
#endif

#if EZTEST_C_LANG_ && EZTEST_C_LANG_ < 1999
# error "Requires C99"
#endif

#if EZTEST_OS_LINUX_ == 0
# error "Linux required!"
#endif

/* End include of: eztest-reqs.h  */
/* Begin include of: eztest-results.h  */

/* Begin include of: eztest-duration.h  */

/* Begin include of: eztest-time.h  */


#define EZTEST_CXX_HAS_TS_                                                     \
    (EZTEST_CXX_LANG_ >= 2020 ||                                               \
     (EZTEST_CXX_LANG_ >= 2017 &&                                              \
      EZTEST_USING_GCC_ >= EZTEST_VERNUM_(9, 0, 0)))

#if EZTEST_CXX_HAS_TS_ || (EZTEST_C_LANG_ >= 2011) ||                          \
    (EZTEST_POSIX_VERSION_ >= 199309L)

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
# if EZTEST_CXX_LANG_
#  include <ctime>
# else
#  include <time.h>
# endif
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

# define EZTEST_TIME_IS_TIMESPEC_ 1

# if EZTEST_CXX_HAS_TS_
#  define EZTEST_TIME_T_ EZTEST_STD_NS_ timespec
# else
#  define EZTEST_TIME_T_ EZTEST_STRUCT_ timespec
# endif

#elif EZTEST_OS_LINUX_
# define EZTEST_TIME_IS_TIMESPEC_ 0

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
# include <sys/time.h>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */
# define EZTEST_TIME_T_ EZTEST_STRUCT_ timeval

#endif

#define EZTEST_TIME_T_INIT_                                                    \
    { 0, 0 }

#define EZTEST_TIME_GET_(tsp)   EZTEST_NS_ eztest_time_get(tsp)
#define EZTEST_TIME_AS_MS_(tsp) EZTEST_NS_ eztest_time_timespec_to_ms(tsp)


EZTEST_NAMESPACE_BEGIN_

#if EZTEST_CXX_HAS_TS_ || EZTEST_C_LANG_ >= 2011
EZTEST_PRIVATE_ int
eztest_time_get(EZTEST_TIME_T_ * eztest_tsp) {
    return EZTEST_CAST_(
        int, EZTEST_STD_NS_ timespec_get(eztest_tsp, TIME_UTC) != TIME_UTC);
}
#elif EZTEST_POSIX_VERSION_ >= 199309L
EZTEST_PRIVATE_ int
eztest_time_get(EZTEST_TIME_T_ * eztest_tsp) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    return clock_gettime(CLOCK_MONOTONIC, eztest_tsp);
    /* NOLINTEND(llvmlibc-callee-namespace) */
}
#elif EZTEST_OS_LINUX_
EZTEST_PRIVATE_ int
eztest_time_get(EZTEST_TIME_T_ * eztest_tsp) {
    return EZTEST_CAST_(int, gettimeofday(eztest_tsp, EZTEST_NULL_));
}
#endif

#define EZTEST_MSEC_TO_SEC_L_ EZTEST_CAST_(int64_t, 1000)
#define EZTEST_USEC_TO_SEC_L_ (EZTEST_MSEC_TO_SEC_L_ * EZTEST_MSEC_TO_SEC_L_)
EZTEST_PRIVATE_
int64_t
eztest_time_timespec_to_ms(const EZTEST_TIME_T_ * eztest_ts) {
#if EZTEST_TIME_IS_TIMESPEC_
    return EZTEST_CAST_(int64_t, eztest_ts->tv_sec) * EZTEST_MSEC_TO_SEC_L_ +
           EZTEST_CAST_(int64_t, eztest_ts->tv_nsec) / (EZTEST_USEC_TO_SEC_L_);
#else
    return EZTEST_CAST_(int64_t, eztest_ts->tv_sec) * EZTEST_MSEC_TO_SEC_L_ +
           EZTEST_CAST_(int64_t, eztest_ts->tv_usec) / (EZTEST_MSEC_TO_SEC_L_);
#endif
}
EZTEST_NAMESPACE_END_

/* End include of: eztest-time.h  */

EZTEST_NAMESPACE_BEGIN_
/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
struct eztest_duration_t {
    EZTEST_TIME_T_ eztest_duration_start_;
    EZTEST_TIME_T_ eztest_duration_end_;

    long eztest_duration_failure_;
};
/* NOLINTEND(llvmlibc-inline-function-decl) */
#define EZTEST_DURATION_T_INIT_                                                \
    { EZTEST_TIME_T_INIT_, EZTEST_TIME_T_INIT_, -1L }
#define EZTEST_DURATION_T_ EZTEST_STRUCT_NS_ eztest_duration_t


EZTEST_PRIVATE_ int64_t
eztest_duration_timer_to_ms(const EZTEST_TIME_T_ * eztest_ts) {
    return EZTEST_TIME_AS_MS_(eztest_ts);
}

EZTEST_PRIVATE_ long
eztest_duration_timer_gettime(EZTEST_TIME_T_ * eztest_ts) {
    return EZTEST_CAST_(long, EZTEST_TIME_GET_(eztest_ts));
}


EZTEST_PRIVATE_ void
eztest_duration_start(EZTEST_DURATION_T_ * eztest_duration) {
    eztest_duration->eztest_duration_failure_ =
        EZTEST_NS_ eztest_duration_timer_gettime(
            &(eztest_duration->eztest_duration_start_));
}
EZTEST_PRIVATE_ void
eztest_duration_end(EZTEST_DURATION_T_ * eztest_duration) {
    unsigned long eztest_duration_result =
        EZTEST_CAST_(unsigned long, eztest_duration->eztest_duration_failure_);
    eztest_duration_result |= EZTEST_CAST_(
        unsigned long, EZTEST_NS_ eztest_duration_timer_gettime(
                           &(eztest_duration->eztest_duration_end_)));

    eztest_duration->eztest_duration_failure_ =
        EZTEST_CAST_(long, eztest_duration_result);
}


EZTEST_PRIVATE_ long
eztest_duration_ms(const EZTEST_DURATION_T_ * eztest_duration) {
    int64_t eztest_duration_complete = 0;
    if (eztest_duration->eztest_duration_failure_ != 0) {
        return -1L;
    }


    eztest_duration_complete = EZTEST_NS_ eztest_duration_timer_to_ms(
                                   &(eztest_duration->eztest_duration_end_)) -
                               EZTEST_NS_ eztest_duration_timer_to_ms(
                                   &(eztest_duration->eztest_duration_start_));

    EZTEST_DISABLE_WUSELESS_CAST_
    return EZTEST_CAST_(long, eztest_duration_complete);
    EZTEST_REENABLE_WUSELESS_CAST_
}


EZTEST_NAMESPACE_END_


/* End include of: eztest-duration.h  */
EZTEST_NAMESPACE_BEGIN_

EZTEST_DISABLE_WPADDED_
struct eztest_results_t {
    EZTEST_DURATION_T_ eztest_suite_duration_;
    EZTEST_ARR_BUILDER_(eztest_stats_,
                        unsigned,
                        EZTEST_NS_ eztest_k_status_end);
    unsigned eztest_num_groups_;
};
EZTEST_REENABLE_WPADDED_
#define EZTEST_RESULTS_T_ EZTEST_STRUCT_NS_ eztest_results_t
#define EZTEST_RESULTS_T_INIT_                                                 \
    { EZTEST_DURATION_T_INIT_, EZTEST_ARR_T_INIT_, 0 }


EZTEST_PRIVATE_ unsigned
eztest_results_count_failed(const EZTEST_RESULTS_T_ * eztest_results) {

    unsigned eztest_cnt = 0;
    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
    eztest_cnt +=
        eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_fail];
    eztest_cnt +=
        eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_fail_sig];
    eztest_cnt +=
        eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_fail_unknown];
    eztest_cnt +=
        eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_fail_timeout];
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    return eztest_cnt;
}


EZTEST_PRIVATE_ unsigned
eztest_results_count_passed(const EZTEST_RESULTS_T_ * eztest_results) {

    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
    return eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_passed];
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
}


EZTEST_PRIVATE_ unsigned
eztest_results_count_disabled(const EZTEST_RESULTS_T_ * eztest_results) {

    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
    return eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_disabled];
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
}


EZTEST_PRIVATE_ unsigned
eztest_results_count_unknown(const EZTEST_RESULTS_T_ * eztest_results) {

    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
    return eztest_results->eztest_stats_[EZTEST_NS_ eztest_k_status_unknown];
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
}


EZTEST_PRIVATE_ unsigned
eztest_results_count_internal_errors(const EZTEST_RESULTS_T_ * eztest_results) {

    unsigned eztest_cnt = 0;
    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
    eztest_cnt +=
        eztest_results
            ->eztest_stats_[EZTEST_NS_ eztest_k_status_internal_error];
    eztest_cnt +=
        eztest_results
            ->eztest_stats_[EZTEST_NS_ eztest_k_status_internal_fatal_error];
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    return eztest_cnt;
}

EZTEST_NAMESPACE_END_
/* End include of: eztest-results.h  */
/* Begin include of: eztest-run.h  */

/* Begin include of: eztest-group-it.h  */


EZTEST_NAMESPACE_BEGIN_
struct eztest_group_it_t {
    EZTEST_TEST_T_ * eztest_cur_test_;
};
#define EZTEST_GROUP_IT_T_INIT_                                                \
    { EZTEST_NULL_ }
#define EZTEST_GROUP_IT_T_ EZTEST_STRUCT_NS_ eztest_group_it_t


EZTEST_PRIVATE_ void
eztest_group_it_deinit(EZTEST_GROUP_IT_T_ * eztest_group_it) {
    (void)eztest_group_it;
}


EZTEST_PRIVATE_ void
eztest_group_it_init(EZTEST_GROUP_IT_T_ *   eztest_group_it,
                     const EZTEST_LIST_T_ * eztest_tests_base) {
    if (eztest_tests_base == EZTEST_NULL_) {
        eztest_group_it->eztest_cur_test_ = EZTEST_NULL_;
    }
    else {
        eztest_group_it->eztest_cur_test_ =
            eztest_tests_base->eztest_tests_begin_;
    }
}


EZTEST_PRIVATE_ EZTEST_TEST_T_ *
eztest_group_it_next(EZTEST_GROUP_IT_T_ * eztest_group_it,
                     int *                eztest_new_group_out) {

    EZTEST_TEST_T_ * eztest_cur_test  = EZTEST_NULL_;
    const char *     eztest_cur_group = EZTEST_NULL_;
    eztest_cur_test                   = eztest_group_it->eztest_cur_test_;
    if (eztest_cur_test == EZTEST_NULL_) {
        *eztest_new_group_out = 0;
        return EZTEST_NULL_;
    }

    eztest_cur_group = eztest_cur_test->eztest_group_;
    eztest_cur_test  = eztest_cur_test->eztest_next_;
    if (eztest_cur_test == EZTEST_NULL_) {
        *eztest_new_group_out = 0;
    }
    else {
        *eztest_new_group_out = EZTEST_CAST_(
            int, EZTEST_STRCMP_(eztest_cur_group,
                                eztest_cur_test->eztest_group_) != 0);
    }

    eztest_group_it->eztest_cur_test_ = eztest_cur_test;
    return eztest_cur_test;
}


EZTEST_PRIVATE_ EZTEST_TEST_T_ *
eztest_group_it_begin(EZTEST_GROUP_IT_T_ * eztest_group_it) {

    return eztest_group_it->eztest_cur_test_;
}

EZTEST_NAMESPACE_END_

/* End include of: eztest-group-it.h  */
/* Begin include of: eztest-proc.h  */

/* Begin include of: eztest-syscall.h  */


/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#include <sys/types.h> /* pid_t.  */
#include <unistd.h>    /* pid_t.  */
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

#if EZTEST_DEFAULT_SOURCE_
/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
# include <signal.h>
# include <sys/syscall.h>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

# define EZTEST_PIDFD_OPEN_(pid, flags)                                        \
     /* NOLINTBEGIN(llvmlibc-callee-namespace) */                              \
     /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg) */                      \
     /* NOLINTBEGIN(hicpp-vararg) */                                           \
                                                                               \
     syscall(EZTEST_CAST_(long, SYS_pidfd_open), pid, flags) \
        /* NOLINTEND(hicpp-vararg) */                       \
        /* NOLINTEND(cppcoreguidelines-pro-type-vararg) */  \
        /* NOLINTEND(llvmlibc-callee-namespace) */

# define EZTEST_KILL_(pid, sig)                                                \
     /* NOLINTBEGIN(llvmlibc-callee-namespace) */                              \
     kill(pid, sig) /* NOLINTEND(llvmlibc-callee-namespace) */

#else
/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
# include <asm/unistd.h>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

EZTEST_NAMESPACE_BEGIN_
# if EZTEST_ARCH_IS_X86_64_


/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ long
eztest_syscall2_impl(long eztest_syscall_no,
                     long eztest_arg0,
                     long eztest_arg1) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(hicpp-no-assembler,misc-const-correctness) */
    register long eztest_rax __asm__("rax") = eztest_syscall_no;
    register long eztest_rdi __asm__("rdi") = eztest_arg0;
    register long eztest_rsi __asm__("rsi") = eztest_arg1;
    __asm__ volatile("syscall"
                     : "+r"(eztest_rax)
                     : "r"(eztest_rdi), "r"(eztest_rsi)
                     : "rcx", "r11", "memory");
    /* NOLINTEND(hicpp-no-assembler,misc-const-correctness) */
    return eztest_rax;
}

# elif EZTEST_ARCH_IS_X86_32_

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ long
eztest_syscall2_impl(long eztest_syscall_no,
                     long eztest_arg0,
                     long eztest_arg1) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(hicpp-no-assembler,misc-const-correctness) */
    register long eztest_eax __asm__("eax") = eztest_syscall_no;
    register long eztest_ebx __asm__("ebx") = eztest_arg0;
    register long eztest_ecx __asm__("ecx") = eztest_arg1;
    __asm__ volatile("int $0x80"
                     : "+r"(eztest_eax)
                     : "r"(eztest_ebx), "r"(eztest_ecx)
                     : "memory");
    /* NOLINTEND(hicpp-no-assembler,misc-const-correctness) */
    return eztest_eax;
}


# elif EZTEST_ARCH_IS_AARCH64_

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */

EZTEST_PRIVATE_ long
eztest_syscall2_impl(long eztest_syscall_no,
                     long eztest_arg0,
                     long eztest_arg1) {

    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(hicpp-no-assembler,misc-const-correctness) */
    register long eztest_x8 __asm__("x8") = eztest_syscall_no;
    register long eztest_x0 __asm__("x0") = eztest_arg0;
    register long eztest_x1 __asm__("x1") = eztest_arg1;
    __asm__ volatile("svc 0"
                     : "+r"(eztest_x0)
                     : "r"(eztest_x8), "r"(eztest_x1)
                     : "memory", "cc");
    /* NOLINTEND(hicpp-no-assembler,misc-const-correctness) */
    return eztest_x0;
}


# elif EZTEST_ARCH_IS_ARM32_

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */

EZTEST_PRIVATE_ long
eztest_syscall2_impl(long eztest_syscall_no,
                     long eztest_arg0,
                     long eztest_arg1) {

    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(hicpp-no-assembler,misc-const-correctness) */
    register long eztest_r7 __asm__("r7") = eztest_syscall_no;
    register long eztest_r0 __asm__("r0") = eztest_arg0;
    register long eztest_r1 __asm__("r1") = eztest_arg1;
    __asm__ volatile("svc 0"
                     : "+r"(eztest_r0)
                     : "r"(eztest_r7), "r"(eztest_r1)
                     : "memory");
    /* NOLINTEND(hicpp-no-assembler,misc-const-correctness) */
    return eztest_r0;
}


# elif EZTEST_ARCH_IS_ANY_RISCV_

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */

EZTEST_PRIVATE_ long
eztest_syscall2_impl(long eztest_syscall_no,
                     long eztest_arg0,
                     long eztest_arg1) {

    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(hicpp-no-assembler,misc-const-correctness) */
    register long eztest_a7 __asm__("a7") = eztest_syscall_no;
    register long eztest_a0 __asm__("a0") = eztest_arg0;
    register long eztest_a1 __asm__("a1") = eztest_arg1;
    __asm__ volatile("ecall\n\t"
                     : "+r"(eztest_a0)
                     : "r"(eztest_a7), "r"(eztest_a1)
                     : "memory");
    /* NOLINTEND(hicpp-no-assembler,misc-const-correctness) */
    return eztest_a0;
}


# else
#  error "No syscall impl for arch!"
# endif

EZTEST_PRIVATE_ long
eztest_syscall2(long eztest_syscall_no, long eztest_arg0, long eztest_arg1) {
    static const unsigned long eztest_syscall_max_valid = -4096UL;
    long eztest_res = EZTEST_NS_ eztest_syscall2_impl(eztest_syscall_no,
                                                      eztest_arg0, eztest_arg1);
    if (EZTEST_CAST_(unsigned long, eztest_res) > eztest_syscall_max_valid) {
        EZTEST_ERRNO_ = EZTEST_CAST_(int, -eztest_res);
        return EZTEST_CAST_(long, -1);
    }
    return eztest_res;
}

# define EZTEST_PIDFD_OPEN_(pid, flags)                                        \
     EZTEST_NS_ eztest_syscall2(EZTEST_CAST_(long, __NR_pidfd_open),           \
                                EZTEST_CAST_(long, pid),                       \
                                EZTEST_CAST_(long, flags))

# define EZTEST_KILL_(pid, sig)                                                \
     EZTEST_NS_ eztest_syscall2(EZTEST_CAST_(long, __NR_kill),                 \
                                EZTEST_CAST_(long, pid),                       \
                                EZTEST_CAST_(long, sig))

EZTEST_NAMESPACE_END_
#endif
/* End include of: eztest-syscall.h  */

EZTEST_NAMESPACE_BEGIN_
typedef unsigned eztest_proc_status_t;
enum {
    eztest_k_proc_unknown,
    eztest_k_proc_returned,
    eztest_k_proc_signalled,
    eztest_k_proc_timed_out
};

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#include <poll.h>         /* pollfd, poll.  */
#include <sched.h>        /* sched_yield. */
#include <signal.h>       /* SIG*, kill.  */
#include <sys/prctl.h>    /* prctl.  */
#include <sys/signalfd.h> /* signalfd.  */
#include <sys/types.h>    /* pid_t. */
#include <sys/wait.h>     /* waitpid, pid_t.  */
#include <unistd.h>       /* fork.  */
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

#if EZTEST_XOPEN_VERSION_ >= 500 || EZTEST_POSIX_VERSION_ >= 199506L
/* Maybe use pthread_sigprocmask (afraid of -lpthread dependency) */
#endif
#define EZTEST_SIGPROCMASK_(todo, new_mask, old_mask)                          \
    /* NOLINTBEGIN(concurrency-mt-unsafe,llvmlibc-callee-namespace) */         \
    sigprocmask(todo, new_mask, old_mask)                                      \
                                                                               \
        /* NOLINTEND(concurrency-mt-unsafe,llvmlibc-callee-namespace) */


typedef int (*eztest_proc_func)(const EZTEST_TEST_T_ *);


struct eztest_proc_result_t {
    eztest_proc_status_t eztest_proc_status_;
    int                  eztest_proc_status_value_;
    EZTEST_DURATION_T_   eztest_proc_duration_;
};
#define EZTEST_PROC_RESULT_T_ EZTEST_STRUCT_NS_ eztest_proc_result_t
#define EZTEST_PROC_RESULT_T_INIT_                                             \
    { 0, 0, EZTEST_DURATION_T_INIT_ }


typedef int eztest_timed_wait_res_t;
enum {
    eztest_k_timed_wait_fallback = -2,
    eztest_k_timed_wait_err      = -1,
    eztest_k_timed_wait_returned = 0,
    eztest_k_timed_wait_timeout  = 1
};
#define EZTEST_TIMED_WAIT_RES_T_ EZTEST_NS_ eztest_timed_wait_res_t

EZTEST_DISABLE_WUSELESS_CAST_
static const pid_t eztest_k_pid_err   = EZTEST_CAST_(pid_t, -1);
static const pid_t eztest_k_pid_child = EZTEST_CAST_(pid_t, 0);
static const pid_t eztest_k_pid_none  = EZTEST_CAST_(pid_t, 0);
EZTEST_REENABLE_WUSELESS_CAST_

EZTEST_PRIVATE_ int
eztest_proc_waitpid(pid_t eztest_proc_pid,
                    int   eztest_blocking,
                    int * eztest_proc_ret_out) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    const pid_t eztest_reaped_pid =
        waitpid(eztest_proc_pid, eztest_proc_ret_out,
                eztest_blocking == 0 ? WNOHANG : 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    EZTEST_DISABLE_WUSELESS_CAST_
    if (eztest_reaped_pid == EZTEST_NS_ eztest_k_pid_err) {
        EZTEST_PERR_(
            "Fatal Internal Error -- "
            "Unable reap test process:\n\t");
        return -1;
    }
    if (eztest_blocking == 0 &&
        eztest_reaped_pid == EZTEST_NS_ eztest_k_pid_none) {
        /* Non blocking by not ready yet.  */
        return 1;
    }
    EZTEST_REENABLE_WUSELESS_CAST_
    if (eztest_reaped_pid != eztest_proc_pid) {
        (void)EZTEST_PRINTF_(
            "Fatal Internal Error -- "
            "Unable reaped unknown test process: %d\n",
            EZTEST_CAST_(int, eztest_reaped_pid));
        return -1;
    }

    return 0;
}

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ int
eztest_proc_wait_on_fd(int eztest_proc_fd, long eztest_proc_timeout_ms) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    EZTEST_STRUCT_ pollfd eztest_poll_fd = { eztest_proc_fd, POLLIN, 0 };
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    const int eztest_poll_res = poll(&eztest_poll_fd, EZTEST_CAST_(nfds_t, 1),
                                     EZTEST_CAST_(int, eztest_proc_timeout_ms));
    /* NOLINTEND(llvmlibc-callee-namespace) */
    if (eztest_poll_res == -1) {
        /* Internal error. */
        EZTEST_PERR_(
            "Internal Error -- "
            "Unable to poll fd for test timeout:\n\t");
        return -1;
    }
    if (eztest_poll_res == 0) {
        /* Timeout.  */
        return 1;
    }
    /* NOLINTNEXTLINE(hicpp-signed-bitwise) */
    if (eztest_poll_res != 1 || (eztest_poll_fd.revents & POLLIN) == 0) {
        (void)EZTEST_PRINTF_(
            "Internal Error -- "
            "Invalid poll result during test timeout:\n"
            "\tReturn Value: %d\n"
            "\tReturn Event: %hx\n",
            eztest_poll_res, eztest_poll_fd.revents);
        return EZTEST_NS_ eztest_k_timed_wait_err;
    }
    return 0;
}


/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ EZTEST_TIMED_WAIT_RES_T_
eztest_proc_timed_wait_loop(pid_t eztest_proc_pid,
                            long  eztest_proc_timeout_ms,
                            int * eztest_proc_ret_out) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    static const long  eztest_k_min_yield_time_ms = 50;
    EZTEST_DURATION_T_ eztest_total_waited        = EZTEST_DURATION_T_INIT_;
    EZTEST_NS_         eztest_duration_start(&eztest_total_waited);
    for (;;) {
        long      eztest_waited   = 0;
        const int eztest_wait_res = EZTEST_NS_ eztest_proc_waitpid(
            eztest_proc_pid, /* eztest_blocking */ 0, eztest_proc_ret_out);
        if (eztest_wait_res == -1) {
            return EZTEST_NS_ eztest_k_timed_wait_err;
        }
        if (eztest_wait_res == 0) {
            return EZTEST_NS_ eztest_k_timed_wait_returned;
        }

        EZTEST_NS_                 eztest_duration_end(&eztest_total_waited);
        eztest_waited = EZTEST_NS_ eztest_duration_ms(&eztest_total_waited);
        if (eztest_waited < 0L) {
            (void)EZTEST_PRINTF_(
                "Internal Error -- "
                "Failed to gettime during backup timed wait...\n"
                "No longer possible to timeout test. Killing.\n");
            return EZTEST_NS_ eztest_k_timed_wait_err;
        }
        if (eztest_waited >= eztest_proc_timeout_ms) {
            EZTEST_KILL_(eztest_proc_pid, SIGKILL);
            return EZTEST_NS_ eztest_k_timed_wait_timeout;
        }
        eztest_proc_timeout_ms -= eztest_waited;
        if (eztest_proc_timeout_ms >= eztest_k_min_yield_time_ms) {
            /* NOLINTBEGIN(llvmlibc-callee-namespace) */
            sched_yield();
            /* NOLINTEND(llvmlibc-callee-namespace) */
        }
    }
}


/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ EZTEST_TIMED_WAIT_RES_T_
eztest_proc_timed_wait_final_wait(pid_t eztest_proc_pid,
                                  int   eztest_wait_res,
                                  int * eztest_proc_ret_out) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    if (eztest_wait_res == 1) {
        EZTEST_KILL_(eztest_proc_pid, SIGKILL);
    }

    if (EZTEST_NS_ eztest_proc_waitpid(eztest_proc_pid,
                                       /* eztest_blocking */ 1,
                                       eztest_proc_ret_out) == -1) {
        return EZTEST_NS_ eztest_k_timed_wait_err;
    }
    if (eztest_wait_res == 0) {
        return EZTEST_NS_ eztest_k_timed_wait_returned;
    }
    if (eztest_wait_res == 1) {
        return EZTEST_NS_ eztest_k_timed_wait_timeout;
    }
    return EZTEST_NS_ eztest_k_timed_wait_err;
}

#if EZTEST_POSIX_VERSION_
/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ EZTEST_TIMED_WAIT_RES_T_
eztest_proc_timed_wait_sigfd(pid_t eztest_proc_pid,
                             long  eztest_proc_timeout_ms,
                             int * eztest_proc_ret_out) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    int        eztest_wait_res   = 0;
    int        eztest_proc_sigfd = 0;
    sigset_t   eztest_ss;
    sigset_t   eztest_prev_ss;
    static int eztest_S_sigfd_unsupported = 0;
    if (eztest_S_sigfd_unsupported != 0) {
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }
    /* Block SIGCHLD so we are ready to handle.  */
    /* NOLINTNEXTLINE(llvmlibc-callee-namespace) */
    if (sigemptyset(&eztest_ss) != 0 || sigaddset(&eztest_ss, SIGCHLD) != 0 ||
        EZTEST_SIGPROCMASK_(SIG_BLOCK, &eztest_ss, &eztest_prev_ss) != 0) {
        EZTEST_PWARN_V_(
            "Internal Error -- "
            "Unable to initialize signal mask for timeout:\n\t");
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }

    eztest_wait_res = EZTEST_NS_ eztest_proc_waitpid(
        eztest_proc_pid, /* eztest_blocking */ 0, eztest_proc_ret_out);
    if (eztest_wait_res == -1) {
        return EZTEST_NS_ eztest_k_timed_wait_err;
    }
    /* After blocking (to prepare to handle) child finished.  */
    if (eztest_wait_res == 0) {
        (void)EZTEST_SIGPROCMASK_(SIG_SETMASK, &eztest_prev_ss, EZTEST_NULL_);
        return EZTEST_NS_ eztest_k_timed_wait_returned;
    }

    /* Setup fd for SIGCHLD.  */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    eztest_proc_sigfd = signalfd(-1, &eztest_ss, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    if (eztest_proc_sigfd == -1) {
        (void)EZTEST_SIGPROCMASK_(SIG_SETMASK, &eztest_prev_ss, EZTEST_NULL_);
        if (EZTEST_ERRNO_ == ENOSYS) {
            eztest_S_sigfd_unsupported = 1;
        }
        EZTEST_PWARN_V_(
            "Internal Error -- "
            "Unable to initialize signal fd for timeout:\n\t");
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }

    eztest_wait_res = EZTEST_NS_ eztest_proc_wait_on_fd(eztest_proc_sigfd,
                                                        eztest_proc_timeout_ms);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    (void)close(eztest_proc_sigfd);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    (void)EZTEST_SIGPROCMASK_(SIG_SETMASK, &eztest_prev_ss, EZTEST_NULL_);

    if (eztest_wait_res == -1) {
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }

    return EZTEST_NS_ eztest_proc_timed_wait_final_wait(
        eztest_proc_pid, eztest_wait_res, eztest_proc_ret_out);
}
#endif

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ EZTEST_TIMED_WAIT_RES_T_
eztest_proc_timed_wait_pidfd(pid_t eztest_proc_pid,
                             long  eztest_proc_timeout_ms,
                             int * eztest_proc_ret_out) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    int        eztest_wait_res            = 0;
    int        eztest_proc_pidfd          = 0;
    static int eztest_S_pidfd_unsupported = 0;
    if (eztest_S_pidfd_unsupported != 0) {
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }

    eztest_proc_pidfd =
        EZTEST_CAST_(int, EZTEST_PIDFD_OPEN_(eztest_proc_pid, 0U));
    if (eztest_proc_pidfd == -1) {
        if (EZTEST_ERRNO_ == ENOSYS) {
            eztest_S_pidfd_unsupported = 1;
        }
        EZTEST_PWARN_V_(
            "Internal Error -- "
            "Unable to initialize pid fd for timeout:\n\t");
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }
    eztest_wait_res = EZTEST_NS_ eztest_proc_wait_on_fd(eztest_proc_pidfd,
                                                        eztest_proc_timeout_ms);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    (void)close(eztest_proc_pidfd);
    /* NOLINTEND(llvmlibc-callee-namespace) */

    if (eztest_wait_res == -1) {
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }

    return EZTEST_NS_ eztest_proc_timed_wait_final_wait(
        eztest_proc_pid, eztest_wait_res, eztest_proc_ret_out);
}

EZTEST_PRIVATE_ EZTEST_TIMED_WAIT_RES_T_
eztest_proc_timed_wait(pid_t eztest_proc_pid,
                       long  eztest_proc_timeout_ms,
                       int * eztest_proc_ret_out) {
    EZTEST_TIMED_WAIT_RES_T_ eztest_wait_res =
        EZTEST_NS_           eztest_proc_timed_wait_pidfd(
            eztest_proc_pid, eztest_proc_timeout_ms, eztest_proc_ret_out);
    if (eztest_wait_res != EZTEST_NS_ eztest_k_timed_wait_fallback) {
        return eztest_wait_res;
    }
#if EZTEST_POSIX_VERSION_
    eztest_wait_res = EZTEST_NS_ eztest_proc_timed_wait_sigfd(
        eztest_proc_pid, eztest_proc_timeout_ms, eztest_proc_ret_out);
    if (eztest_wait_res != EZTEST_NS_ eztest_k_timed_wait_fallback) {
        return eztest_wait_res;
    }
#endif
    return EZTEST_NS_ eztest_proc_timed_wait_loop(
        eztest_proc_pid, eztest_proc_timeout_ms, eztest_proc_ret_out);
}

EZTEST_PRIVATE_ int
eztest_proc_wait(pid_t eztest_proc_pid,
                 long  eztest_proc_timeout_ms,
                 int * eztest_proc_ret_out) {
    if (eztest_proc_timeout_ms > 0L) {
        const EZTEST_TIMED_WAIT_RES_T_ eztest_k_timed_wait_res =
            EZTEST_NS_                 eztest_proc_timed_wait(
                eztest_proc_pid, eztest_proc_timeout_ms, eztest_proc_ret_out);
        switch (eztest_k_timed_wait_res) {
            case EZTEST_NS_ eztest_k_timed_wait_returned:
                return 0;
            case EZTEST_NS_ eztest_k_timed_wait_timeout:
                return 1;
            default:
                /* Cleanup the test process.  */
                EZTEST_KILL_(eztest_proc_pid, SIGKILL);
                (void)EZTEST_NS_ eztest_proc_waitpid(eztest_proc_pid,
                                                     /* eztest_blocking */ 1,
                                                     eztest_proc_ret_out);
                return -1;
        }
    }

    return EZTEST_NS_ eztest_proc_waitpid(eztest_proc_pid,
                                          /* eztest_blocking */ 1,
                                          eztest_proc_ret_out);
}

EZTEST_PRIVATE_ long
eztest_proc_duration_ms(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return EZTEST_NS_ eztest_duration_ms(
        &(eztest_proc_result->eztest_proc_duration_));
}

EZTEST_PRIVATE_ int
eztest_proc_signal_num(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return WTERMSIG(eztest_proc_result->eztest_proc_status_value_);
}

EZTEST_PRIVATE_ const char *
eztest_proc_signal_str(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    switch (EZTEST_NS_ eztest_proc_signal_num(eztest_proc_result)) {
        case SIGABRT:
            return "Aborted";
        case SIGALRM:
            return "Alarm clock";
        case SIGBUS:
            return "Bus error";
        case SIGCHLD:
            return "Child exited";
        case SIGCONT:
            return "Continued";
        case SIGFPE:
            return "Floating point exception";
        case SIGHUP:
            return "Hangup";
        case SIGILL:
            return "Illegal instruction";
        case SIGINT:
            return "Interrupt";
        case SIGKILL:
            return "Killed";
        case SIGPIPE:
            return "Broken pipe";
        case SIGPOLL:
            return "I/O possible";
        case SIGPROF:
            return "Profiling timer expired";
        case SIGQUIT:
            return "Quit";
        case SIGSEGV:
            return "Segmentation fault";
        case SIGSTOP:
            return "Stopped (signal)";
        case SIGSYS:
            return "Bad system call";
        case SIGTERM:
            return "Terminated";
        case SIGTRAP:
            return "Trace/breakpoint trap";
        case SIGTSTP:
            return "Stopped";
        case SIGTTIN:
            return "Stopped (tty input)";
        case SIGTTOU:
            return "Stopped (tty output)";
        case SIGURG:
            return "Urgent I/O condition";
        case SIGUSR1:
            return "User defined signal 1";
        case SIGUSR2:
            return "User defined signal 2";
        case SIGXCPU:
            return "CPU time limit exceeded";
        case SIGXFSZ:
            return "File size limit exceeded";
        default:
            return "Unknown signal";
    }
}

EZTEST_PRIVATE_ int
eztest_proc_returned(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return EZTEST_CAST_(int, eztest_proc_result->eztest_proc_status_ ==
                                 EZTEST_NS_ eztest_k_proc_returned);
}

EZTEST_PRIVATE_ int
eztest_proc_return_value(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return WEXITSTATUS(eztest_proc_result->eztest_proc_status_value_);
}

EZTEST_PRIVATE_ int
eztest_proc_signalled(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return EZTEST_CAST_(int, eztest_proc_result->eztest_proc_status_ ==
                                 EZTEST_NS_ eztest_k_proc_signalled);
}


EZTEST_PRIVATE_ int
eztest_proc_timed_out(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return EZTEST_CAST_(int, eztest_proc_result->eztest_proc_status_ ==
                                 EZTEST_NS_ eztest_k_proc_timed_out);
}

EZTEST_PRIVATE_ int
eztest_proc_unknown_result(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return EZTEST_CAST_(int, eztest_proc_result->eztest_proc_status_ ==
                                 EZTEST_NS_ eztest_k_proc_unknown);
}


EZTEST_PRIVATE_ int
eztest_proc_ret_internal_error(EZTEST_PROC_RESULT_T_ * eztest_proc_res_out) {
    EZTEST_NS_ eztest_duration_end(
        &(eztest_proc_res_out->eztest_proc_duration_));
    return -1;
}

EZTEST_PRIVATE_ pid_t
eztest_testsuite_pid(EZTEST_VOID_ARG_) {
    static pid_t eztest_S_testsuite_pid = EZTEST_NS_ eztest_k_pid_none;
    if (eztest_S_testsuite_pid == EZTEST_NS_ eztest_k_pid_none) {
        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        eztest_S_testsuite_pid = getpid();
        /* NOLINTEND(llvmlibc-callee-namespace) */
    }
    return eztest_S_testsuite_pid;
}

EZTEST_PRIVATE_
int
eztest_proc_run(EZTEST_NS_ eztest_proc_func eztest_to_dispatch,
                const EZTEST_TEST_T_ *      eztest_test,
                long                        eztest_proc_timeout_ms,
                EZTEST_PROC_RESULT_T_ *     eztest_proc_res_out) {
    unsigned eztest_fork_att_cnt  = 0;
    int      eztest_proc_ret      = 0;
    int      eztest_wait_result   = 0;
    pid_t eztest_proc_pid         = EZTEST_NS_ eztest_k_pid_none;
    const pid_t eztest_parent_pid = EZTEST_NS_ eztest_testsuite_pid();
    for (;;) {
        static const unsigned eztest_k_max_fork_att = 3;

        EZTEST_NS_ eztest_duration_start(
            &(eztest_proc_res_out->eztest_proc_duration_));
        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        eztest_proc_pid = fork();
        /* NOLINTEND(llvmlibc-callee-namespace) */
        if (eztest_proc_pid == EZTEST_NS_ eztest_k_pid_err) {
            if (eztest_fork_att_cnt < eztest_k_max_fork_att &&
                EZTEST_ERRNO_ == EAGAIN) {
                ++eztest_fork_att_cnt;
                continue;
            }
            EZTEST_PERR_(
                "Internal Error -- "
                "Unable to fork test:\n\t");
            return EZTEST_NS_ eztest_proc_ret_internal_error(
                eztest_proc_res_out);
        }
        break;
    }

    if (eztest_proc_pid == EZTEST_NS_ eztest_k_pid_child) {
        /* If parent dies, don't leave test running.  */
        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
        int eztest_result = prctl(PR_SET_PDEATHSIG, SIGKILL);
        /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
        /* NOLINTEND(llvmlibc-callee-namespace) */
        if (eztest_result != 0) {
            EZTEST_PWARN_V_(
                "Internal Error -- "
                "Unable to ensure test process will die with testsuite:\n\t");
        }

        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        eztest_result = EZTEST_CAST_(int, getppid() != eztest_parent_pid);
        /* NOLINTEND(llvmlibc-callee-namespace) */
        /* Parent died before call to prctl.  */
        if (eztest_result != 0) {
            EZTEST_EXIT_(1);
        }
        eztest_result = eztest_to_dispatch(eztest_test);
        (void)EZTEST_FFLUSH_(stdout);
        (void)EZTEST_FFLUSH_(stderr);
        EZTEST_EXIT_(eztest_result);
    }

    eztest_wait_result = EZTEST_NS_ eztest_proc_wait(
        eztest_proc_pid, eztest_proc_timeout_ms, &eztest_proc_ret);
    if (eztest_wait_result == -1) {
        return EZTEST_NS_ eztest_proc_ret_internal_error(eztest_proc_res_out);
    }
    EZTEST_NS_ eztest_duration_end(
        &(eztest_proc_res_out->eztest_proc_duration_));

    eztest_proc_res_out->eztest_proc_status_value_ = eztest_proc_ret;
    if (eztest_wait_result > 0) {
        eztest_proc_res_out->eztest_proc_status_ =
            EZTEST_NS_ eztest_k_proc_timed_out;
    }
    else if (WIFEXITED(eztest_proc_ret)) {
        eztest_proc_res_out->eztest_proc_status_ =
            EZTEST_NS_ eztest_k_proc_returned;
    }
    else if (WIFSIGNALED(eztest_proc_ret)) {
        eztest_proc_res_out->eztest_proc_status_ =
            EZTEST_NS_ eztest_k_proc_signalled;
    }
    else {
        eztest_proc_res_out->eztest_proc_status_ =
            EZTEST_NS_ eztest_k_proc_unknown;
    }

    return 0;
}


EZTEST_NAMESPACE_END_

/* End include of: eztest-proc.h  */


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
        if (eztest_run_result > EZTEST_NS_ eztest_k_status_unknown) {
            eztest_run_result = EZTEST_NS_ eztest_k_status_unknown;
        }
        eztest_test->eztest_status_ = eztest_run_result;
        EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
        /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index) */
        ++eztest_results->eztest_stats_[eztest_run_result];
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

/* End include of: eztest-run.h  */

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


/* End include of: eztest-main.h  */
/* Begin include of: eztest-test-setup.h  */


#define EZTEST_INTERNAL_NAME_(group, name, lineno)                             \
    EZTEST_SNAKE_CAT_(EZTEST_SNAKE_CAT_(eztest, group),                        \
                      EZTEST_SNAKE_CAT_(name, lineno))


#if EZTEST_CXX_LANG_
# define EZTEST_CREATE_LINK_IN_TEST_(base_name, struct_name, sink_name)        \
     static const int sink_name =                                              \
         EZTEST_NS_   eztest_list_insert_test(base_name, &(struct_name));

#else
# define EZTEST_CREATE_LINK_IN_TEST_(base_name, struct_name, sink_name)        \
     static void EZTEST_ATTR_CONSTRUCTOR_ sink_name(void) {                    \
         EZTEST_NS_ eztest_list_insert_test(base_name, &(struct_name));        \
     }
#endif

#define EZTEST_CREATE_SETUP_TEST_IMPL_(base_name, func_name, struct_name,      \
                                       sink_name, group, name, msecs, lineno)  \
    /* NOLINTBEGIN(llvmlibc-implementation-in-namespace) */                    \
    /* NOLINTBEGIN(misc-use-anonymous-namespace) */                            \
    static void func_name(void);                                               \
    EZTEST_NAMESPACE_BEGIN_                                                    \
    EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_                                    \
    EZTEST_DISABLE_WUSELESS_CAST_                                              \
    /* NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables) */      \
    static EZTEST_TEST_T_ struct_name = {                                      \
        EZTEST_NULL_, /* NOLINTBEGIN(llvmlibc-callee-namespace) */             \
        func_name,    /* NOLINTEND(llvmlibc-callee-namespace) */               \
        EZTEST_STRINGIFY_(group),                                              \
        EZTEST_STRINGIFY_(name),                                               \
        EZTEST_CAST_(unsigned, lineno),                                        \
        EZTEST_CAST_(int, msecs),                                              \
        EZTEST_CAST_(unsigned, EZTEST_NS_ eztest_k_status_init),               \
        EZTEST_STRUCT_INTT_PADDING_INIT_                                       \
    };                                                                         \
    /* NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables) */        \
    EZTEST_REENABLE_WUSELESS_CAST_                                             \
    EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_                                    \
    EZTEST_CREATE_LINK_IN_TEST_(base_name, EZTEST_NS_ struct_name, sink_name)  \
    EZTEST_NAMESPACE_END_                                                      \
    static void func_name(void) /* NOLINTEND(misc-use-anonymous-namespace) */  \
                                                                               \
        /* NOLINTEND(llvmlibc-implementation-in-namespace) */

#define EZTEST_CREATE_SETUP_TEST_(base_name, internal_name, group, name,       \
                                  msecs, lineno)                               \
    EZTEST_CREATE_SETUP_TEST_IMPL_(                                            \
        base_name, EZTEST_CAT_(internal_name, func),                           \
        EZTEST_CAT_(internal_name, struct), EZTEST_CAT_(internal_name, sink),  \
        group, name, msecs, lineno)

#define EZTEST_CREATE_TEST_(base_name, group, name, msecs, lineno)             \
    EZTEST_DISABLE_WGLOBAL_CONSTRUCTORS_                                       \
    EZTEST_CREATE_SETUP_TEST_(base_name,                                       \
                              EZTEST_INTERNAL_NAME_(group, name, lineno),      \
                              group, name, msecs, lineno)                      \
    EZTEST_REENABLE_WGLOBAL_CONSTRUCTORS_

/* End include of: eztest-test-setup.h  */

#define EZTEST_TIMED(group, name, msecs)                                       \
    EZTEST_CREATE_TEST_(EZTEST_NS_ eztest_list_get_head(), group, name, msecs, \
                        EZTEST_LINE_)
#define EZTEST(group, name) EZTEST_TIMED(group, name, 0)

#define EZTEST_F(group, name) EZTEST_UNIMPLEMENTED_("EZTEST_F")
#define EZTEST_F_TIMED(group, name, msecs)                                     \
    EZTEST_UNIMPLEMENTED_("EZTEST_F_TIMED")

#define EZTEST_P(group, name) EZTEST_UNIMPLEMENTED_("EZTEST_P")
#define EZTEST_P_TIMED(group, name, msecs)                                     \
    EZTEST_UNIMPLEMENTED_("EZTEST_P_TIMED")

#define EZTEST_SCOPED_TRACE(msg) EZTEST_UNIMPLEMENTED_("SCOPED_TRACE")

EZTEST_DISABLE_WCXX98_COMPAT_PEDANTIC_
EZTEST_DISABLE_WVARIADIC_MACROS_

#define EZTEST_ASSERT_THROW(...)     EZTEST_UNIMPLEMENTED_("ASSERT_THROW")
#define EZTEST_ASSERT_ANY_THROW(...) EZTEST_UNIMPLEMENTED_("ASSERT_ANY_THROW")
#define EZTEST_ASSERT_NO_THROW(...)  EZTEST_UNIMPLEMENTED_("ASSERT_NO_THROW")
#define EZTEST_ASSERT_NO_FATAL_FAILURE(...)                                    \
    EZTEST_UNIMPLEMENTED_("ASSERT_NO_FATAL_FAILURE")

#define EZTEST_EXPECT_THROW(...)     EZTEST_UNIMPLEMENTED_("EXPECT_THROW")
#define EZTEST_EXPECT_ANY_THROW(...) EZTEST_UNIMPLEMENTED_("EXPECT_ANY_THROW")
#define EZTEST_EXPECT_NO_THROW(...)  EZTEST_UNIMPLEMENTED_("EXPECT_NO_THROW")
#define EZTEST_EXPECT_NO_FATAL_FAILURE(...)                                    \
    EZTEST_UNIMPLEMENTED_("EXPECT_NO_FATAL_FAILURE")

#define EZTEST_ASSERT_PRED1(...) EZTEST_UNIMPLEMENTED_("EZTEST_ASSERT_PRED1")
#define EZTEST_ASSERT_PRED2(...) EZTEST_UNIMPLEMENTED_("EZTEST_ASSERT_PRED2")
#define EZTEST_ASSERT_PRED3(...) EZTEST_UNIMPLEMENTED_("EZTEST_ASSERT_PRED3")
#define EZTEST_ASSERT_PRED4(...) EZTEST_UNIMPLEMENTED_("EZTEST_ASSERT_PRED4")
#define EZTEST_ASSERT_PRED5(...) EZTEST_UNIMPLEMENTED_("EZTEST_ASSERT_PRED5")

#define EZTEST_EXPECT_PRED1(...) EZTEST_UNIMPLEMENTED_("EZTEST_EXPECT_PRED1")
#define EZTEST_EXPECT_PRED2(...) EZTEST_UNIMPLEMENTED_("EZTEST_EXPECT_PRED2")
#define EZTEST_EXPECT_PRED3(...) EZTEST_UNIMPLEMENTED_("EZTEST_EXPECT_PRED3")
#define EZTEST_EXPECT_PRED4(...) EZTEST_UNIMPLEMENTED_("EZTEST_EXPECT_PRED4")
#define EZTEST_EXPECT_PRED5(...) EZTEST_UNIMPLEMENTED_("EZTEST_EXPECT_PRED5")

#define EZTEST_ASSERT_LONG_DOUBLE_EQ(...)                                      \
    EZTEST_UNIMPLEMENTED_("EZTEST_ASSERT_LONG_DOUBLE_EQ")
#define EZTEST_EXPECT_LONG_DOUBLE_EQ(...)                                      \
    EZTEST_UNIMPLEMENTED_("EZTEST_EXPECT_LONG_DOUBLE_EQ")

EZTEST_REENABLE_WVARIADIC_MACROS_
EZTEST_REENABLE_WCXX98_COMPAT_PEDANTIC_


#define EZTEST_ASSERT_TRUE      EZTEST_ASSERT_TRUE_IMPL_
#define EZTEST_ASSERT_FALSE     EZTEST_ASSERT_FALSE_IMPL_
#define EZTEST_ASSERT_EQ        EZTEST_ASSERT_EQ_IMPL_
#define EZTEST_ASSERT_NE        EZTEST_ASSERT_NE_IMPL_
#define EZTEST_ASSERT_LE        EZTEST_ASSERT_LE_IMPL_
#define EZTEST_ASSERT_LT        EZTEST_ASSERT_LT_IMPL_
#define EZTEST_ASSERT_GE        EZTEST_ASSERT_GE_IMPL_
#define EZTEST_ASSERT_GT        EZTEST_ASSERT_GT_IMPL_
#define EZTEST_ASSERT_STREQ     EZTEST_ASSERT_STREQ_IMPL_
#define EZTEST_ASSERT_STRNE     EZTEST_ASSERT_STRNE_IMPL_
#define EZTEST_ASSERT_STRCASEEQ EZTEST_ASSERT_STRCASEEQ_IMPL_
#define EZTEST_ASSERT_STRCASENE EZTEST_ASSERT_STRCASENE_IMPL_
#define EZTEST_ASSERT_FLOAT_EQ  EZTEST_ASSERT_FLOAT_EQ_IMPL_
#define EZTEST_ASSERT_DOUBLE_EQ EZTEST_ASSERT_DOUBLE_EQ_IMPL_
#define EZTEST_ASSERT_NEAR      EZTEST_ASSERT_NEAR_IMPL_

#define EZTEST_EXPECT_TRUE      EZTEST_EXPECT_TRUE_IMPL_
#define EZTEST_EXPECT_FALSE     EZTEST_EXPECT_FALSE_IMPL_
#define EZTEST_EXPECT_EQ        EZTEST_EXPECT_EQ_IMPL_
#define EZTEST_EXPECT_NE        EZTEST_EXPECT_NE_IMPL_
#define EZTEST_EXPECT_LE        EZTEST_EXPECT_LE_IMPL_
#define EZTEST_EXPECT_LT        EZTEST_EXPECT_LT_IMPL_
#define EZTEST_EXPECT_GE        EZTEST_EXPECT_GE_IMPL_
#define EZTEST_EXPECT_GT        EZTEST_EXPECT_GT_IMPL_
#define EZTEST_EXPECT_STREQ     EZTEST_EXPECT_STREQ_IMPL_
#define EZTEST_EXPECT_STRNE     EZTEST_EXPECT_STRNE_IMPL_
#define EZTEST_EXPECT_STRCASEEQ EZTEST_EXPECT_STRCASEEQ_IMPL_
#define EZTEST_EXPECT_STRCASENE EZTEST_EXPECT_STRCASENE_IMPL_
#define EZTEST_EXPECT_FLOAT_EQ  EZTEST_EXPECT_FLOAT_EQ_IMPL_
#define EZTEST_EXPECT_DOUBLE_EQ EZTEST_EXPECT_DOUBLE_EQ_IMPL_
#define EZTEST_EXPECT_NEAR      EZTEST_EXPECT_NEAR_IMPL_

#if !(EZTEST_STRICT_NAMESPACE)
# define TEST_TIMED              EZTEST_TIMED
# define TEST                    EZTEST
# define TEST_F                  EZTEST_F
# define TEST_F_TIMED            EZTEST_F_TIMED
# define TEST_P                  EZTEST_P
# define TEST_P_TIMED            EZTEST_P_TIMED
# define SCOPED_TRACE            EZTEST_SCOPED_TRACE
# define ASSERT_THROW            EZTEST_ASSERT_THROW
# define ASSERT_ANY_THROW        EZTEST_ASSERT_ANY_THROW
# define ASSERT_NO_THROW         EZTEST_ASSERT_NO_THROW
# define ASSERT_NO_FATAL_FAILURE EZTEST_ASSERT_NO_FATAL_FAILURE
# define EXPECT_THROW            EZTEST_EXPECT_THROW
# define EXPECT_ANY_THROW        EZTEST_EXPECT_ANY_THROW
# define EXPECT_NO_THROW         EZTEST_EXPECT_NO_THROW
# define EXPECT_NO_FATAL_FAILURE EZTEST_EXPECT_NO_FATAL_FAILURE
# define ASSERT_TRUE             EZTEST_ASSERT_TRUE
# define ASSERT_FALSE            EZTEST_ASSERT_FALSE
# define ASSERT_EQ               EZTEST_ASSERT_EQ
# define ASSERT_NE               EZTEST_ASSERT_NE
# define ASSERT_LE               EZTEST_ASSERT_LE
# define ASSERT_LT               EZTEST_ASSERT_LT
# define ASSERT_GE               EZTEST_ASSERT_GE
# define ASSERT_GT               EZTEST_ASSERT_GT
# define ASSERT_STREQ            EZTEST_ASSERT_STREQ
# define ASSERT_STRNE            EZTEST_ASSERT_STRNE
# define ASSERT_STRCASEEQ        EZTEST_ASSERT_STRCASEEQ
# define ASSERT_STRCASENE        EZTEST_ASSERT_STRCASENE
# define ASSERT_FLOAT_EQ         EZTEST_ASSERT_FLOAT_EQ
# define ASSERT_DOUBLE_EQ        EZTEST_ASSERT_DOUBLE_EQ
# define ASSERT_LONG_DOUBLE_EQ   EZTEST_ASSERT_LONG_DOUBLE_EQ
# define ASSERT_NEAR             EZTEST_ASSERT_NEAR
# define ASSERT_PRED1            EZTEST_ASSERT_PRED1
# define ASSERT_PRED2            EZTEST_ASSERT_PRED2
# define ASSERT_PRED3            EZTEST_ASSERT_PRED3
# define ASSERT_PRED4            EZTEST_ASSERT_PRED4
# define ASSERT_PRED5            EZTEST_ASSERT_PRED5


# define EXPECT_TRUE           EZTEST_EXPECT_TRUE
# define EXPECT_FALSE          EZTEST_EXPECT_FALSE
# define EXPECT_EQ             EZTEST_EXPECT_EQ
# define EXPECT_NE             EZTEST_EXPECT_NE
# define EXPECT_LE             EZTEST_EXPECT_LE
# define EXPECT_LT             EZTEST_EXPECT_LT
# define EXPECT_GE             EZTEST_EXPECT_GE
# define EXPECT_GT             EZTEST_EXPECT_GT
# define EXPECT_STREQ          EZTEST_EXPECT_STREQ
# define EXPECT_STRNE          EZTEST_EXPECT_STRNE
# define EXPECT_STRCASEEQ      EZTEST_EXPECT_STRCASEEQ
# define EXPECT_STRCASENE      EZTEST_EXPECT_STRCASENE
# define EXPECT_FLOAT_EQ       EZTEST_EXPECT_FLOAT_EQ
# define EXPECT_DOUBLE_EQ      EZTEST_EXPECT_DOUBLE_EQ
# define EXPECT_LONG_DOUBLE_EQ EZTEST_EXPECT_LONG_DOUBLE_EQ
# define EXPECT_NEAR           EZTEST_EXPECT_NEAR
# define EXPECT_PRED1          EZTEST_EXPECT_PRED1
# define EXPECT_PRED2          EZTEST_EXPECT_PRED2
# define EXPECT_PRED3          EZTEST_EXPECT_PRED3
# define EXPECT_PRED4          EZTEST_EXPECT_PRED4
# define EXPECT_PRED5          EZTEST_EXPECT_PRED5

#endif

EZTEST_REENABLE_WTRADITIONAL_
EZTEST_REENABLE_WSYSTEM_HEADERS_

/* End include of: eztest-api.h  */

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
/* End include of: eztest.h  */
#endif
