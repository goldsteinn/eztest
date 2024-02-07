#ifndef EZTEST_D_EZTEST_D_EZTEST_CONTAINERS_H_
#define EZTEST_D_EZTEST_D_EZTEST_CONTAINERS_H_

#include "eztest-lang.h"
#include "eztest-libc.h"


#if EZTEST_CXX_LANG_ >= 2011
# include <array>
# define EZTEST_ARR_BUILDER_(name, T, k_n) EZTEST_STD_NS_ array<T, k_n> name
#else
# define EZTEST_ARR_BUILDER_(name, T, k_n) T name[k_n]
#endif

#endif
