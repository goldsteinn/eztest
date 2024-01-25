#include "test-suite-common.h"

/* NOLINTBEGIN(cppcoreguidelines-macro-usage) */
#ifndef EZTEST_DISABLE_WARNINGS
# define EZTEST_DISABLE_WARNINGS 1
#endif
/* NOLINTEND(cppcoreguidelines-macro-usage) */
#include "eztest/eztest.h"

/* NOLINTBEGIN(altera-unroll-loops) */

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#include <cstddef>
#include <cstdlib>
#include <random>
#include <string>

#if TS_CXX_LANG_ >= 2017
# include <string_view>
#endif
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

/* NOLINTBEGIN(llvmlibc-implementation-in-namespace) */
static const std::size_t k_str_sz = 256;

/* NOLINTBEGIN(misc-use-anonymous-namespace) */
/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
/* NOLINTBEGIN(modernize-use-trailing-return-type) */
static char *
simple_rand_string(unsigned seed, std::size_t size, unsigned rand_case) {
    /* NOLINTEND(modernize-use-trailing-return-type) */
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    std::size_t idx = 0;
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast) */
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc) */
    /* NOLINTBEGIN(hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    char * ptr = reinterpret_cast<char *>(std::malloc(size + 1));
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(hicpp-no-malloc) */
    /* NOLINTEND(cppcoreguidelines-no-malloc) */
    /* NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast) */

    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    static const unsigned char k_num_letters = 26;
    static const unsigned char k_num_digits  = 10;
    static const char          k_case_diff   = 32;

    TS_DISABLE_WCXX98_COMPAT_
    ASSERT_EQ(ptr, TS_NULL_);
    std::seed_seq rseed({ seed });
    TS_REENABLE_WCXX98_COMPAT_
    std::mt19937                                 reng(rseed);
    std::uniform_int_distribution<unsigned char> rdist(0);

    for (idx = 0; idx < size; ++idx) {
        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        const unsigned char todo = rdist(reng) % 3U;
        unsigned char       chr  = rdist(reng);
        /* NOLINTEND(llvmlibc-callee-namespace) */
        if (todo == 0) {
            chr = static_cast<unsigned char>('a' + (chr % k_num_letters));
        }
        else if (todo == 1) {
            chr = static_cast<unsigned char>('A' + (chr % k_num_letters));
        }
        else {
            chr = static_cast<unsigned char>('0' + (chr % k_num_digits));
        }

        TS_DISABLE_WUNSAFE_BUFFER_USAGE_
        /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
        ptr[idx] = static_cast<char>(chr);
        /* NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
        TS_REENABLE_WUNSAFE_BUFFER_USAGE_
    }
    TS_DISABLE_WUNSAFE_BUFFER_USAGE_
    /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
    ptr[idx] = '\0';
    /* NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
    TS_REENABLE_WUNSAFE_BUFFER_USAGE_

    if (rand_case != 0) {
        TS_DISABLE_WCXX98_COMPAT_
        std::seed_seq r_caseseed({ rand_case });
        TS_REENABLE_WCXX98_COMPAT_
        std::mt19937 r_caseeng(r_caseseed);

        for (idx = 0; idx < size; ++idx) {
            TS_DISABLE_WUNSAFE_BUFFER_USAGE_
            /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
            char chr = ptr[idx];
            /* NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
            TS_REENABLE_WUNSAFE_BUFFER_USAGE_
            if (chr >= 'a' && chr <= 'z') {
                /* NOLINTBEGIN(llvmlibc-callee-namespace) */
                if ((rdist(r_caseeng) % 2U) == 0) {
                    chr = static_cast<char>(chr - k_case_diff);
                }
                /* NOLINTEND(llvmlibc-callee-namespace) */
            }
            else if (chr >= 'A' && chr <= 'Z') {
                /* NOLINTBEGIN(llvmlibc-callee-namespace) */
                if ((rdist(r_caseeng) % 2U) == 0) {
                    chr = static_cast<char>(chr + k_case_diff);
                }
                /* NOLINTEND(llvmlibc-callee-namespace) */
            }
            TS_DISABLE_WUNSAFE_BUFFER_USAGE_
            /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
            ptr[idx] = chr;
            /* NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
            TS_REENABLE_WUNSAFE_BUFFER_USAGE_
        }
    }

    /* NOLINTEND(fuchsia-default-arguments-calls) */
    return ptr;
}
/* NOLINTEND(misc-use-anonymous-namespace) */
/* NOLINTEND(llvmlibc-implementation-in-namespace) */


