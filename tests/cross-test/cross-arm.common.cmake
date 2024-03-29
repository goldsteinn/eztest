#
# CMake Toolchain file for crosscompiling on ARM.
#
# Target operating system name.
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(EZTEST_TEST_RUN_ENV_ "qemu-arm-static -L /usr/arm-linux-gnueabi/")
set(EZTEST_TEST_TARGET_ARCH_ "arm")

# Where to look for the target environment. (More paths can be added here)
set(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabi)
# set(CMAKE_SYSROOT /usr/arm-linux-gnueabi)

# Adjust the default behavior of the FIND_XXX() commands: search programs in the
# host environment only.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search headers and libraries in the target environment only.
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ARM)
