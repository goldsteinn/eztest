#ifndef EZTEST_D_EZTEST_D_EZTEST_PROC_H_
#define EZTEST_D_EZTEST_D_EZTEST_PROC_H_

#include "eztest-duration.h"
#include "eztest-lang.h"
#include "eztest-libc-incs.h"
#include "eztest-syscall.h"

EZTEST_NAMESPACE_BEGIN_
typedef unsigned eztest_proc_status_t;
/* NOLINTBEGIN(cppcoreguidelines-use-enum-class) */
enum {
    eztest_k_proc_unknown,
    eztest_k_proc_returned,
    eztest_k_proc_signalled,
    eztest_k_proc_timed_out
};
/* NOLINTEND(cppcoreguidelines-use-enum-class) */
#define EZTEST_PROC_STATUS_T_ EZTEST_NS_ eztest_proc_status_t

/* NOLINTBEGIN(llvmlibc-restrict-system-libc-headers) */
#include <poll.h>         /* pollfd, poll.  */
#include <sched.h>        /* sched_yield. */
#include <signal.h>       /* SIG*, kill.  */
#include <sys/prctl.h>    /* prctl.  */
#include <sys/signalfd.h> /* signalfd.  */
#include <sys/types.h>    /* pid_t. */
#include <sys/wait.h>     /* waitpid, pid_t.  */
#include <unistd.h>       /* fork.  */
/* NOLINTEND(llvmlibc-restrict-system-libc-headers) */

#if EZTEST_XOPEN_VERSION_ >= 500 || EZTEST_POSIX_VERSION_ >= 199506L
/* Maybe use pthread_sigprocmask (afraid of -lpthread dependency) */
#endif
#define EZTEST_SIGPROCMASK_(todo, new_mask, old_mask)                          \
    /* NOLINTBEGIN(concurrency-mt-unsafe,llvmlibc-callee-namespace) */         \
    sigprocmask(todo, new_mask, old_mask)                                      \
                                                                               \
        /* NOLINTEND(concurrency-mt-unsafe,llvmlibc-callee-namespace) */


typedef int (*eztest_proc_func)(const EZTEST_TEST_T_ *);
#define EZTEST_PROC_FUNC_ EZTEST_NS_ eztest_proc_func

struct eztest_proc_result_t {
    EZTEST_PROC_STATUS_T_ eztest_proc_status_;
    int                   eztest_proc_status_value_;
    EZTEST_DURATION_T_    eztest_proc_duration_;
};
#define EZTEST_PROC_RESULT_T_      EZTEST_STRUCT_NS_ eztest_proc_result_t
#define EZTEST_PROC_RESULT_T_INIT_ { 0, 0, EZTEST_DURATION_T_INIT_ }


typedef int eztest_timed_wait_res_t;
/* NOLINTBEGIN(cppcoreguidelines-use-enum-class) */
enum {
    eztest_k_timed_wait_fallback = -2,
    eztest_k_timed_wait_err      = -1,
    eztest_k_timed_wait_returned = 0,
    eztest_k_timed_wait_timeout  = 1
};
/* NOLINTEND(cppcoreguidelines-use-enum-class) */
#define EZTEST_TIMED_WAIT_RES_T_ EZTEST_NS_ eztest_timed_wait_res_t

EZTEST_DISABLE_WUSELESS_CAST_
static const pid_t eztest_k_pid_err   = EZTEST_CAST_(pid_t, -1);
static const pid_t eztest_k_pid_child = EZTEST_CAST_(pid_t, 0);
static const pid_t eztest_k_pid_none  = EZTEST_CAST_(pid_t, 0);
EZTEST_REENABLE_WUSELESS_CAST_

