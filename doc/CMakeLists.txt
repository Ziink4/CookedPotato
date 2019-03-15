# Set target name
set(POTATO_TARGET cookbook)
message("Configuring ${POTATO_TARGET}")

find_package(Doxygen REQUIRED)

configure_file(Doxyfile ${CMAKE_BINARY_DIR}/Doxyfile COPYONLY)

add_custom_target(${POTATO_TARGET}
    COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/Doxyfile"
	COMMENT "Building documentation"
)