import sys
import os
import multiprocessing

assert len(sys.argv) >= 2

G_COMPILER = sys.argv[1].lower()
G_COMPILER_NORM = {
    "clang": "clang",
    "llvm": "clang",
    "clang++": "clang",
    "gcc": "gcc",
    "gnu": "gcc",
    "g++": "gcc"
}

assert G_COMPILER in G_COMPILER_NORM
G_COMPILER = G_COMPILER_NORM[G_COMPILER]

G_VERS = " ".join(sys.argv[2:])
G_VERS = G_VERS.split()

G_TEST_DIR = ".build-all"

G_SRC_DIR = sys.argv[0]
G_SRC_DIR = os.path.dirname(G_SRC_DIR)
G_SRC_DIR = os.path.realpath(os.path.join(G_SRC_DIR, ".."))

G_README = os.path.join(G_SRC_DIR, "README.md")
assert os.path.isfile(G_README) and os.access(G_README, os.R_OK)
try:
    G_f = open(G_README)
    G_content = G_f.read()
    G_f.close()
    assert G_content.startswith("# EZTEST")
except Exception:
    assert False, "Unable to verify!"


def os_do(cmd):
    #    print(cmd)
    r = os.system(cmd)
    if r != 0:
        r = 1
    return r


assert os_do("mkdir -p {}".format(G_TEST_DIR)) == 0


def run_test_impl(ver, c_std, cxx_std, ext):
    status = []
    cver = "{}/{}".format(G_COMPILER, ver)
    hdr = "Testing: {:<32}".format(cver + " ext=" + ext + " c" + c_std +
                                   " cxx" + cxx_std)
    #    print(hdr)
    test_dir = os.path.join(
        G_TEST_DIR, "{}-{}-ext{}-c{}-cxx{}".format(G_COMPILER,
                                                   ver.replace(".", "-"), ext,
                                                   c_std, cxx_std))
    os_do("rm -r {} > /dev/null 2>&1".format(test_dir))
    assert os_do("mkdir -p {}".format(test_dir)) == 0

    if c_std != "":
        c_std = "-DCMAKE_C_STANDARD={}".format(c_std)
    else:
        c_std = ""
    if cxx_std != "":
        cxx_std = "-DCMAKE_CXX_STANDARD={}".format(cxx_std)
    else:
        cxx_std = ""

    ext = "-DCMAKE_C_EXTENSIONS={} -DCMAKE_CXX_EXTENSIONS={}".format(ext, ext)

    cmake_res = os_do(
        "(cd {}; cmake {} -GNinja {} {} {} -DCMAKE_C_COMPILER=$(compiler-vers --ver {} --get-c) -DCMAKE_CXX_COMPILER=$(compiler-vers --ver {} --get-cc) -DCMAKE_BUILD_TYPE=Release > log.txt 2>&1)"
        .format(test_dir, G_SRC_DIR, c_std, cxx_std, ext, cver, cver))

    omap = {0: "P", 1: "F", -1: "U"}

    total_res = 0
    for lang in ["c", "cxx"]:
        todo = "all-{}".format(lang)
        todo_san = "all-all-{}".format(lang)
        res = -1
        res_san = -1
        if cmake_res == 0:
            res = os_do(
                "(cd {}; ninja --verbose check-{} >> log.txt 2>&1)".format(
                    test_dir, todo))
            if res == 0:
                res_san = os_do(
                    "(cd {}; ninja --verbose check-{} >> log.txt 2>&1)".format(
                        test_dir, todo_san))

        if res == 1 or res_san == 1:
            total_res = 1
        elif total_res == 0 and (res == -1 or res_san == -1):
            total_res = -1

        status.append("{}: {}".format(todo, omap[res]))
        status.append("{}: {}".format(todo_san, omap[res_san]))

    tail = ""
    if total_res == 0:
        tail = "Passed"
    elif total_res < 0:
        tail = "Unsupported"
    else:
        tail = "Failed"

    print(hdr + " - ".join(status) + " -- " + tail)


def run_test(ver):
    for standard in [("99", "11"), ("11", "14"), ("17", "17"), ("23", "20"),
                     ("", "23")]:
        for ext in ["ON", "OFF"]:
            run_test_impl(ver, standard[0], standard[1], ext)


with multiprocessing.Pool(max(int(os.cpu_count() / 2), 1)) as pool:
    pool.map(run_test, G_VERS)