TEST(assert_cp_str, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef";
    std::string  str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}

TEST(assert_cp_str, eq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdef";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}


TEST(assert_cp_str, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef";
    std::string  str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
}

TEST(assert_cp_str, eq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdef";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
}


TEST(assert_cp_str, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
}

TEST(assert_cp_str, eq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
}


TEST(assert_cp_str, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdef");
}

TEST(assert_cp_str, eq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdef");
}

TEST(assert_cp_str, eq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, eq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, eq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_str, eq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_str, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef";
    std::string  str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}


TEST(assert_cp_str, ne05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdef";
    const std::string str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}


TEST(assert_cp_str, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdeff";
    std::string  str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
}


TEST(assert_cp_str, ne15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdeff";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
}


TEST(assert_cp_str, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
}

TEST(assert_cp_str, ne25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
}


TEST(assert_cp_str, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdeff");
}

TEST(assert_cp_str, ne35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdeff");
}

TEST(assert_cp_str, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, ne45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, ne55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, ne65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_str, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, ne75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_str, ne8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_str, ne85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_str, ne9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, ne95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "AbcdeF";
    std::string  str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}

TEST(assert_cp_str, caseeq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "AbcdeF";
    const std::string str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}


TEST(assert_cp_str, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "123abcDef";
    std::string  str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
    ASSERT_STRCASENE(str1, str0);
}

TEST(assert_cp_str, caseeq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "123abcDef";
    const std::string str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
    ASSERT_STRCASENE(str1, str0);
}


TEST(assert_cp_str, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
    ASSERT_STRCASENE("abcdef", str1);
}

TEST(assert_cp_str, caseeq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdEf");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
    ASSERT_STRCASENE("abcdef", str1);
}


TEST(assert_cp_str, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdefabc");
    ASSERT_STRCASENE(str1, "abcdefabc");
}

TEST(assert_cp_str, caseeq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdefabc");
    ASSERT_STRCASENE(str1, "abcdefabc");
}

TEST(assert_cp_str, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    ASSERT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, caseeq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    ASSERT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    ASSERT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, caseeq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    ASSERT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_str, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef0";
    std::string  str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}

TEST(assert_cp_str, casene05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdef0";
    const std::string str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}


TEST(assert_cp_str, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdeF";
    std::string  str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
}

TEST(assert_cp_str, casene15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdeF";
    const std::string str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
}


TEST(assert_cp_str, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
}

TEST(assert_cp_str, casene25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
}


TEST(assert_cp_str, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "Abcdeff");
}

TEST(assert_cp_str, casene35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "Abcdeff");
}

TEST(assert_cp_str, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, casene45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, casene55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, casene65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_str, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, casene75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_str, casene8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, casene85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_str, casene9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_str, casene95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_str_str, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str0 = "abcdef";
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}
TEST(assert_str_str, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "abcdef";
    std::string       str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}

TEST(assert_str_str, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "abcdef";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}

TEST(assert_str_str, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string       str0 = "abcdef";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}


TEST(assert_str_str, eq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_str_str, eq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    std::string       str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_str_str, eq6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string       str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_str_str, eq7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_str_str, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str0 = "Abcdef";
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}
TEST(assert_str_str, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "Abcdef";
    std::string       str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}

TEST(assert_str_str, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "Abcdef";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}

