#ifndef EZTEST_D_EZTEST_D_EZTEST_LANG_BITS_H_
#define EZTEST_D_EZTEST_D_EZTEST_LANG_BITS_H_


#ifdef __cplusplus
# define EZTEST_C_VER_DEF_ 0
# if __cplusplus != 0
#  define EZTEST_CXX_VER_DEF_ (__cplusplus)
# else
#  define EZTEST_CXX_VER_DEF_ 1
# endif
# define EZTEST_C_LANG_ 0

#else
# define EZTEST_CXX_VER_DEF_ 0
# if (defined __STDC_VERSION__) && (__STDC_VERSION__ != 0)
#  define EZTEST_C_VER_DEF_ (__STDC_VERSION__)
# else
#  define EZTEST_C_VER_DEF_ 1
# endif
# define EZTEST_CXX_LANG_ 0
#endif

#if EZTEST_CXX_VER_DEF_ >= 202101L
# define EZTEST_CXX_LANG_ 2023
#endif
#if EZTEST_CXX_VER_DEF_ == 202002L
# define EZTEST_CXX_LANG_ 2020
#endif
#if EZTEST_CXX_VER_DEF_ == 201703L
# define EZTEST_CXX_LANG_ 2017
#endif
#if EZTEST_CXX_VER_DEF_ == 201402L
# define EZTEST_CXX_LANG_ 2014
#endif
#if EZTEST_CXX_VER_DEF_ == 201103L
# define EZTEST_CXX_LANG_ 2011
#endif
#if (!defined EZTEST_CXX_LANG_) && EZTEST_CXX_VER_DEF_ >= 201103L
# define EZTEST_CXX_LANG_ 2011
#endif
#if EZTEST_CXX_VER_DEF_ == 199711L
# define EZTEST_CXX_LANG_ 1998
#endif
#if EZTEST_CXX_VER_DEF_ > 0 && EZTEST_CXX_VER_DEF_ < 199711L
# define EZTEST_CXX_LANG_ 1
#endif
#if EZTEST_C_VER_DEF_ >= 202311L
# define EZTEST_C_LANG_ 2023
#endif
#if EZTEST_C_VER_DEF_ == 201710L
# define EZTEST_C_LANG_ 2017
#endif
#if EZTEST_C_VER_DEF_ == 201112L
# define EZTEST_C_LANG_ 2011
#endif
#if EZTEST_C_VER_DEF_ == 199901L
# define EZTEST_C_LANG_ 1999
#endif
#if (!defined EZTEST_C_LANG_) && EZTEST_C_VER_DEF_ >= 199901L
# define EZTEST_C_LANG_ 1999
#endif

#if EZTEST_C_VER_DEF_ == 199409L
# define EZTEST_C_LANG_ 1994
#endif
#if EZTEST_C_VER_DEF_ > 0 && EZTEST_C_VER_DEF_ < 199409L
# define EZTEST_C_LANG_ 1
#endif


#if !EZTEST_C_LANG_ && !EZTEST_CXX_LANG_
# error "Unable to determing C/CXX standard"
#endif
#if EZTEST_C_LANG_ && EZTEST_CXX_LANG_
# error "Somehow found both C/CXX enabled"
#endif

#endif
