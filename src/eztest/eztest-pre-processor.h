#ifndef EZTEST_D_EZTEST_D_EZTEST_PRE_PROCESSOR_H_
#define EZTEST_D_EZTEST_D_EZTEST_PRE_PROCESSOR_H_


#define EZTEST_STRINGIFY_IMPL_(eztest_expr) #eztest_expr
#define EZTEST_STRINGIFY_(eztest_expr)      EZTEST_STRINGIFY_IMPL_(eztest_expr)

#define EZTEST_CAT_IMPL_(eztest_expr0, eztest_expr1) eztest_expr0##eztest_expr1
#define EZTEST_CAT_(eztest_expr0, eztest_expr1)                                \
    EZTEST_CAT_IMPL_(eztest_expr0, eztest_expr1)

#define EZTEST_SNAKE_CAT_IMPL_(eztest_expr0, eztest_expr1)                     \
    eztest_expr0##_##eztest_expr1
#define EZTEST_SNAKE_CAT_(eztest_expr0, eztest_expr1)                          \
    EZTEST_SNAKE_CAT_IMPL_(eztest_expr0, eztest_expr1)


#ifdef __LINE__
# define EZTEST_LINE_ __LINE__
#else
# define EZTEST_LINE_ 0
#endif

#if (defined __COUNTER__) && (EZTEST_USE_COUNTER)
# define EZTEST_COUNTER_ __COUNTER__
#else
# define EZTEST_COUNTER_ EZTEST_LINE_
#endif

#ifdef __FILE__
# define EZTEST_FILE_ __FILE__
#else
# define EZTEST_FILE_ ""
#endif

#define EZTEST_UID_ EZTEST_SNAKE_CAT_(EZTEST_LINE_, EZTEST_COUNTER_)

#define EZTEST_UNIQUE_NAME_(eztest_var)                                        \
    EZTEST_SNAKE_CAT_(eztest_var, EZTEST_UID_)

#endif