EZTEST_PRIVATE_ int
eztest_proc_waitpid(pid_t eztest_proc_pid,
                    int   eztest_blocking,
                    int * eztest_proc_ret_out) {
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    const pid_t eztest_reaped_pid =
        waitpid(eztest_proc_pid, eztest_proc_ret_out,
                eztest_blocking == 0 ? WNOHANG : 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    EZTEST_DISABLE_WUSELESS_CAST_
    if (eztest_reaped_pid == EZTEST_NS_ eztest_k_pid_err) {
        EZTEST_PERR_(
            "Fatal Internal Error -- "
            "Unable reap test process:\n\t");
        return -1;
    }
    if (eztest_blocking == 0 &&
        eztest_reaped_pid == EZTEST_NS_ eztest_k_pid_none) {
        /* Non blocking by not ready yet.  */
        return 1;
    }
    EZTEST_REENABLE_WUSELESS_CAST_
    if (eztest_reaped_pid != eztest_proc_pid) {
        (void)EZTEST_PRINTF_(
            "Fatal Internal Error -- "
            "Unable reaped unknown test process: %d\n",
            EZTEST_CAST_(int, eztest_reaped_pid));
        return -1;
    }

    return 0;
}

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ int
eztest_proc_wait_on_fd(int eztest_proc_fd, long eztest_proc_timeout_ms) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    /* NOLINTBEGIN(modernize-use-designated-initializers) */
    EZTEST_STRUCT_ pollfd eztest_poll_fd = { eztest_proc_fd, POLLIN, 0 };
    /* NOLINTEND(modernize-use-designated-initializers) */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    const int eztest_poll_res = poll(&eztest_poll_fd, EZTEST_CAST_(nfds_t, 1),
                                     EZTEST_CAST_(int, eztest_proc_timeout_ms));
    /* NOLINTEND(llvmlibc-callee-namespace) */
    if (eztest_poll_res == -1) {
        /* Internal error. */
        EZTEST_PERR_(
            "Internal Error -- "
            "Unable to poll fd for test timeout:\n\t");
        return -1;
    }
    if (eztest_poll_res == 0) {
        /* Timeout.  */
        return 1;
    }
    /* NOLINTNEXTLINE(hicpp-signed-bitwise) */
    if (eztest_poll_res != 1 || (eztest_poll_fd.revents & POLLIN) == 0) {
        (void)EZTEST_PRINTF_(
            "Internal Error -- "
            "Invalid poll result during test timeout:\n"
            "\tReturn Value: %d\n"
            "\tReturn Event: %hx\n",
            eztest_poll_res, eztest_poll_fd.revents);
        return EZTEST_NS_ eztest_k_timed_wait_err;
    }
    return 0;
}


/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ EZTEST_TIMED_WAIT_RES_T_
eztest_proc_timed_wait_loop(pid_t eztest_proc_pid,
                            long  eztest_proc_timeout_ms,
                            int * eztest_proc_ret_out) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    static const long  eztest_k_min_yield_time_ms = 50;
    EZTEST_DURATION_T_ eztest_total_waited        = EZTEST_DURATION_T_INIT_;
    EZTEST_NS_         eztest_duration_start(&eztest_total_waited);
    for (;;) {
        long      eztest_waited   = 0;
        const int eztest_wait_res = EZTEST_NS_ eztest_proc_waitpid(
            eztest_proc_pid, /* eztest_blocking */ 0, eztest_proc_ret_out);
        if (eztest_wait_res == -1) {
            return EZTEST_NS_ eztest_k_timed_wait_err;
        }
        if (eztest_wait_res == 0) {
            return EZTEST_NS_ eztest_k_timed_wait_returned;
        }

        EZTEST_NS_                 eztest_duration_end(&eztest_total_waited);
        eztest_waited = EZTEST_NS_ eztest_duration_ms(&eztest_total_waited);
        if (eztest_waited < 0L) {
            (void)EZTEST_PRINTF_(
                "Internal Error -- "
                "Failed to gettime during backup timed wait...\n"
                "No longer possible to timeout test. Killing.\n");
            return EZTEST_NS_ eztest_k_timed_wait_err;
        }
        if (eztest_waited >= eztest_proc_timeout_ms) {
            EZTEST_KILL_(eztest_proc_pid, SIGKILL);
            return EZTEST_NS_ eztest_k_timed_wait_timeout;
        }
        eztest_proc_timeout_ms -= eztest_waited;
        if (eztest_proc_timeout_ms >= eztest_k_min_yield_time_ms) {
            /* NOLINTBEGIN(llvmlibc-callee-namespace) */
            sched_yield();
            /* NOLINTEND(llvmlibc-callee-namespace) */
        }
    }
}


