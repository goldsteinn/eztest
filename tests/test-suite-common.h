/* NOLINTBEGIN(llvm-header-guard) */
#ifndef TS_D_TESTS_D_TEST_SUITE_COMMON_H_
#define TS_D_TESTS_D_TEST_SUITE_COMMON_H_
/* NOLINTEND(llvm-header-guard) */

/* NOLINTBEGIN(cppcoreguidelines-macro-usage) */
#define TS_STRINGIFY_IMPL_(ts_expr) #ts_expr
#define TS_STRINGIFY_(ts_expr)      TS_STRINGIFY_IMPL_(ts_expr)

#define TS_VERNUM_(ts_major, ts_minor, ts_patch)                               \
 (((ts_major)*100 * 100) + ((ts_minor)*100) + (ts_patch))

#ifdef __clang__
# ifdef __clang_major__
#  define TS_CLANG_MAJOR_ __clang_major__
# else
#  define TS_CLANG_MAJOR_ 0
# endif
# ifdef __clang_minor__
#  define TS_CLANG_MINOR_ __clang_minor__
# else
#  define TS_CLANG_MINOR_ 0
# endif

# ifdef __clang_patchlevel__
#  define TS_CLANG_PATCHLEVEL_ __clang_patchlevel__
# else
#  define TS_CLANG_PATCHLEVEL_ 0
# endif

# ifdef __has_feature
#  define TS_HAS_FEATURE_(feat) __has_feature(feat)
# else
#  define TS_HAS_FEATURE_(feat) 0
# endif


# define TS_USING_CLANG_                                                       \
  TS_VERNUM_(TS_CLANG_MAJOR_, TS_CLANG_MINOR_, TS_CLANG_PATCHLEVEL_)

# define TS_DISABLE_WARNING_(ts_warning)                                       \
  _Pragma("clang diagnostic push")                                             \
      _Pragma(TS_STRINGIFY_(clang diagnostic ignored ts_warning))
# define TS_REENABLE_WARNING_ _Pragma("clang diagnostic pop")

#endif
#if !(defined __clang__) && (defined __GNUC__)


# define TS_GCC_MAJOR_ __GNUC__
# ifdef __GNUC_minor__
#  define TS_GCC_MINOR_ __GNUC_MINOR__
# else
#  define TS_GCC_MINOR_ 0
# endif

# ifdef __GNUC_patchlevel__
#  define TS_GCC_PATCHLEVEL_ __GNUC_PATCHLEVEL__
# else
#  define TS_GCC_PATCHLEVEL_ 0
# endif

# define TS_USING_GCC_                                                         \
  TS_VERNUM_(TS_GCC_MAJOR_, TS_GCC_MINOR_, TS_GCC_PATCHLEVEL_)

# define TS_DISABLE_WARNING_(ts_warning)                                       \
  _Pragma("GCC diagnostic push")                                               \
      _Pragma(TS_STRINGIFY_(GCC diagnostic ignored ts_warning))
# define TS_REENABLE_WARNING_ _Pragma("GCC diagnostic pop")
#endif

#ifndef TS_DISABLE_WARNING_
# define TS_DISABLE_WARNING_(ts_warning)
# define TS_REENABLE_WARNING_
#endif

#ifndef TS_USING_CLANG_
# define TS_USING_CLANG_ 0
#endif

#ifndef TS_USING_GCC_
# define TS_USING_GCC_ 0
#endif


#define TS_HAS_CLANG_VER_(major, minor, patch)                                 \
 TS_USING_CLANG_ >= TS_VERNUM_(major, minor, patch)
#define TS_HAS_GCC_VER_(major, minor, patch)                                   \
 TS_USING_GCC_ >= TS_VERNUM_(major, minor, patch)

#ifdef __cplusplus
# if __cplusplus == 199711L
#  define TS_CXX_LANG_ 1998
# elif __cplusplus == 201103L
#  define TS_CXX_LANG_ 2011
# elif __cplusplus == 201402L
#  define TS_CXX_LANG_ 2014
# elif __cplusplus == 201703L
#  define TS_CXX_LANG_ 2017
# elif __cplusplus == 202002L
#  define TS_CXX_LANG_ 2020
# elif __cplusplus >= 202101L
#  define TS_CXX_LANG_ 2023
# else
#  define TS_CXX_LANG_ 1
# endif
# define TS_C_LANG_ 0
#elif defined(__STDC__)
# if defined(__STDC_VERSION__)
#  if (__STDC_VERSION__ >= 202311L)
#   define TS_C_LANG_ 2023
#  elif (__STDC_VERSION__ >= 201710L)
#   define TS_C_LANG_ 2017
#  elif (__STDC_VERSION__ >= 201112L)
#   define TS_C_LANG_ 2011
#  elif (__STDC_VERSION__ >= 199901L)
#   define TS_C_LANG_ 1999
#  elif (__STDC_VERSION__ >= 199409L)
#   define TS_C_LANG_ 1994
#  else
#   define TS_C_LANG_ 1990
#  endif
# else
#  define TS_C_LANG_ 1989
# endif
# define TS_CXX_LANG_ 0
#endif


