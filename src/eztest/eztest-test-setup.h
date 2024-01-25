#ifndef EZTEST_D_EZTEST_D_EZTEST_TEST_SETUP_H_
#define EZTEST_D_EZTEST_D_EZTEST_TEST_SETUP_H_

#include "eztest-compiler.h"
#include "eztest-lang.h"
#include "eztest-list.h"
#include "eztest-pre-processor.h"
#include "eztest-test.h"

#define EZTEST_INTERNAL_NAME_(group, name, lineno)                             \
 EZTEST_SNAKE_CAT_(EZTEST_SNAKE_CAT_(eztest, group),                           \
                   EZTEST_SNAKE_CAT_(name, lineno))


#if EZTEST_CXX_LANG_
# define EZTEST_CREATE_LINK_IN_TEST_(base_name, struct_name, sink_name)        \
  static const int sink_name =                                                 \
      EZTEST_NS_   eztest_list_insert_test(base_name, &(struct_name));

#else
# define EZTEST_CREATE_LINK_IN_TEST_(base_name, struct_name, sink_name)        \
  static void EZTEST_ATTR_CONSTRUCTOR_ sink_name(void) {                       \
   EZTEST_NS_ eztest_list_insert_test(base_name, &(struct_name));              \
  }
#endif

#define EZTEST_CREATE_SETUP_TEST_IMPL_(base_name, func_name, struct_name,      \
                                       sink_name, group, name, msecs, lineno)  \
 /* NOLINTBEGIN(llvmlibc-implementation-in-namespace) */                       \
 /* NOLINTBEGIN(misc-use-anonymous-namespace) */                               \
 static void func_name(void);                                                  \
 EZTEST_NAMESPACE_BEGIN_                                                       \
 EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_                                       \
 EZTEST_DISABLE_WUSELESS_CAST_                                                 \
 /* NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables) */         \
 static EZTEST_TEST_T_ struct_name = {                                         \
     EZTEST_NULL_, /* NOLINTBEGIN(llvmlibc-callee-namespace) */                \
     func_name,    /* NOLINTEND(llvmlibc-callee-namespace) */                  \
     EZTEST_STRINGIFY_(group),                                                 \
     EZTEST_STRINGIFY_(name),                                                  \
     EZTEST_CAST_(unsigned, lineno),                                           \
     EZTEST_CAST_(int, msecs),                                                 \
     EZTEST_CAST_(unsigned, EZTEST_NS_ eztest_k_status_init),                  \
     EZTEST_STRUCT_INTT_PADDING_INIT_                                          \
 };                                                                            \
 /* NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables) */           \
 EZTEST_REENABLE_WUSELESS_CAST_                                                \
 EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_                                       \
 EZTEST_CREATE_LINK_IN_TEST_(base_name, EZTEST_NS_ struct_name, sink_name)     \
 EZTEST_NAMESPACE_END_                                                         \
 static void func_name(void) /* NOLINTEND(misc-use-anonymous-namespace) */     \
                                                                               \
     /* NOLINTEND(llvmlibc-implementation-in-namespace) */

#define EZTEST_CREATE_SETUP_TEST_(base_name, internal_name, group, name,       \
                                  msecs, lineno)                               \
 EZTEST_CREATE_SETUP_TEST_IMPL_(base_name, EZTEST_CAT_(internal_name, func),   \
                                EZTEST_CAT_(internal_name, struct),            \
                                EZTEST_CAT_(internal_name, sink), group, name, \
                                msecs, lineno)

#define EZTEST_CREATE_TEST_(base_name, group, name, msecs, lineno)             \
 EZTEST_DISABLE_WGLOBAL_CONSTRUCTORS_                                          \
 EZTEST_CREATE_SETUP_TEST_(base_name,                                          \
                           EZTEST_INTERNAL_NAME_(group, name, lineno), group,  \
                           name, msecs, lineno)                                \
 EZTEST_REENABLE_WGLOBAL_CONSTRUCTORS_

#endif
