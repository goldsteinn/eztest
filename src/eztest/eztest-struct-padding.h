#ifndef EZTEST_D_EZTEST_D_EZTEST_STRUCT_PADDING_H_
#define EZTEST_D_EZTEST_D_EZTEST_STRUCT_PADDING_H_

#include "eztest-libc-incs.h"

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

#endif
