#! /usr/bin/env python3

import subprocess
import argparse
import traceback
import sys
import re
import platform
import datetime
import os

parser = argparse.ArgumentParser(description="Run a complete test")

parser.add_argument("--compiler",
                    action="store",
                    default=None,
                    help="Compiler used")
parser.add_argument("--san",
                    action="store",
                    default=None,
                    help="San option used")
parser.add_argument("--env",
                    action="store",
                    default=None,
                    help="Env (qemu basically)")
parser.add_argument("--arch", action="store", default=None, help="Target Arch")
parser.add_argument("--exe",
                    action="store",
                    default=None,
                    help="Executable",
                    required=True)
parser.add_argument("--src",
                    action="store",
                    default=None,
                    help="Source file",
                    required=True)
parser.add_argument("--dump-stdout",
                    action="store_true",
                    default=False,
                    help="Dump log to stdout on failure")
parser.add_argument("--lang",
                    action="store",
                    default=None,
                    help="Language for the exe")
parser.add_argument("--lang-info",
                    action="store",
                    default=None,
                    help="Language info (version)")

G_BASENAME = None
G_SRCNAME = None
G_INPUT = None
G_DUMP = False
G_ENV = None
G_ARCH = None
G_COMPILER = None
G_COMP_VERSION = 0
G_LANG = None
G_LANG_INFO = None
k_NO_SAN = 0
k_MSAN = 2
k_ASAN = 4
k_TSAN = 8
k_USAN = 16
k_LSAN = 32


def get_nosig(mask):
    return mask << 10


k_NOSIG_USAN = get_nosig(k_USAN)
k_NOSIG_ASAN = get_nosig(k_ASAN)
k_NOSIG_LSAN = get_nosig(k_LSAN)
k_NOSIG_TSAN = get_nosig(k_TSAN)
k_NOSIG_MSAN = get_nosig(k_MSAN)

k_ANY_SAN = k_MSAN | k_ASAN | k_TSAN | k_USAN | k_LSAN
k_ANY_NOSIG_SAN = k_NOSIG_USAN | k_NOSIG_TSAN | k_NOSIG_LSAN | k_NOSIG_MSAN | k_NOSIG_ASAN

G_SAN_OPT = None
G_LOGGER = None


def is_cxx():
    return G_SRCNAME.endswith(".cc")


def verval(vstr):
    if isinstance(vstr, list) or isinstance(vstr, tuple):
        vstr = "-".join(vstr)
    elif isinstance(vstr, int):
        vstr = str(vstr)

    vstr = vstr.replace("/", "-")
    vstr = vstr.replace(".", "-")
    vstr = vstr.split("-")
    while len(vstr) < 3:
        vstr.append(0)
    vstr = vstr[0:3]
    try:
        return int(vstr[0]) * 1000 * 1000 + int(vstr[1]) * 1000 + int(vstr[2])
    except Exception:
        return 0


class logger_t():

    def __init__(self):
        self.str_ = ""
        self.stdout_ = ""
        self.logfile_ = None

    def log(self, msg, end="\n"):
        self.str_ += str(msg) + end

    def write_impl(self, fname, content):
        if content == "":
            return False

        if os.path.isfile(fname) or os.path.isdir(fname):
            return False
        try:
            f = open(fname, "w+")
            f.write(content)
            f.close()
        except Exception:
            return False
        return True

    def write(self):
        if G_DUMP:
            print("--- STDOUT ---")
            print(self.stdout_)
            print("--- STATE ---")
            print(self.str_)
            return
        date = datetime.datetime.now()
        date_str = date.strftime("%Y-%m-%d-%H-%M-%S")
        logfile = "{}.{}.{}".format(G_INPUT, date_str, "log")
        stdoutfile = "{}.{}.{}".format(G_INPUT, date_str, "stdout")

        if not self.write_impl(logfile, self.str_):
            print("Failed to write log")
        self.logfile_ = logfile
        if not self.write_impl(stdoutfile, self.stdout_):
            print("Failed to write stdout")


G_LOGGER = logger_t()


def log(msg, end="\n"):
    global G_LOGGER
    G_LOGGER.log(msg, end)


def log_add_std_outputs(stdout_data):
    global G_LOGGER
    G_LOGGER.stdout_ = stdout_data


def re_srcname():
    return os.path.realpath(G_SRCNAME).replace('.', '\\.')


