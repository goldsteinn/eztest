#include "test-suite-common.h"

#ifndef EZTEST_DISABLE_WARNINGS
# define EZTEST_DISABLE_WARNINGS 1
#endif
#include "eztest/eztest.h"

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#include <signal.h>
#include <unistd.h>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */


/* NOLINTBEGIN(altera-unroll-loops) */
#if TS_USING_GCC_ || TS_HAS_CLANG_VER_(14, 0, 0) || !EZTEST_ARCH_IS_ANY_RISCV_
TS_DISABLE_WSUGGEST_ATTRIBUTE_PURE_
TEST(sigs, fault_self_Uultamsan_sigfail) {
    int * ptr = TS_NULL_;
    /* NOLINTBEGIN(hicpp-no-assembler) */
    __asm__ volatile("" : [ptr] "+r"(ptr) : : "memory");
    /* NOLINTEND(hicpp-no-assembler) */
    *ptr = 2;
    /* NOLINTBEGIN(hicpp-no-assembler) */
    __asm__ volatile("" : [ptr] "+r"(ptr) : : "memory");
    /* NOLINTEND(hicpp-no-assembler) */
    ASSERT_EQ(*ptr, 1);
}
#endif

TS_DISABLE_WMISSING_NORETURN_
TEST(sigs, assert_true_false_fail) {
    ASSERT_FALSE(1);
}
TS_REENABLE_WMISSING_NORETURN_
#if EZTEST_ARCH_IS_ANY_X86_
TEST(sigs, fpe_self_Uultamsan_sigfail) {
    long val = 0;
    /* NOLINTBEGIN(hicpp-no-assembler) */
    __asm__ volatile("" : "+r"(val) : : "memory");
    /* NOLINTEND(hicpp-no-assembler) */
    /* NOLINTBEGIN(*-magic-numbers) */
    val = 1231L / val;
    /* NOLINTEND(*-magic-numbers) */
    ASSERT_TRUE(val);
}
#elif EZTEST_ARCH_IS_AARCH64_
TEST(sigs, fpe_self_Uusan_fail) {
    long val = 0;
    /* NOLINTBEGIN(hicpp-no-assembler) */
    __asm__ volatile("" : "+r"(val) : : "memory");
    /* NOLINTEND(hicpp-no-assembler) */
    /* NOLINTBEGIN(*-magic-numbers) */
    val = 1231L / val;
    /* NOLINTEND(*-magic-numbers) */
    ASSERT_TRUE(val);
}
#endif

TEST(sigs, illegal_instruction_self_sigfail) {
    /* NOLINTBEGIN(hicpp-no-assembler) */
#if EZTEST_ARCH_IS_ANY_X86_
    __asm__ volatile("ud2" : : :);
#elif EZTEST_ARCH_IS_AARCH64_
    __asm__ volatile("brk\t#1000" : : :);
#elif EZTEST_ARCH_IS_RISCV64_
    __asm__ volatile("ebreak" : : :);
#else
    TS_KILL_(getpid(), SIGKILL);
#endif
    /* NOLINTEND(hicpp-no-assembler) */
}
TS_REENABLE_WSUGGEST_ATTRIBUTE_PURE_
/* NOLINTEND(altera-unroll-loops) */
