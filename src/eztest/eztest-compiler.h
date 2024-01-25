#ifndef EZTEST_D_EZTEST_D_EZTEST_COMPILER_H_
#define EZTEST_D_EZTEST_D_EZTEST_COMPILER_H_

#include "eztest-pre-processor.h"

#define EZTEST_VERNUM_(eztest_major, eztest_minor, eztest_patch)               \
 (((eztest_major)*100 * 100) + ((eztest_minor)*100) + (eztest_patch))

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
  EZTEST_VERNUM_(EZTEST_CLANG_MAJOR_, EZTEST_CLANG_MINOR_,                     \
                 EZTEST_CLANG_PATCHLEVEL_)

# define EZTEST_DISABLE_WARNING_(eztest_warning)                               \
  _Pragma("clang diagnostic push")                                             \
      _Pragma(EZTEST_STRINGIFY_(clang diagnostic ignored eztest_warning))

# define EZTEST_REENABLE_WARNING_ _Pragma("clang diagnostic pop")
#endif
#if !(defined __clang__) && (defined __GNUC__)

# define EZTEST_GCC_MAJOR_ __GNUC__
# ifdef __GNUC_minor__
#  define EZTEST_GCC_MINOR_ __GNUC_MINOR__
# else
#  define EZTEST_GCC_MINOR_ 0
# endif

# ifdef __GNUC_patchlevel__
#  define EZTEST_GCC_PATCHLEVEL_ __GNUC_PATCHLEVEL__
# else
#  define EZTEST_GCC_PATCHLEVEL_ 0
# endif

# define EZTEST_USING_GCC_                                                     \
  EZTEST_VERNUM_(EZTEST_GCC_MAJOR_, EZTEST_GCC_MINOR_, EZTEST_GCC_PATCHLEVEL_)

# define EZTEST_DISABLE_WARNING_(eztest_warning)                               \
  _Pragma("GCC diagnostic push")                                               \
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
#include "eztest-compiler-warnings.h"
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


#endif
