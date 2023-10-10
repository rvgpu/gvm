set(LIBCUDART_FIELS
    cuda_runtime.cpp
    cuda_runtime_api.cpp
   )

# find_package(PkgConfig)
# pkg_search_module(rvgpu_lib REQUIRED librvgpu)

add_library(cudart SHARED ${LIBCUDART_FIELS})
set_target_properties(cudart PROPERTIES VERSION 11.0)
target_link_libraries(cudart rvgpu)
target_include_directories(cudart PRIVATE ${project_top_path}/device)

# target_link_libraries(cudart ${rvgpu_lib_LIBRARIES})
# target_link_directories(cudart PRIVATE ${rvgpu_lib_LIBRARY_DIRS})
# target_include_directories(cudart PRIVATE ${rvgpu_lib_INCLUDE_DIRS})

install(TARGETS cudart LIBRARY DESTINATION lib)