execute_process(
    COMMAND llvm-as ${CMAKE_CURRENT_SOURCE_DIR}/libdevice.10.ll -o ${CMAKE_CURRENT_BINARY_DIR}/libdevice.10.bc
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libdevice.10.bc DESTINATION nvvm/libdevice)