def re_basename():
    return G_BASENAME.replace('.', '\\.')


def re_exename():
    return os.path.realpath(G_INPUT).replace('.', '\\.')


def re_exe_basename():
    return os.path.basename(G_INPUT).replace('.', '\\.')


class pp_stack_t():

    def __init__(self):
        self.k_IF_0 = 0
        self.k_IF_0_STICKY = 1
        self.k_IF_1 = 2
        self.k_IF_U = 3

        self.stack_ = []

        self.known_archs_ = [
            "X86_64", "AARCH64", "RISCV64", "ARM32", "RISCV32", "ANY_X86",
            "ANY_ARM", "ANY_RISCV", "X86_32"
        ]

        self.arch_fmt_ = "EZTEST_ARCH_IS_{}_"

        self.re_compiler_pattern_ = re.compile(
            r'(TS_HAS_(\w+)_VER_\s*\((\s*\d+\s*,\s*\d+\s*,\s*\d+\s*)\))')

        self.known_compilers_ = ["CLANG", "GCC"]
        self.comp_def_ = ""
        if G_COMPILER is not None:
            if G_COMPILER == "clang":
                self.comp_def_ = "CLANG"
            if G_COMPILER == "gnu":
                self.comp_def_ = "GCC"
        self.cver_ = G_COMP_VERSION

        host_arch = platform.machine().lower()
        self.arch_def_ = ("X86_64", "ANY_X86")
        self.arch_word_size_ = 64

        if host_arch in ("aarch64"):
            self.arch_def_ = ("AARCH64", "ANY_ARM")
            self.arch_word_size_ = 64
        elif host_arch in ("arm64", "armv6l", "armv7l"):
            self.arch_def_ = ("ARM32", "ANY_ARM")
            self.arch_word_size_ = 32
        elif host_arch in ("i686", "i386", "i86pc", "x86"):
            self.arch_def_ = ("X86_32", "ANY_X86")
            self.arch_word_size_ = 32
        elif host_arch in ("i686-64", "ia64", "amd64", "x86_64"):
            self.arch_def_ = ("X86_64", "ANY_X86")
            self.arch_word_size_ = 64
        elif host_arch in ("riscv32"):
            self.arch_def_ = ("RISCV32", "ANY_RISCV")
            self.arch_word_size_ = 32
        elif host_arch in ("riscv64"):
            self.arch_def_ = ("RISCV64", "ANY_RISCV")
            self.arch_word_size_ = 64

        if G_ARCH is not None or G_ENV is not None:
            arch = G_ARCH
            if arch is None:
                arch = re.match(r'^qemu-(\w+)(?:-static)', G_ENV)
                if arch:
                    arch = arch.group(1)
            if arch:
                if arch == "x86-32":
                    self.arch_word_size_ = 32
                    self.arch_def_ = ("X86_32", "ANY_X86")
                elif arch == "arm":
                    self.arch_word_size_ = 32
                    self.arch_def_ = ("ARM32", "ANY_ARM")
                elif arch == "aarch64":
                    self.arch_word_size_ = 64
                    self.arch_def_ = ("AARCH64", "ANY_ARM")
                elif arch == "riscv32":
                    self.arch_word_size_ = 32
                    self.arch_def_ = ("RISCV32", "ANY_RISCV")
                elif arch == "riscv64":
                    self.arch_word_size_ = 64
                    self.arch_def_ = ("RISCV64", "ANY_RISCV")

        self.re_pp_directive = re.compile(
            r'^\s*#\s*(ifdef\s+|if\s+|ifndef\s+|else|endif|elif\s+)')
        self.re_simple_expr = re.compile(r'^[!\s\d\(\)\*\+-/=^%|&><]*$')

    def valid_value(self, value):
        return value in (self.k_IF_0, self.k_IF_0_STICKY, self.k_IF_1,
                         self.k_IF_U)

    def empty(self):
        return len(self.stack_) == 0

    def is_directive(self, line):
        return self.re_pp_directive.match(line)

    def push(self, val):
        assert self.valid_value(val)
        self.stack_.append(val)

    def pop(self):
        assert not self.empty()
        val = self.stack_.pop()
        assert self.valid_value(val)
        return val

    def directive_with_value(self, directive, content):
        expr_val = None

        if directive in ("if", "elif"):
            content = content.replace("\t", " ")
            clen = 0
            while clen != len(content):
                clen = len(content)
                content = content.replace("  ", " ")

            if G_LANG is None:
                pass
            elif G_LANG == "C":
                content = content.replace("TS_CXX_LANG_", "0")
                content = content.replace("TS_C_LANG_", str(G_LANG_INFO))
            else:
                content = content.replace("TS_C_LANG_", "0")
                content = content.replace("TS_CXX_LANG_", str(G_LANG_INFO))

            for arch in self.arch_def_:
                content = content.replace(self.arch_fmt_.format(arch), "1")
            for arch in self.known_archs_:
                content = content.replace(self.arch_fmt_.format(arch), "0")
            content = content.replace("EZTEST_WORD_SIZE_",
                                      str(self.arch_word_size_))
            if self.comp_def_ != "":
                content = content.replace(
                    "TS_USING_{}_".format(self.comp_def_), "1")
            for comp_def in self.known_compilers_:
                content = content.replace("TS_USING_{}_".format(comp_def), "0")

            matches = self.re_compiler_pattern_.findall(content)

            if len(matches) != 0 and self.cver_ != 0:
                for match in matches:
                    if len(match) != 3:
                        continue
                    if match[1] != self.comp_def_:
                        content = content.replace(match[0], "0")
                        continue

                    ver = match[2].replace(" ", "")
                    ver = ver.replace("\t", "")
                    ver = ver.replace(",", ".")
                    ver = verval(ver)
                    if ver > self.cver_:
                        content = content.replace(match[0], "0")
                    else:
                        content = content.replace(match[0], "1")

            if self.re_simple_expr.match(content):
                try:
                    content = content.replace("!", "0==")
                    content = content.replace("||", " or ")
                    content = content.replace("&&", " and ")
                    content = eval(content)
                except Exception:
                    pass
            try:
                expr_val = int(content)
            except Exception:
                pass

        if expr_val is None:
            expr_val = self.k_IF_U
        elif expr_val == 0:
            expr_val = self.k_IF_0
        else:
            expr_val = self.k_IF_1
        if directive == "elif":
            if self.empty():
                return False
            prev_val = self.pop()
            if prev_val == self.k_IF_1 or prev_val == self.k_IF_0_STICKY:
                expr_val = self.k_IF_0_STICKY

        self.push(expr_val)
        return True

    def directive_without_value(self, directive):
        if self.empty():
            return False
        prev_val = self.pop()
        if directive == "else":
            if prev_val == self.k_IF_1 or prev_val == self.k_IF_0_STICKY:
                self.push(self.k_IF_0_STICKY)
            elif prev_val == self.k_IF_0:
                self.push(self.k_IF_1)
            else:
                self.push(self.k_IF_U)
        return True

    def add_directive(self, line):
        if line.count("#") == 0:
            return False
        line = line[line.find("#") + 1:]
        line = line.lstrip()
        line = line.split()

        directive = line[0]
        if directive in ("if", "ifdef", "ifndef", "elif"):
            if len(line) <= 1:
                return False
            content = " ".join(line[1:])
            return self.directive_with_value(directive, content)
        else:
            if len(line) > 1:
                return False
            return self.directive_without_value(directive)

    def accepting_lines(self):
        return self.empty() or (self.stack_[-1]
                                not in (self.k_IF_0, self.k_IF_0_STICKY))


