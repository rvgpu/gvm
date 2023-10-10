set(LIBCUDART_FIELS
    cuda_runtime.cpp
    cuda_runtime_api.cpp
   )

add_library(cudart SHARED ${LIBCUDART_FIELS})
set_target_properties(cudart PROPERTIES VERSION 11.0)
target_link_libraries(cudart rvgpu)
target_include_directories(cudart PRIVATE ${project_top_path}/device)

install(TARGETS cudart LIBRARY DESTINATION lib)