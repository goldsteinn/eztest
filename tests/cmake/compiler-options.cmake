if(EZTEST_COMPILER_OPTIONS_INC_)
  return()
endif()
set(EZTEST_COMPILER_OPTIONS_INC_ ON)

option(
  EZTEST_STACK_ALLOC_LIMIT_
  "Set warning limit for stack size related checks (0 means none)"
  0
)
option(
  EZTEST_HEAP_ALLOC_LIMIT_
  "Set warning limit for heap size related checks (0 means none)"
  0
)

set(
  EZTEST_CLANG_18_0_0_WARNING_COMMON_FLAGS_
  "-Weverything"
  "-Wunsafe-buffer-usage -fsafe-buffer-usage-suggestions"
)

if(${EZTEST_STACK_ALLOC_LIMIT_} GREATER 0)
  list(
    APPEND
    EZTEST_CLANG_18_0_0_WARNING_COMMON_FLAGS_
    "-Wframe-larger-than=${EZTEST_STACK_ALLOC_LIMIT_}"
  )
endif()

set(
  EZTEST_CLANG_18_0_0_WARNING_C_FLAGS_
  ${EZTEST_CLANG_18_0_0_WARNING_COMMON_FLAGS_}
)
set(
  EZTEST_CLANG_18_0_0_WARNING_CXX_FLAGS_
  ${EZTEST_CLANG_18_0_0_WARNING_COMMON_FLAGS_}
)