def replace_str_and_comments(match):
    return " "


def find_all_source_tests(src_file):
    re_comment_and_str_pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE)
    re_test_pattern = re.compile(
        r'((?:EZ)?TEST(?:_F|_P)?(?:_TIMED)?[\n\s]*\([^\)\(]*\))\s*{',
        re.DOTALL | re.MULTILINE)

    src_code = None
    try:
        f = open(src_file)
        src_code = f.read()
        f.close()
    except Exception as e:
        assert False, "Unable to read {}\n\t{}".format(src_file, str(e))

    src_code = re.sub(re_comment_and_str_pattern, replace_str_and_comments,
                      src_code)

    src_lines = src_code.split("\n")
    src_code = []

    ppstack = pp_stack_t()
    for line in src_lines:
        if ppstack.is_directive(line):
            if not ppstack.add_directive(line):
                assert False, "Invalid pp directives in {}".format(src_file)

        elif ppstack.accepting_lines():
            src_code.append(line)

    src_code = "\n".join(src_code)

    return re_test_pattern.findall(src_code)


k_DISABLE = 0
k_OKAY = 1
k_FAIL = 2
k_TIMEFAIL = 3
k_SIGFAIL = 4
k_LEAKFAIL = 5


class test_t():

    def __init__(self, test):

        self.suite_ = None
        self.name_ = None
        self.expec_ = -1
        self.expec_san_ = k_NO_SAN
        orig_testline = test
        assert test.count("(") == 1
        assert test.count(")") == 1

        test = test.split("(")
        test_type = test[0]
        test_name = test[1]

        assert test_name.count(")") == 1
        test_name = test_name.split(")")[0]

        num_commas = 1
        if "TIMED" in test_type:
            num_commas = 2
        assert test_name.count(",") == num_commas

        test_name = test_name.split(",")

        self.suite_ = test_name[0].lstrip().rstrip()
        self.name_ = test_name[1].lstrip().rstrip()
        if self.name_.startswith("DISABLED_"):
            self.expec_ = k_DISABLE
        else:
            san_only_fail = False
            name = self.name_
            if name.endswith("failsan"):
                san_only_fail = True
                name = name[:-3]

            postfix_keys = (("_okay", k_OKAY), ("_fail", k_FAIL), ("_timefail",
                                                                   k_TIMEFAIL),
                            ("_sigfail", k_SIGFAIL), ("_leakfail", k_LEAKFAIL))
            san_postfix_keys = (("m", k_MSAN), ("a", k_ASAN), ("t", k_TSAN),
                                ("u", k_USAN), ("l", k_LSAN), ("U",
                                                               k_NOSIG_USAN),
                                ("A", k_NOSIG_ASAN), ("M", k_NOSIG_MSAN),
                                ("T", k_NOSIG_TSAN), ("L", k_NOSIG_LSAN))

            matched = False
            for option in postfix_keys:
                if name.endswith(option[0]):
                    self.expec_ = option[1]
                    name_pieces = name.split("_")
                    assert len(name_pieces) >= 2
                    if name_pieces[-2].endswith("san"):
                        san_piece = name_pieces[-2][:-3]
                        if san_piece == "":
                            self.expec_san_ |= k_ANY_SAN
                        else:
                            for san_option in san_postfix_keys:
                                if ("N" + san_option[0]) in san_piece:
                                    self.expec_san_ |= (~san_option[1])
                                elif san_option[0] in san_piece:
                                    self.expec_san_ |= (san_option[1])
                    matched = True
                    break
            assert matched, "Unknown test decl: {}".format(orig_testline)
            if san_only_fail and (self.expec_san_ & G_SAN_OPT[1]) == 0:
                self.expec_ = k_OKAY

    def key(self):
        return "{}.{}".format(self.suite_, self.name_)

    def re_key(self):
        return "{}\\.{}".format(self.suite_, self.name_)

    def link_re_func(self):
        return r'eztest_{}_{}_\d+func'.format(self.suite_, self.name_)

    def expec_fail(self):
        return self.expec_ in (k_FAIL, k_TIMEFAIL, k_SIGFAIL, k_LEAKFAIL)

    def expec_mask_fail(self, mask):
        return (self.expec_san_ & mask & G_SAN_OPT[1]) != 0

    def expec_san_fail(self):

        return self.expec_mask_fail(k_ANY_SAN)

    def expec_nosig_san_fail(self):
        return self.expec_mask_fail(k_ANY_NOSIG_SAN)


