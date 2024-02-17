#ifndef EZTEST_D_EZTEST_D_EZTEST_CXX_ASSERTS_IMPL_H_
#define EZTEST_D_EZTEST_D_EZTEST_CXX_ASSERTS_IMPL_H_

#if !EZTEST_CXX_LANG_
# error "CXX implementation included without CXX!"
#endif

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#if EZTEST_CXX_LANG_ >= 2017
# include <string_view>
#endif

#include <cstdarg>
#include <string>
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

EZTEST_NAMESPACE_BEGIN_

EZTEST_DISABLE_WTEMPLATES_
EZTEST_DISABLE_WUNUSED_TEMPLATE_
EZTEST_DISABLE_WUNUSED_MEMBER_FUNCTION_

class eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t & eztest_var) {
        return EZTEST_NS_ eztest_hex_print_var(
            EZTEST_REINTERPRET_CAST_(const uint8_t *, &eztest_var),
            /* NOLINTNEXTLINE(bugprone-sizeof-container) */
            sizeof(eztest_T_t));
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(bool eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var ? "true" : "false");
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(unsigned char eztest_var) {
        return EZTEST_PRINTF_("%hhu", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(unsigned short eztest_var) {
        return EZTEST_PRINTF_("%hu", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(unsigned int eztest_var) {
        return EZTEST_PRINTF_("%u", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(unsigned long eztest_var) {
        return EZTEST_PRINTF_("%lu", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(signed char eztest_var) {
        return EZTEST_PRINTF_("%hhd", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(signed short eztest_var) {
        return EZTEST_PRINTF_("%hd", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(signed int eztest_var) {
        return EZTEST_PRINTF_("%d", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(signed long eztest_var) {
        return EZTEST_PRINTF_("%ld", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(char eztest_var) {
        return EZTEST_PRINTF_("%c", eztest_var);
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(float eztest_var) {
        EZTEST_DISABLE_WDOUBLE_PROMOTION_
        return EZTEST_PRINTF_("%f", eztest_var);
        EZTEST_REENABLE_WDOUBLE_PROMOTION_
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(double eztest_var) {
        return EZTEST_PRINTF_("%lf", eztest_var);
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(long double eztest_var) {
        return EZTEST_PRINTF_("%Lf", eztest_var);
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(eztest_T_t * eztest_var) {
        return EZTEST_PRINTF_("%p", EZTEST_CAST_(void *, eztest_var));
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t * eztest_var) {
        return EZTEST_PRINTF_("%p", EZTEST_CAST_(const void *, eztest_var));
    }


    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const EZTEST_STD_NS_ string & eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var.c_str());
    }


#if EZTEST_CXX_LANG_ >= 2011
    EZTEST_DISABLE_WCXX98_COMPAT_
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(EZTEST_STD_NS_ nullptr_t) {
        return EZTEST_PRINTF_("%p", EZTEST_CAST_(void *, EZTEST_NULL_));
    }
    EZTEST_REENABLE_WCXX98_COMPAT_
    EZTEST_DISABLE_WCXX98_COMPAT_PEDANTIC_
    EZTEST_DISABLE_WLONG_LONG_

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(unsigned long long eztest_var) {
        return EZTEST_PRINTF_("%llu", eztest_var);
    }
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(signed long long eztest_var) {
        return EZTEST_PRINTF_("%lld", eztest_var);
    }

    EZTEST_REENABLE_WLONG_LONG_
    EZTEST_REENABLE_WCXX98_COMPAT_PEDANTIC_

#endif

#if EZTEST_CXX_LANG_ >= 2017
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(EZTEST_STD_NS_ string_view eztest_var) {
        if (eztest_var.length() >= INT_MAX) {
            return EZTEST_NS_ eztest_hex_print_var(
                EZTEST_REINTERPRET_CAST_(const uint8_t *, &eztest_var),
                /* NOLINTNEXTLINE(bugprone-sizeof-container) */
                sizeof(eztest_var));
        }
        return EZTEST_PRINTF_("%.*s", static_cast<int>(eztest_var.length()),
                              eztest_var.data());
    }
#endif
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_eq_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) == (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return eztest_op0 == eztest_op1;
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_ne_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) != (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return !EZTEST_NS_ eztest_cxx_binop_eq_t::eztest_cxx_run(eztest_op0,
                                                                 eztest_op1);
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};


class eztest_cxx_binop_gt_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) > (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return eztest_op0 > eztest_op1;
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};


class eztest_cxx_binop_lt_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) < (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return eztest_op0 < eztest_op1;
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_ge_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) >= (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return !EZTEST_NS_ eztest_cxx_binop_lt_t::eztest_cxx_run(eztest_op0,
                                                                 eztest_op1);
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};


class eztest_cxx_binop_le_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) <= (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        return !EZTEST_NS_ eztest_cxx_binop_gt_t::eztest_cxx_run(eztest_op0,
                                                                 eztest_op1);
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_streq_t : public EZTEST_NS_ eztest_cxx_print_var_t {

    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run_with_1length(const char *          eztest_op0,
                                EZTEST_STD_NS_ size_t eztest_op0_len,
                                const char *          eztest_op1) {
        if (eztest_op1 == EZTEST_NULL_) {
            return eztest_op0_len == 0;
        }
        if (EZTEST_STRLEN_(eztest_op1) != eztest_op0_len) {
            return false;
        }
        return EZTEST_MEMCMP_(eztest_op0, eztest_op1, eztest_op0_len) == 0;
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */

   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t & eztest_var) {
        return EZTEST_NS_ eztest_cxx_print_var_t::eztest_cxx_print_var(
            eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) eq (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char * eztest_op0, const char * eztest_op1) {
        if (eztest_op0 == EZTEST_NULL_) {
            return eztest_op1 == EZTEST_NULL_;
        }
        if (eztest_op1 == EZTEST_NULL_) {
            return false;
        }
        return EZTEST_STRCMP_(eztest_op0, eztest_op1) == 0;
    }
#if EZTEST_CXX_LANG_ >= 2017
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const char *                       eztest_op1) {
        return EZTEST_NS_ eztest_cxx_binop_streq_t::eztest_cxx_run_with_1length(
            eztest_op0.data(), eztest_op0.length(), eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char *                       eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_NS_ eztest_cxx_binop_streq_t::eztest_cxx_run_with_1length(
            eztest_op1.data(), eztest_op1.length(), eztest_op0);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_STD_NS_ operator==(eztest_op0, eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string &      eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_STD_NS_ operator==(EZTEST_STD_NS_ string_view(eztest_op0),
                                         eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const EZTEST_STD_NS_ string &      eztest_op1) {
        return EZTEST_STD_NS_ operator==(
            eztest_op0, EZTEST_STD_NS_ string_view(eztest_op1));
    }
#endif

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string & eztest_op0,
                   const char *                  eztest_op1) {
        return EZTEST_NS_ eztest_cxx_binop_streq_t::eztest_cxx_run_with_1length(
            eztest_op0.c_str(), eztest_op0.length(), eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char *                  eztest_op0,
                   const EZTEST_STD_NS_ string & eztest_op1) {
        return EZTEST_NS_ eztest_cxx_binop_streq_t::eztest_cxx_run_with_1length(
            eztest_op1.c_str(), eztest_op1.length(), eztest_op0);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string & eztest_op0,
                   const EZTEST_STD_NS_ string & eztest_op1) {
        return EZTEST_STD_NS_ operator==(eztest_op0, eztest_op1);
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_strne_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t & eztest_var) {
        return EZTEST_NS_ eztest_cxx_print_var_t::eztest_cxx_print_var(
            eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) ne (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
         */
        return !EZTEST_NS_ eztest_cxx_binop_streq_t ::eztest_cxx_run(
            eztest_op0, eztest_op1);
        /* NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
         */
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_strcaseeq_t : public EZTEST_NS_ eztest_cxx_print_var_t {

    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run_with_2length(const char *          eztest_op0,
                                EZTEST_STD_NS_ size_t eztest_op0_len,
                                const char *          eztest_op1,
                                EZTEST_STD_NS_ size_t eztest_op1_len) {
        if (eztest_op1_len != eztest_op0_len) {
            return false;
        }
        return EZTEST_STRNCASECMP_(eztest_op0, eztest_op1, eztest_op0_len) == 0;
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run_with_1length(const char *          eztest_op0,
                                EZTEST_STD_NS_ size_t eztest_op0_len,
                                const char *          eztest_op1) {
        if (eztest_op1 == EZTEST_NULL_) {
            return eztest_op0_len == 0;
        }

        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_2length(
                eztest_op0, eztest_op0_len, eztest_op1,
                EZTEST_STRLEN_(eztest_op1));
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */

   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t & eztest_var) {
        return EZTEST_NS_ eztest_cxx_print_var_t::eztest_cxx_print_var(
            eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) case-eq (%s)", eztest_op0_expr,
                              eztest_op1_expr);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char * eztest_op0, const char * eztest_op1) {
        if (eztest_op0 == EZTEST_NULL_) {
            return eztest_op1 == EZTEST_NULL_;
        }
        if (eztest_op1 == EZTEST_NULL_) {
            return false;
        }
        return EZTEST_STRCASECMP_(eztest_op0, eztest_op1) == 0;
    }
#if EZTEST_CXX_LANG_ >= 2017
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const char *                       eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_1length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char *                       eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_1length(
                eztest_op1.data(), eztest_op1.length(), eztest_op0);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_2length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1.data(),
                eztest_op1.length());
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string &      eztest_op0,
                   const EZTEST_STD_NS_ string_view & eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_2length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1.data(),
                eztest_op1.length());
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string_view & eztest_op0,
                   const EZTEST_STD_NS_ string &      eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_2length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1.data(),
                eztest_op1.length());
    }
#endif

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string & eztest_op0,
                   const char *                  eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_1length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const char *                  eztest_op0,
                   const EZTEST_STD_NS_ string & eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_1length(
                eztest_op1.data(), eztest_op1.length(), eztest_op0);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const EZTEST_STD_NS_ string & eztest_op0,
                   const EZTEST_STD_NS_ string & eztest_op1) {
        return EZTEST_NS_
            eztest_cxx_binop_strcaseeq_t::eztest_cxx_run_with_2length(
                eztest_op0.data(), eztest_op0.length(), eztest_op1.data(),
                eztest_op1.length());
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_strcasene_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(char * eztest_var) {
        return EZTEST_PRINTF_("%s", eztest_var);
    }

    template<typename eztest_T_t>
    EZTEST_PRIVATE_ int
    eztest_cxx_print_var(const eztest_T_t & eztest_var) {
        return EZTEST_NS_ eztest_cxx_print_var_t::eztest_cxx_print_var(
            eztest_var);
    }

    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) case-ne (%s)", eztest_op0_expr,
                              eztest_op1_expr);
    }

    template<typename eztest_T0_t, typename eztest_T1_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1) {
        /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
         */
        return !EZTEST_NS_ eztest_cxx_binop_strcaseeq_t ::eztest_cxx_run(
            eztest_op0, eztest_op1);
        /* NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
         */
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_flt_eq_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) != (%s)", eztest_op0_expr, eztest_op1_expr);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const float & eztest_op0, const float & eztest_op1) {
        return EZTEST_NS_ eztest_flt_compare(eztest_op0, eztest_op1) != 0;
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

class eztest_cxx_binop_dbl_eq_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr) {
        return EZTEST_PRINTF_("(%s) != (%s)", eztest_op0_expr, eztest_op1_expr);
    }


    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const double & eztest_op0, const double & eztest_op1) {
        return EZTEST_NS_ eztest_dbl_compare(eztest_op0, eztest_op1) != 0;
    }

    /* NOLINTEND(llvmlibc-inline-function-decl) */
};


class eztest_cxx_ternop_near_t : public EZTEST_NS_ eztest_cxx_print_var_t {
   public:
    /* NOLINTBEGIN(llvmlibc-inline-function-decl) */
    EZTEST_PRIVATE_ int
    eztest_cxx_print_op_desc(const char * eztest_op0_expr,
                             const char * eztest_op1_expr,
                             const char * eztest_op2_expr) {
        return EZTEST_PRINTF_("abs(%s - %s) < (%s)", eztest_op0_expr,
                              eztest_op1_expr, eztest_op2_expr);
    }

    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const double & eztest_op0,
                   const double & eztest_op1,
                   const double & eztest_op2) {
        return EZTEST_ABS_(eztest_op0 - eztest_op1) <= EZTEST_ABS_(eztest_op2);
    }

    template<typename eztest_T0_t, typename eztest_T1_t, typename eztest_T2_t>
    EZTEST_PRIVATE_CXX_INL_ bool
    eztest_cxx_run(const eztest_T0_t & eztest_op0,
                   const eztest_T1_t & eztest_op1,
                   const eztest_T2_t & eztest_op2) {
        return EZTEST_ABS_(eztest_op0 - eztest_op1) <= EZTEST_ABS_(eztest_op2);
    }
    /* NOLINTEND(llvmlibc-inline-function-decl) */
};

EZTEST_REENABLE_WUNUSED_MEMBER_FUNCTION_


EZTEST_PRIVATE_CXX_INL_ void
eztest_cxx_fail(int eztest_exit_on_failure) {
    EZTEST_NS_ eztest_cur_test_set_failed();
    if (eztest_exit_on_failure != 0) {
        (void)EZTEST_FFLUSH_(EZTEST_STDOUT_);
        EZTEST_EXIT_(1);
    }
}

EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_
/* NOLINTBEGIN(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_T0_t>
EZTEST_PRIVATE_
EZTEST_ATTR_FMT_(7,
                 8) void eztest_cxx_bool_assert(int eztest_exit_on_failure,
                                                int eztest_lineno,
                                                const char * eztest_file,
                                                const char * eztest_op0_expr,
                                                bool         eztest_expec,
                                                const eztest_T0_t & eztest_op0,
                                                const char *        eztest_fmt,
                                                ...) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTEND(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
    EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_
    if ((!eztest_op0) == eztest_expec) {
        (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: (%s) to be %s\n",
                             eztest_file, eztest_lineno, eztest_op0_expr,
                             eztest_expec ? "true" : "false");
        (void)EZTEST_PRINTF_("  Actual  : ");
        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        EZTEST_NS_ eztest_cxx_print_var_t::eztest_cxx_print_var(eztest_op0);
        /* NOLINTEND(llvmlibc-callee-namespace) */
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("  Expected: %s\n",
                             eztest_expec ? "true" : "false");
        if (eztest_fmt != EZTEST_NULL_) {
            /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg) */
            /* NOLINTBEGIN(hicpp-vararg) */
            /* NOLINTBEGIN(cppcoreguide*-pro-bounds-array-to-pointer-decay) */
            /* NOLINTBEGIN(hicpp-no-array-decay) */
            /* NOLINTBEGIN(cppcoreguidelines-init-variables) */
            EZTEST_STD_NS_ va_list eztest_ap;
            /* NOLINTEND(cppcoreguidelines-init-variables) */
            va_start(eztest_ap, eztest_fmt);
            (void)EZTEST_VFPRINTF_(EZTEST_STDOUT_, eztest_fmt, eztest_ap);
            va_end(eztest_ap);

            /* NOLINTEND(hicpp-no-array-decay) */
            /* NOLINTEND(cppcoreguide*-pro-bounds-array-to-pointer-decay) */
            /* NOLINTEND(hicpp-vararg) */
            /* NOLINTEND(cppcoreguidelines-pro-type-vararg) */
        }
        EZTEST_NS_ eztest_cxx_fail(eztest_exit_on_failure);
    }
}

/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_T0_t>
EZTEST_PRIVATE_CXX_INL_ void
eztest_cxx_bool_assert(int                 eztest_exit_on_failure,
                       int                 eztest_lineno,
                       const char *        eztest_file,
                       const char *        eztest_op0_expr,
                       bool                eztest_expec,
                       const eztest_T0_t & eztest_op0) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    EZTEST_NS_ eztest_cxx_bool_assert(eztest_exit_on_failure, eztest_lineno,
                                      eztest_file, eztest_op0_expr,
                                      eztest_expec, eztest_op0, EZTEST_NULL_);
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}

EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_
/* NOLINTBEGIN(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_cxx_binop_t,
         typename eztest_T0_t,
         typename eztest_T1_t>
EZTEST_PRIVATE_
EZTEST_ATTR_FMT_(8,
                 9) void eztest_cxx_binop_assert(int eztest_exit_on_failure,
                                                 int eztest_lineno,
                                                 const char * eztest_file,
                                                 const char * eztest_op0_expr,
                                                 const char * eztest_op1_expr,
                                                 const eztest_T0_t & eztest_op0,
                                                 const eztest_T1_t & eztest_op1,
                                                 const char *        eztest_fmt,
                                                 ...) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTEND(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
    EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_
    /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay) */
    /* NOLINTBEGIN(hicpp-no-array-decay) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    if (!eztest_cxx_binop_t::eztest_cxx_run(eztest_op0, eztest_op1)) {
        (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: ", eztest_file,
                             eztest_lineno);
        (void)eztest_cxx_binop_t::eztest_cxx_print_op_desc(eztest_op0_expr,
                                                           eztest_op1_expr);
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("   Op0: ");
        eztest_cxx_binop_t::eztest_cxx_print_var(eztest_op0);
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("   Op1: ");
        eztest_cxx_binop_t::eztest_cxx_print_var(eztest_op1);
        /* NOLINTEND(llvmlibc-callee-namespace) */
        (void)EZTEST_PRINTF_("\n");
        if (eztest_fmt != EZTEST_NULL_) {
            /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg) */
            /* NOLINTBEGIN(hicpp-vararg) */
            /* NOLINTBEGIN(cppcoreguidelines-init-variables) */
            EZTEST_STD_NS_ va_list eztest_ap;
            /* NOLINTEND(cppcoreguidelines-init-variables) */
            va_start(eztest_ap, eztest_fmt);
            (void)EZTEST_VFPRINTF_(EZTEST_STDOUT_, eztest_fmt, eztest_ap);
            va_end(eztest_ap);
            /* NOLINTEND(hicpp-vararg) */
            /* NOLINTEND(cppcoreguidelines-pro-type-vararg) */
        }
        EZTEST_NS_ eztest_cxx_fail(eztest_exit_on_failure);
    }
    /* NOLINTEND(hicpp-no-array-decay) */
    /* NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay) */
}
/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_cxx_binop_t,
         typename eztest_T0_t,
         typename eztest_T1_t>
EZTEST_PRIVATE_CXX_INL_ void
eztest_cxx_binop_assert(int                 eztest_exit_on_failure,
                        int                 eztest_lineno,
                        const char *        eztest_file,
                        const char *        eztest_op0_expr,
                        const char *        eztest_op1_expr,
                        const eztest_T0_t & eztest_op0,
                        const eztest_T1_t & eztest_op1) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    EZTEST_NS_ eztest_cxx_binop_assert<eztest_cxx_binop_t>(
        eztest_exit_on_failure, eztest_lineno, eztest_file, eztest_op0_expr,
        eztest_op1_expr, eztest_op0, eztest_op1, EZTEST_NULL_);
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}


EZTEST_DISABLE_GCC7_GCC8_UBSAN_WPADDED_
/* NOLINTBEGIN(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_cxx_ternop_t,
         typename eztest_T0_t,
         typename eztest_T1_t,
         typename eztest_T2_t>
EZTEST_PRIVATE_
EZTEST_ATTR_FMT_(10, 11) void eztest_cxx_ternop_assert(
    int                 eztest_exit_on_failure,
    int                 eztest_lineno,
    const char *        eztest_file,
    const char *        eztest_op0_expr,
    const char *        eztest_op1_expr,
    const char *        eztest_op2_expr,
    const eztest_T0_t & eztest_op0,
    const eztest_T1_t & eztest_op1,
    const eztest_T2_t & eztest_op2,
    const char *        eztest_fmt,
    ...) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTEND(cert-dcl50-cpp,bugprone-easily-swappable-parameters) */
    EZTEST_REENABLE_GCC7_GCC8_UBSAN_WPADDED_
    /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay) */
    /* NOLINTBEGIN(hicpp-no-array-decay) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    if (!eztest_cxx_ternop_t::eztest_cxx_run(eztest_op0, eztest_op1,
                                             eztest_op2)) {
        (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: ", eztest_file,
                             eztest_lineno);
        (void)eztest_cxx_ternop_t::eztest_cxx_print_op_desc(
            eztest_op0_expr, eztest_op1_expr, eztest_op2_expr);
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("   Arg0: ");
        eztest_cxx_ternop_t::eztest_cxx_print_var(eztest_op0);
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("   Arg1: ");
        eztest_cxx_ternop_t::eztest_cxx_print_var(eztest_op1);
        (void)EZTEST_PRINTF_("\n");
        (void)EZTEST_PRINTF_("   Arg2: ");
        eztest_cxx_ternop_t::eztest_cxx_print_var(eztest_op2);
        /* NOLINTEND(llvmlibc-callee-namespace) */
        (void)EZTEST_PRINTF_("\n");
        if (eztest_fmt != EZTEST_NULL_) {
            /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg) */
            /* NOLINTBEGIN(hicpp-vararg) */
            /* NOLINTBEGIN(cppcoreguidelines-init-variables) */
            EZTEST_STD_NS_ va_list eztest_ap;
            /* NOLINTEND(cppcoreguidelines-init-variables) */
            va_start(eztest_ap, eztest_fmt);
            (void)EZTEST_VFPRINTF_(EZTEST_STDOUT_, eztest_fmt, eztest_ap);
            va_end(eztest_ap);
            /* NOLINTEND(hicpp-vararg) */
            /* NOLINTEND(cppcoreguidelines-pro-type-vararg) */
        }
        EZTEST_NS_ eztest_cxx_fail(eztest_exit_on_failure);
    }
    /* NOLINTEND(hicpp-no-array-decay) */
    /* NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay) */
}