/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ EZTEST_TIMED_WAIT_RES_T_
eztest_proc_timed_wait_final_wait(pid_t eztest_proc_pid,
                                  int   eztest_wait_res,
                                  int * eztest_proc_ret_out) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    if (eztest_wait_res == 1) {
        EZTEST_KILL_(eztest_proc_pid, SIGKILL);
    }

    if (EZTEST_NS_ eztest_proc_waitpid(eztest_proc_pid,
                                       /* eztest_blocking */ 1,
                                       eztest_proc_ret_out) == -1) {
        return EZTEST_NS_ eztest_k_timed_wait_err;
    }
    if (eztest_wait_res == 0) {
        return EZTEST_NS_ eztest_k_timed_wait_returned;
    }
    if (eztest_wait_res == 1) {
        return EZTEST_NS_ eztest_k_timed_wait_timeout;
    }
    return EZTEST_NS_ eztest_k_timed_wait_err;
}

#if EZTEST_POSIX_VERSION_
/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ EZTEST_TIMED_WAIT_RES_T_
eztest_proc_timed_wait_sigfd(pid_t eztest_proc_pid,
                             long  eztest_proc_timeout_ms,
                             int * eztest_proc_ret_out) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    int        eztest_wait_res   = 0;
    int        eztest_proc_sigfd = 0;
    sigset_t   eztest_ss;
    sigset_t   eztest_prev_ss;
    static int eztest_S_sigfd_unsupported = 0;
    if (eztest_S_sigfd_unsupported != 0) {
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }
    /* Block SIGCHLD so we are ready to handle.  */
    /* NOLINTNEXTLINE(llvmlibc-callee-namespace) */
    if (sigemptyset(&eztest_ss) != 0 || sigaddset(&eztest_ss, SIGCHLD) != 0 ||
        EZTEST_SIGPROCMASK_(SIG_BLOCK, &eztest_ss, &eztest_prev_ss) != 0) {
        EZTEST_PWARN_V_(
            "Internal Error -- "
            "Unable to initialize signal mask for timeout:\n\t");
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }

    eztest_wait_res = EZTEST_NS_ eztest_proc_waitpid(
        eztest_proc_pid, /* eztest_blocking */ 0, eztest_proc_ret_out);
    if (eztest_wait_res == -1) {
        return EZTEST_NS_ eztest_k_timed_wait_err;
    }
    /* After blocking (to prepare to handle) child finished.  */
    if (eztest_wait_res == 0) {
        (void)EZTEST_SIGPROCMASK_(SIG_SETMASK, &eztest_prev_ss, EZTEST_NULL_);
        return EZTEST_NS_ eztest_k_timed_wait_returned;
    }

    /* Setup fd for SIGCHLD.  */
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    eztest_proc_sigfd = signalfd(-1, &eztest_ss, 0);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    if (eztest_proc_sigfd == -1) {
        (void)EZTEST_SIGPROCMASK_(SIG_SETMASK, &eztest_prev_ss, EZTEST_NULL_);
        if (EZTEST_ERRNO_ == ENOSYS) {
            eztest_S_sigfd_unsupported = 1;
        }
        EZTEST_PWARN_V_(
            "Internal Error -- "
            "Unable to initialize signal fd for timeout:\n\t");
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }

    eztest_wait_res = EZTEST_NS_ eztest_proc_wait_on_fd(eztest_proc_sigfd,
                                                        eztest_proc_timeout_ms);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    (void)close(eztest_proc_sigfd);
    /* NOLINTEND(llvmlibc-callee-namespace) */
    (void)EZTEST_SIGPROCMASK_(SIG_SETMASK, &eztest_prev_ss, EZTEST_NULL_);

    if (eztest_wait_res == -1) {
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }

    return EZTEST_NS_ eztest_proc_timed_wait_final_wait(
        eztest_proc_pid, eztest_wait_res, eztest_proc_ret_out);
}
#endif