class expected_results_t():

    def __init__(self, src_tests):
        self.suites_ = {}
        self.suite_ord_ = []
        self.fail_ord_ = []

        self.ntests_ = len(src_tests)
        self.nokay_ = 0
        self.nfails_ = 0
        self.ndisabled_ = 0
        self.nactive_suites_ = 0

        active_suites = set()
        for test in src_tests:
            test = test_t(test)

            if test.suite_ not in self.suites_:
                self.suite_ord_.append(test.suite_)
                self.suites_[test.suite_] = []
            self.suites_[test.suite_].append(test)

            if test.expec_ == k_DISABLE:
                self.ndisabled_ += 1
            elif test.expec_ == k_OKAY:
                self.nokay_ += 1
                active_suites.add(test.suite_)
            else:
                self.nfails_ += 1
                active_suites.add(test.suite_)

        self.nactive_suites_ = len(active_suites)
        for suite in self.suite_ord_:
            for test in self.suites_[suite]:
                if test.expec_fail():
                    self.fail_ord_.append(test)

    def expec_success(self):
        return self.nfails_ == 0


class output_t():

    def __init__(self, output):
        self.lines_ = output.split("\n")
        self.idx_ = 0
        self.proper_matched_ = set()

    def dump(self):
        for i in range(0, self.idx_):
            if i in self.proper_matched_:
                log("Matched  : {}".format(self.lines_[i]))
            else:
                log("Skipped  : {}".format(self.lines_[i]))
        for i in range(self.idx_, len(self.lines_)):
            log("Unmatched: {}".format(self.lines_[i]))

    def done(self):
        return self.idx_ >= len(self.lines_)

    def cur_line(self):
        assert not self.done()
        return self.lines_[self.idx_]

    def step(self, n):
        if self.done():
            self.dump()
            assert False
        self.idx_ += n

    def match_impl(self, line, use_re):
        if self.done():
            return False

        if use_re:
            if not re.match(line, self.cur_line()):
                return False
        else:
            if line != self.cur_line():
                return False

        self.proper_matched_.add(self.idx_)
        self.step(1)
        return True

    def match(self, line):
        return self.match_impl(line, False)

    def re_match(self, line):
        return self.match_impl(line, True)

    def fail_match(self, line):
        self.dump()
        assert False, "Failed:\nExpec : {}\nvs\nActual: {}\n".format(
            line, self.cur_line())

    def must_match(self, line):
        if not self.match(line):
            self.fail_match(line)

    def must_re_match(self, line):
        if not self.re_match(line):
            self.fail_match(line)

    def re_match_arr(self, lines, must=False):
        idx = 0
        while idx < len(lines):
            if self.re_match(lines[idx]):
                idx += 1
            else:
                incr = 1
                if must:
                    incr = 0
                self.step(incr)
                if must or self.done():
                    for i in range(0, len(lines)):
                        hdr = "Found   :"
                        if i >= idx:
                            hdr = "NotFound:"
                        log("{}{}".format(hdr, lines[i]))
                    self.dump()
                    assert False

    def must_re_match_arr(self, lines):
        self.re_match_arr(lines, True)