/* NOLINTBEGIN(llvmlibc-inline-function-decl) */
template<typename eztest_cxx_ternop_t,
         typename eztest_T0_t,
         typename eztest_T1_t,
         typename eztest_T2_t>
EZTEST_PRIVATE_CXX_INL_ void
eztest_cxx_ternop_assert(int                 eztest_exit_on_failure,
                         int                 eztest_lineno,
                         const char *        eztest_file,
                         const char *        eztest_op0_expr,
                         const char *        eztest_op1_expr,
                         const char *        eztest_op2_expr,
                         const eztest_T0_t & eztest_op0,
                         const eztest_T1_t & eztest_op1,
                         const eztest_T2_t & eztest_op2) {
    /* NOLINTEND(llvmlibc-inline-function-decl) */
    /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
    EZTEST_NS_ eztest_cxx_ternop_assert<eztest_cxx_ternop_t>(
        eztest_exit_on_failure, eztest_lineno, eztest_file, eztest_op0_expr,
        eztest_op1_expr, eztest_op2_expr, eztest_op0, eztest_op1, eztest_op2,
        EZTEST_NULL_);
    /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
}


EZTEST_REENABLE_WUNUSED_TEMPLATE_
EZTEST_REENABLE_WTEMPLATES_

EZTEST_NAMESPACE_END_

