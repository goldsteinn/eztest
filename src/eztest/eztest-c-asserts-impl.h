#ifndef EZTEST_D_EZTEST_D_EZTEST_C_ASSERTS_IMPL_H_
#define EZTEST_D_EZTEST_D_EZTEST_C_ASSERTS_IMPL_H_ 1

#if !EZTEST_C_LANG_
# error "C implementation included without C!"
#endif


#if EZTEST_C_LANG_ >= 2011 && (EZTEST_C_PRINT_ARGS)
# define EZTEST_C11_DISABLE_WLONG_LONG_      EZTEST_DISABLE_WLONG_LONG_
# define EZTEST_C11_DISABLE_WC99_COMPAT_     EZTEST_DISABLE_WC99_COMPAT_
# define EZTEST_C11_DISABLE_WC99_C11_COMPAT_ EZTEST_DISABLE_WC99_C11_COMPAT_
# define EZTEST_C11_DISABLE_WC90_C99_COMPAT_ EZTEST_DISABLE_WC90_C99_COMPAT_
# define EZTEST_C11_DISABLE_WC11_EXTENSIONS_ EZTEST_DISABLE_WC11_EXTENSIONS_
# define EZTEST_C11_DISABLE_WPRE_C11_COMPAT_ EZTEST_DISABLE_WPRE_C11_COMPAT_

# define EZTEST_C11_REENABLE_WLONG_LONG_      EZTEST_REENABLE_WLONG_LONG_
# define EZTEST_C11_REENABLE_WC99_C11_COMPAT_ EZTEST_REENABLE_WC99_C11_COMPAT_
# define EZTEST_C11_REENABLE_WC90_C99_COMPAT_ EZTEST_REENABLE_WC90_C99_COMPAT_
# define EZTEST_C11_REENABLE_WC99_COMPAT_     EZTEST_REENABLE_WC99_COMPAT_
# define EZTEST_C11_REENABLE_WC11_EXTENSIONS_ EZTEST_REENABLE_WC11_EXTENSIONS_
# define EZTEST_C11_REENABLE_WPRE_C11_COMPAT_ EZTEST_REENABLE_WPRE_C11_COMPAT_

/* clang-format off */
#define EZTEST_C_GET_VAR_FMT_SPECIFIER_(var)    \
    _Generic((var),                             \
             _Bool : "%d",                      \
             unsigned char : "%hhu",            \
             unsigned short : "%hu",            \
             unsigned int : "%u",               \
             unsigned long : "%lu",             \
             unsigned long long : "%llu",       \
             signed char : "%hhd",              \
             signed short : "%hd",              \
             signed int : "%d",                 \
             signed long : "%ld",               \
             signed long long : "%lld",         \
             char : "%c",                       \
             long double : "%Lf",               \
             double : "%lf",                    \
             float : "%f",                      \
             void * :"%p",                      \
             const void * :"%p",                \
             _Bool * : "%p",                    \
             const _Bool * : "%p",              \
             unsigned char * : "%p",            \
             const unsigned char * : "%p",      \
             unsigned short * : "%p",           \
             const unsigned short * : "%p",     \
             unsigned int * : "%p",             \
             const unsigned int * : "%p",       \
             unsigned long * : "%p",            \
             const unsigned long * : "%p",      \
             unsigned long long * : "%p",       \
             const unsigned long long * : "%p", \
             signed char * : "%p",              \
             const signed char * : "%p",        \
             signed short * : "%p",             \
             const signed short * : "%p",       \
             signed int * : "%p",               \
             const signed int * : "%p",         \
             signed long * : "%p",              \
             const signed long * : "%p",        \
             signed long long * : "%p",         \
             const signed long long * : "%p",   \
             char * : "%p",                     \
             const char * : "%p",               \
             long double * : "%p",              \
             const long double * : "%p",        \
             double * : "%p",                   \
             const double * : "%p",             \
             float * : "%p",                    \
             const float * : "%p",              \
             default : EZTEST_NULL_)


#define EZTEST_C_DO_PRINT_VAR_(fmt, var)                                \
    _Generic((var),                                                     \
             default : EZTEST_PRINTF_((fmt), (var)))

