cmake_minimum_required(VERSION 3.12)
project(RVGVM)

enable_testing()
include(compile_options.cmake)

find_package(PkgConfig)
pkg_search_module(rvgpu_lib REQUIRED librvgpu)

add_library(cudart SHARED cuda_runtime_api.c)
set_target_properties(cudart PROPERTIES VERSION 11.0)

target_link_libraries(cudart ${rvgpu_lib_LIBRARIES})
target_include_directories(cudart PRIVATE ${rvgpu_lib_INCLUDE_DIRS})
target_include_directories(cudart PRIVATE /usr/include)

install(TARGETS cudart LIBRARY DESTINATION lib)

# add_subdirectory(driver)
# add_subdirectory(runtime)
# add_subdirectory(cuda)