set(
  EZTEST_GCC_14_0_0_WARNING_COMMON_FLAGS_
  "-WNSObject-attribute"
  "-Wabi=0"
  "-Waddress"
  "-Waddress-of-packed-member"
  "-Waggregate-return"
  "-Waggressive-loop-optimizations"
  "-Wall"
  "-Walloc-zero"
  "-Walloca"
  "-Wanalyzer-allocation-size"
  "-Wanalyzer-deref-before-check"
  "-Wanalyzer-double-fclose"
  "-Wanalyzer-double-free"
  "-Wanalyzer-exposure-through-output-file"
  "-Wanalyzer-exposure-through-uninit-copy"
  "-Wanalyzer-fd-access-mode-mismatch"
  "-Wanalyzer-fd-double-close"
  "-Wanalyzer-fd-leak"
  "-Wanalyzer-fd-phase-mismatch"
  "-Wanalyzer-fd-type-mismatch"
  "-Wanalyzer-fd-use-after-close"
  "-Wanalyzer-fd-use-without-check"
  "-Wanalyzer-file-leak"
  "-Wanalyzer-free-of-non-heap"
  "-Wanalyzer-imprecise-fp-arithmetic"
  "-Wanalyzer-infinite-recursion"
  "-Wanalyzer-jump-through-null"
  "-Wanalyzer-malloc-leak"
  "-Wanalyzer-mismatching-deallocation"
  "-Wanalyzer-null-argument"
  "-Wanalyzer-null-dereference"
  "-Wanalyzer-out-of-bounds"
  "-Wanalyzer-possible-null-argument"
  "-Wanalyzer-possible-null-dereference"
  "-Wanalyzer-putenv-of-auto-var"
  "-Wanalyzer-shift-count-negative"
  "-Wanalyzer-shift-count-overflow"
  "-Wanalyzer-stale-setjmp-buffer"
  "-Wanalyzer-tainted-allocation-size"
  "-Wanalyzer-tainted-array-index"
  "-Wanalyzer-tainted-assertion"
  "-Wanalyzer-tainted-divisor"
  "-Wanalyzer-tainted-offset"
  "-Wanalyzer-tainted-size"
  "-Wanalyzer-too-complex"
  "-Wanalyzer-unsafe-call-within-signal-handler"
  "-Wanalyzer-use-after-free"
  "-Wanalyzer-use-of-pointer-in-stale-stack-frame"
  "-Wanalyzer-use-of-uninitialized-value"
  "-Wanalyzer-va-arg-type-mismatch"
  "-Wanalyzer-va-list-exhausted"
  "-Wanalyzer-va-list-leak"
  "-Wanalyzer-va-list-use-after-va-end"
  "-Wanalyzer-write-to-const"
  "-Wanalyzer-write-to-string-literal"
  "-Warith-conversion"
  "-Warray-bounds=2"
  "-Warray-compare"
  "-Warray-parameter=2"
  "-Wattribute-alias=2"
  "-Wattribute-warning"
  "-Wattributes"
  "-Wbidi-chars=any,ucn"
  "-Wbool-compare"
  "-Wbool-operation"
  "-Wbuiltin-declaration-mismatch"
  "-Wbuiltin-macro-redefined"
  "-Wcannot-profile"
  "-Wcast-align=strict"
  "-Wcast-function-type"
  "-Wcast-qual"
  "-Wchar-subscripts"
  "-Wclobbered"
  "-Wcomment"
  "-Wcomments"
  "-Wcomplain-wrong-lang"
  "-Wconversion"
  "-Wcoverage-invalid-line-number"
  "-Wcoverage-mismatch"
  "-Wcpp"
  "-Wdangling-else"
  "-Wdangling-pointer=2"
  "-Wdate-time"
  "-Wdeprecated"
  "-Wdeprecated-declarations"
  "-Wdisabled-optimization"
  "-Wdiv-by-zero"
  "-Wdouble-promotion"
  "-Wduplicated-branches"
  "-Wduplicated-cond"
  "-Wempty-body"
  "-Wendif-labels"
  "-Wenum-compare"
  "-Wenum-conversion"
  "-Wexpansion-to-defined"
  "-Wextra"
  "-Wflex-array-member-not-at-end"
  "-Wfloat-conversion"
  "-Wfloat-equal"
  "-Wformat-contains-nul"
  "-Wformat-diag"
  "-Wformat-extra-args"
  "-Wformat-nonliteral"
  "-Wformat-overflow=2"
  "-Wformat-security"
  "-Wformat-signedness"
  "-Wformat-truncation=2"
  "-Wformat-y2k"
  "-Wformat-zero-length"
  "-Wformat=2"
  "-Wframe-address"
  "-Wfree-nonheap-object"
  "-Whsa"
  "-Wif-not-aligned"
  "-Wignored-attributes"
  "-Wignored-qualifiers"
  "-Wimplicit-fallthrough=5"
  "-Winfinite-recursion"
  "-Winit-self"
  "-Winline"
  "-Wint-in-bool-context"
  "-Wint-to-pointer-cast"
  "-Winvalid-memory-model"
  "-Winvalid-pch"
  "-Winvalid-utf8"
  "-Wlogical-not-parentheses"
  "-Wlogical-op"
  "-Wlong-long"
  "-Wlto-type-mismatch"
  "-Wmain"
  "-Wmaybe-uninitialized"
  "-Wmemset-elt-size"
  "-Wmemset-transposed-args"
  "-Wmisleading-indentation"
  "-Wmismatched-dealloc"
  "-Wmissing-attributes"
  "-Wmissing-braces"
  "-Wmissing-declarations"
  "-Wmissing-field-initializers"
  "-Wmissing-format-attribute"
  "-Wmissing-include-dirs"
  "-Wmissing-noreturn"
  "-Wmissing-profile"
  "-Wmultichar"
  "-Wmultistatement-macros"
  "-Wnarrowing"
  "-Wnonnull"
  "-Wnonnull-compare"
  "-Wnormalized=nfc"
  "-Wnull-dereference"
  "-Wodr"
  "-Wopenacc-parallelism"
  "-Wopenmp-simd"
  "-Woverflow"
  "-Woverlength-strings"
  "-Wpacked"
  "-Wpacked-bitfield-compat"
  "-Wpacked-not-aligned"
  "-Wpadded"
  "-Wparentheses"
  "-Wpedantic"
  "-Wpointer-arith"
  "-Wpointer-compare"
  "-Wpragmas"
  "-Wprio-ctor-dtor"
  "-Wpsabi"
  "-Wredundant-decls"
  "-Wrestrict"
  "-Wreturn-local-addr"
  "-Wreturn-type"
  "-Wscalar-storage-order"
  "-Wsequence-point"
  "-Wshadow"
  "-Wshadow-compatible-local"
  "-Wshadow-local"
  "-Wshift-count-negative"
  "-Wshift-count-overflow"
  "-Wshift-negative-value"
  "-Wshift-overflow=2"
  "-Wsign-compare"
  "-Wsign-conversion"
  "-Wsizeof-array-argument"
  "-Wsizeof-array-div"
  "-Wsizeof-pointer-div"
  "-Wsizeof-pointer-memaccess"
  "-Wstack-protector"
  "-Wstrict-aliasing=1"
  "-Wstrict-overflow=5"
  "-Wstring-compare"
  "-Wstringop-overflow=4"
  "-Wstringop-overread"
  "-Wstringop-truncation"
  "-Wsuggest-attribute=cold"
  "-Wsuggest-attribute=const"
  "-Wsuggest-attribute=format"
  "-Wsuggest-attribute=malloc"
  "-Wsuggest-attribute=noreturn"
  "-Wsuggest-attribute=pure"
  "-Wsuggest-final-methods"
  "-Wsuggest-final-types"
  "-Wswitch"
  "-Wswitch-bool"
  "-Wswitch-default"
  "-Wswitch-enum"
  "-Wswitch-outside-range"
  "-Wswitch-unreachable"
  "-Wsync-nand"
  # This isn't really a test for eztest codebase
  # "-Wsystem-headers"
  "-Wtautological-compare"
  "-Wtrampolines"
  "-Wtrigraphs"
  "-Wtrivial-auto-var-init"
  "-Wtsan"
  "-Wtype-limits"
  "-Wundef"
  "-Wunicode"
  "-Wuninitialized"
  "-Wunknown-pragmas"
  "-Wunreachable-code"
  "-Wunsafe-loop-optimizations"
  "-Wunused"
  "-Wunused-but-set-parameter"
  "-Wunused-but-set-variable"
  "-Wunused-const-variable=2"
  "-Wunused-function"
  "-Wunused-label"
  "-Wunused-local-typedefs"
  "-Wunused-macros"
  "-Wunused-result"
  "-Wunused-value"
  "-Wunused-variable"
  "-Wuse-after-free=3"
  "-Wvarargs"
  "-Wvariadic-macros"
  "-Wvector-operation-performance"
  "-Wvla"
  "-Wvla-parameter"
  "-Wvolatile-register-var"
  "-Wwrite-strings"
  "-Wxor-used-as-pow"
  "-Wzero-length-bounds"
  "-Wno-unused-function"
)

