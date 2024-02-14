option(EZTEST_TEST_LOG_TO_STDOUT_
       "Bool: set/unset to configure whether dump test failures to stdout" OFF
)
option(EZTEST_TEST_WERROR_ "Bool: set/unset to configure -Werror is enabled" ON)

option(EZTEST_TEST_WEVERYTHING_
       "Bool: set/unset to configure whether all warnings are on" ON
)

option(EZTEST_TEST_HIDE_WARNINGS_
       "Bool: set/unset to configure whether to hide known warnings" ON
)

option(EZTEST_TEST_SANITIZERS_
       "Bool: set/unset to configure sanitizers are enabled" ON
)

option(
  EZTEST_TEST_INSTALLED_NO_FAIL_
  "Bool: set/unset to configure whether install find test can fail if no installation"
  OFF
)

cmake_policy(SET CMP0101 NEW)

if(EZTEST_TEST_LOG_TO_STDOUT_)
  set(EZTEST_TEST_LOG_TO_STDOUT_ "--dump-stdout")
else()
  set(EZTEST_TEST_LOG_TO_STDOUT_ "")
endif()

if(EZTEST_TEST_RUN_ENV_)
  set(EZTEST_TEST_RUN_ENV_ "--env=${EZTEST_TEST_RUN_ENV_}")
  set(EZTEST_TEST_SANITIZERS_ OFF)
else()
  set(EZTEST_TEST_RUN_ENV_ "")
endif()

if(EZTEST_TEST_TARGET_ARCH_)
  set(EZTEST_TEST_TARGET_ARCH_ "--arch=${EZTEST_TEST_TARGET_ARCH_}")
else()
  set(EZTEST_TEST_TARGET_ARCH_ "")
endif()

find_file(EZTEST_TEST_RUN_TEST_ run-test.py PATHS ${PROJECT_SOURCE_DIR}/scripts)

find_file(EZTEST_TEST_RUN_EXTERNAL_TEST_ run-external-test.py
          PATHS ${PROJECT_SOURCE_DIR}/scripts
)

if(NOT EZTEST_TEST_RUN_TEST_)
  message(WARNING "Cannot find run-test.py. Unable to run tests.")
  return()
endif()

if(EZTEST_TEST_HIDE_WARNINGS_)
  set(EZTEST_TEST_HIDE_WARNINGS_ "-DEZTEST_DISABLE_WARNINGS=1")
else()
  set(EZTEST_TEST_HIDE_WARNINGS_ "-DEZTEST_DISABLE_WARNINGS=0")
endif()

set(EZTEST_TEST_FORTIFY_SOURCE_ "-D_FORTIFY_SOURCE=2")
set(EZTEST_TEST_COMPILER_OPTS_
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-g3"
    "-fno-omit-frame-pointer"
    "-fstack-protector"
    "-fstrict-enums"
    "-fno-exceptions"
    "-fno-rtti"
    ${EZTEST_TEST_HIDE_WARNINGS_}
)

set(EZTEST_TEST_LINK_OPTS_ "-rdynamic")

set(EZTEST_TEST_COMPILER_C_OPTS_ ${EZTEST_TEST_COMPILER_OPTS_})
set(EZTEST_TEST_COMPILER_CXX_OPTS_ ${EZTEST_TEST_COMPILER_OPTS_})

if(NOT
   "${CMAKE_C_FLAGS}"
   STREQUAL
   ""
)
  string(
    REPLACE " "
            ";"
            EZTEST_TEST_COMPILER_C_OPTS_USR_
            ${CMAKE_C_FLAGS}
  )

  list(APPEND EZTEST_TEST_COMPILER_C_OPTS_ ${EZTEST_TEST_COMPILER_C_OPTS_USR_})
