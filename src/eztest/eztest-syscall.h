#ifndef EZTEST_D_EZTEST_D_EZTEST_SYSCALL_H_
#define EZTEST_D_EZTEST_D_EZTEST_SYSCALL_H_

#include "eztest-arch.h"
#include "eztest-compiler.h"
#include "eztest-lang.h"
#include "eztest-libc.h"

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#include <sys/types.h> /* pid_t.  */
#include <unistd.h>    /* pid_t.  */
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

#if EZTEST_DEFAULT_SOURCE_
/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
# include <signal.h>
# include <sys/syscall.h>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

# define EZTEST_PIDFD_OPEN_(pid, flags)                                        \
  /* NOLINTBEGIN(llvmlibc-callee-namespace) */                                 \
  /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg) */                         \
  /* NOLINTBEGIN(hicpp-vararg) */                                              \
                                                                               \
  syscall(EZTEST_CAST_(long, SYS_pidfd_open), pid, flags) \
        /* NOLINTEND(hicpp-vararg) */                       \
        /* NOLINTEND(cppcoreguidelines-pro-type-vararg) */  \
        /* NOLINTEND(llvmlibc-callee-namespace) */

# define EZTEST_KILL_(pid, sig)                                                \
  /* NOLINTBEGIN(llvmlibc-callee-namespace) */                                 \
  kill(pid, sig) /* NOLINTEND(llvmlibc-callee-namespace) */

#else
/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
# include <asm/unistd.h>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

EZTEST_NAMESPACE_BEGIN_
# if EZTEST_ARCH_IS_X86_64_


/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ long
eztest_syscall2_impl(long eztest_syscall_no,
                     long eztest_arg0,
                     long eztest_arg1) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(hicpp-no-assembler,misc-const-correctness) */
    register long eztest_rax __asm__("rax") = eztest_syscall_no;
    register long eztest_rdi __asm__("rdi") = eztest_arg0;
    register long eztest_rsi __asm__("rsi") = eztest_arg1;
    __asm__ volatile("syscall"
                     : "+r"(eztest_rax)
                     : "r"(eztest_rdi), "r"(eztest_rsi)
                     : "rcx", "r11", "memory");
    /* NOLINTEND(hicpp-no-assembler,misc-const-correctness) */
    return eztest_rax;
}

# elif EZTEST_ARCH_IS_X86_32_

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ long
eztest_syscall2_impl(long eztest_syscall_no,
                     long eztest_arg0,
                     long eztest_arg1) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(hicpp-no-assembler,misc-const-correctness) */
    register long eztest_eax __asm__("eax") = eztest_syscall_no;
    register long eztest_ebx __asm__("ebx") = eztest_arg0;
    register long eztest_ecx __asm__("ecx") = eztest_arg1;
    __asm__ volatile("int $0x80"
                     : "+r"(eztest_eax)
                     : "r"(eztest_ebx), "r"(eztest_ecx)
                     : "memory");
    /* NOLINTEND(hicpp-no-assembler,misc-const-correctness) */
    return eztest_eax;
}


# elif EZTEST_ARCH_IS_AARCH64_

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */

EZTEST_PRIVATE_ long
eztest_syscall2_impl(long eztest_syscall_no,
                     long eztest_arg0,
                     long eztest_arg1) {

    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(hicpp-no-assembler,misc-const-correctness) */
    register long eztest_x8 __asm__("x8") = eztest_syscall_no;
    register long eztest_x0 __asm__("x0") = eztest_arg0;
    register long eztest_x1 __asm__("x1") = eztest_arg1;
    __asm__ volatile("svc 0"
                     : "+r"(eztest_x0)
                     : "r"(eztest_x8), "r"(eztest_x1)
                     : "memory", "cc");
    /* NOLINTEND(hicpp-no-assembler,misc-const-correctness) */
    return eztest_x0;
}


# elif EZTEST_ARCH_IS_ARM32_

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */

EZTEST_PRIVATE_ long
eztest_syscall2_impl(long eztest_syscall_no,
                     long eztest_arg0,
                     long eztest_arg1) {

    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(hicpp-no-assembler,misc-const-correctness) */
    register long eztest_r7 __asm__("r7") = eztest_syscall_no;
    register long eztest_r0 __asm__("r0") = eztest_arg0;
    register long eztest_r1 __asm__("r1") = eztest_arg1;
    __asm__ volatile("svc 0"
                     : "+r"(eztest_r0)
                     : "r"(eztest_r7), "r"(eztest_r1)
                     : "memory");
    /* NOLINTEND(hicpp-no-assembler,misc-const-correctness) */
    return eztest_r0;
}


# elif EZTEST_ARCH_IS_ANY_RISCV_

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */

EZTEST_PRIVATE_ long
eztest_syscall2_impl(long eztest_syscall_no,
                     long eztest_arg0,
                     long eztest_arg1) {

    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(hicpp-no-assembler,misc-const-correctness) */
    register long eztest_a7 __asm__("a7") = eztest_syscall_no;
    register long eztest_a0 __asm__("a0") = eztest_arg0;
    register long eztest_a1 __asm__("a1") = eztest_arg1;
    __asm__ volatile("ecall\n\t"
                     : "+r"(eztest_a0)
                     : "r"(eztest_a7), "r"(eztest_a1)
                     : "memory");
    /* NOLINTEND(hicpp-no-assembler,misc-const-correctness) */
    return eztest_a0;
}


# else
#  error "No syscall impl for arch!"
# endif

EZTEST_PRIVATE_ long
eztest_syscall2(long eztest_syscall_no, long eztest_arg0, long eztest_arg1) {
    static const unsigned long eztest_syscall_max_valid = -4096UL;
    long eztest_res = EZTEST_NS_ eztest_syscall2_impl(eztest_syscall_no,
                                                      eztest_arg0, eztest_arg1);
    if (EZTEST_CAST_(unsigned long, eztest_res) > eztest_syscall_max_valid) {
        EZTEST_ERRNO_ = EZTEST_CAST_(int, -eztest_res);
        return EZTEST_CAST_(long, -1);
    }
    return eztest_res;
}

# define EZTEST_PIDFD_OPEN_(pid, flags)                                        \
  EZTEST_NS_ eztest_syscall2(EZTEST_CAST_(long, __NR_pidfd_open),              \
                             EZTEST_CAST_(long, pid),                          \
                             EZTEST_CAST_(long, flags))

# define EZTEST_KILL_(pid, sig)                                                \
  EZTEST_NS_ eztest_syscall2(EZTEST_CAST_(long, __NR_kill),                    \
                             EZTEST_CAST_(long, pid), EZTEST_CAST_(long, sig))

EZTEST_NAMESPACE_END_
#endif
#endif