/* NOLINTBEGIN(bugprone-easily-swappable-parameters) */
EZTEST_PRIVATE_ EZTEST_TIMED_WAIT_RES_T_
eztest_proc_timed_wait_pidfd(pid_t eztest_proc_pid,
                             long  eztest_proc_timeout_ms,
                             int * eztest_proc_ret_out) {
    /* NOLINTEND(bugprone-easily-swappable-parameters) */
    int        eztest_wait_res            = 0;
    int        eztest_proc_pidfd          = 0;
    static int eztest_S_pidfd_unsupported = 0;
    if (eztest_S_pidfd_unsupported != 0) {
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }

    eztest_proc_pidfd =
        EZTEST_CAST_(int, EZTEST_PIDFD_OPEN_(eztest_proc_pid, 0U));
    if (eztest_proc_pidfd == -1) {
        if (EZTEST_ERRNO_ == ENOSYS) {
            eztest_S_pidfd_unsupported = 1;
        }
        EZTEST_PWARN_V_(
            "Internal Error -- "
            "Unable to initialize pid fd for timeout:\n\t");
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }
    eztest_wait_res = EZTEST_NS_ eztest_proc_wait_on_fd(eztest_proc_pidfd,
                                                        eztest_proc_timeout_ms);
    /* NOLINTBEGIN(llvmlibc-callee-namespace) */
    (void)close(eztest_proc_pidfd);
    /* NOLINTEND(llvmlibc-callee-namespace) */

    if (eztest_wait_res == -1) {
        return EZTEST_NS_ eztest_k_timed_wait_fallback;
    }

    return EZTEST_NS_ eztest_proc_timed_wait_final_wait(
        eztest_proc_pid, eztest_wait_res, eztest_proc_ret_out);
}

EZTEST_PRIVATE_ EZTEST_TIMED_WAIT_RES_T_
eztest_proc_timed_wait(pid_t eztest_proc_pid,
                       long  eztest_proc_timeout_ms,
                       int * eztest_proc_ret_out) {
    EZTEST_TIMED_WAIT_RES_T_ eztest_wait_res =
        EZTEST_NS_           eztest_proc_timed_wait_pidfd(
            eztest_proc_pid, eztest_proc_timeout_ms, eztest_proc_ret_out);
    if (eztest_wait_res != EZTEST_NS_ eztest_k_timed_wait_fallback) {
        return eztest_wait_res;
    }
#if EZTEST_POSIX_VERSION_
    eztest_wait_res = EZTEST_NS_ eztest_proc_timed_wait_sigfd(
        eztest_proc_pid, eztest_proc_timeout_ms, eztest_proc_ret_out);
    if (eztest_wait_res != EZTEST_NS_ eztest_k_timed_wait_fallback) {
        return eztest_wait_res;
    }
#endif
    return EZTEST_NS_ eztest_proc_timed_wait_loop(
        eztest_proc_pid, eztest_proc_timeout_ms, eztest_proc_ret_out);
}

EZTEST_PRIVATE_ int
eztest_proc_wait(pid_t eztest_proc_pid,
                 long  eztest_proc_timeout_ms,
                 int * eztest_proc_ret_out) {
    if (eztest_proc_timeout_ms > 0L) {
        const EZTEST_TIMED_WAIT_RES_T_ eztest_k_timed_wait_res =
            EZTEST_NS_                 eztest_proc_timed_wait(
                eztest_proc_pid, eztest_proc_timeout_ms, eztest_proc_ret_out);
        switch (eztest_k_timed_wait_res) {
            case EZTEST_NS_ eztest_k_timed_wait_returned:
                return 0;
            case EZTEST_NS_ eztest_k_timed_wait_timeout:
                return 1;
            default:
                /* Cleanup the test process.  */
                EZTEST_KILL_(eztest_proc_pid, SIGKILL);
                (void)EZTEST_NS_ eztest_proc_waitpid(eztest_proc_pid,
                                                     /* eztest_blocking */ 1,
                                                     eztest_proc_ret_out);
                return -1;
        }
    }

    return EZTEST_NS_ eztest_proc_waitpid(eztest_proc_pid,
                                          /* eztest_blocking */ 1,
                                          eztest_proc_ret_out);
}

