set(LIBCUDART_FIELS
    cuda_initialize.cpp
    cuda_runtime.cpp
    cuda_runtime_api.cpp
    cuda_fatbinary.cpp
    cuda_elf.cpp
   )

add_library(cudart SHARED ${LIBCUDART_FIELS})
set_target_properties(cudart PROPERTIES VERSION 11.0)
target_link_libraries(cudart rvgpu gvm_utils)
target_include_directories(cudart PRIVATE ${project_top_path}/device)
target_include_directories(cudart PRIVATE include)

install(TARGETS cudart LIBRARY DESTINATION lib)
