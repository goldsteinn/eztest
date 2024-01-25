#
# CMake Toolchain file for crosscompiling on ARM.
#
# Target operating system name.
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR riscv64)

set(EZTEST_TEST_RUN_ENV_ "qemu-riscv64-static -L /usr/riscv64-linux-gnu/")
set(EZTEST_TEST_TARGET_ARCH_ "riscv64")

# Where to look for the target environment. (More paths can be added here)
set(CMAKE_FIND_ROOT_PATH /usr/riscv64-linux-gnu)
#set(CMAKE_SYSROOT /usr/riscv64-linux-gnu)

# Adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment only.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search headers and libraries in the target environment only.
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE arm64)