EZTEST_PRIVATE_ long
eztest_proc_duration_ms(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return EZTEST_NS_ eztest_duration_ms(
        &(eztest_proc_result->eztest_proc_duration_));
}

EZTEST_PRIVATE_ int
eztest_proc_signal_num(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return WTERMSIG(eztest_proc_result->eztest_proc_status_value_);
}

EZTEST_PRIVATE_ const char *
eztest_proc_signal_str(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    switch (EZTEST_NS_ eztest_proc_signal_num(eztest_proc_result)) {
        case SIGABRT:
            return "Aborted";
        case SIGALRM:
            return "Alarm clock";
        case SIGBUS:
            return "Bus error";
        case SIGCHLD:
            return "Child exited";
        case SIGCONT:
            return "Continued";
        case SIGFPE:
            return "Floating point exception";
        case SIGHUP:
            return "Hangup";
        case SIGILL:
            return "Illegal instruction";
        case SIGINT:
            return "Interrupt";
        case SIGKILL:
            return "Killed";
        case SIGPIPE:
            return "Broken pipe";
        case SIGPOLL:
            return "I/O possible";
        case SIGPROF:
            return "Profiling timer expired";
        case SIGQUIT:
            return "Quit";
        case SIGSEGV:
            return "Segmentation fault";
        case SIGSTOP:
            return "Stopped (signal)";
        case SIGSYS:
            return "Bad system call";
        case SIGTERM:
            return "Terminated";
        case SIGTRAP:
            return "Trace/breakpoint trap";
        case SIGTSTP:
            return "Stopped";
        case SIGTTIN:
            return "Stopped (tty input)";
        case SIGTTOU:
            return "Stopped (tty output)";
        case SIGURG:
            return "Urgent I/O condition";
        case SIGUSR1:
            return "User defined signal 1";
        case SIGUSR2:
            return "User defined signal 2";
        case SIGXCPU:
            return "CPU time limit exceeded";
        case SIGXFSZ:
            return "File size limit exceeded";
        default:
            return "Unknown signal";
    }
}

EZTEST_PRIVATE_ int
eztest_proc_returned(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return EZTEST_CAST_(int, eztest_proc_result->eztest_proc_status_ ==
                                 EZTEST_NS_ eztest_k_proc_returned);
}

EZTEST_PRIVATE_ int
eztest_proc_return_value(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return WEXITSTATUS(eztest_proc_result->eztest_proc_status_value_);
}

EZTEST_PRIVATE_ int
eztest_proc_signalled(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return EZTEST_CAST_(int, eztest_proc_result->eztest_proc_status_ ==
                                 EZTEST_NS_ eztest_k_proc_signalled);
}


EZTEST_PRIVATE_ int
eztest_proc_timed_out(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return EZTEST_CAST_(int, eztest_proc_result->eztest_proc_status_ ==
                                 EZTEST_NS_ eztest_k_proc_timed_out);
}

EZTEST_PRIVATE_ int
eztest_proc_unknown_result(const EZTEST_PROC_RESULT_T_ * eztest_proc_result) {
    return EZTEST_CAST_(int, eztest_proc_result->eztest_proc_status_ ==
                                 EZTEST_NS_ eztest_k_proc_unknown);
}


EZTEST_PRIVATE_ int
eztest_proc_ret_internal_error(EZTEST_PROC_RESULT_T_ * eztest_proc_res_out) {
    EZTEST_NS_ eztest_duration_end(
        &(eztest_proc_res_out->eztest_proc_duration_));
    return -1;
}

EZTEST_PRIVATE_ pid_t
eztest_testsuite_pid(EZTEST_VOID_ARG_) {
    static pid_t eztest_S_testsuite_pid = EZTEST_NS_ eztest_k_pid_none;
    if (eztest_S_testsuite_pid == EZTEST_NS_ eztest_k_pid_none) {
        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        eztest_S_testsuite_pid = getpid();
        /* NOLINTEND(llvmlibc-callee-namespace) */
    }
    return eztest_S_testsuite_pid;
}

