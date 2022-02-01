cmake_minimum_required(VERSION 3.18)
project(Properties)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/cmake")

enable_testing()

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
