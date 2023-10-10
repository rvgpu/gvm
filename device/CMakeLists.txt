set(LIBRVGDEV_FILES
    rvgpu.cpp
   )

add_library(rvgpu SHARED ${LIBRVGDEV_FILES})
set_target_properties(rvgpu PROPERTIES VERSION 1.0)

install(TARGETS rvgpu LIBRARY DESTINATION lib)
