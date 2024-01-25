include(${CMAKE_CURRENT_LIST_DIR}/cross-riscv64.common.cmake)

set(CMAKE_C_FLAGS "--target=riscv64-linux-gnu ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "--target=riscv64-linux-gnu ${CMAKE_CXX_FLAGS}")