/* clang-format on */
#else
# define EZTEST_C11_DISABLE_WLONG_LONG_
# define EZTEST_C11_REENABLE_WLONG_LONG_

# define EZTEST_C_GET_VAR_FMT_SPECIFIER_(var) EZTEST_NULL_
# define EZTEST_C_DO_PRINT_VAR_(fmt, var)     0
#endif

#define EZTEST_C_PRINT_VAR_IMPL_(var, tmpvar)                                  \
 do {                                                                          \
  EZTEST_C11_DISABLE_WLONG_LONG_                                               \
  EZTEST_C11_DISABLE_WC99_C11_COMPAT_                                          \
  EZTEST_C11_DISABLE_WC90_C99_COMPAT_                                          \
  EZTEST_C11_DISABLE_WPRE_C11_COMPAT_                                          \
  /* NOLINTBEGIN(bugprone-macro-parentheses) */                                \
  const char * tmpvar = EZTEST_C_GET_VAR_FMT_SPECIFIER_(var);                  \
  /* NOLINTEND(bugprone-macro-parentheses) */                                  \
  EZTEST_C11_REENABLE_WPRE_C11_COMPAT_                                         \
  EZTEST_C11_REENABLE_WC90_C99_COMPAT_                                         \
  EZTEST_C11_REENABLE_WC99_C11_COMPAT_                                         \
  EZTEST_C11_REENABLE_WLONG_LONG_                                              \
  if ((tmpvar) != EZTEST_NULL_) {                                              \
   EZTEST_C11_DISABLE_WC99_C11_COMPAT_                                         \
   EZTEST_C11_DISABLE_WC90_C99_COMPAT_                                         \
   EZTEST_C11_DISABLE_WPRE_C11_COMPAT_                                         \
   EZTEST_DISABLE_WFORMAT_NONLITERAL_(void)                                    \
   EZTEST_C_DO_PRINT_VAR_((tmpvar), (var));                                    \
   EZTEST_REENABLE_WFORMAT_NONLITERAL_                                         \
   EZTEST_C11_REENABLE_WPRE_C11_COMPAT_                                        \
   EZTEST_C11_REENABLE_WC90_C99_COMPAT_                                        \
   EZTEST_C11_REENABLE_WC99_C11_COMPAT_                                        \
  }                                                                            \
  else {                                                                       \
   (void)EZTEST_NS_ eztest_hex_print_var(                                      \
       EZTEST_CAST_(const uint8_t *, &(var)), sizeof(var));                    \
  }                                                                            \
 } while (0)


#define EZTEST_C_PRINT_VAR_(var)                                               \
 EZTEST_C_PRINT_VAR_IMPL_(var, EZTEST_UNIQUE_NAME_(eztest_var_fmt_tmp_))

#define EZTEST_C_PRINT_STR_(var) (void)EZTEST_PRINTF_("%s", var);


#define EZTEST_C_ASSERT_PRINT_BOOL_HDR_(expec_str, expr_op0_str)               \
 (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: (%s) to be %s\n",              \
                      EZTEST_FILE_, EZTEST_LINE_, expr_op0_str, expec_str);

#define EZTEST_C_ASSERT_PRINT_BINOP_HDR_(op_fmt, expr_op0_str, expr_op1_str)   \
 (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: " op_fmt "\n", EZTEST_FILE_,   \
                      EZTEST_LINE_, expr_op0_str, expr_op1_str);

#define EZTEST_C_ASSERT_PRINT_TERNOP_HDR_(op_fmt, expr_op0_str, expr_op1_str,  \
                                          expr_op2_str)                        \
 (void)EZTEST_PRINTF_("%s:%d Failure\nExpected: " op_fmt "\n", EZTEST_FILE_,   \
                      EZTEST_LINE_, expr_op0_str, expr_op1_str, expr_op2_str);

#define EZTEST_C_ASSERT_PRINT_BOOL_(expec_str, expr_op0_str, expr_op0_var)     \
 EZTEST_C_ASSERT_PRINT_BOOL_HDR_(expec_str, expr_op0_str);                     \
 (void)EZTEST_PRINTF_("  Actual  : ");                                         \
 EZTEST_C_PRINT_VAR_(expr_op0_var);                                            \
 (void)EZTEST_PRINTF_("\n");                                                   \
 (void)EZTEST_PRINTF_("  Expected: %s", expec_str);                            \
 (void)EZTEST_PRINTF_("\n");

#define EZTEST_C_ASSERT_PRINT_BINOP_(op_fmt, expr_op0_str, expr_op1_str,       \
                                     expr_op0_var, expr_op1_var)               \
 EZTEST_C_ASSERT_PRINT_BINOP_HDR_(op_fmt, expr_op0_str, expr_op1_str);         \
 (void)EZTEST_PRINTF_("  Lhs: ");                                              \
 EZTEST_C_PRINT_VAR_(expr_op0_var);                                            \
 (void)EZTEST_PRINTF_("\n");                                                   \
 (void)EZTEST_PRINTF_("  Rhs: ");                                              \
 EZTEST_C_PRINT_VAR_(expr_op1_var);                                            \
 (void)EZTEST_PRINTF_("\n");