if(${EZTEST_STACK_ALLOC_LIMIT_} GREATER 0)
  list(
    APPEND
    EZTEST_GCC_18_0_0_WARNING_COMMON_FLAGS_
    "-Walloca-larger-than=${EZTEST_STACK_ALLOC_LIMIT_}"
    "-Wframe-larger-than=${EZTEST_STACK_ALLOC_LIMIT_}"
    "-Wlarger-than=${EZTEST_STACK_ALLOC_LIMIT_}"
    "-Wstack-usage=${EZTEST_STACK_ALLOC_LIMIT_}"
    "-Wvla-larger-than=${EZTEST_STACK_ALLOC_LIMIT_}"
  )
endif()
if(${EZTEST_HEAP_ALLOC_LIMIT_} GREATER 0)
  list(
    APPEND
    EZTEST_GCC_18_0_0_WARNING_COMMON_FLAGS_
    "-Walloc-size-larger-than=${EZTEST_HEAP_ALLOC_LIMIT_}"
  )
endif()

set(
  EZTEST_GCC_14_0_0_WARNING_C_FLAGS_
  "-Wabsolute-value"
  "-Wbad-function-cast"
  "-Wc++-compat"
  "-Wc11-c2x-compat"
  # "-Wc90-c99-compat"
  "-Wc99-c11-compat"
  "-Wdeclaration-after-statement"
  "-Wdesignated-init"
  "-Wdiscarded-array-qualifiers"
  # "-Wtraditional"
  "-Wdiscarded-qualifiers"
  "-Wduplicate-decl-specifier"
  "-Wenum-int-mismatch"
  "-Wimplicit"
  "-Wimplicit-function-declaration"
  "-Wimplicit-int"
  "-Wincompatible-pointer-types"
  "-Wint-conversion"
  "-Wjump-misses-init"
  "-Wmissing-parameter-type"
  "-Wmissing-prototypes"
  "-Wnested-externs"
  "-Wold-style-declaration"
  "-Wold-style-definition"
  "-Woverride-init"
  "-Woverride-init-side-effects"
  "-Wpointer-sign"
  "-Wpointer-to-int-cast"
  "-Wstrict-flex-arrays -fstrict-flex-arrays"
  "-Wstrict-prototypes"
  # "-Wtraditional-conversion"
  "-Wunsuffixed-float-constants"
  ${EZTEST_GCC_14_0_0_WARNING_COMMON_FLAGS_}
)
set(
  EZTEST_GCC_14_0_0_WARNING_CXX_FLAGS_
  "-Wabi-tag"
  "-Waligned-new=all"
  "-Wc++0x-compat"
  "-Wc++11-compat"
  "-Wc++11-extensions"
  "-Wc++14-compat"
  "-Wc++14-extensions"
  "-Wc++17-compat"
  "-Wc++17-extensions"
  "-Wc++1z-compat"
  "-Wc++20-compat"
  "-Wc++20-extensions"
  "-Wc++23-extensions"
  "-Wc++2a-compat"
  "-Wcatch-value=3"
  "-Wchanges-meaning"
  "-Wclass-conversion"
  "-Wclass-memaccess"
  "-Wcomma-subscript"
  "-Wconditionally-supported"
  "-Wconversion-null"
  "-Wctad-maybe-unsupported"
  "-Wctor-dtor-privacy"
  "-Wdangling-reference"
  "-Wdelete-incomplete"
  "-Wdelete-non-virtual-dtor"
  "-Wdeprecated-copy"
  "-Wdeprecated-copy-dtor"
  "-Wdeprecated-enum-enum-conversion"
  "-Wdeprecated-enum-float-conversion"
  "-Weffc++"
  "-Welaborated-enum-base"
  "-Wexceptions"
  "-Wextra-semi"
  "-Winaccessible-base"
  "-Winherited-variadic-ctor"
  "-Winit-list-lifetime"
  "-Winterference-size"
  "-Winvalid-constexpr"
  "-Winvalid-imported-macros"
  "-Winvalid-offsetof"
  "-Wliteral-suffix"
  "-Wmismatched-new-delete"
  "-Wmismatched-tags"
  "-Wmissing-requires"
  "-Wmissing-template-keyword"
  "-Wmultiple-inheritance"
  "-Wnamespaces"
  "-Wnoexcept"
  "-Wnoexcept-type"
  "-Wnon-template-friend"
  "-Wnon-virtual-dtor"
  "-Wold-style-cast"
  "-Woverloaded-virtual"
  "-Wpessimizing-move"
  "-Wplacement-new=2"
  "-Wpmf-conversions"
  "-Wrange-loop-construct"
  "-Wredundant-move"
  "-Wredundant-tags"
  "-Wregister"
  "-Wreorder"
  "-Wself-move"
  "-Wsign-promo"
  "-Wsized-deallocation"
  "-Wstrict-null-sentinel"
  "-Wsubobject-linkage"
  "-Wsuggest-override"
  "-Wsynth"
  "-Wtemplates"
  "-Wterminate"
  "-Wuseless-cast"
  "-Wvexing-parse"
  "-Wvirtual-inheritance"
  "-Wvirtual-move-assign"
  "-Wvolatile"
  "-Wzero-as-null-pointer-constant"
  ${EZTEST_GCC_14_0_0_WARNING_COMMON_FLAGS_}
)