TEST(assert_str_str, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string       str0 = "abcdef";
    const std::string str1("Abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}


TEST(assert_str_str, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_str_str, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    std::string       str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_str_str, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string       str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_str_str, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_str_str, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str0 = "Abcdef";
    std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}
TEST(assert_str_str, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "Abcdef";
    std::string       str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}

TEST(assert_str_str, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "Abcdef";
    const std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}

TEST(assert_str_str, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string       str0 = "Abcdef";
    const std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}


TEST(assert_str_str, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_str_str, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    std::string       str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_str_str, caseeq6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string       str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_str_str, caseeq7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_str_str, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str0 = "Abcdef";
    std::string str1("aacdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}
TEST(assert_str_str, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "bbcdef";
    std::string       str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}

TEST(assert_str_str, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "Abcdef";
    const std::string str1("0bcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}

TEST(assert_str_str, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string       str0 = "abcdef";
    const std::string str1("Abcde0");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}


TEST(assert_str_str, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_str_str, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    std::string       str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_str_str, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string       str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_str_str, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_cp, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", "abcdef");
}
TEST(assert_cp_cp, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, "abcdef");
}

TEST(assert_cp_cp, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef";
    const char * str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}

TEST(assert_cp_cp, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
}


TEST(assert_cp_cp, eq8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char * str2(str0);
    char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_cp, eq9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    char *       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_cp, eq10_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char *       str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_cp, eq11_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_cp, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("Abcdef", "abcdef");
}
TEST(assert_cp_cp, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, "abcdef");
}

TEST(assert_cp_cp, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "Abcdef";
    const char * str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}

TEST(assert_cp_cp, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str1 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
}


TEST(assert_cp_cp, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char * str2 = str0;
    char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_cp, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    char *       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_cp, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char *       str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_cp, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_cp, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("Abcdef", "abcdeF");
    ASSERT_STRCASENE("Abcdef", "abcdeF");
}
TEST(assert_cp_cp, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, "abcdeF");
    ASSERT_STRCASENE(str0, "abcdeF");
}

TEST(assert_cp_cp, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "Abcdef";
    const char * str1 = "abcdeF";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}

TEST(assert_cp_cp, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str1 = "abcdeF";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("Abcdef", str1);
    ASSERT_STRCASENE("Abcdef", str1);
}


TEST(assert_cp_cp, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char * str2 = str0;
    char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_cp, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    char *       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_cp, caseeq6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char *       str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_cp, caseeq7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_cp, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("Abcdef", "aacdef");
}
TEST(assert_cp_cp, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "bbcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, "abcdef");
}

TEST(assert_cp_cp, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "Abcdef";
    const char * str1 = "0bcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}

TEST(assert_cp_cp, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str1 = "Abcde0";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
}

TEST(assert_cp_cp, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char * str2 = str0;
    char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_cp, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    char *       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_cp, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char *       str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_cp, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

#if TS_CXX_LANG_ >= 2017

TEST(assert_sview_str, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    std::string            str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}

TEST(assert_sview_str, eq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    const std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}


TEST(assert_sview_str, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    std::string            str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
}

TEST(assert_sview_str, eq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    const std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
}


TEST(assert_sview_str, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
}

TEST(assert_sview_str, eq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
}


TEST(assert_sview_str, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdef");
}

TEST(assert_sview_str, eq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdef");
}

TEST(assert_sview_str, eq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, eq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, eq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_str, eq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_str, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    std::string            str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}


TEST(assert_sview_str, ne05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    const std::string      str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}


TEST(assert_sview_str, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdeff";
    std::string            str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
}


TEST(assert_sview_str, ne15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdeff";
    const std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
}


TEST(assert_sview_str, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
}

TEST(assert_sview_str, ne25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
}


TEST(assert_sview_str, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdeff");
}

TEST(assert_sview_str, ne35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdeff");
}

TEST(assert_sview_str, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, ne45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, ne55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, ne65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_str, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, ne75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_str, ne8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_str, ne85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_str, ne9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, ne95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "AbcdeF";
    std::string            str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}

TEST(assert_sview_str, caseeq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "AbcdeF";
    const std::string      str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}


TEST(assert_sview_str, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "123abcDef";
    std::string            str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
    ASSERT_STRCASENE(str1, str0);
}

TEST(assert_sview_str, caseeq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "123abcDef";
    const std::string      str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
    ASSERT_STRCASENE(str1, str0);
}


TEST(assert_sview_str, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
    ASSERT_STRCASENE("abcdef", str1);
}

TEST(assert_sview_str, caseeq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdEf");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
    ASSERT_STRCASENE("abcdef", str1);
}


TEST(assert_sview_str, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdefabc");
    ASSERT_STRCASENE(str1, "abcdefabc");
}

TEST(assert_sview_str, caseeq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdefabc");
    ASSERT_STRCASENE(str1, "abcdefabc");
}

TEST(assert_sview_str, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    ASSERT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, caseeq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    ASSERT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    ASSERT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, caseeq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    ASSERT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_str, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef0";
    std::string            str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}

TEST(assert_sview_str, casene05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef0";
    const std::string      str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}


TEST(assert_sview_str, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdeF";
    std::string            str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
}

TEST(assert_sview_str, casene15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdeF";
    const std::string      str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
}


TEST(assert_sview_str, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
}

TEST(assert_sview_str, casene25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
}


TEST(assert_sview_str, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "Abcdeff");
}

TEST(assert_sview_str, casene35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "Abcdeff");
}

TEST(assert_sview_str, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, casene45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, casene55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, casene65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_str, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, casene75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_str, casene8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, casene85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_str, casene9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_str, casene95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_sview, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdef";
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}

TEST(assert_cp_sview, eq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdef";
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}


TEST(assert_cp_sview, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdef";
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
}

TEST(assert_cp_sview, eq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdef";
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
}


TEST(assert_cp_sview, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
}

TEST(assert_cp_sview, eq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
}


TEST(assert_cp_sview, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdef");
}

TEST(assert_cp_sview, eq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdef");
}

TEST(assert_cp_sview, eq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, eq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, eq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_sview, eq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_sview, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdef";
    std::string_view str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}


TEST(assert_cp_sview, ne05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdef";
    const std::string_view str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}


TEST(assert_cp_sview, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdeff";
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
}


TEST(assert_cp_sview, ne15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdeff";
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
}


TEST(assert_cp_sview, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
}

TEST(assert_cp_sview, ne25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
}


TEST(assert_cp_sview, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdeff");
}

TEST(assert_cp_sview, ne35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdeff");
}

TEST(assert_cp_sview, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, ne45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, ne55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, ne65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_sview, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, ne75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_sview, ne8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_sview, ne85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_sview, ne9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, ne95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "AbcdeF";
    std::string_view str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}

TEST(assert_cp_sview, caseeq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "AbcdeF";
    const std::string_view str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}


TEST(assert_cp_sview, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "123abcDef";
    std::string_view str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
    ASSERT_STRCASENE(str1, str0);
}

TEST(assert_cp_sview, caseeq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "123abcDef";
    const std::string_view str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str0);
    ASSERT_STRCASENE(str1, str0);
}


TEST(assert_cp_sview, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
    ASSERT_STRCASENE("abcdef", str1);
}

TEST(assert_cp_sview, caseeq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdEf");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
    ASSERT_STRCASENE("abcdef", str1);
}


TEST(assert_cp_sview, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdefabc");
    ASSERT_STRCASENE(str1, "abcdefabc");
}

TEST(assert_cp_sview, caseeq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, "abcdefabc");
    ASSERT_STRCASENE(str1, "abcdefabc");
}

TEST(assert_cp_sview, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    ASSERT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, caseeq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str1, str2);
    ASSERT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    ASSERT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, caseeq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str1);
    ASSERT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_sview, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdef0";
    std::string_view str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}

