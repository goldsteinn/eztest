include(${CMAKE_CURRENT_LIST_DIR}/cross-arm.common.cmake)

set(CMAKE_C_FLAGS "--target=arm-linux-gnueabi ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "--target=arm-linux-gnueabi ${CMAKE_CXX_FLAGS}")