def match_lines(expec, output):
    output.must_re_match(r'^Running main\(\) from .*$')
    output.must_match("[==========] Running {} tests".format(expec.ntests_))
    output.must_match("[----------] Global test environment set-up.")
    for suite in expec.suite_ord_:
        suite_first_active = False
        for test in expec.suites_[suite]:
            if test.expec_ == k_DISABLE:
                continue

            if not suite_first_active:
                output.must_match(
                    "[----------] Running tests from {}".format(suite))
                suite_first_active = True

            output.must_match("[ RUN      ] {}".format(test.key()))

            expec_artifacts = []
            if test.expec_san_fail():
                assert G_SAN_OPT[0] is not None
                if test.expec_ == k_SIGFAIL:
                    expec_artifacts.append(
                        r'(^{}:DEADLYSIGNAL|^{}:\d+:\d+: runtime error:)'.
                        format(G_SAN_OPT[0], re_srcname()))
                    expec_artifacts.append(
                        r'==\d+==ERROR: {}:[^\(]+\(pc 0x[0-9a-fA-F]+ bp 0x[0-9a-fA-F]+ sp 0x[0-9a-fA-F]+[^\(]*\)$'
                        .format(G_SAN_OPT[0]))
                    expec_artifacts.append(
                        r'^\s*#\d+(\s.*\s|\s|\s\s){}(\s|\(\)\s).*({}|{})'.
                        format(test.link_re_func(), re_basename(),
                               re_exe_basename()))
                    expec_artifacts.append(r'==\d+==ABORTING$')
                if test.expec_ == k_LEAKFAIL:
                    expec_artifacts.append(
                        r'==\d+==ERROR: LeakSanitizer: detected memory leaks')
                    expec_artifacts.append(
                        r'Direct leak of \d+ byte\(s\) in \d+ object\(s\) allocated from:'
                    )
                    expec_artifacts.append(
                        r'SUMMARY: {}: \d+ byte\(s\) leaked in \d+ allocation\(s\).'
                        .format(G_SAN_OPT[0]))
            else:
                if test.expec_ == k_FAIL:
                    expec_artifacts.append(r'^.*{}:\d+ Failure$'.format(
                        re_srcname()))
                    expec_artifacts.append(r'^Expected:')
                    if is_cxx():
                        expec_artifacts.append(r'^.*$')
                elif test.expec_ == k_SIGFAIL:
                    expec_artifacts.append(
                        r'^Test died with signal: \[\d+\] -> .*$')

            expec_status = None
            if test.expec_ == k_OKAY:
                expec_status = r'^\[       OK \] {} \(\d+ ms\)$'.format(
                    test.re_key())
            elif test.expec_ == k_TIMEFAIL:
                expec_status = r'^\[  TIMEOUT \] {} \(After \d+ ms\)$'.format(
                    test.re_key())
            else:
                expec_status = r'^\[  FAILED  \] {} \(\d+ ms\)$'.format(
                    test.re_key())

            if G_ENV is not None and test.expec_ == k_SIGFAIL:
                output.re_match(r'qemu:\s+uncaught\s+target\s+signal\s+\d')

            if test.expec_mask_fail(k_NOSIG_USAN):
                output.re_match_arr([r'^.*\d+:\d+:\s+runtime\s+error:'] +
                                    expec_artifacts)
            elif test.expec_san_fail():
                output.re_match_arr(expec_artifacts)
            else:
                output.must_re_match_arr(expec_artifacts)
            while True:
                if output.re_match(expec_status):
                    break
                else:
                    if output.done():
                        log("Failed to match: {}".format(expec_status))
                    output.step(1)
        if suite_first_active:
            output.must_re_match(
                r'^\[----------\] Ran tests from {} \((-1|\d+) ms total\)'.
                format(suite))
            output.must_match("")

    output.must_match("[----------] Global test environment tear-down")
    output.must_re_match(
        r'^\[==========\] {} tests from {} suites ran. \(\d+ ms total\)$'.
        format(expec.ntests_ - expec.ndisabled_, expec.nactive_suites_))

    output.must_match("[  PASSED  ] {} tests.".format(expec.nokay_))
    if expec.nfails_ != 0:
        output.must_match("[  FAILED  ] {} tests.".format(expec.nfails_))
        for test in expec.fail_ord_:
            fail_str = None
            if test.expec_ == k_FAIL or (test.expec_san_fail() and
                                         (test.expec_ == k_SIGFAIL
                                          or test.expec_ == k_LEAKFAIL)):
                fail_str = "Assert Failure"
            elif test.expec_ == k_TIMEFAIL:
                fail_str = "Timeout"
            elif test.expec_ == k_SIGFAIL:
                fail_str = "Signal"
            else:
                assert False, "Unknown failure type"

            expec_fail_status = r'^\[  FAILED  \] {}\s*: \({}\)$'.format(
                test.re_key(), fail_str)

            output.must_re_match(expec_fail_status)
        output.must_re_match("")
        output.must_re_match("{} FAILED TESTS".format(expec.nfails_))
    if expec.ndisabled_ != 0:
        output.must_re_match("  YOU HAVE {} DISABLED TESTS".format(
            expec.ndisabled_))
        output.must_match("")
    output.must_match("")
    if not output.done():
        output.dump()
        assert False