TEST(assert_cp_sview, casene05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdef0";
    const std::string_view str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}


TEST(assert_cp_sview, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdeF";
    std::string_view str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
}

TEST(assert_cp_sview, casene15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdeF";
    const std::string_view str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
}


TEST(assert_cp_sview, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
}

TEST(assert_cp_sview, casene25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
}


TEST(assert_cp_sview, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "Abcdeff");
}

TEST(assert_cp_sview, casene35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "Abcdeff");
}

TEST(assert_cp_sview, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, casene45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, casene55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, casene65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_sview, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, casene75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_sview, casene8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, casene85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_cp_sview, casene9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_cp_sview, casene95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_sview, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", "abcdef");
}
TEST(assert_sview_sview, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, "abcdef");
}

TEST(assert_sview_sview, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    const std::string_view str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
}

TEST(assert_sview_sview, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("abcdef", str1);
}


TEST(assert_sview_sview, eq8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string_view str2(str0);
    std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_sview, eq9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    std::string_view       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_sview, eq10_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    std::string_view       str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_sview, eq11_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_sview, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("Abcdef", "abcdef");
}
TEST(assert_sview_sview, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, "abcdef");
}

TEST(assert_sview_sview, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "Abcdef";
    const std::string_view str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str0, str1);
}

TEST(assert_sview_sview, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ("abcdef", str1);
}


TEST(assert_sview_sview, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string_view str2 = str0;
    std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_sview, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    std::string_view       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_sview, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    std::string_view       str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_sview, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_sview, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("Abcdef", "abcdeF");
    ASSERT_STRCASENE("Abcdef", "abcdeF");
}
TEST(assert_sview_sview, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, "abcdeF");
    ASSERT_STRCASENE(str0, "abcdeF");
}