EZTEST_DISABLE_WCXX98_COMPAT_PEDANTIC_
EZTEST_DISABLE_WVARIADIC_MACROS_

#define EZTEST_GET_TERNOP_EXPRESSIONS_IMPL_(expr0, expr1, expr2, ...)          \
 EZTEST_STRINGIFY_(expr0), EZTEST_STRINGIFY_(expr1), EZTEST_STRINGIFY_(expr2)
#define EZTEST_GET_TERNOP_EXPRESSIONS_(...)                                    \
 EZTEST_GET_TERNOP_EXPRESSIONS_IMPL_(__VA_ARGS__, eztest0, eztest1, eztest2,   \
                                     eztest3)

#define EZTEST_GET_BINOP_EXPRESSIONS_IMPL_(expr0, expr1, ...)                  \
 EZTEST_STRINGIFY_(expr0), EZTEST_STRINGIFY_(expr1)
#define EZTEST_GET_BINOP_EXPRESSIONS_(...)                                     \
 EZTEST_GET_BINOP_EXPRESSIONS_IMPL_(__VA_ARGS__, eztest0, eztest1, eztest2)

#define EZTEST_GET_BOOL_EXPRESSIONS_IMPL_(expr0, ...) EZTEST_STRINGIFY_(expr0)
#define EZTEST_GET_BOOL_EXPRESSIONS_(...)                                      \
 EZTEST_GET_BOOL_EXPRESSIONS_IMPL_(__VA_ARGS__, eztest0, eztest1)