def run_proc(exe):
    assert os.path.isfile(exe) and os.access(
        exe, os.X_OK), "No executable: {}".format(exe)
    exe = os.path.realpath(exe)
    cmds = []
    if G_ENV is not None:
        cmds += G_ENV.split()
    cmds.append(exe)

    proc = subprocess.Popen(cmds,
                            stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT)
    stdout_data, unused = proc.communicate(timeout=60)

    assert unused is None
    ret = proc.returncode
    if stdout_data is not None:
        stdout_data = stdout_data.decode("utf-8")
    else:
        stdout_data = ""

    return stdout_data, ret


def run_test(exe, src):
    test_name = G_BASENAME
    if G_SAN_OPT[0] is not None:
        test_name += " + " + G_SAN_OPT[0]

    print("[ RUN      ] {}".format(test_name))
    errhdr = "[  FAILED  ] "
    errexit = 1
    sys.stdout.flush()

    try:
        stdout_res, ret = run_proc(exe)
        log_add_std_outputs(stdout_res)

        if re.match(
                r'^.*\serror\swhile\sloading\sshared\slibraries:\slib.*san\.so.*$',
                stdout_res):
            assert G_SAN_OPT[0] is not None
            errhdr = "[      BAD ] "
            errexit = 2
            assert False

        expec_res = expected_results_t(find_all_source_tests(src))

        if expec_res.expec_success():
            assert ret == 0
        else:
            assert (ret & 0xff) != 0
            assert (ret & 0xff) == ret
        output = output_t(stdout_res)
        # err_output = output_t(stderr_res)
        match_lines(expec_res, output)

        print("[       OK ] {}".format(test_name))
        sys.stdout.flush()
        sys.exit(0)
    except Exception:
        log("".join(traceback.format_stack()[:-1]))
        log("".join(traceback.format_exc()))
        G_LOGGER.write()
        print("{} {}".format(errhdr, test_name))
        if G_LOGGER.logfile_ is not None:
            print("\tWrote log to: {}".format(
                os.path.realpath(G_LOGGER.logfile_)))
        sys.stdout.flush()
        sys.exit(errexit)