#define EZTEST_C_ASSERT_PRINT_TERNOP_(op_fmt, expr_op0_str, expr_op1_str,      \
                                      expr_op2_str, expr_op0_var,              \
                                      expr_op1_var, expr_op2_var)              \
 EZTEST_C_ASSERT_PRINT_TERNOP_HDR_(op_fmt, expr_op0_str, expr_op1_str,         \
                                   expr_op2_str);                              \
 (void)EZTEST_PRINTF_("  Arg0: ");                                             \
 EZTEST_C_PRINT_VAR_(expr_op0_var);                                            \
 (void)EZTEST_PRINTF_("\n");                                                   \
 (void)EZTEST_PRINTF_("  Arg1: ");                                             \
 EZTEST_C_PRINT_VAR_(expr_op1_var);                                            \
 (void)EZTEST_PRINTF_("\n");                                                   \
 (void)EZTEST_PRINTF_("  Arg2: ");                                             \
 EZTEST_C_PRINT_VAR_(expr_op2_var);                                            \
 (void)EZTEST_PRINTF_("\n");

#define EZTEST_C_ASSERT_PRINT_STR_(op_fmt, expr_op0_str, expr_op1_str,         \
                                   expr_op0_var, expr_op1_var)                 \
 EZTEST_C_ASSERT_PRINT_BINOP_HDR_(op_fmt, expr_op0_str, expr_op1_str);         \
 (void)EZTEST_PRINTF_("  Lhs: ");                                              \
 EZTEST_C_PRINT_STR_(expr_op0_var);                                            \
 (void)EZTEST_PRINTF_("\n");                                                   \
 (void)EZTEST_PRINTF_("  Rhs: ");                                              \
 EZTEST_C_PRINT_STR_(expr_op1_var);                                            \
 (void)EZTEST_PRINTF_("\n");


#if (defined EZTEST_AUTO_) && EZTEST_C_LANG_ >= 2011 && (EZTEST_C_PRINT_ARGS)
# define EZTEST_C_ASSERT_BOOL_(fail_on_err, expec, expr_op0, ...)              \
  do {                                                                         \
   const EZTEST_AUTO_(expr_op0) eztest_expr_op0_tmp_ = expr_op0;               \
   if (EZTEST_C_ASSERT_CHECK_BOOL_(expec, eztest_expr_op0_tmp_)) {             \
    EZTEST_C_ASSERT_PRINT_BOOL_((expec) ? "true" : "false",                    \
                                EZTEST_STRINGIFY_(expr_op0),                   \
                                eztest_expr_op0_tmp_);                         \
    EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                           \
   }                                                                           \
  } while (0)


# define EZTEST_C_ASSERT_BINOP_(fail_on_err, op, op_fmt, expr_op0, expr_op1,   \
                                ...)                                           \
  do {                                                                         \
   const EZTEST_AUTO_(expr_op0) eztest_expr_op0_tmp_ = expr_op0;               \
   const EZTEST_AUTO_(expr_op1) eztest_expr_op1_tmp_ = expr_op1;               \
   if (EZTEST_C_ASSERT_CHECK_BINOP_(op, eztest_expr_op0_tmp_,                  \
                                    eztest_expr_op1_tmp_)) {                   \
    EZTEST_C_ASSERT_PRINT_BINOP_(op_fmt, EZTEST_STRINGIFY_(expr_op0),          \
                                 EZTEST_STRINGIFY_(expr_op1),                  \
                                 eztest_expr_op0_tmp_, eztest_expr_op1_tmp_);  \
    EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                           \
   }                                                                           \
  } while (0)