endif()
if(NOT
   "${CMAKE_CXX_FLAGS}"
   STREQUAL
   ""
)
  string(
    REPLACE " "
            ";"
            EZTEST_TEST_COMPILER_CXX_OPTS_USR_
            ${CMAKE_CXX_FLAGS}
  )
  list(APPEND EZTEST_TEST_COMPILER_CXX_OPTS_
       ${EZTEST_TEST_COMPILER_CXX_OPTS_USR_}
  )
endif()

set(EZTEST_TEST_LINK_C_OPTS_ ${EZTEST_TEST_LINK_OPTS_})
set(EZTEST_TEST_LINK_CXX_OPTS_ ${EZTEST_TEST_LINK_OPTS_})

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/sanitizers.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler-options.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/static-analysis.cmake)

if(NOT EZTEST_WARNING_C_FLAGS_)
  message("No C Warnings")
endif()
if(NOT EZTEST_WARNING_CXX_FLAGS_)
  message("No CXX Warnings")
endif()
if(NOT EZTEST_TEST_C_SANITIZER_OPTS_AND_POSTFIXES_)
  message("No C San options")
endif()
if(NOT EZTEST_TEST_CXX_SANITIZER_OPTS_AND_POSTFIXES_)
  message("No CXX San options")
endif()

if(EZTEST_TEST_WEVERYTHING_)
  list(APPEND EZTEST_TEST_COMPILER_C_OPTS_ ${EZTEST_WARNING_C_FLAGS_})
  list(APPEND EZTEST_TEST_COMPILER_CXX_OPTS_ ${EZTEST_WARNING_CXX_FLAGS_})
endif()

eztest_filter_supported_flags_("COMPILER" "C" EZTEST_TEST_COMPILER_C_OPTS_)
eztest_filter_supported_flags_("COMPILER" "CXX" EZTEST_TEST_COMPILER_CXX_OPTS_)
eztest_filter_supported_flags_("LINKER" "C" EZTEST_TEST_LINKER_C_OPTS_)
eztest_filter_supported_flags_("LINKER" "CXX" EZTEST_TEST_LINKER_CXX_OPTS_)

if(EZTEST_TEST_WERROR_)
  list(APPEND EZTEST_TEST_COMPILER_C_OPTS_ "-Werror")

  list(APPEND EZTEST_TEST_COMPILER_CXX_OPTS_ "-Werror")
endif()

set(EZTEST_TEST_EXTERNAL_TARGET_ "check-external")
set(EZTEST_TEST_CHECK_ALL_TARGET_ "check-all")
set(EZTEST_TEST_CHECK_ALL_ALLSAN_TARGET_ "check-all-san")
set(EZTEST_TEST_CHECK_ALL_ALL_TARGET_ "check-all-all")

set(EZTEST_TEST_BUILD_ALL_TARGET_ "build-all")
set(EZTEST_TEST_BUILD_ALL_ALLSAN_TARGET_ "build-all-san")
set(EZTEST_TEST_BUILD_ALL_ALL_TARGET_ "build-all-all")
add_custom_target(${EZTEST_TEST_CHECK_ALL_ALL_TARGET_})
add_custom_target(${EZTEST_TEST_BUILD_ALL_ALL_TARGET_})

set(EZTEST_TEST_STANDARDS_INFO_TARGET_ eztest-standard-info)
add_executable(
  "${EZTEST_TEST_STANDARDS_INFO_TARGET_}-cxx"
  ${CMAKE_CURRENT_SOURCE_DIR}/config/eztest-standard-info.cc
)

add_executable(
  "${EZTEST_TEST_STANDARDS_INFO_TARGET_}-c"
  ${CMAKE_CURRENT_SOURCE_DIR}/config/eztest-standard-info.c
)