set(EZTEST_CLANG_WARNING_C_FLAGS_ ${EZTEST_CLANG_18_0_0_WARNING_C_FLAGS_})
set(EZTEST_CLANG_WARNING_CXX_FLAGS_ ${EZTEST_CLANG_18_0_0_WARNING_CXX_FLAGS_})

set(EZTEST_GCC_WARNING_C_FLAGS_ ${EZTEST_GCC_14_0_0_WARNING_C_FLAGS_})
set(EZTEST_GCC_WARNING_CXX_FLAGS_ ${EZTEST_GCC_14_0_0_WARNING_CXX_FLAGS_})

include(CheckCompilerFlag)
include(CheckLinkerFlag)

function(
    eztest_supports_flag_
    EZTEST_INFRA_
    EZTEST_LANG_
    EZTEST_FLAG_
    EZTEST_SUPPORTS_FLAG_OUT_
  )
  string(REPLACE ";" "__" EZTEST_FLAG_FLAG_ "${EZTEST_FLAG_}")
  string(REPLACE " " "__" EZTEST_FLAG_FLAG_ "${EZTEST_FLAG_FLAG_}")

  set(
    EZTEST_FLAG_IS_SUPPORTED_RESULT_
    "EZTEST_${EZTEST_LANG_}_${EZTEST_INFRA_}_SUPPORTS_FLAG_${EZTEST_FLAG_FLAG_}"
  )
  if(${EZTEST_INFRA_} STREQUAL "COMPILER")
    check_compiler_flag(
      "${EZTEST_LANG_}"
      "${EZTEST_FLAG_}"
      ${EZTEST_FLAG_IS_SUPPORTED_RESULT_}
    )
  elseif(${EZTEST_INFRA_} STREQUAL "LINKER")
    check_linker_flag(
      "${EZTEST_LANG_}"
      "${EZTEST_FLAG_}"
      ${EZTEST_FLAG_IS_SUPPORTED_RESULT_}
    )
  else()
    message(FATAL_ERROR "Unknown infra: ${EZTEST_INFRA_}")
  endif()
  if(${EZTEST_FLAG_IS_SUPPORTED_RESULT_} EQUAL 1)
    set(${EZTEST_SUPPORTS_FLAG_OUT_} ON PARENT_SCOPE)
  else()
    set(${EZTEST_SUPPORTS_FLAG_OUT_} OFF PARENT_SCOPE)
  endif()
