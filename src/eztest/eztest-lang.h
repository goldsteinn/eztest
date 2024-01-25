#ifndef EZTEST_D_EZTEST_D_EZTEST_LANG_H_
#define EZTEST_D_EZTEST_D_EZTEST_LANG_H_

#include "eztest-compiler.h"
#include "eztest-lang-bits.h"
#include "eztest-pre-processor.h"


#if EZTEST_CXX_LANG_
# define EZTEST_STRUCT_

# define EZTEST_NAMESPACE_BEGIN_                                               \
  EZTEST_DISABLE_WNAMESPACES_                                                  \
  namespace eztest {

# define EZTEST_NAMESPACE_END_                                                 \
  }                                                                            \
  EZTEST_REENABLE_WNAMESPACES_

# define EZTEST_NS_                                                            \
  /* NOLINTBEGIN(llvmlibc-callee-namespace) */                                 \
  eztest::/* NOLINTEND(llvmlibc-callee-namespace) */

# define EZTEST_STD_NS_                                                        \
  /* NOLINTBEGIN(llvmlibc-callee-namespace) */                                 \
  std::/* NOLINTEND(llvmlibc-callee-namespace) */

# define EZTEST_VOID_ARG_

# if EZTEST_CXX_LANG_ >= 1998
#  define EZTEST_INLINE_ inline
# endif

# define EZTEST_PRIVATE_CXX_INL_ /* NOLINTBEGIN(llvmlibc-inl*-func*-decl) */   \
  static EZTEST_INLINE_          /* NOLINTEND(llvmlibc-inl*-func*-decl) */


# define EZTEST_PRIVATE_                                                       \
  /* NOLINTBEGIN(llvmlibc-inl*-func*-decl) */                                  \
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
  /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */               \
  reinterpret_cast<type>(                                                      \
      var) /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */

# if EZTEST_CXX_LANG_ >= 2011
#  define EZTEST_STATIC_ASSERT_MSG_(cond, msg)                                 \
   EZTEST_DISABLE_WCXX98_COMPAT_ static_assert(cond, msg)                      \
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
  static                 /* NOLINTEND(llvmlibc-inline-function-decl) */
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
  struct EZTEST_UNIQUE_NAME_(eztest_static_assertion) {                        \
   char EZTEST_UNIQUE_NAME_(eztest_x_)[(cond) ? 1 : -1];                       \
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


#endif
