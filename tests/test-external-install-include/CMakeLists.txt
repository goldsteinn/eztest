cmake_minimum_required(VERSION 3.5.0)
project(
  "eztest-install-included"
  VERSION 0.0.1
  DESCRIPTION "Test project for a test project..."
  LANGUAGES C CXX
)

find_package(eztest REQUIRED)

add_executable(test-c test.c)
add_executable(test-cc test.cc)

target_link_libraries(test-c PRIVATE eztest::eztest)
target_link_libraries(test-cc PRIVATE eztest::eztest)

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