def get_compiler_comp(cstr_in):
    cstr_in = cstr_in.lower()
    cstr_in = cstr_in.replace("/", "-")
    cstr_in = cstr_in.replace(".", "-")
    if "-" not in cstr_in:
        return cstr_in, 0

    pieces = cstr_in.split("-")
    compiler = pieces[0]
    if len(pieces) == 1:
        return compiler, 0
    return compiler, verval(pieces[1:])


G_ARGS = parser.parse_args()
G_INPUT = G_ARGS.exe
G_SRCNAME = G_ARGS.src
assert G_INPUT is not None and G_SRCNAME is not None
G_BASENAME = os.path.basename(G_SRCNAME)
G_DUMP = G_ARGS.dump_stdout
G_ENV = G_ARGS.env
G_ARCH = G_ARGS.arch
G_COMPILER = G_ARGS.compiler
G_COMP_VERSION = 0
G_LANG = G_ARGS.lang
G_LANG_INFO = G_ARGS.lang_info

if G_COMPILER is None:
    G_COMPILER = ""
else:
    G_COMPILER, G_COMP_VERSION = get_compiler_comp(G_COMPILER)
assert G_COMPILER in ("", "gnu", "clang")

G_SAN = G_ARGS.san
if G_SAN is None or G_SAN == "":
    G_SAN = ""
elif not G_SAN.startswith('-'):
    G_SAN = G_SAN[1:]

try:
    G_SAN_OPT = {
        "": (None, k_NO_SAN),
        "-msan": ("MemorySanitizer", k_MSAN),
        "-asan": ("(AddressSanitizer|ASAN)", k_ASAN),
        "-tsan": ("ThreadSanitizer", k_TSAN),
        "-usan": ("UndefinedBehaviorSanitizer", k_USAN),
        "-lsan": ("LeakSanitizer", k_LSAN)
    }
    G_SAN_OPT = G_SAN_OPT[G_SAN]
except Exception:
    G_SAN_OPT = (None, k_NO_SAN)

if G_COMPILER == "gnu" and G_SAN_OPT[1] == k_USAN:
    G_SAN_OPT = ("UndefinedBehaviorSanitizer", k_NOSIG_USAN)
if G_COMPILER == "clang" and G_COMP_VERSION != 0 and G_COMP_VERSION < verval(
        6):
    if G_SAN_OPT[1] in (k_USAN, k_LSAN, k_TSAN, k_MSAN):
        G_SAN_OPT = (G_SAN_OPT[0], get_nosig(G_SAN_OPT[1]))

if G_LANG is None:
    G_LANG_INFO = None
else:
    G_LANG = G_LANG.upper()
    assert G_LANG in ("C", "CXX"), "Val: {}".format(G_LANG)
    if not os.access(str(G_LANG_INFO), os.X_OK):
        G_LANG_INFO = None
    if G_LANG_INFO is not None:
        G_LANG_INFO_CMDS = []
        if G_ENV is not None:
            G_LANG_INFO_CMDS += G_ENV.split()
        G_LANG_INFO_CMDS.append(os.path.realpath(G_LANG_INFO))
        try:
            G_LANG_INFO = subprocess.check_output(
                G_LANG_INFO_CMDS, stderr=subprocess.DEVNULL).decode()
            assert G_LANG_INFO.startswith(G_LANG + "=")
            G_LANG_INFO = int(G_LANG_INFO[len(G_LANG) + 1:])
        except Exception:
            G_LANG_INFO = None
    if G_LANG_INFO is None:
        G_LANG = None

run_test(G_INPUT, G_SRCNAME)