#define EZTEST_ASSERT_BOOL_IMPL_(exit_on_fail, expec, ...)                     \
 EZTEST_NS_ eztest_cxx_bool_assert(exit_on_fail, EZTEST_LINE_, EZTEST_FILE_,   \
                                   EZTEST_GET_BOOL_EXPRESSIONS_(__VA_ARGS__),  \
                                   expec, __VA_ARGS__)


#define EZTEST_ASSERT_BINOP_IMPL_(exit_on_fail, binop_t, ...)                  \
 EZTEST_NS_ eztest_cxx_binop_assert<EZTEST_NS_ binop_t>(                       \
     exit_on_fail, EZTEST_LINE_, EZTEST_FILE_,                                 \
     EZTEST_GET_BINOP_EXPRESSIONS_(__VA_ARGS__), __VA_ARGS__)

#define EZTEST_ASSERT_TERNOP_IMPL_(exit_on_fail, ternop_t, ...)                \
 EZTEST_NS_ eztest_cxx_ternop_assert<EZTEST_NS_ ternop_t>(                     \
     exit_on_fail, EZTEST_LINE_, EZTEST_FILE_,                                 \
     EZTEST_GET_TERNOP_EXPRESSIONS_(__VA_ARGS__), __VA_ARGS__)

#define EZTEST_ASSERT_TRUE_IMPL_(...)                                          \
 EZTEST_ASSERT_BOOL_IMPL_(1, true, __VA_ARGS__)