EZTEST_PRIVATE_
int
eztest_proc_run(EZTEST_PROC_FUNC_       eztest_to_dispatch,
                const EZTEST_TEST_T_ *  eztest_test,
                long                    eztest_proc_timeout_ms,
                EZTEST_PROC_RESULT_T_ * eztest_proc_res_out) {
    unsigned eztest_fork_att_cnt  = 0;
    int      eztest_proc_ret      = 0;
    int      eztest_wait_result   = 0;
    pid_t eztest_proc_pid         = EZTEST_NS_ eztest_k_pid_none;
    const pid_t eztest_parent_pid = EZTEST_NS_ eztest_testsuite_pid();
    for (;;) {
        static const unsigned eztest_k_max_fork_att = 3;

        EZTEST_NS_ eztest_duration_start(
            &(eztest_proc_res_out->eztest_proc_duration_));
        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        eztest_proc_pid = fork();
        /* NOLINTEND(llvmlibc-callee-namespace) */
        if (eztest_proc_pid == EZTEST_NS_ eztest_k_pid_err) {
            if (eztest_fork_att_cnt < eztest_k_max_fork_att &&
                EZTEST_ERRNO_ == EAGAIN) {
                ++eztest_fork_att_cnt;
                continue;
            }
            EZTEST_PERR_(
                "Internal Error -- "
                "Unable to fork test:\n\t");
            return EZTEST_NS_ eztest_proc_ret_internal_error(
                eztest_proc_res_out);
        }
        break;
    }

    if (eztest_proc_pid == EZTEST_NS_ eztest_k_pid_child) {
        /* If parent dies, don't leave test running.  */
        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        /* NOLINTBEGIN(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
        int eztest_result = prctl(PR_SET_PDEATHSIG, SIGKILL);
        /* NOLINTEND(cppcoreguidelines-pro-type-vararg,hicpp-vararg) */
        /* NOLINTEND(llvmlibc-callee-namespace) */
        if (eztest_result != 0) {
            EZTEST_PWARN_V_(
                "Internal Error -- "
                "Unable to ensure test process will die with testsuite:\n\t");
        }

        /* NOLINTBEGIN(llvmlibc-callee-namespace) */
        eztest_result = EZTEST_CAST_(int, getppid() != eztest_parent_pid);
        /* NOLINTEND(llvmlibc-callee-namespace) */
        /* Parent died before call to prctl.  */
        if (eztest_result != 0) {
            EZTEST_EXIT_(1);
        }
        eztest_result = eztest_to_dispatch(eztest_test);
        (void)EZTEST_FFLUSH_(stdout);
        (void)EZTEST_FFLUSH_(stderr);
        EZTEST_EXIT_(eztest_result);
    }

    eztest_wait_result = EZTEST_NS_ eztest_proc_wait(
        eztest_proc_pid, eztest_proc_timeout_ms, &eztest_proc_ret);
    if (eztest_wait_result == -1) {
        return EZTEST_NS_ eztest_proc_ret_internal_error(eztest_proc_res_out);
    }
    EZTEST_NS_ eztest_duration_end(
        &(eztest_proc_res_out->eztest_proc_duration_));

    eztest_proc_res_out->eztest_proc_status_value_ = eztest_proc_ret;
    if (eztest_wait_result > 0) {
        eztest_proc_res_out->eztest_proc_status_ =
            EZTEST_NS_ eztest_k_proc_timed_out;
    }
    else if (WIFEXITED(eztest_proc_ret)) {
        eztest_proc_res_out->eztest_proc_status_ =
            EZTEST_NS_ eztest_k_proc_returned;
    }
    else if (WIFSIGNALED(eztest_proc_ret)) {
        eztest_proc_res_out->eztest_proc_status_ =
            EZTEST_NS_ eztest_k_proc_signalled;
    }
    else {
        eztest_proc_res_out->eztest_proc_status_ =
            EZTEST_NS_ eztest_k_proc_unknown;
    }

    return 0;
}


EZTEST_NAMESPACE_END_

#endif
