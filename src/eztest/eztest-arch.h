#ifndef EZTEST_D_EZTEST_D_EZTEST_ARCH_H_
#define EZTEST_D_EZTEST_D_EZTEST_ARCH_H_

#if defined(__AMDGPU__)
# define EZTEST_ARCH_IS_AMDGPU_ 1
#else
# define EZTEST_ARCH_IS_AMDGPU_ 0
#endif

#if defined(__NVPTX__)
# define EZTEST_ARCH_IS_NVPTX_ 1
#else
# define EZTEST_ARCH_IS_NVPTX_ 0
#endif

#if EZTEST_ARCH_IS_NVPTX_ || EZTEST_ARCH_IS_AMDGPU_
# define EZTEST_ARCH_IS_GPU_ 1
#else
# define EZTEST_ARCH_IS_GPU_ 0
#endif

#if defined(__pnacl__) || defined(__CLR_VER) || EZTEST_ARCH_IS_GPU_
# define EZTEST_ARCH_IS_VM_ 1
#else
# define EZTEST_ARCH_IS_VM_ 0
#endif

#if (defined(_M_IX86) || defined(__i386__)) && !EZTEST_ARCH_IS_VM_
# define EZTEST_ARCH_IS_X86_32_ 1
#else
# define EZTEST_ARCH_IS_X86_32_ 0
#endif

#if (defined(_M_X64) || defined(__x86_64__)) && !EZTEST_ARCH_IS_VM_
# define EZTEST_ARCH_IS_X86_64_ 1
#else
# define EZTEST_ARCH_IS_X86_64_ 0
#endif

#if EZTEST_ARCH_IS_X86_32_ || EZTEST_ARCH_IS_X86_64_
# define EZTEST_ARCH_IS_ANY_X86_ 1
#else
# define EZTEST_ARCH_IS_ANY_X86_ 0
#endif

#if (defined(__arm__) || defined(_M_ARM))
# define EZTEST_ARCH_IS_ARM32_ 1
#else
# define EZTEST_ARCH_IS_ARM32_ 0
#endif

#if defined(__aarch64__) || defined(__arm64__) || defined(_M_ARM64)
# define EZTEST_ARCH_IS_AARCH64_ 1
#else
# define EZTEST_ARCH_IS_AARCH64_ 0
#endif

#if EZTEST_ARCH_IS_AARCH64_ || EZTEST_ARCH_IS_ARM32_
# define EZTEST_ARCH_IS_ANY_ARM_ 1
#else
# define EZTEST_ARCH_IS_ANY_ARM_ 0
#endif

#if defined(__riscv) && (__riscv_xlen == 64)
# define EZTEST_ARCH_IS_RISCV64_ 1
#else
# define EZTEST_ARCH_IS_RISCV64_ 0
#endif

#if defined(__riscv) && (__riscv_xlen == 32)
# define EZTEST_ARCH_IS_RISCV32_ 1
#else
# define EZTEST_ARCH_IS_RISCV32_ 0
#endif

#if EZTEST_ARCH_IS_RISCV64_ || EZTEST_ARCH_IS_RISCV32_
# define EZTEST_ARCH_IS_ANY_RISCV_ 1
#else
# define EZTEST_ARCH_IS_ANY_RISCV_ 0
#endif

#if EZTEST_ARCH_IS_RISCV32_ || EZTEST_ARCH_IS_ARM32_ || EZTEST_ARCH_IS_X86_32_
# define EZTEST_WORD_SIZE_ 32
#else
# define EZTEST_WORD_SIZE_ 64
#endif

#endif