#define EZTEST_ASSERT_FALSE_IMPL_(...)                                         \
 EZTEST_ASSERT_BOOL_IMPL_(1, false, __VA_ARGS__)
#define EZTEST_ASSERT_EQ_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_eq_t, __VA_ARGS__)
#define EZTEST_ASSERT_NE_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_ne_t, __VA_ARGS__)
#define EZTEST_ASSERT_LE_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_le_t, __VA_ARGS__)
#define EZTEST_ASSERT_LT_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_lt_t, __VA_ARGS__)
#define EZTEST_ASSERT_GE_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_ge_t, __VA_ARGS__)
#define EZTEST_ASSERT_GT_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_gt_t, __VA_ARGS__)
#define EZTEST_ASSERT_STREQ_IMPL_(...)                                         \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_streq_t, __VA_ARGS__)
#define EZTEST_ASSERT_STRNE_IMPL_(...)                                         \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_strne_t, __VA_ARGS__)
#define EZTEST_ASSERT_STRCASEEQ_IMPL_(...)                                     \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_strcaseeq_t, __VA_ARGS__)
#define EZTEST_ASSERT_STRCASENE_IMPL_(...)                                     \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_strcasene_t, __VA_ARGS__)
#define EZTEST_ASSERT_FLOAT_EQ_IMPL_(...)                                      \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_flt_eq_t, __VA_ARGS__)
#define EZTEST_ASSERT_DOUBLE_EQ_IMPL_(...)                                     \
 EZTEST_ASSERT_BINOP_IMPL_(1, eztest_cxx_binop_dbl_eq_t, __VA_ARGS__)
