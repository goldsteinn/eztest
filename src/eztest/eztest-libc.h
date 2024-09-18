#ifndef EZTEST_D_EZTEST_D_EZTEST_LIBC_H_
#define EZTEST_D_EZTEST_D_EZTEST_LIBC_H_


#include "eztest-compiler.h"
#include "eztest-lang.h"
#include "eztest-libc-incs.h"

/* TODO: Wrap the call to exit in a mutex.  */
#define EZTEST_EXIT_    /* NOLINTBEGIN(concurrency-mt-unsafe) */               \
    EZTEST_STD_NS_ exit /* NOLINTEND(concurrency-mt-unsafe) */
EZTEST_DISABLE_WCXX98_COMPAT_PEDANTIC_

#define EZTEST_PRINTF_(...)                                                    \
    /* NOLINTBEGIN(clang-ana*-sec*.insecureAPI.Depr*OrUnsafeBufferHandling) */ \
    /* NOLINTBEGIN(cppcoreguide*-pro-type-vararg,hicpp-vararg) */              \
    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_                          \
    EZTEST_STD_NS_ fprintf(EZTEST_STDOUT_, __VA_ARGS__)                        \
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_                         \
    /* NOLINTEND(cppcoreguide*-pro-type-vararg,hicpp-vararg) */                \
    /* NOLINTEND(clang-ana*-sec*.insecureAPI.Depr*OrUnsafeBufferHandling) */


EZTEST_REENABLE_WCXX98_COMPAT_PEDANTIC_

#define EZTEST_VFPRINTF_                                                       \
    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ EZTEST_STD_NS_ vfprintf  \
        EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
#define EZTEST_FFLUSH_ EZTEST_STD_NS_ fflush
#define EZTEST_ERRNO_  errno
#define EZTEST_STDOUT_                                                         \
    EZTEST_DISABLE_WDISABLED_MACRO_EXPANSION_ stdout                           \
        EZTEST_REENABLE_WDISABLED_MACRO_EXPANSION_

/* strerror is safe here. We have complete control of the threads
   and know in the parent proc there will only be 1 thread (the
   forked test has a seperate address space so no concern about race
   conditions from user code).  */
#if (EZTEST_POSIX_VERSION_ >= 200112L || EZTEST_XOPEN_VERSION_ >= 600)
# if EZTEST_GNU_SOURCE_
#  define EZTEST_STRERROR_R_(errnum, buf, bufsz)                               \
      EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ strerror_r(errnum,     \
                                                                   buf, bufsz) \
          EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
# else
#  define EZTEST_STRERROR_R_(errnum, buf, bufsz)                               \
      (EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ strerror_r(           \
           errnum, buf, bufsz)                                                 \
                   EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ == 0     \
           ? &((buf)[0])                                                       \
           : "Unknown error")
# endif
#else
# if EZTEST_CXX_LANG_
#  define EZTEST_STRERROR_R_(errnum, buf, bufsz)                                                 \
      /* NOLINTBEGIN(concurrency-mt-unsafe) */                                                   \
      EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ std::strerror(errnum)                    \
          EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ /* NOLINTEND(concurrency-mt-unsafe) \
                                                              */
# else
#  define EZTEST_STRERROR_R_(errnum, buf, bufsz)                                                 \
      /* NOLINTBEGIN(concurrency-mt-unsafe) */                                                   \
      EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ strerror(errnum)                         \
          EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ /* NOLINTEND(concurrency-mt-unsafe) \
                                                              */
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


#define EZTEST_STRLEN_(str)                                                    \
    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ EZTEST_STD_NS_ strlen(   \
        str) EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_

#define EZTEST_STRCMP_(lhs, rhs)                                               \
    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ EZTEST_STD_NS_ strcmp(   \
        lhs, rhs) EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_

#define EZTEST_STARTSWITH_(prefix, str)                                        \
    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_(                         \
        EZTEST_STD_NS_ strncmp(prefix, str, EZTEST_STD_NS_ strlen(prefix)) ==  \
        0)                                                                     \
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_

#define EZTEST_MEMCPY_(dst, src, sz)                                           \
    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ EZTEST_STD_NS_ memcpy(   \
        dst, src, sz) EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_
#define EZTEST_MEMSET_(dst, val, sz) EZTEST_STD_NS_ memset(dst, val, sz)
#define EZTEST_MEMCMP_(s0, s1, sz)                                             \
    EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ EZTEST_STD_NS_ memcmp(   \
        s0, s1, sz) EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_

#if EZTEST_POSIX_VERSION_ >= 200809L || EZTEST_GNU_SOURCE_ != 0
# define EZTEST_STRNLEN_(str, maxlen)                                                               \
     /* NOLINTBEGIN(llvmlibc-callee-namespace) */                                                   \
     EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_                                              \
     strnlen(str, maxlen)                                                                           \
         EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ /* NOLINTEND(llvmlibc-callee-namespace) \
                                                             */

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
# define EZTEST_STRCASECMP_(lhs, rhs)                                                               \
     /* NOLINTBEGIN(llvmlibc-callee-namespace) */                                                   \
     EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_                                              \
     strcasecmp(lhs, rhs)                                                                           \
         EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_IN_LIBC_CALL_ /* NOLINTEND(llvmlibc-callee-namespace) \
                                                             */

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
#endif