#if (defined __cplusplus)
# if __cplusplus >= 201103L
#  define TS_NULL_ nullptr
# else
#  define TS_NULL_ reinterpret_cast<void *>(NULL)
# endif
#else
# define TS_NULL_ NULL
#endif
#define TS_KILL_ EZTEST_KILL_


#if (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE) != 0 &&                     \
    ((defined EZTEST_ASAN_) || (defined EZTEST_MSAN_))
# error "_FORTIFY_SOURCE and address/memory sanitizers are incompatible."
#endif


#if ((TS_HAS_GCC_VER_(4, 5, 3)) && TS_C_LANG_)
# define TS_DISABLE_WUNSUFFIXED_FLOAT_CONSTANTS_                               \
  TS_DISABLE_WARNING_("-Wunsuffixed-float-constants")
# define TS_REENABLE_WUNSUFFIXED_FLOAT_CONSTANTS_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
# define TS_REENABLE_WUNSUFFIXED_FLOAT_CONSTANTS_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0) || TS_HAS_GCC_VER_(4, 4, 7))
# define TS_DISABLE_WMISSING_NORETURN_  TS_DISABLE_WARNING_("-Wmissing-noreturn")
# define TS_REENABLE_WMISSING_NORETURN_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WMISSING_NORETURN_
# define TS_REENABLE_WMISSING_NORETURN_
#endif


#if (TS_HAS_CLANG_VER_(4, 0, 0) || TS_HAS_GCC_VER_(6, 1, 0))
# define TS_DISABLE_WFLOAT_CONVERSION_  TS_DISABLE_WARNING_("-Wfloat-conversion")
# define TS_REENABLE_WFLOAT_CONVERSION_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WFLOAT_CONVERSION_
# define TS_REENABLE_WFLOAT_CONVERSION_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0) || TS_HAS_GCC_VER_(4, 4, 7))
# define TS_DISABLE_WFLOAT_EQUAL_  TS_DISABLE_WARNING_("-Wfloat-equal")
# define TS_REENABLE_WFLOAT_EQUAL_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WFLOAT_EQUAL_
# define TS_REENABLE_WFLOAT_EQUAL_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0) || TS_HAS_GCC_VER_(4, 6, 4))
# define TS_DISABLE_WDOUBLE_PROMOTION_  TS_DISABLE_WARNING_("-Wdouble-promotion")
# define TS_REENABLE_WDOUBLE_PROMOTION_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WDOUBLE_PROMOTION_
# define TS_REENABLE_WDOUBLE_PROMOTION_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0))
# define TS_DISABLE_WCXX98_COMPAT_  TS_DISABLE_WARNING_("-Wc++98-compat")
# define TS_REENABLE_WCXX98_COMPAT_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WCXX98_COMPAT_
# define TS_REENABLE_WCXX98_COMPAT_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0))
# define TS_DISABLE_WCXX98_COMPAT_PEDANTIC_                                    \
  TS_DISABLE_WARNING_("-Wc++98-compat-pedantic")
# define TS_REENABLE_WCXX98_COMPAT_PEDANTIC_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WCXX98_COMPAT_PEDANTIC_
# define TS_REENABLE_WCXX98_COMPAT_PEDANTIC_
#endif

#if (TS_HAS_CLANG_VER_(16, 0, 0))
# define TS_DISABLE_WUNSAFE_BUFFER_USAGE_                                      \
  TS_DISABLE_WARNING_("-Wunsafe-buffer-usage")
# define TS_REENABLE_WUNSAFE_BUFFER_USAGE_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WUNSAFE_BUFFER_USAGE_
# define TS_REENABLE_WUNSAFE_BUFFER_USAGE_
#endif

#if TS_HAS_CLANG_VER_(4, 0, 0) || TS_HAS_GCC_VER_(4, 5, 3)
# define TS_DISABLE_WCONVERSION_NULL_  TS_DISABLE_WARNING_("-Wconversion-null")
# define TS_REENABLE_WCONVERSION_NULL_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WCONVERSION_NULL_
# define TS_REENABLE_WCONVERSION_NULL_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0))
# define TS_DISABLE_WLITERAL_CONVERSION_                                       \
  TS_DISABLE_WARNING_("-Wliteral-conversion")