#define EZTEST_ASSERT_NEAR_IMPL_(...)                                          \
 EZTEST_ASSERT_TERNOP_IMPL_(1, eztest_cxx_ternop_near_t, __VA_ARGS__)

#define EZTEST_EXPECT_TRUE_IMPL_(...)                                          \
 EZTEST_ASSERT_BOOL_IMPL_(0, true, __VA_ARGS__)
#define EZTEST_EXPECT_FALSE_IMPL_(...)                                         \
 EZTEST_ASSERT_BOOL_IMPL_(0, false, __VA_ARGS__)
#define EZTEST_EXPECT_EQ_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_eq_t, __VA_ARGS__)
#define EZTEST_EXPECT_NE_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_ne_t, __VA_ARGS__)
#define EZTEST_EXPECT_LE_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_le_t, __VA_ARGS__)
#define EZTEST_EXPECT_LT_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_lt_t, __VA_ARGS__)
#define EZTEST_EXPECT_GE_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_ge_t, __VA_ARGS__)
#define EZTEST_EXPECT_GT_IMPL_(...)                                            \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_gt_t, __VA_ARGS__)
#define EZTEST_EXPECT_STREQ_IMPL_(...)                                         \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_streq_t, __VA_ARGS__)
#define EZTEST_EXPECT_STRNE_IMPL_(...)                                         \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_strne_t, __VA_ARGS__)
#define EZTEST_EXPECT_STRCASEEQ_IMPL_(...)                                     \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_strcaseeq_t, __VA_ARGS__)
#define EZTEST_EXPECT_STRCASENE_IMPL_(...)                                     \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_strcasene_t, __VA_ARGS__)
#define EZTEST_EXPECT_FLOAT_EQ_IMPL_(...)                                      \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_flt_eq_t, __VA_ARGS__)
#define EZTEST_EXPECT_DOUBLE_EQ_IMPL_(...)                                     \
 EZTEST_ASSERT_BINOP_IMPL_(0, eztest_cxx_binop_dbl_eq_t, __VA_ARGS__)
#define EZTEST_EXPECT_NEAR_IMPL_(...)                                          \
 EZTEST_ASSERT_TERNOP_IMPL_(0, eztest_cxx_ternop_near_t, __VA_ARGS__)


EZTEST_REENABLE_WCXX98_COMPAT_PEDANTIC_
EZTEST_REENABLE_WVARIADIC_MACROS_
#endif