# define EZTEST_C_ASSERT_TERNOP_(fail_on_err, op, op_fmt, expr_op0, expr_op1,  \
                                 expr_op2, ...)                                \
  do {                                                                         \
   const EZTEST_AUTO_(expr_op0) eztest_expr_op0_tmp_ = expr_op0;               \
   const EZTEST_AUTO_(expr_op1) eztest_expr_op1_tmp_ = expr_op1;               \
   const EZTEST_AUTO_(expr_op2) eztest_expr_op2_tmp_ = expr_op2;               \
   if (EZTEST_C_ASSERT_CHECK_TERNOP_(op, eztest_expr_op0_tmp_,                 \
                                     eztest_expr_op1_tmp_,                     \
                                     eztest_expr_op2_tmp_)) {                  \
    EZTEST_C_ASSERT_PRINT_TERNOP_(                                             \
        op_fmt, EZTEST_STRINGIFY_(expr_op0), EZTEST_STRINGIFY_(expr_op1),      \
        EZTEST_STRINGIFY_(expr_op2), eztest_expr_op0_tmp_,                     \
        eztest_expr_op1_tmp_, eztest_expr_op2_tmp_);                           \
    EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                           \
   }                                                                           \
  } while (0)

# define EZTEST_C_ASSERT_STR_(fail_on_err, op, op_fmt, expr_op0, expr_op1,     \
                              ...)                                             \
  do {                                                                         \
   const EZTEST_AUTO_(expr_op0) eztest_expr_op0_tmp_ = expr_op0;               \
   const EZTEST_AUTO_(expr_op1) eztest_expr_op1_tmp_ = expr_op1;               \
   if (EZTEST_C_ASSERT_CHECK_BINOP_(op, eztest_expr_op0_tmp_,                  \
                                    eztest_expr_op1_tmp_)) {                   \
    EZTEST_C_ASSERT_PRINT_STR_(op_fmt, EZTEST_STRINGIFY_(expr_op0),            \
                               EZTEST_STRINGIFY_(expr_op1),                    \
                               eztest_expr_op0_tmp_, eztest_expr_op1_tmp_);    \
    EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                           \
   }                                                                           \
  } while (0)


#else
# define EZTEST_C_ASSERT_BOOL_(fail_on_err, expec, expr, ...)                  \
  do {                                                                         \
   if (EZTEST_C_ASSERT_CHECK_BOOL_(expec, expr)) {                             \
    EZTEST_C_ASSERT_PRINT_BOOL_HDR_((expec) ? "true" : "false",                \
                                    EZTEST_STRINGIFY_(expr));                  \
    EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                           \
   }                                                                           \
  } while (0)

# define EZTEST_C_ASSERT_BINOP_(fail_on_err, op, op_fmt, expr_op0, expr_op1,   \
                                ...)                                           \
  do {                                                                         \
   if (EZTEST_C_ASSERT_CHECK_BINOP_(op, expr_op0, expr_op1)) {                 \
    EZTEST_C_ASSERT_PRINT_BINOP_HDR_(op_fmt, EZTEST_STRINGIFY_(expr_op0),      \
                                     EZTEST_STRINGIFY_(expr_op1));             \
    EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                           \
   }                                                                           \
  } while (0)


# define EZTEST_C_ASSERT_TERNOP_(fail_on_err, op, op_fmt, expr_op0, expr_op1,  \
                                 expr_op2, ...)                                \
  do {                                                                         \
   if (EZTEST_C_ASSERT_CHECK_TERNOP_(op, expr_op0, expr_op1, expr_op2)) {      \
    EZTEST_C_ASSERT_PRINT_TERNOP_HDR_(op_fmt, EZTEST_STRINGIFY_(expr_op0),     \
                                      EZTEST_STRINGIFY_(expr_op1),             \
                                      EZTEST_STRINGIFY_(expr_op2));            \
    EZTEST_C_ASSERT_FAIL_(fail_on_err, __VA_ARGS__);                           \
   }                                                                           \
  } while (0)

