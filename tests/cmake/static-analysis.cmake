if(EZTEST_STATIC_ANALYSIS_INC_)
  return()
endif()
set(EZTEST_STATIC_ANALYSIS_INC_ ON)

# Search for external programs
set(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)

option(EZTEST_CLANG_TIDY "Path: path to clang tidy executable")

set(EZTEST_CLANG_TIDY_EXE_NAMES_
    clang-tidy-22  
    clang-tidy-21  
    clang-tidy-20
    clang-tidy-19
    clang-tidy-18
    clang-tidy-17
    clang-tidy-16
    clang-tidy-15
    clang-tidy-14
    clang-tidy-13
    clang-tidy-12
    clang-tidy-11
    clang-tidy-10
    clang-tidy
)

if(EZTEST_CLANG_TIDY)
  find_program(
    EZTEST_CLANG_TIDY_EXE_
    NAMES ${EZTEST_CLANG_TIDY} NO_CACHE
    NO_DEFAULT_PATH
    NO_PACKAGE_ROOT_PATH
    NO_CMAKE_PATH
    NO_CMAKE_ENVIRONMENT_PATH
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_SYSTEM_PATH
    NO_CMAKE_FIND_ROOT_PATH
  )

endif()
if(NOT EZTEST_CLANG_TIDY_EXE_)
  find_program(
    EZTEST_CLANG_TIDY_EXE_ NAMES ${EZTEST_CLANG_TIDY_EXE_NAMES_} NO_CACHE
  )
endif()

if(NOT EZTEST_CLANG_TIDY_EXE_)
  message(WARNING "Unable to find clang-tidy")
  function(eztest_sa_add_source_file_ EZTEST_SA_SOURCE_FILE_ EZTEST_SA_LANG_)

  endfunction()
  return()
endif()

# execute_process( COMMAND ${EZTEST_CLANG_TIDY_EXE_} --version ERROR_VARIABLE
# EZTEST_CLANG_TIDY_VERSION_ERR_ OUTPUT_VARIABLE EZTEST_CLANG_TIDY_VERSION_OUT_
# )
#
# if(EZTEST_CLANG_TIDY_VERSION_ERR_) unset(EZTEST_CLANG_TIDY_VERSION_OUT_)
# endif()
#
# if(EZTEST_CLANG_TIDY_VERSION_OUT_) string( REGEX MATCH "version[
# ]+[0-9]+\.[0-9]+\.[0-9]+" EZTEST_CLANG_TIDY_VERSION_
# ${EZTEST_CLANG_TIDY_VERSION_OUT_} ) string( REGEX MATCH
# "[0-9]+\.[0-9]+\.[0-9]+" EZTEST_CLANG_TIDY_VERSION_
# ${EZTEST_CLANG_TIDY_VERSION_} ) string( REPLACE "." ";"
# EZTEST_CLANG_TIDY_VERSION_ ${EZTEST_CLANG_TIDY_VERSION_} ) list( GET
# EZTEST_CLANG_TIDY_VERSION_ 0 EZTEST_CLANG_TIDY_VERSION_ ) endif()
#
# if(NOT EZTEST_CLANG_TIDY_VERSION_) message(WARNING "Unable to determine
# clang-tidy version") else() if(EZTEST_CLANG_TIDY_VERSION_ LESS 19)
# message(WARNING "clang-tidy version ${EZTEST_CLANG_TIDY_VERSION_} found.
# Minimum 14 required!") function(eztest_sa_add_source_file_
# EZTEST_SA_SOURCE_FILE_ EZTEST_SA_LANG_) endfunction() return() endif() endif()

set(EZTEST_SA_FIXUP_COMPILE_COMMANDS_TARGET_
    "${PROJECT_BINARY_DIR}/.eztest-fixup-compile-commands.json"
)

add_custom_command(
  OUTPUT ${EZTEST_SA_FIXUP_COMPILE_COMMANDS_TARGET_}
  COMMAND sed -e "s/-fstrict-flex-arrays//g" -i
          ${PROJECT_BINARY_DIR}/compile_commands.json
)

set(EZTEST_SA_TARGET_ "run-static-analysis")
add_custom_target(${EZTEST_SA_TARGET_})

function(eztest_sa_add_source_file_ EZTEST_SA_SOURCE_FILE_ EZTEST_SA_LANG_)
  if(NOT EZTEST_CLANG_TIDY_EXE_)
    return()
  endif()
  cmake_path(
    GET
    EZTEST_SA_SOURCE_FILE_
    FILENAME
    EZTEST_SA_SOURCE_FILE_TARGET_
  )
  string(
    REGEX
    REPLACE "[_\./]"
            "-"
            EZTEST_SA_SOURCE_FILE_TARGET_
            ${EZTEST_SA_SOURCE_FILE_TARGET_}
  )
  set(EZTEST_SA_SOURCE_FILE_TARGET_
      "${EZTEST_SA_TARGET_}-${EZTEST_SA_SOURCE_FILE_TARGET_}"
  )

  add_custom_target(
    ${EZTEST_SA_SOURCE_FILE_TARGET_}
    DEPENDS ${EZTEST_FREEZE_TARGET_} ${EZTEST_SA_FIXUP_COMPILE_COMMANDS_TARGET_}
    COMMAND
      ${EZTEST_CLANG_TIDY_EXE_} ${EZTEST_SA_SOURCE_FILE_}
      -p=${PROJECT_BINARY_DIR} -header-filter=.*
      -extra-arg=-Wno-unknown-warning-option
  )
  string(TOLOWER ${EZTEST_SA_LANG_} EZTEST_SA_LOWER_LANG_)
  set(EZTEST_SA_LANG_TARGET_ "${EZTEST_SA_TARGET_}-${EZTEST_SA_LOWER_LANG_}")
  if(NOT TARGET ${EZTEST_SA_LANG_TARGET_})
    add_custom_target(${EZTEST_SA_LANG_TARGET_})
    add_dependencies(${EZTEST_SA_TARGET_} ${EZTEST_SA_LANG_TARGET_})
  endif()

  add_dependencies(${EZTEST_SA_LANG_TARGET_} ${EZTEST_SA_SOURCE_FILE_TARGET_})
endfunction()
