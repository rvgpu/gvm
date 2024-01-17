set(LIBCUDART_FIELS
    debug.cpp
   )

add_library(gvm_utils STATIC ${LIBCUDART_FIELS})
target_compile_options(gvm_utils PRIVATE -fPIC)
