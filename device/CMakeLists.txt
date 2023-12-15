add_subdirectory(nvvm)

set(LIBRVGDEV_FILES
    rvgpu.cpp
    rvg_device.cpp
    rvg_simulator.cpp
    rvg_memory_manager.cpp
   )

add_library(rvgpu SHARED ${LIBRVGDEV_FILES})
target_link_libraries(rvgpu ${rvgsim_LIBRARIES})

set_target_properties(rvgpu PROPERTIES VERSION 1.0)
install(TARGETS rvgpu LIBRARY DESTINATION lib)
