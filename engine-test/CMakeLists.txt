# Set target name
set(POTATO_TARGET starch_test)
message("Configuring ${POTATO_TARGET}")

# Add sources
add_executable(${POTATO_TARGET}
    terrain.cpp
    entity.cpp
)

potato_setup_compile_options(TARGET ${POTATO_TARGET})

# Include engine sources
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/../external/googletest
	${CMAKE_CURRENT_BINARY_DIR}/../external/googletest
	EXCLUDE_FROM_ALL
)

# Include Google Test
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../external/googletest/googletest/include)

# Link to main target
target_link_libraries(${POTATO_TARGET} starch)
target_link_libraries(${POTATO_TARGET} gtest_main)

