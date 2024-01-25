#! /usr/bin/env python3

import sys
import os
import argparse
import subprocess

G_PARSER = argparse.ArgumentParser(description="Run an external test")
G_PARSER.add_argument("--src",
                      action="store",
                      default=None,
                      required=True,
                      help="Directory to run")
G_PARSER.add_argument("--dst",
                      action="store",
                      default=None,
                      required=True,
                      help="Build directory")
G_PARSER.add_argument("--install",
                      action="store",
                      default=None,
                      help="Install directory")
G_PARSER.add_argument("--no-fail",
                      action="store_true",
                      default=False,
                      help="If install not there fail")

G_ARGS, G_UNKNOWNARGS = G_PARSER.parse_known_args()

G_SRC = G_ARGS.src
assert os.path.isdir(G_SRC)
G_SRC = os.path.realpath(G_SRC)
G_DIRNAME = os.path.basename(G_SRC)
G_DST = G_ARGS.dst

G_INSTALL = G_ARGS.install
G_NO_FAIL = G_ARGS.no_fail

if G_INSTALL is not None:
    G_INSTALL_POSTFIXES = [
        "", "include", "include/eztest", "include/eztest/eztest.h", "lib",
        "lib/cmake", "lib/cmake/eztest/", "lib/cmake/eztest/eztest-config.cmake",
        "lib/cmake/eztest/eztest-config-version.cmake",
        "lib/cmake/eztest/eztest-targets.cmake"
    ]
    for G_POSTFIX in G_INSTALL_POSTFIXES:
        if not os.path.exists(os.path.join(G_INSTALL, G_POSTFIX)):

            if G_NO_FAIL:
                sys.exit(1)
            print("Skipping install test")                
            sys.exit(0)
    G_UNKNOWNARGS.append("-DCMAKE_PREFIX_PATH={}".format(G_INSTALL))

try:
    subprocess.check_output(["cmake", "-S", G_SRC, "-B", G_DST, "-GNinja"] +
                            G_UNKNOWNARGS)
    subprocess.check_output(
        ["cmake", "--build", G_DST, "--target", "check-all"])
except Exception:
    sys.exit(1)
sys.exit(0)
