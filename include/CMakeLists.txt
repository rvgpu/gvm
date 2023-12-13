file(GLOB INC_HEADER_FILES *.h)
install(FILES ${INC_HEADER_FILES} DESTINATION include)

add_subdirectory(crt)
