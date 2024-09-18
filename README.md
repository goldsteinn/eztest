# EZTest

An easy to use and lightweight unit test framework for **C/C++** on
**Linux** exported as a single header file
[`eztest.h`](https://github.com/goldsteinn/eztest/blob/main/include/eztest/eztest.h)

The API is made to mostly match
[`GoogleTest`](https://github.com/google/googletest). For some
projects it can be a drop-in replacements, for others it won't work.

The key selling point, and primary motivating factor for writing
`EZTest`, is that it will work out of the box with
[`-fsanitizer=memory`](https://clang.llvm.org/docs/MemorySanitizer.html),
as opposed to [`GoogleTest`](https://github.com/google/googletest)
which requires re-building from source along with an
[`-fsanitizer=memory`](https://clang.llvm.org/docs/MemorySanitizer.html)
enabled [`libc++`](https://libcxx.llvm.org/) to work.



- [1. Overview and Motivation](#1-overview-and-motivation)
- [2. Installation](#2-installation)
    - [2.1. Installing Using CMake](#21-installing-using-cmake)
    - [2.2. Installing As Submodule](#22-installing-as-submodule)
    - [2.3. Advanced Installation](#23-advanced-installation)
- [3. Usage](#3-usage)
    - [3.1. Namespacing](#31-namespacing)
    - [3.2. Running Tests](#32-running-tests)
    - [3.3. Test Setup](#33-test-setup)
    - [3.4. Asserts and Expects](#34-asserts-and-expects)
    - [3.5. Printing On Failure](#35-printing-on-failure)
    - [3.6. Disabling Tests](#36-disabling-tests)
    - [3.7. Difference From GoogleTest](#37-difference-from-googletest)
- [4. Advanced Usage and Toggles](#4-advanced-usage-and-toggles)
    - [4.1. Behavioral Toggles](#41-behavioral-toggles)
    - [4.2. Compilation Toggles](#42-compilation-toggles)
- [5. System Requirements](#5-system-requirements)
    - [5.1. Operating System](#51-operating-system)
    - [5.2. Compiler](#52-compiler)
    - [5.3. Language](#53-language)
    - [5.4. Architecture](#54-architecture)
- [6. Developer Info](#6-developer-info)
    - [6.1. EZTest Source](#61-eztest-source)
    - [6.2. EZTest Header Generation](#62-eztest-header-generation)
    - [6.3. Internal Testing of EZTest](#63-internal-testing-of-eztest)
## 1. Overview and Motivation


The general motivating factor for `EZTest` is to be an alternative to
[`GoogleTest`](https://github.com/google/googletest) with a few
important distinguishing characteristics.

1. `EZTest` tests do not link against the C++ runtime library
   (`libc++.so`/`libstdc++.so`). This makes compiling the tests with
   [`-fsanitizer=memory`](https://clang.llvm.org/docs/MemorySanitizer.html)
   trivial.
2. `EZTest` runs each test as its own process (using
   [`fork`](https://man7.org/linux/man-pages/man2/fork.2.html)). This
   allows for signal handling of buggy tests with clear error
   messages. Further it isolates tests from one another preventing
   potential corruption carrying over from one test to another.
3. `EZTest` is packages as just a single header file and requires no
   extra link/compilation steps to get working.

## 2. Installation

<!-- See https://github.com/bernedom/SI/blob/main/doc/installation-guide.md -->
The default installation location is `/usr/local`.

Keep in mind, the only file necessary to get started is
[`eztest.h`](https://github.com/goldsteinn/eztest/blob/main/include/eztest/eztest.h),
so feel free to just copy and include it as you see fit.

### 2.1. Installing Using CMake

Clone the repository and run these commands in the cloned folder:
```sh
mkdir build && cd build
cmake .. # Use -DCMAKE_INSTALL_PREFIX=<your_path> to control the destination
cmake --build . --target install
```

Then to use the installed library, add the following to your `cmake` project:

```cmake
find_package(eztest REQUIRED)
target_link_libraries(your_test_target eztest::eztest)
```

### 2.2. Installing As Submodule

Clone the repository and add the following to your `cmake` project
```cmake
add_subdirectory(path/to/your/cloned/eztest)
target_link_libraries(your_test_target eztest)
```

### 2.3. Advanced Installation

There are several toggles for modify how the
[`eztest.h`](https://github.com/goldsteinn/eztest/blob/main/include/eztest/eztest.h)
is generated/installed.

These include
```cmake
option(
  EZTEST_ULP_PRECISION
  "Int: Set float/double compare ULP bound"
  OFF)
option(
  EZTEST_FLOAT_ULP_PRECISION
  "Int: Set float compare ULP bound"
  OFF)
option(
  EZTEST_DOUBLE_ULP_PRECISION
  "Int: Set double compare ULP bound"
  OFF)
option(
  EZTEST_DISABLE_WARNINGS
  "Bool: Set/unset to configure whether warnings are supressed with pragmas"
  OFF)
option(
  EZTEST_DISABLE_LINTS
  "Bool: Set/unset to configure whether lints are supressed with comments"
  OFF)
option(
  EZTEST_STRICT_NAMESPACE
  "Bool: Set/unset to configure whether generic TEST/ASSERT/EXPECT macros are defined"
  OFF)
```

and can be set during the installation setup. All of these other than
`EZTEST_DISABLE_LINTS` have corresponding macros (see [4. Advanced
Usage and Toggles](#4-advanced-usage-and-toggles)). The
`EZTEST_DISABLE_LINTS` option will determine whether `/* NOLINT* */`
directives are transferred from the source code to the header during
generation. If you want to ensure certain code characteristics using
`clang-tidy` including in the `EZTest` header, set
`-DEZTEST_DISABLE_LINTS=ON` during installation.

## 3. Usage

The API is similiar to that of
[`GoogleTest`](https://github.com/google/googletest) but there are
some key distinction.

### 3.1. Namespacing

All symbols and macros defined in
[`eztest.h`](https://github.com/goldsteinn/eztest/blob/main/include/eztest/eztest.h)
are prefixed `eztest` or `EZTEST`. Furthermore if compiling with `C++`
all symbols are inside the `eztest::` namespace. Assuming your code
has no symbols/macros begining with `eztest` or `EZTEST` and/or no
symbols in the `eztest::` namespace, there should be no symbol
conflicts when using `EZTest`.

### 3.2. Running Tests

1. Include [`eztest.h`](https://github.com/goldsteinn/eztest/blob/main/include/eztest/eztest.h) in your test file
2. Build your test executable
3. Run the resulting executable.

For example take the following `test.cc`

```C
/* eztest.h contains `main`.  */
#include "eztest/eztest.h"

TEST(foo, bar) {
    ASSERT_EQ(0, 0);
}
```

To run the test(s) we would do the following:
```sh
clang++ test.cc -O3 -o test
./test
```

### 3.3. Test Setup

Tests are created with the following macros:
- `TEST(suite, name)`
- `TEST_TIMED(suite, name, timeout_in_milliseconds)`

The usage is identical to
[`GoogleTest`](https://github.com/google/googletest) i.e:

```C
TEST(my_suite, my_test) {
   /* Test code goes here... */
}
```

### 3.4. Asserts and Expects

There are assertions / expect statements a variety of different
checks. The difference between an `ASSERT` check and `EXPECT` check,
is that if an `ASSERT` check fails, the test will end
immediately. Alternatively if an `EXPECT` check fails, the test will
continue running but will fail on termination.


- `{ASSERT|EXPECT}_TRUE(arg:bool)`
    - Checks the `arg` is `true`
- `{ASSERT|EXPECT}_FALSE(arg:bool)`
    - Checks the `arg` is `false`
- `{ASSERT|EXPECT}_EQ(lhs:anyT, rhs:anyT)`
    - Checks that `lhs == rhs`
- `{ASSERT|EXPECT}_NE(lhs:anyT, rhs:anyT)`
    - Checks that `lhs != rhs`
- `{ASSERT|EXPECT}_LE(lhs:anyT, rhs:anyT)`
    - Checks that `lhs <= rhs`
- `{ASSERT|EXPECT}_LT(lhs:anyT, rhs:anyT)`
    - Checks that `lhs < rhs`
- `{ASSERT|EXPECT}_GE(lhs:anyT, rhs:anyT)`
    - Checks that `lhs >= rhs`
- `{ASSERT|EXPECT}_GT(lhs:anyT, rhs:anyT)`
    - Checks that `lhs > rhs`
- `{ASSERT|EXPECT}_STREQ(lhs:str, rhs:str)`
    - Checks that `strcmp(lhs, rhs) == 0`
- `{ASSERT|EXPECT}_STRNE(lhs:str, rhs:str)`
    - Checks that `strcmp(lhs, rhs) != 0`
- `{ASSERT|EXPECT}_STRCASEEQ(lhs:str, rhs:str)`
    - Checks that `strcasecmp(lhs, rhs) == 0`
- `{ASSERT|EXPECT}_STRCASENE(lhs:str, rhs:str)`
    - Checks that `strcasecmp(lhs, rhs) != 0`
- `{ASSERT|EXPECT}_FLOAT_EQ(lhs:float, rhs:float)`
    - Checks that `ULP_difference(lhs, rhs) < Threshold`
        - See more on [`ULP`](https://en.wikipedia.org/wiki/Unit_in_the_last_place).
- `{ASSERT|EXPECT}_DOUBLE_EQ(lhs:double, rhs:double)`
    - Checks that `ULP_difference(lhs, rhs) < Threshold`
- `{ASSERT|EXPECT}_NEAR(lhs:fp, rhs:fp, bound:fp)`
    - Checks that `abs(lhs - rhs) <= bound`

In the above:
- `bool` is an type that supports the `!` operator.
- `anyT` is any type that the specified operator is valid for.
- `str` is one of the following:
    - `char *`
    - `std::string` (if using `C++`)
    - `std::string_view` (if using `C++17` or newer)
- `fp` is one of the following:
    - `float`
    - `double`

### 3.5. Printing On Failure

Failure messages that print the variables exist in the following
cases:
- You are using `C++`
- You are using `C11` or newer with a compiler that supports the
  [`__typeof__`](https://gcc.gnu.org/onlinedocs/gcc/Typeof.html)
  extension.

Otherwise, the failure message will only indicate the line number /
variables names that failed.

In additional to default failure messages, you can also optionally
include [`printf`](https://en.cppreference.com/w/cpp/io/c/fprintf) as
optional additional arguments to any `ASSERT`/`EXPECT` macro that will
be printed only on failure. For example:

```C
/* int a, b, c; */
int d = a + b;
ASSERT_EQ(c, d, "Something something %d + %d\n", a, b);
```

### 3.6. Disabling Tests

Tests can be disabled from running (but still built) by prefixing the
test name with `DISABLED_`.

This behaves exactly the same as
[`GoogleTest`](https://github.com/google/googletest).


### 3.7. Difference From GoogleTest

There are several key distinctions between the `EZTest` API and that
of [`GoogleTest`](https://github.com/google/googletest).

In no particularly the notable differences are:

*Support/fix is planned.

1. *The following macros are unimplemented in `EZTest`:
    - `TEST_F`
    - `TEST_P`
    - `SCOPED_TRACE`
    - `{ASSERT|EXPECT}_THROW`
    - `{ASSERT|EXPECT}_ANY_THROW`
    - `{ASSERT|EXPECT}_NO_THROW`
    - `{ASSERT|EXPECT}_NO_FATAL_FAILURE`
    - `{ASSERT|EXPECT}_PRED1`
    - `{ASSERT|EXPECT}_PRED2`
    - `{ASSERT|EXPECT}_PRED3`
    - `{ASSERT|EXPECT}_PRED4`
    - `{ASSERT|EXPECT}_PRED5`

2. There is no test
   [`Fixture`](https://google.github.io/googletest/advanced.html) to
   inherit from in `EZTest`.

3. `EZTest` uses `C-style` printing as opposed to `C++-style` operator `<<`
   printing.

4. *There are no
   [`DeathTests`](https://google.github.io/googletest/advanced.html) in `EZTest`.

5. *There is an environment variable / commandline support in
   `EZTest`. This is relevant to
    - Test filtering.
    - Test repeating
    - Test shuffling
    - Test listing
    - etc...

6. *There are no toggles for modify test printouts in `EZTest`.

7. *There is no support for generating an XML/JSON files for the test results in `EZTest`.

8. *There are slight differences in the printout format.

9. *No global variables for changing behavior
    - Instead there are some macros.

## 4. Advanced Usage and Toggles

There are some macros that can be defined which will change the
behavior/compilation of
[`eztest.h`](https://github.com/goldsteinn/eztest/blob/main/include/eztest/eztest.h).

For the most part, the defaults should be fine.

### 4.1. Behavioral Toggles
The following macros can be defined to change behavior.

1. `EZTEST_ULP_PRECISION`
    - `default:4`
    - This will change the
      [`ULP`](https://en.wikipedia.org/wiki/Unit_in_the_last_place)
      for both `{ASSERT|EXPECT}_{FLOAT|DOUBLE}_EQ`
2. `EZTEST_FLOAT_ULP_PRECISION`
    - `default:EZTEST_ULP_PRECISION`
    - This will change the
      [`ULP`](https://en.wikipedia.org/wiki/Unit_in_the_last_place)
      for both `{ASSERT|EXPECT}_FLOAT_EQ`
3. `EZTEST_DOUBLE_ULP_PRECISION`
    - `default:EZTEST_ULP_PRECISION`
    - This will change the
      [`ULP`](https://en.wikipedia.org/wiki/Unit_in_the_last_place)
      for both `{ASSERT|EXPECT}_DOUBLE_EQ`
4. `EZTEST_C_PRINT_ARGS`
    - `default:1`
    - If set to `0` and using the `C` language, `eztest` will stop
      trying to print arguments on failure.
5. `EZTEST_VERBOSITY`
    - `default:0`
    - Increase value to include more internal printouts (mostly just
      non-fatal warnings).

### 4.2. Compilation Toggles
The following macros can be defined to change compilation.

1. `EZTEST_DISABLE_WARNINGS`
    - `default:1`
    - If set, `eztest` will enable
      [`Pragmas`](https://gcc.gnu.org/onlinedocs/cpp/Pragmas.html) to
      disable known, inevitable, warnings. These warnings mostly only
      show up if compiling with [`Clang's
      -Weverything`](https://clang.llvm.org/docs/UsersManual.html#diagnostics-enable-everything)
      or an excessive amount of `GCC` warnings. If compiling with
      `-Wall -Wextra -Wpedantic` the only warning that may show up is
      `-Wunused-function` depending on the set of `ASSERT`/`EXPECT`
      checks used. The total set of disabled warnings are:
        - `-Waggregate-returns`
        - `-Wcxx98-compat-pedantic`
        - `-Wcxx98-compat`
        - `-Wdouble-promotion`
        - `-Wfloat-equal`
        - `-Wformat-nonliteral`
        - `-Wglobal-constructors`
        - `-Wpadded`
        - `-Wunsafe-buffer-usage`
        - `-Wunsafe-buffer-usage-in-libc-call`
        - `-Wunused-function`
        - `-Wunused-member-function`
        - `-Wunused-result`
        - `-Wunused-template`
    - Note the `Pragmas` are used minimally and will never apply to
      your own code.

2. `EZTEST_STRICT_NAMESPACE`
    - `default:0`
    - If set, then general `{ASSERT|EXPECT}_*` and `TEST*` macros will
      be prefixed with `EZTEST_`

## 5. System Requirements

There are some system requirements. Some of these may not be
hard-requirements, but at the very least they are untested.

### 5.1. Operating System

`Linux` is the only tested OS at the moment. It's probably that any
`unix` based system would work.

### 5.2. Compiler

`GCC`/`Clang` are the only tested compilers are the moment.

### 5.3. Language
1. If `C`
    - `C99` or newer
    - Support for `__attribute__((constructor))`
2. If `C++`
    - `C++11` or newer

### 5.4. Architecture
If compiling **without `posix`** specification
    - `x86-64`
    - `x86-32`
    - `arm`
    - `aarch64`
    - `riscv64`
    - `riscv32`

Otherwise any target should work.


## 6. Developer Info


### 6.1. EZTest Source

The source code is located in
[`src/eztest`](https://github.com/goldsteinn/eztest/tree/main/src/eztest).

The source code and includable
[`eztest.h`](https://github.com/goldsteinn/eztest/blob/main/include/eztest/eztest.h)
files seperate. The actual
[`eztest.h`](https://github.com/goldsteinn/eztest/blob/main/include/eztest/eztest.h)
header is autogenerated. This is a convenience to make development
simpler.


### 6.2. EZTest Header Generation

To generate the
[`eztest.h`](https://github.com/goldsteinn/eztest/blob/main/include/eztest/eztest.h)
header file, we use the
[`scripts/freeze.py`](https://github.com/goldsteinn/eztest/blob/main/scripts/freeze.py)
script.

Generally there is no need to invoke the script directly. It will
either be invoked by `cmake` as needed for tests/installation, or by
the wrapper script
[`quick-regen.py`](https://github.com/goldsteinn/eztest/blob/main/scripts/quick-regen.py).

### 6.3. Internal Testing of EZTest

Tests are located in the
[`tests`](https://github.com/goldsteinn/eztest/tree/main/tests)
directory.

To build the tests you can run:
```sh
mkdir build && cd build
cmake .. -DEZTEST_BUILD_TESTS=ON
make check-all # Run "unit tests"
make check-external # Run "integration tests"
make run-static-analysis # Run clang-tidy
```

The general `cmake` compiler/flags/language arguments will also
apply. As well there are toolchain files are testing cross
compilation.

To see some examples of the internal tests usage see
[.github/workflows/ci.yaml`](https://github.com/goldsteinn/eztest/blob/main/.github/workflows/ci.yaml).