# define EZTEST_C_ASSERT_STR_(fail_on_err, op, op_fmt, expr_op0, expr_op1,     \
                              ...)                                             \
  EZTEST_C_ASSERT_BINOP_(fail_on_err, op, op_fmt, expr_op0, expr_op1,          \
                         __VA_ARGS__)
#endif

#define EZTEST_C_ASSERT_FAIL_(fail_on_err, ...)                                \
 (void)EZTEST_PRINTF_(__VA_ARGS__);                                            \
 EZTEST_NS_ eztest_cur_test_set_failed();                                      \
 if (fail_on_err) {                                                            \
  (void)EZTEST_FFLUSH_(stdout);                                                \
  (void)EZTEST_FFLUSH_(stderr);                                                \
  EZTEST_EXIT_(1);                                                             \
 }

#define EZTEST_C_ASSERT_CHECK_BOOL_(expec, expr)                               \
 ((expec) ? (!(expr)) : (!!(expr)))

#define EZTEST_C_ASSERT_CHECK_BINOP_(op, expr_op0, expr_op1)                   \
 (!(op((expr_op0), (expr_op1))))

#define EZTEST_C_ASSERT_CHECK_TERNOP_(op, expr_arg0, expr_arg1, expr_arg2)     \
 (!(op((expr_arg0), (expr_arg1), (expr_arg2))))

#define EZTEST_C_BINOP_EQ_(op0, op1) ((op0) == (op1))
#define EZTEST_C_BINOP_LT_(op0, op1) ((op0) < (op1))
#define EZTEST_C_BINOP_LE_(op0, op1) ((op0) <= (op1))
#define EZTEST_C_FMT_BINOP_(op)      "(%s) " op " (%s)"
#define EZTEST_C_TERNOP_FP_NEAR_(op0, op1, abs_err)                            \
 (EZTEST_ABS_((op0) - (op1)) <= EZTEST_ABS_(abs_err))

#define EZTEST_C_FLT_COMPARE_WRAPPER_(op0, op1)                                \
 EZTEST_NS_ eztest_flt_compare(EZTEST_CAST_(float, op0),                       \
                               EZTEST_CAST_(float, op1))
#define EZTEST_C_DBL_COMPARE_WRAPPER_(op0, op1)                                \
 EZTEST_NS_ eztest_dbl_compare(EZTEST_CAST_(double, op0),                      \
                               EZTEST_CAST_(double, op1))

#define EZTEST_C_ASSERT_TRUE_IMPL_(fail_on_err, ...)                           \
 EZTEST_C_ASSERT_BOOL_(fail_on_err, 1, __VA_ARGS__)
#define EZTEST_C_ASSERT_FALSE_IMPL_(fail_on_err, ...)                          \
 EZTEST_C_ASSERT_BOOL_(fail_on_err, 0, __VA_ARGS__)

#define EZTEST_C_ASSERT_EQ_IMPL_(fail_on_err, ...)                             \
 EZTEST_C_ASSERT_BINOP_(fail_on_err, EZTEST_C_BINOP_EQ_,                       \
                        EZTEST_C_FMT_BINOP_("=="), __VA_ARGS__)
#define EZTEST_C_ASSERT_NE_IMPL_(fail_on_err, ...)                             \
 EZTEST_C_ASSERT_BINOP_(fail_on_err, !EZTEST_C_BINOP_EQ_,                      \
                        EZTEST_C_FMT_BINOP_("!="), __VA_ARGS__)
#define EZTEST_C_ASSERT_LE_IMPL_(fail_on_err, ...)                             \
 EZTEST_C_ASSERT_BINOP_(fail_on_err, EZTEST_C_BINOP_LE_,                       \
                        EZTEST_C_FMT_BINOP_("<="), __VA_ARGS__)
#define EZTEST_C_ASSERT_LT_IMPL_(fail_on_err, ...)                             \
 EZTEST_C_ASSERT_BINOP_(fail_on_err, EZTEST_C_BINOP_LT_,                       \
                        EZTEST_C_FMT_BINOP_("<"), __VA_ARGS__)
