#include <stdio.h>

#ifdef __cplusplus
# if __cplusplus == 199711L
#  define CONFIG_CXX_LANG 1998
# elif __cplusplus == 201103L
#  define CONFIG_CXX_LANG 2011
# elif __cplusplus == 201402L
#  define CONFIG_CXX_LANG 2014
# elif __cplusplus == 201703L
#  define CONFIG_CXX_LANG 2017
# elif __cplusplus == 202002L
#  define CONFIG_CXX_LANG 2020
# elif __cplusplus >= 202101L
#  define CONFIG_CXX_LANG 2023
# else
#  define CONFIG_CXX_LANG 1
# endif
# define CONFIG_C_LANG 0
#elif defined(__STDC__)
# if defined(__STDC_VERSION__)
#  if (__STDC_VERSION__ >= 202311L)
#   define CONFIG_C_LANG 2023
#  elif (__STDC_VERSION__ >= 201710L)
#   define CONFIG_C_LANG 2017
#  elif (__STDC_VERSION__ >= 201112L)
#   define CONFIG_C_LANG 2011
#  elif (__STDC_VERSION__ >= 199901L)
#   define CONFIG_C_LANG 1999
#  elif (__STDC_VERSION__ >= 199409L)
#   define CONFIG_C_LANG 1994
#  else
#   define CONFIG_C_LANG 1990
#  endif
# else
#  define CONFIG_C_LANG 1989
# endif
# define CONFIG_CXX_LANG 0
#endif