# define TS_REENABLE_WLITERAL_CONVERSION_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WLITERAL_CONVERSION_
# define TS_REENABLE_WLITERAL_CONVERSION_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0))
# define TS_DISABLE_WDISABLED_MACRO_EXPANSION_                                 \
  TS_DISABLE_WARNING_("-Wdisabled-macro-expansion")
# define TS_REENABLE_WDISABLED_MACRO_EXPANSION_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WDISABLED_MACRO_EXPANSION_
# define TS_REENABLE_WDISABLED_MACRO_EXPANSION_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0) || TS_HAS_GCC_VER_(4, 4, 7))
# define TS_DISABLE_WSTACK_PROTECTOR_  TS_DISABLE_WARNING_("-Wstack-protector")
# define TS_REENABLE_WSTACK_PROTECTOR_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WSTACK_PROTECTOR_
# define TS_REENABLE_WSTACK_PROTECTOR_
#endif

#if ((TS_HAS_GCC_VER_(6, 1, 0)) && TS_CXX_LANG_)
# define TS_DISABLE_WTEMPLATES_  TS_DISABLE_WARNING_("-Wtemplates")
# define TS_REENABLE_WTEMPLATES_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WTEMPLATES_
# define TS_REENABLE_WTEMPLATES_
#endif

#if ((TS_HAS_GCC_VER_(4, 8, 1)) && TS_CXX_LANG_)
# define TS_DISABLE_WUSELESS_CAST_  TS_DISABLE_WARNING_("-Wuseless-cast")
# define TS_REENABLE_WUSELESS_CAST_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WUSELESS_CAST_
# define TS_REENABLE_WUSELESS_CAST_
#endif

#if ((TS_HAS_CLANG_VER_(5, 0, 0) || TS_HAS_GCC_VER_(4, 7, 1)) && TS_CXX_LANG_)
# define TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_                            \
  TS_DISABLE_WARNING_("-Wzero-as-null-pointer-constant")
# define TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WZERO_AS_NULL_POINTER_CONSTANT_
# define TS_REENABLE_WZERO_AS_NULL_POINTER_CONSTANT_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0))
# define TS_DISABLE_WFLOAT_OVERFLOW_CONVERSION_                                \
  TS_DISABLE_WARNING_("-Wfloat-overflow-conversion")
# define TS_REENABLE_WFLOAT_OVERFLOW_CONVERSION_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WFLOAT_OVERFLOW_CONVERSION_
# define TS_REENABLE_WFLOAT_OVERFLOW_CONVERSION_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0) || TS_HAS_GCC_VER_(6, 1, 0))
# define TS_DISABLE_WFLOAT_CONVERSION_  TS_DISABLE_WARNING_("-Wfloat-conversion")
# define TS_REENABLE_WFLOAT_CONVERSION_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WFLOAT_CONVERSION_
# define TS_REENABLE_WFLOAT_CONVERSION_
#endif

#if (TS_HAS_CLANG_VER_(16, 0, 0))
# define TS_DISABLE_WUNSAFE_BUFFER_USAGE_                                      \
  TS_DISABLE_WARNING_("-Wunsafe-buffer-usage")
# define TS_REENABLE_WUNSAFE_BUFFER_USAGE_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WUNSAFE_BUFFER_USAGE_
# define TS_REENABLE_WUNSAFE_BUFFER_USAGE_
#endif

#if (TS_HAS_GCC_VER_(4, 6, 4))
# define TS_DISABLE_WSUGGEST_ATTRIBUTE_PURE_                                   \
  TS_DISABLE_WARNING_("-Wsuggest-attribute=pure")
# define TS_REENABLE_WSUGGEST_ATTRIBUTE_PURE_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WSUGGEST_ATTRIBUTE_PURE_
# define TS_REENABLE_WSUGGEST_ATTRIBUTE_PURE_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0) || TS_HAS_GCC_VER_(4, 4, 7))
# define TS_DISABLE_WPADDED_  TS_DISABLE_WARNING_("-Wpadded")
# define TS_REENABLE_WPADDED_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WPADDED_
# define TS_REENABLE_WPADDED_
#endif

#if (TS_HAS_CLANG_VER_(4, 0, 0) || TS_HAS_GCC_VER_(4, 4, 7))
# define TS_DISABLE_WEXTRA_  TS_DISABLE_WARNING_("-Wextra")
# define TS_REENABLE_WEXTRA_ TS_REENABLE_WARNING_
#else
# define TS_DISABLE_WEXTRA_
# define TS_REENABLE_WEXTRA_
#endif

/* NOLINTEND(cppcoreguidelines-macro-usage) */

#endif
