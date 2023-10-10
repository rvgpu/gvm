cmake_minimum_required(VERSION 3.12)
project(RVGVM)

enable_testing()
include(compile_options.cmake)

set(project_top_path ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(device)
add_subdirectory(cudart)
# add_subdirectory(runtime)
