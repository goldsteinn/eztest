cmake_minimum_required(VERSION 3.5.0)
project(
  "eztest-cmake-included"
  VERSION 0.0.1
  DESCRIPTION "Test project for a test project..."
  LANGUAGES C CXX
)

option(
  EZTEST_TEST_EXTERNAL_INCLUDE_PATH_
  "Path: Location of eztest dir"
  ${PROJECT_SOURCE_DIR}/../..
)
if(NOT EZTEST_TEST_EXTERNAL_INCLUDE_PATH_)
  message(FATAL_ERROR "EZTEST_TEST_EXTERNAL_INCLUDE_PATH_ is required!")
endif()

add_subdirectory(
  ${EZTEST_TEST_EXTERNAL_INCLUDE_PATH_}
  ${PROJECT_BINARY_DIR}/eztest-artifacts/${PROJECT_NAME}
)
add_executable(test-c test.c)
add_executable(test-cc test.cc)

target_link_libraries(test-c PRIVATE eztest)
target_link_libraries(test-cc PRIVATE eztest)

add_custom_target(
  check-c
  DEPENDS test-c
  COMMAND
  "./test-c"
)

add_custom_target(
  check-cc
  DEPENDS test-cc
  COMMAND
  "./test-cc"
)

add_custom_target(
  "check-all"
  DEPENDS check-c check-cc
)
