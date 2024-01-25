#ifndef EZTEST_D_EZTEST_D_EZTEST_ASSERTS_IMPL_H_
#define EZTEST_D_EZTEST_D_EZTEST_ASSERTS_IMPL_H_

#include "eztest-compiler.h"
#include "eztest-fail.h"
#include "eztest-float-compare.h"
#include "eztest-hex-var-printer.h"
#include "eztest-lang.h"
#include "eztest-libc.h"
#include "eztest-libm.h"
#include "eztest-pre-processor.h"

#if EZTEST_CXX_LANG_
# include "eztest-cxx-asserts-impl.h"
#else
# include "eztest-c-asserts-impl.h"
#endif

#endif