endfunction()

function(eztest_filter_supported_flags_ EZTEST_INFRA_ EZTEST_LANG_ EZTEST_FLAGS_INOUT_)
  list(REMOVE_DUPLICATES EZTEST_FLAGS_INOUT_)
  list(LENGTH "${EZTEST_FLAGS_INOUT_}" EZTEST_NFLAGS_)
  set(EZTEST_STEP_ 1)
  set(EZTEST_START_ 0)

  while(${EZTEST_NFLAGS_} GREATER 0)
    while(ON)
      if(${EZTEST_STEP_} EQUAL 0)
        message(FATAL_ERROR "Zero length slice!")
      endif()
      list(
        SUBLIST
        "${EZTEST_FLAGS_INOUT_}"
        ${EZTEST_START_}
        ${EZTEST_STEP_}
        EZTEST_FLAGS_SLICE_
      )
      eztest_supports_flag_(${EZTEST_INFRA_} ${EZTEST_LANG_} "${EZTEST_FLAGS_SLICE_}" EZTEST_SLICE_OKAY_)
      if(${EZTEST_SLICE_OKAY_})
        list(
          APPEND
          EZTEST_SUPPORTED_FLAGS_
          ${EZTEST_FLAGS_SLICE_}
        )
        break()
      endif()
      if(${EZTEST_STEP_} EQUAL 1)
        break()
      endif()
      math(EXPR EZTEST_STEP_ "${EZTEST_STEP_} / 2")
      if(${EZTEST_STEP_} EQUAL 0)
        set(EZTEST_STEP_ 1)
      endif()

    endwhile()

    math(EXPR EZTEST_NFLAGS_ "${EZTEST_NFLAGS_} - ${EZTEST_STEP_}")
    math(EXPR EZTEST_START_ "${EZTEST_START_} + ${EZTEST_STEP_}")
    math(EXPR EZTEST_STEP_ "${EZTEST_STEP_} * 2")
    if(${EZTEST_STEP_} GREATER ${EZTEST_NFLAGS_})
      set(EZTEST_STEP_ ${EZTEST_NFLAGS_})
    endif()
  endwhile()
  set(${EZTEST_FLAGS_INOUT_} ${EZTEST_SUPPORTED_FLAGS_} PARENT_SCOPE)
endfunction()


if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
  set(EZTEST_WARNING_C_FLAGS_ ${EZTEST_CLANG_WARNING_C_FLAGS_})
else()
  set(EZTEST_WARNING_C_FLAGS_ ${EZTEST_GCC_WARNING_C_FLAGS_})
endif()
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(EZTEST_WARNING_CXX_FLAGS_ ${EZTEST_CLANG_WARNING_CXX_FLAGS_})
else()
  set(EZTEST_WARNING_CXX_FLAGS_ ${EZTEST_GCC_WARNING_CXX_FLAGS_})
endif()

string(REPLACE " " ";" EZTEST_WARNING_CXX_FLAGS_ "${EZTEST_WARNING_CXX_FLAGS_}")
string(REPLACE " " ";" EZTEST_WARNING_C_FLAGS_ "${EZTEST_WARNING_C_FLAGS_}")

foreach (
    EZTEST_BUILD_TYPE_FLAGS_
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_RELWITHDEBINFO
    CMAKE_CXX_FLAGS_MINSIZEREL
    CMAKE_C_FLAGS_RELEASE
    CMAKE_C_FLAGS_RELWITHDEBINFO
    CMAKE_C_FLAGS_MINSIZEREL)
  string (
    REGEX REPLACE
    "(^| )-DNDEBUG($| )"
    " "
    "${EZTEST_BUILD_TYPE_FLAGS_}"
    "${${EZTEST_BUILD_TYPE_FLAGS_}}"
  )
endforeach()
