#ifndef EZTEST_D_EZTEST_D_EZTEST_REQS_H_
#define EZTEST_D_EZTEST_D_EZTEST_REQS_H_

#include "eztest-arch.h"
#include "eztest-compiler.h"
#include "eztest-lang.h"
#include "eztest-system.h"

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

#endif