function(eztest_test_add_test_file_ EZTEST_TEST_DIR_ EZTEST_TEST_BASENAME_)
  string(
    REGEX
    REPLACE "[\._]"
            "-"
            EZTEST_TEST_EXE_TARGET_
            "eztest-${EZTEST_TEST_BASENAME_}"
  )

  set(EZTEST_TEST_SRC_ "${EZTEST_TEST_DIR_}/${EZTEST_TEST_BASENAME_}")

  string(
    REGEX
    REPLACE "^test[-_]"
            ""
            EZTEST_TEST_TARGET_
            ${EZTEST_TEST_BASENAME_}
  )
  string(
    REGEX
    REPLACE "[\._]"
            "-"
            EZTEST_TEST_TARGET_
            ${EZTEST_TEST_TARGET_}
  )

  set(EZTEST_TEST_CHECK_TARGET_ "check-${EZTEST_TEST_TARGET_}")
  set(EZTEST_TEST_BUILD_TARGET_ "build-${EZTEST_TEST_TARGET_}")

  get_filename_component(EZTEST_LANG_ ${EZTEST_TEST_BASENAME_} LAST_EXT)
  if(${EZTEST_LANG_} STREQUAL ".c")
    set(EZTEST_LANG_ "C")
  elseif(${EZTEST_LANG_} STREQUAL ".cc")
    set(EZTEST_LANG_ "CXX")
  else()
    message(FATAL_ERROR "Unknown language for file: ${EZTEST_TEST_BASENAME_}")
  endif()

  string(TOLOWER ${EZTEST_LANG_} EZTEST_LOWER_LANG_)
  eztest_sa_add_source_file_(${EZTEST_TEST_SRC_} ${EZTEST_LANG_})

  set(EZTEST_TEST_SANITIZER_OPTS_AND_POSTFIXES_
      ${EZTEST_TEST_${EZTEST_LANG_}_SANITIZER_OPTS_AND_POSTFIXES_}
  )

  set(EZTEST_TEST_COMPILER_OPTS_ ${EZTEST_TEST_${EZTEST_LANG_}_COMPILER_OPTS_})
  set(EZTEST_TEST_LINKER_OPTS_ ${EZTEST_TEST_${EZTEST_LANG_}_LINKER_OPTS_})

  foreach(EZTEST_TEST_SAN_OPTS_AND_POSTFIX_ IN
          LISTS EZTEST_TEST_SANITIZER_OPTS_AND_POSTFIXES_
  )

    eztest_test_san_split_opt_and_postfix_(
      ${EZTEST_TEST_SAN_OPTS_AND_POSTFIX_}
      EZTEST_TEST_SAN_LINK_OPT_
      EZTEST_TEST_SAN_COMPILER_OPT_
      EZTEST_TEST_SAN_POSTFIX_
    )

    unset(EZTEST_TEST_USE_LINK_OPTS_)
    list(
      APPEND
      EZTEST_TEST_USE_LINK_OPTS_
      ${EZTEST_TEST_LINK_${EZTEST_LANG_}_OPTS_}
      ${EZTEST_TEST_SAN_LINK_OPT_}
    )

    unset(EZTEST_TEST_USE_COMPILER_OPTS_)
    list(
      APPEND
      EZTEST_TEST_USE_COMPILER_OPTS_
      ${EZTEST_TEST_COMPILER_${EZTEST_LANG_}_OPTS_}
      ${EZTEST_TEST_SAN_COMPILER_OPT_}
    )

    set(EZTEST_TEST_EXE_SAN_TARGET_
        "${EZTEST_TEST_EXE_TARGET_}${EZTEST_TEST_SAN_POSTFIX_}"
    )
    set(EZTEST_TEST_CHECK_SAN_TARGET_
        "${EZTEST_TEST_CHECK_TARGET_}${EZTEST_TEST_SAN_POSTFIX_}"
    )
    set(EZTEST_TEST_BUILD_SAN_TARGET_
        "${EZTEST_TEST_BUILD_TARGET_}${EZTEST_TEST_SAN_POSTFIX_}"
    )

    set(EZTEST_TEST_CHECK_ALL_LANG_SAN_TARGET_
        "${EZTEST_TEST_CHECK_ALL_TARGET_}-${EZTEST_LOWER_LANG_}${EZTEST_TEST_SAN_POSTFIX_}"
    )
    set(EZTEST_TEST_BUILD_ALL_LANG_SAN_TARGET_
        "${EZTEST_TEST_BUILD_ALL_TARGET_}-${EZTEST_LOWER_LANG_}${EZTEST_TEST_SAN_POSTFIX_}"
    )

    add_executable(
      ${EZTEST_TEST_EXE_SAN_TARGET_} EXCLUDE_FROM_ALL ${EZTEST_TEST_SRC_}
    )
    target_include_directories(
      ${EZTEST_TEST_EXE_SAN_TARGET_} PRIVATE ${PROJECT_BINARY_DIR}/include
    )
    target_compile_options(
      ${EZTEST_TEST_EXE_SAN_TARGET_} BEFORE
      PRIVATE ${EZTEST_TEST_USE_COMPILER_OPTS_}
    )
    target_link_options(
      ${EZTEST_TEST_EXE_SAN_TARGET_} PRIVATE ${EZTEST_TEST_USE_LINK_OPTS_}
    )

    add_dependencies(${EZTEST_TEST_EXE_SAN_TARGET_} ${EZTEST_FREEZE_TARGET_})

    set(EZTEST_TEST_LANG_STANDARDS_INFO_TARGET_
        "${EZTEST_TEST_STANDARDS_INFO_TARGET_}-${EZTEST_LOWER_LANG_}"
    )

    add_custom_target(
      ${EZTEST_TEST_BUILD_SAN_TARGET_} DEPENDS ${EZTEST_TEST_EXE_SAN_TARGET_}
    )

    add_custom_target(
      ${EZTEST_TEST_CHECK_SAN_TARGET_}
      DEPENDS ${EZTEST_TEST_EXE_SAN_TARGET_}
              ${EZTEST_TEST_LANG_STANDARDS_INFO_TARGET_}
      COMMAND
        ${EZTEST_TEST_RUN_TEST_} --exe=${EZTEST_TEST_EXE_SAN_TARGET_}
        --src=${EZTEST_TEST_SRC_}
        --compiler=${CMAKE_${EZTEST_LANG_}_COMPILER_ID}-${CMAKE_${EZTEST_LANG_}_COMPILER_VERSION}
        --san="s${EZTEST_TEST_SAN_POSTFIX_}" --lang=${EZTEST_LANG_}
        --lang-info=${EZTEST_TEST_LANG_STANDARDS_INFO_TARGET_}
        "${EZTEST_TEST_LOG_TO_STDOUT_}" "${EZTEST_TEST_RUN_ENV_}"
        "${EZTEST_TEST_TARGET_ARCH_}"
    )

    # First of {lang}-{san} type
    if(NOT TARGET ${EZTEST_TEST_CHECK_ALL_LANG_SAN_TARGET_})
      set(EZTEST_TEST_CHECK_ALL_SAN_TARGET_
          "${EZTEST_TEST_CHECK_ALL_TARGET_}${EZTEST_TEST_SAN_POSTFIX_}"
      )
      set(EZTEST_TEST_BUILD_ALL_SAN_TARGET_
          "${EZTEST_TEST_BUILD_ALL_TARGET_}${EZTEST_TEST_SAN_POSTFIX_}"
      )

      # Setup generic-{san} target
      if(NOT TARGET ${EZTEST_TEST_CHECK_ALL_SAN_TARGET_})
        # we build all-all from all-all-lang so no need to link all-{san} to
        # anything
        add_custom_target(${EZTEST_TEST_CHECK_ALL_SAN_TARGET_})
        add_custom_target(${EZTEST_TEST_BUILD_ALL_SAN_TARGET_})
      endif()
      set(EZTEST_TEST_CHECK_ALL_ALL_LANG_TARGET_
          "${EZTEST_TEST_CHECK_ALL_ALL_TARGET_}-${EZTEST_LOWER_LANG_}"
      )
      set(EZTEST_TEST_BUILD_ALL_ALL_LANG_TARGET_
          "${EZTEST_TEST_BUILD_ALL_ALL_TARGET_}-${EZTEST_LOWER_LANG_}"
      )
      # Setup all-all-lang target
      if(NOT TARGET ${EZTEST_TEST_CHECK_ALL_ALL_LANG_TARGET_})
        add_custom_target(${EZTEST_TEST_CHECK_ALL_ALL_LANG_TARGET_})
        add_custom_target(${EZTEST_TEST_BUILD_ALL_ALL_LANG_TARGET_})
        # all-all-lang -> all-all
        add_dependencies(
          ${EZTEST_TEST_CHECK_ALL_ALL_TARGET_}
          ${EZTEST_TEST_CHECK_ALL_ALL_LANG_TARGET_}
        )
        add_dependencies(
          ${EZTEST_TEST_BUILD_ALL_ALL_TARGET_}
          ${EZTEST_TEST_BUILD_ALL_ALL_LANG_TARGET_}
        )
      endif()

      # Add {lang}-{san} target
      add_custom_target(${EZTEST_TEST_CHECK_ALL_LANG_SAN_TARGET_})
      add_custom_target(${EZTEST_TEST_BUILD_ALL_LANG_SAN_TARGET_})
      # Add {lang}-{san} -> generic-{san}
      add_dependencies(
        ${EZTEST_TEST_CHECK_ALL_SAN_TARGET_}
        ${EZTEST_TEST_CHECK_ALL_LANG_SAN_TARGET_}
      )
      add_dependencies(
        ${EZTEST_TEST_BUILD_ALL_SAN_TARGET_}
        ${EZTEST_TEST_BUILD_ALL_LANG_SAN_TARGET_}
      )
      # Add {lang}-{san} -> all-all-lang
      add_dependencies(
        ${EZTEST_TEST_CHECK_ALL_ALL_LANG_TARGET_}
        ${EZTEST_TEST_CHECK_ALL_LANG_SAN_TARGET_}
      )
      add_dependencies(
        ${EZTEST_TEST_BUILD_ALL_ALL_LANG_TARGET_}
        ${EZTEST_TEST_BUILD_ALL_LANG_SAN_TARGET_}
      )

      # If there is an actual sanitizer
      if(NOT
         "${EZTEST_TEST_SAN_POSTFIX_}"
         STREQUAL
         ""
      )
        if(NOT TARGET ${EZTEST_TEST_CHECK_ALL_ALLSAN_TARGET_})
          add_custom_target(${EZTEST_TEST_CHECK_ALL_ALLSAN_TARGET_})
          add_custom_target(${EZTEST_TEST_BUILD_ALL_ALLSAN_TARGET_})
          add_dependencies(
            ${EZTEST_TEST_CHECK_ALL_ALL_TARGET_}
            ${EZTEST_TEST_CHECK_ALL_ALLSAN_TARGET_}
          )
          add_dependencies(
            ${EZTEST_TEST_BUILD_ALL_ALL_TARGET_}
            ${EZTEST_TEST_BUILD_ALL_ALLSAN_TARGET_}
          )
        endif()

        # setup check-all-{lang}-san
        set(EZTEST_TEST_CHECK_ALL_LANG_ALLSAN_TARGET_
            "${EZTEST_TEST_CHECK_ALL_TARGET_}-${EZTEST_LOWER_LANG_}-san"
        )
        set(EZTEST_TEST_BUILD_ALL_LANG_ALLSAN_TARGET_
            "${EZTEST_TEST_BUILD_ALL_TARGET_}-${EZTEST_LOWER_LANG_}-san"
        )
        if(NOT TARGET ${EZTEST_TEST_CHECK_ALL_LANG_ALLSAN_TARGET_})
          add_custom_target(${EZTEST_TEST_CHECK_ALL_LANG_ALLSAN_TARGET_})
          add_custom_target(${EZTEST_TEST_BUILD_ALL_LANG_ALLSAN_TARGET_})
          # check-all-{lang}-san -> check-all-san
          add_dependencies(
            ${EZTEST_TEST_CHECK_ALL_ALLSAN_TARGET_}
            ${EZTEST_TEST_CHECK_ALL_LANG_ALLSAN_TARGET_}
          )
          add_dependencies(
            ${EZTEST_TEST_BUILD_ALL_ALLSAN_TARGET_}
            ${EZTEST_TEST_BUILD_ALL_LANG_ALLSAN_TARGET_}
          )
        endif()
        # {lang}-{san} -> check-all-{lang}-san
        add_dependencies(
          ${EZTEST_TEST_CHECK_ALL_LANG_ALLSAN_TARGET_}
          ${EZTEST_TEST_CHECK_ALL_LANG_SAN_TARGET_}
        )
        add_dependencies(
          ${EZTEST_TEST_BUILD_ALL_LANG_ALLSAN_TARGET_}
          ${EZTEST_TEST_BUILD_ALL_LANG_SAN_TARGET_}
        )
      endif()

    endif()
    # This -> {lang}-san
    add_dependencies(
      ${EZTEST_TEST_CHECK_ALL_LANG_SAN_TARGET_}
      ${EZTEST_TEST_CHECK_SAN_TARGET_}
    )
    add_dependencies(
      ${EZTEST_TEST_BUILD_ALL_LANG_SAN_TARGET_}
      ${EZTEST_TEST_BUILD_SAN_TARGET_}
    )
  endforeach()