#define EZTEST_C_ASSERT_GE_IMPL_(fail_on_err, ...)                             \
 EZTEST_C_ASSERT_BINOP_(fail_on_err, !EZTEST_C_BINOP_LT_,                      \
                        EZTEST_C_FMT_BINOP_(">="), __VA_ARGS__)
#define EZTEST_C_ASSERT_GT_IMPL_(fail_on_err, ...)                             \
 EZTEST_C_ASSERT_BINOP_(fail_on_err, !EZTEST_C_BINOP_LE_,                      \
                        EZTEST_C_FMT_BINOP_(">"), __VA_ARGS__)

#define EZTEST_C_ASSERT_STREQ_IMPL_(fail_on_err, ...)                          \
 EZTEST_C_ASSERT_STR_(fail_on_err, !EZTEST_STRCMP_, EZTEST_C_FMT_BINOP_("eq"), \
                      __VA_ARGS__)
#define EZTEST_C_ASSERT_STRNE_IMPL_(fail_on_err, ...)                          \
 EZTEST_C_ASSERT_STR_(fail_on_err, EZTEST_STRCMP_, EZTEST_C_FMT_BINOP_("ne"),  \
                      __VA_ARGS__)
#define EZTEST_C_ASSERT_STRCASEEQ_IMPL_(fail_on_err, ...)                      \
 EZTEST_C_ASSERT_STR_(fail_on_err, !EZTEST_STRCASECMP_,                        \
                      EZTEST_C_FMT_BINOP_("case-eq"), __VA_ARGS__)
#define EZTEST_C_ASSERT_STRCASENE_IMPL_(fail_on_err, ...)                      \
 EZTEST_C_ASSERT_STR_(fail_on_err, EZTEST_STRCASECMP_,                         \
                      EZTEST_C_FMT_BINOP_("case-ne"), __VA_ARGS__)

#define EZTEST_C_ASSERT_FLOAT_EQ_IMPL_(fail_on_err, ...)                       \
 EZTEST_C_ASSERT_BINOP_(fail_on_err, EZTEST_C_FLT_COMPARE_WRAPPER_,            \
                        EZTEST_C_FMT_BINOP_("=="), __VA_ARGS__)
#define EZTEST_C_ASSERT_DOUBLE_EQ_IMPL_(fail_on_err, ...)                      \
 EZTEST_C_ASSERT_BINOP_(fail_on_err, EZTEST_C_DBL_COMPARE_WRAPPER_,            \
                        EZTEST_C_FMT_BINOP_("=="), __VA_ARGS__)
#define EZTEST_C_ASSERT_NEAR_IMPL_(fail_on_err, ...)                           \
 EZTEST_C_ASSERT_TERNOP_(fail_on_err, EZTEST_C_TERNOP_FP_NEAR_,                \
                         "abs(%s - %s) <= (%s)", __VA_ARGS__)


#define EZTEST_PP_ARGS_TO_N_(...) EZTEST_PP_ARGS_TO_N_PRIM_(__VA_ARGS__)
#define EZTEST_PP_ARGS_TO_N_PRIM_(                                             \
    a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16,     \
    a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, \
    a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, \
    a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, \
    a62, a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, \
    a77, a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, \
    a92, a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104,      \
    a105, a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116,    \
    a117, a118, a119, a120, a121, a122, a123, a124, a125, a126, a127, a128,    \
    a129, a130, a131, a132, a133, a134, a135, a136, a137, a138, a139, a140,    \
    a141, a142, a143, a144, a145, a146, a147, a148, a149, a150, a151, a152,    \
    a153, a154, a155, a156, a157, a158, a159, a160, a161, a162, a163, a164,    \
    a165, a166, a167, a168, a169, a170, a171, a172, a173, a174, a175, a176,    \
    a177, a178, a179, a180, a181, a182, a183, a184, a185, a186, a187, a188,    \
    a189, a190, a191, a192, a193, a194, a195, a196, a197, a198, a199, a200,    \
    a201, a202, a203, a204, a205, a206, a207, a208, a209, a210, a211, a212,    \
    a213, a214, a215, a216, a217, a218, a219, a220, a221, a222, a223, a224,    \
    a225, a226, a227, a228, a229, a230, a231, a232, a233, a234, a235, a236,    \
    a237, a238, a239, a240, a241, a242, a243, a244, a245, a246, a247, a248,    \
    a249, a250, a251, a252, a253, a254, a255, a256, a257, aN, ...)             \
 aN
