cmake_minimum_required(VERSION 3.5.0)

project(
  "eztest"
  VERSION 0.0.1
  DESCRIPTION "A unit testing framework for C/C++"
  LANGUAGES C CXX
)

# User options
option(
  EZTEST_INSTALL_CMAKE_PACKAGE
  "Bool: set/unset to configure whether to install findable cmake package"
  ON
)
option(
  EZTEST_BUILD_TESTS
  "Bool: Set/unset to configure whether to build tests or not"
  OFF
)
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


# Install helpers
include(GNUInstallDirs)

# Export for clang tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#message(FATAL_ERROR "${CMAKE_C_COMPILER_LOADED} / ${CMAKE_CXX_COMPILER_LOADED} -- ${CMAKE_C_STANDARD} / ${CMAKE_CXX_STANDARD} -- ${C_STANDARD} / ${CXX_STANDARD} -- ${CMAKE_C_FLAGS} / ${CMAKE_CXX_FLAGS}")


# Libary export
add_library(eztest INTERFACE)
target_include_directories(
  eztest
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Check if this is a toplevel directory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # Creating eztest.h single header
  find_file(
    EZTEST_FREEZE_
    freeze.py
    PATHS ${PROJECT_SOURCE_DIR}/scripts
  )
  if(NOT EZTEST_FREEZE_)
    message(FATAL_ERROR "Unable to find freeze.py script")
  endif()

  if(EZTEST_ULP_PRECISION)
    set(EZTEST_ULP_PRECISION_ "--fp-ulp=${EZTEST_ULP_PRECISION}")
  endif()
  if(EZTEST_FLOAT_ULP_PRECISION)
    set(EZTEST_FLOAT_ULP_PRECISION_ "--flt-ulp=${EZTEST_FLOAT_ULP_PRECISION}")
  endif()
  if(EZTEST_FLOAT_ULP_PRECISION)
    set(EZTEST_DOUBLE_ULP_PRECISION_ "--dbl-ulp=${EZTEST_DOUBLE_ULP_PRECISION}")
  endif()
  if(EZTEST_DISABLE_WARNINGS)
    set(EZTEST_DISABLE_WARNINGS_ "--disable-warnings")
  else()
    set(EZTEST_DISABLE_WARNINGS_ "--enable-warnings")
  endif()
  if(EZTEST_DISABLE_LINTS)
    set(EZTEST_LINTS_WARNINGS_ "--disable-lints")
  endif()
  if(EZTEST_STRICT_NAMESPACE)
    set(EZTEST_STRICT_NAMESPACE_ "--strict-namespace")
  endif()

  set(EZTEST_FREEZE_TARGET_ "eztest-freeze-hdr-")
  set(EZTEST_INTERNAL_PREFIX_ "include/eztest")

  # Call scripts/freeze.py with arguments. Set all sources as dependency
  add_custom_command(
    OUTPUT include/eztest/eztest.h
    COMMAND ${EZTEST_FREEZE_}
    ${EZTEST_ULP_PRECISION_}
    ${EZTEST_FLOAT_ULP_PRECISION_}
    ${EZTEST_DOUBLE_ULP_PRECISION_}
    ${EZTEST_DISABLE_WARNINGS_}
    ${EZTEST_LINTS_WARNINGS_}
    ${EZTEST_STRICT_NAMESPACE_}
    --src=${PROJECT_SOURCE_DIR}/src/eztest/eztest.h
    --prefix=${PROJECT_BINARY_DIR}/${EZTEST_INTERNAL_PREFIX_}
    --dst=eztest.h
    --trim-pragmas
    DEPENDS
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-api.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-arch.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-asserts-impl.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-c-asserts-impl.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-compiler-warnings.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-compiler.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-containers.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-cxx-asserts-impl.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-duration.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-fail.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-float-compare.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-group-it.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-hex-var-printer.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-lang-bits.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-lang.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-libc-incs.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-libc.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-libm.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-list.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-main.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-pre-processor.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-proc.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-reqs.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-results.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-run.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-status.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-struct-padding.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-syscall.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-system.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-test-setup.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-test.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest-time.h
    ${PROJECT_SOURCE_DIR}/src/eztest/eztest.h
  )

  add_custom_target(
    ${EZTEST_FREEZE_TARGET_}
    ALL
    DEPENDS ${PROJECT_BINARY_DIR}/${EZTEST_INTERNAL_PREFIX_}/eztest.h
  )


  if(EZTEST_INSTALL_CMAKE_PACKAGE)
    install(
      TARGETS eztest
      EXPORT eztest_targets
    )

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
      "eztest-config-version.cmake"
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY SameMajorVersion
    )

    configure_package_config_file(
      "${PROJECT_SOURCE_DIR}/cmake/eztest-config.cmake.in"
      "${PROJECT_BINARY_DIR}/eztest-config.cmake"
      INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )

    install(
      EXPORT eztest_targets
      FILE eztest-targets.cmake
      NAMESPACE eztest::
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )

    install(
      FILES "${PROJECT_BINARY_DIR}/eztest-config.cmake"
      "${PROJECT_BINARY_DIR}/eztest-config-version.cmake"
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )
  endif()

  install(
    DIRECTORY ${PROJECT_BINARY_DIR}/include/eztest
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

  if(EZTEST_BUILD_TESTS)
    add_subdirectory(tests)
  endif()
else()
  macro(eztest_add_flag_ EZTEST_FLAG_)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EZTEST_FLAG}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EZTEST_FLAG}")
  endmacro()

  if(EZTEST_ULP_PRECISION)
    eztest_add_flag_("-DEZTEST_ULP_PRECISION=${EZTEST_ULP_PRECISION}")
  endif()
  if(EZTEST_FLOAT_ULP_PRECISION)
    eztest_add_flag_("-DEZTEST_FLOAT_ULP_PRECISION=${EZTEST_FLOAT_ULP_PRECISION}")
  endif()
  if(EZTEST_DOUBLE_ULP_PRECISION)
    eztest_add_flag_("-DEZTEST_DOUBLE_ULP_PRECISION=${EZTEST_DOUBLE_ULP_PRECISION}")
  endif()
  if(EZTEST_DISABLE_WARNINGS)
    eztest_add_flag_("-DEZTEST_DISABLE_WARNINGS=1")
  else()
    eztest_add_flag_("-DEZTEST_DISABLE_WARNINGS=0")
  endif()
endif()