TEST(assert_sview_sview, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "Abcdef";
    const std::string_view str1 = "abcdeF";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str0, str1);
    ASSERT_STRCASENE(str0, str1);
}

TEST(assert_sview_sview, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1 = "abcdeF";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE("Abcdef", str1);
    ASSERT_STRCASENE("Abcdef", str1);
}


TEST(assert_sview_sview, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string_view str2 = str0;
    std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_sview, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    std::string_view       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_sview, caseeq6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    std::string_view       str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_sview, caseeq7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRNE(str2, str3);
    ASSERT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_sview, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("Abcdef", "aacdef");
}
TEST(assert_sview_sview, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "bbcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, "abcdef");
}

TEST(assert_sview_sview, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "Abcdef";
    const std::string_view str1 = "0bcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str0, str1);
}

TEST(assert_sview_sview, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1 = "Abcde0";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ("abcdef", str1);
}

TEST(assert_sview_sview, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string_view str2 = str0;
    std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_sview, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    std::string_view       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(assert_sview_sview, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    std::string_view       str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(assert_sview_sview, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    ASSERT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}
#endif


TEST(expect_cp_str, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef";
    std::string  str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}

TEST(expect_cp_str, eq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdef";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}


TEST(expect_cp_str, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef";
    std::string  str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
}

TEST(expect_cp_str, eq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdef";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
}


TEST(expect_cp_str, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
}

TEST(expect_cp_str, eq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
}


TEST(expect_cp_str, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdef");
}

TEST(expect_cp_str, eq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdef");
}

TEST(expect_cp_str, eq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, eq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, eq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_str, eq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_str, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef";
    std::string  str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}


TEST(expect_cp_str, ne05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdef";
    const std::string str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}


TEST(expect_cp_str, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdeff";
    std::string  str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
}


TEST(expect_cp_str, ne15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdeff";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
}


TEST(expect_cp_str, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
}

TEST(expect_cp_str, ne25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
}


TEST(expect_cp_str, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdeff");
}

TEST(expect_cp_str, ne35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdeff");
}

TEST(expect_cp_str, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, ne45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, ne55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, ne65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_str, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, ne75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_str, ne8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_str, ne85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_str, ne9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, ne95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "AbcdeF";
    std::string  str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}

TEST(expect_cp_str, caseeq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "AbcdeF";
    const std::string str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}


TEST(expect_cp_str, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "123abcDef";
    std::string  str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
    EXPECT_STRCASENE(str1, str0);
}

TEST(expect_cp_str, caseeq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "123abcDef";
    const std::string str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
    EXPECT_STRCASENE(str1, str0);
}


TEST(expect_cp_str, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
    EXPECT_STRCASENE("abcdef", str1);
}

TEST(expect_cp_str, caseeq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdEf");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
    EXPECT_STRCASENE("abcdef", str1);
}


TEST(expect_cp_str, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdefabc");
    EXPECT_STRCASENE(str1, "abcdefabc");
}

TEST(expect_cp_str, caseeq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdefabc");
    EXPECT_STRCASENE(str1, "abcdefabc");
}

TEST(expect_cp_str, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    EXPECT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, caseeq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    EXPECT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    EXPECT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, caseeq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    EXPECT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_str, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef0";
    std::string  str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}

TEST(expect_cp_str, casene05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdef0";
    const std::string str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}


TEST(expect_cp_str, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdeF";
    std::string  str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
}

TEST(expect_cp_str, casene15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *      str0 = "abcdeF";
    const std::string str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
}


TEST(expect_cp_str, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
}

TEST(expect_cp_str, casene25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
}


TEST(expect_cp_str, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "Abcdeff");
}

TEST(expect_cp_str, casene35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "Abcdeff");
}

TEST(expect_cp_str, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, casene45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, casene55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, casene65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_str, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, casene75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_str, casene8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, casene85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_str, casene9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_str, casene95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_str_str, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str0 = "abcdef";
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}
TEST(expect_str_str, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "abcdef";
    std::string       str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}

TEST(expect_str_str, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "abcdef";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}

TEST(expect_str_str, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string       str0 = "abcdef";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}


TEST(expect_str_str, eq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_str_str, eq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    std::string       str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_str_str, eq6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string       str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_str_str, eq7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_str_str, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str0 = "Abcdef";
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}
TEST(expect_str_str, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "Abcdef";
    std::string       str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}

TEST(expect_str_str, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "Abcdef";
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}

TEST(expect_str_str, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string       str0 = "abcdef";
    const std::string str1("Abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}


TEST(expect_str_str, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_str_str, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    std::string       str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_str_str, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string       str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_str_str, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_str_str, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str0 = "Abcdef";
    std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}
TEST(expect_str_str, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "Abcdef";
    std::string       str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}

TEST(expect_str_str, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "Abcdef";
    const std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}

TEST(expect_str_str, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string       str0 = "Abcdef";
    const std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}


TEST(expect_str_str, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_str_str, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    std::string       str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_str_str, caseeq6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string       str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_str_str, caseeq7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_str_str, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str0 = "Abcdef";
    std::string str1("aacdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}
TEST(expect_str_str, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "bbcdef";
    std::string       str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}

TEST(expect_str_str, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str0 = "Abcdef";
    const std::string str1("0bcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}

TEST(expect_str_str, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string       str0 = "abcdef";
    const std::string str1("Abcde0");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}


TEST(expect_str_str, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string str2(str0);
    std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_str_str, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    std::string       str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_str_str, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string       str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_str_str, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string str2(str0);
    const std::string str3(str1);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_cp, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", "abcdef");
}
TEST(expect_cp_cp, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, "abcdef");
}

TEST(expect_cp_cp, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "abcdef";
    const char * str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}

TEST(expect_cp_cp, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
}


TEST(expect_cp_cp, eq8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char * str2(str0);
    char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_cp, eq9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    char *       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_cp, eq10_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char *       str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_cp, eq11_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_cp, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("Abcdef", "abcdef");
}
TEST(expect_cp_cp, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, "abcdef");
}

TEST(expect_cp_cp, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "Abcdef";
    const char * str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}

TEST(expect_cp_cp, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str1 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
}


TEST(expect_cp_cp, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char * str2 = str0;
    char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_cp, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    char *       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_cp, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char *       str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_cp, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_cp, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("Abcdef", "abcdeF");
    EXPECT_STRCASENE("Abcdef", "abcdeF");
}
TEST(expect_cp_cp, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, "abcdeF");
    EXPECT_STRCASENE(str0, "abcdeF");
}

TEST(expect_cp_cp, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "Abcdef";
    const char * str1 = "abcdeF";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}

TEST(expect_cp_cp, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str1 = "abcdeF";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("Abcdef", str1);
    EXPECT_STRCASENE("Abcdef", str1);
}


TEST(expect_cp_cp, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char * str2 = str0;
    char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_cp, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    char *       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_cp, caseeq6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char *       str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_cp, caseeq7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_cp, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("Abcdef", "aacdef");
}
TEST(expect_cp_cp, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "bbcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, "abcdef");
}

TEST(expect_cp_cp, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str0 = "Abcdef";
    const char * str1 = "0bcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}

TEST(expect_cp_cp, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char * str1 = "Abcde0";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
}

TEST(expect_cp_cp, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char * str2 = str0;
    char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_cp, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    char *       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_cp, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    char *       str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_cp, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const char * str2 = str0;
    const char * str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

#if TS_CXX_LANG_ >= 2017

TEST(expect_sview_str, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    std::string            str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}

TEST(expect_sview_str, eq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    const std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}


TEST(expect_sview_str, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    std::string            str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
}

TEST(expect_sview_str, eq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    const std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
}


TEST(expect_sview_str, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
}

TEST(expect_sview_str, eq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
}


TEST(expect_sview_str, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdef");
}

TEST(expect_sview_str, eq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdef");
}

TEST(expect_sview_str, eq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, eq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, eq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_str, eq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_str, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    std::string            str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}


TEST(expect_sview_str, ne05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    const std::string      str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}


TEST(expect_sview_str, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdeff";
    std::string            str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
}


TEST(expect_sview_str, ne15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdeff";
    const std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
}


TEST(expect_sview_str, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
}

TEST(expect_sview_str, ne25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
}


TEST(expect_sview_str, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdeff");
}

TEST(expect_sview_str, ne35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdeff");
}

TEST(expect_sview_str, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, ne45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, ne55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, ne65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_str, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, ne75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_str, ne8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_str, ne85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_str, ne9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, ne95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "AbcdeF";
    std::string            str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}

TEST(expect_sview_str, caseeq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "AbcdeF";
    const std::string      str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}


TEST(expect_sview_str, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "123abcDef";
    std::string            str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
    EXPECT_STRCASENE(str1, str0);
}

TEST(expect_sview_str, caseeq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "123abcDef";
    const std::string      str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
    EXPECT_STRCASENE(str1, str0);
}


TEST(expect_sview_str, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
    EXPECT_STRCASENE("abcdef", str1);
}

TEST(expect_sview_str, caseeq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdEf");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
    EXPECT_STRCASENE("abcdef", str1);
}


TEST(expect_sview_str, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdefabc");
    EXPECT_STRCASENE(str1, "abcdefabc");
}

TEST(expect_sview_str, caseeq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdefabc");
    EXPECT_STRCASENE(str1, "abcdefabc");
}

TEST(expect_sview_str, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    EXPECT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, caseeq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    EXPECT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    EXPECT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, caseeq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    EXPECT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_str, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef0";
    std::string            str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}

TEST(expect_sview_str, casene05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef0";
    const std::string      str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}


TEST(expect_sview_str, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdeF";
    std::string            str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
}

TEST(expect_sview_str, casene15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdeF";
    const std::string      str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
}


TEST(expect_sview_str, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
}

TEST(expect_sview_str, casene25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
}


TEST(expect_sview_str, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "Abcdeff");
}

TEST(expect_sview_str, casene35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "Abcdeff");
}

TEST(expect_sview_str, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, casene45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string      str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, casene55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str1 = ptr1;
    const std::string str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, casene65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_str, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, casene75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_str, casene8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, casene85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_str, casene9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    std::string      str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_str, casene95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view  str0 = ptr0;
    const std::string str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_sview, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdef";
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}

TEST(expect_cp_sview, eq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdef";
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}


TEST(expect_cp_sview, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdef";
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
}

TEST(expect_cp_sview, eq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdef";
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
}


TEST(expect_cp_sview, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
}

TEST(expect_cp_sview, eq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
}


TEST(expect_cp_sview, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdef");
}

TEST(expect_cp_sview, eq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdef");
}

TEST(expect_cp_sview, eq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, eq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, eq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_sview, eq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_sview, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdef";
    std::string_view str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}


TEST(expect_cp_sview, ne05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdef";
    const std::string_view str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}


TEST(expect_cp_sview, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdeff";
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
}


TEST(expect_cp_sview, ne15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdeff";
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
}


TEST(expect_cp_sview, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
}

TEST(expect_cp_sview, ne25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdeff");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
}


TEST(expect_cp_sview, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdeff");
}

TEST(expect_cp_sview, ne35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdeff");
}

TEST(expect_cp_sview, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, ne45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, ne55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, ne65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_sview, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, ne75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_sview, ne8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_sview, ne85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_sview, ne9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, ne95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "AbcdeF";
    std::string_view str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}

TEST(expect_cp_sview, caseeq05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "AbcdeF";
    const std::string_view str1("aBcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}


TEST(expect_cp_sview, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "123abcDef";
    std::string_view str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
    EXPECT_STRCASENE(str1, str0);
}

TEST(expect_cp_sview, caseeq15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "123abcDef";
    const std::string_view str1("123abCDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str0);
    EXPECT_STRCASENE(str1, str0);
}


TEST(expect_cp_sview, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcDef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
    EXPECT_STRCASENE("abcdef", str1);
}

TEST(expect_cp_sview, caseeq25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdEf");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
    EXPECT_STRCASENE("abcdef", str1);
}


TEST(expect_cp_sview, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdefabc");
    EXPECT_STRCASENE(str1, "abcdefabc");
}

TEST(expect_cp_sview, caseeq35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdefABC");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, "abcdefabc");
    EXPECT_STRCASENE(str1, "abcdefabc");
}

TEST(expect_cp_sview, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    EXPECT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, caseeq45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str1, str2);
    EXPECT_STRCASENE(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    EXPECT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, caseeq55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str1);
    EXPECT_STRCASENE(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_sview, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdef0";
    std::string_view str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}

TEST(expect_cp_sview, casene05_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdef0";
    const std::string_view str1("abcdef9");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}


TEST(expect_cp_sview, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *     str0 = "abcdeF";
    std::string_view str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
}

TEST(expect_cp_sview, casene15_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const char *           str0 = "abcdeF";
    const std::string_view str1("abcdFe");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
}


TEST(expect_cp_sview, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
}

TEST(expect_cp_sview, casene25_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcabc");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
}


TEST(expect_cp_sview, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    std::string_view str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "Abcdeff");
}

TEST(expect_cp_sview, casene35_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1("abcdeF");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "Abcdeff");
}

TEST(expect_cp_sview, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, casene45_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str2);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, casene55_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str2(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    free(str1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, casene65_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, str0);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_sview, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, casene75_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1("abcdef");
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_sview, casene8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, casene85_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str1, "abcdef");
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_cp_sview, casene9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_cp_sview, casene95_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * str0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    const std::string_view str1(str0);
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(str0);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_sview, eq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", "abcdef");
}
TEST(expect_sview_sview, eq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, "abcdef");
}

TEST(expect_sview_sview, eq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "abcdef";
    const std::string_view str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
}

TEST(expect_sview_sview, eq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("abcdef", str1);
}


TEST(expect_sview_sview, eq8_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string_view str2(str0);
    std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_sview, eq9_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    std::string_view       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_sview, eq10_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    std::string_view       str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_sview, eq11_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_sview, ne0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("Abcdef", "abcdef");
}
TEST(expect_sview_sview, ne1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, "abcdef");
}

TEST(expect_sview_sview, ne2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "Abcdef";
    const std::string_view str1 = "abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str0, str1);
}

TEST(expect_sview_sview, ne3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ("abcdef", str1);
}


TEST(expect_sview_sview, ne4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string_view str2 = str0;
    std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_sview, ne5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    std::string_view       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_sview, ne6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    std::string_view       str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_sview, ne7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STREQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_sview, caseeq0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("Abcdef", "abcdeF");
    EXPECT_STRCASENE("Abcdef", "abcdeF");
}
TEST(expect_sview_sview, caseeq1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "Abcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, "abcdeF");
    EXPECT_STRCASENE(str0, "abcdeF");
}

TEST(expect_sview_sview, caseeq2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "Abcdef";
    const std::string_view str1 = "abcdeF";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str0, str1);
    EXPECT_STRCASENE(str0, str1);
}

TEST(expect_sview_sview, caseeq3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1 = "abcdeF";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE("Abcdef", str1);
    EXPECT_STRCASENE("Abcdef", str1);
}


TEST(expect_sview_sview, caseeq4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string_view str2 = str0;
    std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_sview, caseeq5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    std::string_view       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_sview, caseeq6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    std::string_view       str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_sview, caseeq7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRNE(str2, str3);
    EXPECT_STRCASENE(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_sview, casene0_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("Abcdef", "aacdef");
}
TEST(expect_sview_sview, casene1_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "bbcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, "abcdef");
}

TEST(expect_sview_sview, casene2_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str0 = "Abcdef";
    const std::string_view str1 = "0bcdef";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str0, str1);
}

TEST(expect_sview_sview, casene3_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    const std::string_view str1 = "Abcde0";
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ("abcdef", str1);
}

TEST(expect_sview_sview, casene4_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0(ptr0);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str1(ptr1);
    std::string_view str2 = str0;
    std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_sview, casene5_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    std::string_view       str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}


TEST(expect_sview_sview, casene6_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(1, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(0, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    std::string_view       str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}

TEST(expect_sview_sview, casene7_fail) {
    /* NOLINTBEGIN(misc-const-correctness) */
    /* NOLINTBEGIN(fuchsia-default-arguments-calls) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr0 = simple_rand_string(0, k_str_sz, 1);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view str0 = ptr0;
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    char * ptr1 = simple_rand_string(1, k_str_sz, 2);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    std::string_view       str1 = ptr1;
    const std::string_view str2 = str0;
    const std::string_view str3 = str1;
    /* NOLINTEND(fuchsia-default-arguments-calls) */
    /* NOLINTEND(misc-const-correctness) */
    EXPECT_STRCASEEQ(str2, str3);
    /* NOLINTBEGIN(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
    /* NOLINTBEGIN(cppcoreguidelines-owning-memory) */
    free(ptr0);
    free(ptr1);
    /* NOLINTEND(cppcoreguidelines-owning-memory) */
    /* NOLINTEND(cppcoreguidelines-no-malloc,hicpp-no-malloc) */
}
#endif


/* NOLINTEND(altera-unroll-loops) */