endfunction()

function(eztest_test_add_tests_)
  foreach(EZTEST_TEST_FILE_ IN LISTS ARGN)
    eztest_test_add_test_file_(${CMAKE_CURRENT_SOURCE_DIR} ${EZTEST_TEST_FILE_})
  endforeach()
endfunction()

eztest_test_add_tests_(
  test-complete.c
  test-complete.cc
  test-sig.c
  test-success.c
  test-strings-success.cc
  test-strings-failure.cc
  test-fail.c
  test-c11-bool.c
)

if(NOT EZTEST_TEST_RUN_EXTERNAL_TEST_)
  message(
    WARNING "Cannot find run-external-test.py. Unable to run external tests."
  )
  return()
endif()

add_custom_target(
  check-external-cmake-include
  COMMAND
    ${EZTEST_TEST_RUN_EXTERNAL_TEST_}
    --src=${PROJECT_SOURCE_DIR}/tests/test-external-cmake-include
    --dst=${PROJECT_BINARY_DIR}/tests/test-external-cmake-include
    -DEZTEST_TEST_EXTERNAL_INCLUDE_PATH_=${PROJECT_SOURCE_DIR}
)

unset(EZTEST_TEST_EXTERNAL_INSTALL_INCLUDE_MAY_FAIL_)
if(EZTEST_TEST_INSTALLED_NO_FAIL_
   OR "${CMAKE_INSTALL_PREFIX}" STREQUAL
      "${PROJECT_BINARY_DIR}/tests/test-installed-eztest"
)
  set(EZTEST_TEST_EXTERNAL_INSTALL_INCLUDE_MAY_FAIL_ "--no-fail")
endif()
add_custom_target(
  check-external-install-include
  COMMAND
    ${EZTEST_TEST_RUN_EXTERNAL_TEST_}
    --src=${PROJECT_SOURCE_DIR}/tests/test-external-install-include
    --dst=${PROJECT_BINARY_DIR}/tests/test-external-install-include
    --install=${PROJECT_BINARY_DIR}/tests/test-installed-eztest
    "${EZTEST_TEST_EXTERNAL_INSTALL_INCLUDE_MAY_FAIL_}"
)

add_custom_target(
  ${EZTEST_TEST_EXTERNAL_TARGET_} DEPENDS check-external-cmake-include
                                          check-external-install-include
)