#define EZTEST_PP_NARG_1N_(...)                                                \
 EZTEST_PP_ARGS_TO_N_(__VA_ARGS__, EZTEST_PP_REVERSE_SEQ_1N_())
#define EZTEST_PP_REVERSE_SEQ_1N_()                                            \
 N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, \
     N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,   \
     N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,   \
     N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,   \
     N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,   \
     N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,   \
     N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,   \
     N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,   \
     N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,   \
     N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N, N,   \
     N, N, N, N, N, N, N, N, N, N, N, N, N, N, 1, BAD


#define EZTEST_CLEANED_VA_ARGS_1(...) __VA_ARGS__, "%s", ""
#define EZTEST_CLEANED_VA_ARGS_N(...) __VA_ARGS__
#define EZTEST_CLEAN_VA_ARGS_(...)                                             \
 EZTEST_CAT_(EZTEST_CLEANED_VA_ARGS_, EZTEST_PP_NARG_1N_(__VA_ARGS__))         \
 (__VA_ARGS__)

#define EZTEST_ASSERT_TRUE_IMPL_(...)                                          \
 EZTEST_C_ASSERT_TRUE_IMPL_(1, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_FALSE_IMPL_(...)                                         \
 EZTEST_C_ASSERT_FALSE_IMPL_(1, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_EQ_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_EQ_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_NE_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_NE_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_LE_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_LE_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_LT_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_LT_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_GE_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_GE_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_GT_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_GT_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_STREQ_IMPL_(op0, ...)                                    \
 EZTEST_C_ASSERT_STREQ_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_STRNE_IMPL_(op0, ...)                                    \
 EZTEST_C_ASSERT_STRNE_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_STRCASEEQ_IMPL_(op0, ...)                                \
 EZTEST_C_ASSERT_STRCASEEQ_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_STRCASENE_IMPL_(op0, ...)                                \
 EZTEST_C_ASSERT_STRCASENE_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_FLOAT_EQ_IMPL_(op0, ...)                                 \
 EZTEST_C_ASSERT_FLOAT_EQ_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_DOUBLE_EQ_IMPL_(op0, ...)                                \
 EZTEST_C_ASSERT_DOUBLE_EQ_IMPL_(1, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_ASSERT_NEAR_IMPL_(op0, op1, ...)                                \
 EZTEST_C_ASSERT_NEAR_IMPL_(1, op0, op1, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))


#define EZTEST_EXPECT_TRUE_IMPL_(...)                                          \
 EZTEST_C_ASSERT_TRUE_IMPL_(0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_FALSE_IMPL_(...)                                         \
 EZTEST_C_ASSERT_FALSE_IMPL_(0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_EQ_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_EQ_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_NE_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_NE_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_LE_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_LE_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_LT_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_LT_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_GE_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_GE_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_GT_IMPL_(op0, ...)                                       \
 EZTEST_C_ASSERT_GT_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_STREQ_IMPL_(op0, ...)                                    \
 EZTEST_C_ASSERT_STREQ_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_STRNE_IMPL_(op0, ...)                                    \
 EZTEST_C_ASSERT_STRNE_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_STRCASEEQ_IMPL_(op0, ...)                                \
 EZTEST_C_ASSERT_STRCASEEQ_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_STRCASENE_IMPL_(op0, ...)                                \
 EZTEST_C_ASSERT_STRCASENE_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_FLOAT_EQ_IMPL_(op0, ...)                                 \
 EZTEST_C_ASSERT_FLOAT_EQ_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_DOUBLE_EQ_IMPL_(op0, ...)                                \
 EZTEST_C_ASSERT_DOUBLE_EQ_IMPL_(0, op0, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))
#define EZTEST_EXPECT_NEAR_IMPL_(op0, op1, ...)                                \
 EZTEST_C_ASSERT_NEAR_IMPL_(0, op0, op1, EZTEST_CLEAN_VA_ARGS_(__VA_ARGS__))


#endif
