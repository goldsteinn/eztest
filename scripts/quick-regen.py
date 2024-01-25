#! /usr/bin/env python3

import os
import sys
import pathlib
import subprocess

G_PROGNAME = sys.argv[0]
G_SCRIPT_DIR = os.path.dirname(G_PROGNAME)
G_PROJECT_DIR = os.path.realpath(os.path.join(G_SCRIPT_DIR, ".."))
G_README = os.path.join(G_PROJECT_DIR, "README.md")

assert os.path.isfile(G_README) and os.access(G_README, os.R_OK)
try:
    G_f = open(G_README)
    G_content = G_f.read()
    G_f.close()
    assert G_content.startswith("# EZTEST")
except Exception:
    assert False, "Unable to verify!"
G_FREEZE_SCRIPT = os.path.join(G_PROJECT_DIR, "scripts")
G_FREEZE_SCRIPT = os.path.join(G_FREEZE_SCRIPT, "freeze.py")

G_SRC_EZTEST_H = os.path.join(G_PROJECT_DIR, "src")
G_SRC_EZTEST_H = os.path.join(G_SRC_EZTEST_H, "eztest")
G_SRC_EZTEST_H = os.path.join(G_SRC_EZTEST_H, "eztest.h")

G_INSTALL_DIR = os.path.join(G_PROJECT_DIR, "include")
G_INSTALL_DIR = os.path.join(G_INSTALL_DIR, "eztest")

pathlib.Path(G_INSTALL_DIR).mkdir(parents=True, exist_ok=True)
G_INSTALL_CMD = "python3 {} --src={} --prefix={} --dst=eztest.h --trim-pragmas".format(
    G_FREEZE_SCRIPT, G_SRC_EZTEST_H, G_INSTALL_DIR)
print(G_INSTALL_CMD)
subprocess.check_output(G_INSTALL_CMD.split())
