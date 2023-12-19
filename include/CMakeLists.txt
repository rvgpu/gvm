file(GLOB INC_HEADER_FILES *.h)
install(FILES ${INC_HEADER_FILES} DESTINATION include)
file(GLOB INC_HPP_FILES *.hpp)
install(FILES ${INC_HPP_FILES} DESTINATION include)

add_subdirectory(crt)
add_subdirectory(nv)
