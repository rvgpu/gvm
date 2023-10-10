cmake_minimum_required(VERSION 3.12)
project(RVGVM)

enable_testing()
include(compile_options.cmake)
find_package(PkgConfig)
set(project_top_path ${CMAKE_CURRENT_SOURCE_DIR})

pkg_search_module(rvgsim REQUIRED librvgsim)
link_directories(rvgpu PRIVATE ${rvgsim_LIBRARY_DIRS})
include_directories(rvgpu PRIVATE ${rvgsim_INCLUDE_DIRS})

add_subdirectory(device)
add_subdirectory(cudart)
# add_subdirectory(runtime)
