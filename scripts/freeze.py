#! /usr/bin/env python3

import sys
import re
import datetime
import os
import argparse
import subprocess
import copy

parser = argparse.ArgumentParser(
    description="Create single header file for eztest")

parser.add_argument("--dst",
                    action="store",
                    default="eztest.h",
                    help="Destination file")
parser.add_argument("--trim-pragmas",
                    action="store_true",
                    default=False,
                    help="Trim unused pragmas")
parser.add_argument("--prefix",
                    action="store",
                    default="eztest.h",
                    help="Destination directory")
parser.add_argument("--src",
                    action="store",
                    default=None,
                    help="Source top level file name",
                    required=True)
parser.add_argument("--fp-ulp",
                    action="store",
                    default=None,
                    help="Set fp ULP Bound")
parser.add_argument(
    "--flt-ulp",
    action="store",
    default=None,
    help="Set float ULP Bound (overrides --fp-ulp for FLOAT_EQ)")
parser.add_argument(
    "--dbl-ulp",
    action="store",
    default=None,
    help="Set double ULP Bound (overrides --fp-ulp for DOUBLE_EQ)")
parser.add_argument("--disable-warnings",
                    action="store_true",
                    default=False,
                    help="Disable known warnings with pragmas")
parser.add_argument("--enable-warnings",
                    action="store_true",
                    default=False,
                    help="Enable known warnings with pragmas")

parser.add_argument("--disable-lints",
                    action="store_true",
                    default=False,
                    help="Disable known clang tidy lints")
parser.add_argument("--strict-namespace",
                    action="store_true",
                    default=False,
                    help="Dont include the generic test/assert/expect macros")

parser.add_argument("--clang-format",
                    action="store",
                    default=None,
                    help="Path to clang format")

G_TRIM_PRAGMAS = False
G_PRAGMAS = None
G_BASEDIR = None
G_INCLUDED = None
G_COMMENT_AND_STR_PATTERN = re.compile(
    r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
    re.DOTALL | re.MULTILINE)


def add_define(name, val):
    lines = []
    lines.append("#ifndef {}".format(name))
    lines.append("#define {} {}".format(name, val))
    lines.append("#endif")
    return lines


def remove_lint(text):
    global G_COMMENT_AND_STR_PATTERN

    def lint_replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return s.replace("NOLINT", "DISABLED_nolint")
        else:
            return s

    return re.sub(G_COMMENT_AND_STR_PATTERN, lint_replacer, text)


def c_code(text):
    global G_COMMENT_AND_STR_PATTERN

    def comment_replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " "
        else:
            return s

    return re.sub(G_COMMENT_AND_STR_PATTERN, comment_replacer, text)


