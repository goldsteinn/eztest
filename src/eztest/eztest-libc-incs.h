#ifndef EZTEST_D_EZTEST_D_EZTEST_LIBC_INCS_H_
#define EZTEST_D_EZTEST_D_EZTEST_LIBC_INCS_H_

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


#endif