def fillin_pragmas(lines, pragmas):
    if pragmas is None:
        return lines
    lines_in = copy.deepcopy(lines)
    idx = -1
    try:
        idx = lines.index(pragmas[0])
        lines[idx] = "\n".join(pragmas[1])

        re_pragmas_line = re.compile(
            r'^\s*#\s*if\s+[\(]*\s*EZTEST_HAS_[A-Z_]+_\s*\(\s*\d+\s*,\s*\d+\s*,\s*\d+\s*\)[A-Z_0-9\(\)(?:\|\|)\s,(?:\&\&)\\]*\n\s*#\s*define\s+(EZTEST_DISABLE_W[A-Z0-9_]+_)\s+[\\]?\s*EZTEST_DISABLE_WARNING_\s*[\\]?\s*\(\s*[\\]?\s*\"-W[a-zA-Z0-9+-]+\"\s*\)\s*\n\s*#\s*define\s+(EZTEST_REENABLE_W[A-Z0-9_]+_)\s+[\\]?\s*EZTEST_REENABLE_WARNING_\s*\n\s*#\s*else\s*\n\s*#\s*define\s+(EZTEST_DISABLE_W[A-Z0-9_]+_)\s*\n\s*#\s*define\s+(EZTEST_REENABLE_W[A-Z0-9_]+_)\s*\n\s*#\s*endif\s*$',
            re.DOTALL | re.MULTILINE)

        code = c_code("\n".join(lines))
        tok_code = code
        tok_code = tok_code.replace(",", " , ")
        tok_code = tok_code.replace(")", " ) ")
        tok_code = tok_code.replace("(", " ( ")
        lines = tok_code.split()
        all_toks = {}
        for tok in lines:
            all_toks.setdefault(tok, 0)
            all_toks[tok] += 1

        pragma_lines = "\n".join(pragmas[1])
        orig_code = "\n".join(lines_in)
        all_matches = set()
        all_pragmas = set()

        def pragmas_replacer(match):
            assert match.group(1) == match.group(3)
            assert match.group(2) == match.group(4)

            assert match.group(0) not in all_matches
            all_matches.add(match.group(0))

            assert pragma_lines.count(match.group(0)) == 1
            assert code.count(match.group(0)) == 1
            assert match.group(0) not in orig_code, "Not in orig: {}".format(
                match.group(0))

            assert match.group(1) not in all_pragmas
            all_pragmas.add(match.group(1))

            assert match.group(2) not in all_pragmas
            all_pragmas.add(match.group(2))

            assert match.group(1) in all_toks
            assert match.group(2) in all_toks

            cnt1 = all_toks[match.group(1)]
            cnt2 = all_toks[match.group(2)]

            assert match.group(1).count("EZTEST_DISABLE_") == 1
            assert match.group(1).replace("EZTEST_DISABLE_",
                                          "EZTEST_REENABLE_") == match.group(2)
            assert match.group(2).count("EZTEST_REENABLE_") == 1
            assert match.group(2).replace("EZTEST_REENABLE_",
                                          "EZTEST_DISABLE_") == match.group(1)

            assert cnt1 == cnt2, "Cnts don't match: {} -- {} != {}".format(
                match.group(1), cnt1, cnt2)
            assert cnt1 >= 2

            if cnt1 == 2:
                return "\n"
            else:
                return match.group(0)

        pragma_lines = re_pragmas_line.sub(pragmas_replacer, pragma_lines)
        assert len(all_matches) >= 1000
        assert 2 * len(all_matches) == len(all_pragmas), "{} vs {}".format(
            len(all_matches), len(all_pragmas))

        assert idx >= 0
        assert idx < len(lines_in)

        lines_in[idx] = pragma_lines
    except Exception as e:
        assert idx >= 0
        assert lines_in[idx] == pragmas[0]
        lines_in[idx] = "\n".join(pragmas[1])
        print("Failed to trim pragmas: {}".format(str(e)))

    return lines_in


def freeze_file(fname):
    global G_BASEDIR
    global G_INCLUDED
    global G_PRAGMAS
    global G_TRIM_PRAGMAS
    text = None
    try:
        f = open(os.path.join(G_BASEDIR, fname))
        text = f.read()
        f.close()
    except Exception as e:
        print("Error: Unable to read '{}'\n\t{}".format(fname, str(e)))
        return None

    lines_out = []
    text = text.split("\n")

    hdr_guard_name = "EZTEST_D_EZTEST_D_{}_".format(
        fname.replace("-", "_").replace(".", "_").upper())

    hdr_guard_ifndef = r'^\s*#\s*ifndef\s+{}\s*$'.format(hdr_guard_name)
    hdr_guard_define = r'^\s*#\s*define\s+{}(\s+1)?\s*$'.format(hdr_guard_name)
    hdr_guard_endif = "#endif"

    while True:
        prev_len = len(text)
        if len(text) == 0:
            break
        if text[0].lstrip().rstrip() == "":
            text = text[1:]
        if len(text) == 0:
            break
        if text[-1].lstrip().rstrip() == "":
            text = text[:-1]
        if prev_len == len(text):
            break

    if len(text) >= 3:
        if re.match(hdr_guard_ifndef, text[0]) and re.match(
                hdr_guard_define, text[1]) and hdr_guard_endif == text[-1]:
            text = text[2:-1]
        else:
            assert False, "No hdr guard: {}".format(fname)
    lines_out.append("/* Begin include of: {}  */".format(fname))
    for line in text:

        line = line.rstrip()
        # Multiline strings/comments will be an issue here
        code = c_code(line)
        includes = re.findall(r"\s*#\s*include \"eztest-.*\.h\"", code)
        if len(includes) > 1:
            print(
                "Error: Found multiple includes in one line\n\t\"{}\"".format(
                    line))
            return None

        if len(includes) == 0:
            lines_out.append(line)
        else:
            include = includes[0]
            if include in G_INCLUDED:
                continue
            G_INCLUDED.add(include)
            assert line.count(include) == 1
            inc_file = include[include.find("\"") + 1:include.rfind("\"")]
            inc_lines = freeze_file(inc_file)
            if inc_lines is None:
                return None
            if inc_file == "eztest-compiler-warnings.h" and G_TRIM_PRAGMAS:
                key = '(FREEZER:[[[INCLUDE_OF_{}]]])'.format(inc_file.upper())
                lines_out.append(key)
                assert G_PRAGMAS is None
                G_PRAGMAS = (key, inc_lines)
            else:
                lines_out += inc_lines

    lines_out.append("/* End include of: {}  */".format(fname))
    return lines_out


G_ARGS = parser.parse_args()
G_DST = G_ARGS.dst
G_PREFIX = G_ARGS.prefix
G_SRC = G_ARGS.src
G_FP_ULP = G_ARGS.fp_ulp
G_FLT_ULP = G_ARGS.flt_ulp
G_DBL_ULP = G_ARGS.dbl_ulp
G_DISABLE_WARNINGS = G_ARGS.disable_warnings
G_ENABLE_WARNINGS = G_ARGS.enable_warnings
G_DISABLE_LINTS = G_ARGS.disable_lints
G_STRICT_NAMESPACE = G_ARGS.strict_namespace
G_CLANG_FORMAT = G_ARGS.clang_format
G_TRIM_PRAGMAS = G_ARGS.trim_pragmas
if G_DST is None:
    print("Error: --dst must not be none")
    sys.exit(5)

if not os.path.isfile(G_SRC):
    print("Error: Toplevel source header not found at: {}".format(G_SRC))
    sys.exit(1)

if G_DISABLE_WARNINGS and G_ENABLE_WARNINGS:
    print("Error: " +
          "--disable-warnings and --enable-warnings are mutually exclusive")
    sys.exit(2)

if G_FP_ULP is not None and G_FLT_ULP is not None and G_DBL_ULP is not None:
    print("Error: " +
          "--fp-ulp is useless as --flt-ulp and --dbl-ulp have been set")
    sys.exit(3)

if G_CLANG_FORMAT is None or not os.access(G_CLANG_FORMAT, os.X_OK):
    try:
        G_CLANG_FORMAT = subprocess.check_output(["which", "clang-format"],
                                                 stderr=subprocess.DEVNULL)
    except Exception:
        print("Warning: Unable to find clang format")
        G_CLANG_FORMAT = None

G_BASEDIR = os.path.dirname(G_SRC)
G_INCLUDED = set()

G_EZTEST_OUT = freeze_file(os.path.basename(G_SRC))
if G_EZTEST_OUT is None:
    print("Error: freezing '{}'".format(G_SRC))
    sys.exit(3)

G_LINES_OUT = []
G_LINES_OUT.append("#ifndef EZTEST_EZTEST_H_")
G_LINES_OUT.append("#define EZTEST_EZTEST_H_")

G_LINES_OUT.append("/*")
G_LINES_OUT.append(" * Single header of entire eztest suite.")
G_LINES_OUT.append(" * Generated: {}".format(datetime.datetime.now()))
G_LINES_OUT.append(" */")
if G_FP_ULP is not None:
    G_LINES_OUT += add_define("EZTEST_ULP_PRECISION", G_FP_ULP)
if G_FLT_ULP is not None:
    G_LINES_OUT += add_define("EZTEST_FLOAT_ULP_PRECISION", G_FLT_ULP)
if G_DBL_ULP is not None:
    G_LINES_OUT += add_define("EZTEST_DOUBLE_ULP_PRECISION", G_DBL_ULP)
if G_DISABLE_WARNINGS:
    G_LINES_OUT += add_define("EZTEST_DISABLE_WARNINGS", 1)
if G_ENABLE_WARNINGS:
    G_LINES_OUT += add_define("EZTEST_DISABLE_WARNINGS", 0)
if G_STRICT_NAMESPACE:
    G_LINES_OUT += add_define("EZTEST_STRICT_NAMESPACE", 1)

G_LINES_OUT += G_EZTEST_OUT

G_LINES_OUT.append("#endif")

G_LINES_OUT = fillin_pragmas(G_LINES_OUT, G_PRAGMAS)

G_EZTEST_OUT = "\n".join(G_LINES_OUT)
if G_DISABLE_LINTS:
    G_EZTEST_OUT = remove_lint(G_EZTEST_OUT)

if G_CLANG_FORMAT is not None:
    try:
        G_EZTEST_OUT = subprocess.check_output(
            ["clang-format", "-"],
            input=G_EZTEST_OUT.encode(),
            stderr=subprocess.DEVNULL).decode()
    except Exception:
        print("Warning: clang-format failed to run")

try:
    if G_PREFIX is not None:
        G_DST = os.path.join(G_PREFIX, G_DST)
        os.makedirs(G_PREFIX, exist_ok=True)

    G_DST_F = open(G_DST, "w+")
    G_DST_F.write(G_EZTEST_OUT + "\n")
    G_DST_F.close()
except Exception as e:
    print("Unable to write out eztest to '{}'\n\t{}".format(G_DST, str(e)))
    sys.exit(5)
sys.exit(0)
