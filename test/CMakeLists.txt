# Set target name
set(TEST_TARGET gtest_${ENGINE_TARGET})

message("Configuring ${TEST_TARGET}")

# Add sources
add_executable(${TEST_TARGET}
    src/terrain.cpp
    src/entity.cpp
)

# Include external directories
target_include_directories(${TEST_TARGET} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../external)

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/../external/googletest
	${CMAKE_CURRENT_BINARY_DIR}/../external/googletest
	EXCLUDE_FROM_ALL
)

#Include Google Test
target_include_directories(${TEST_TARGET} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../external/googletest/googletest/include)

# Link to main target
target_link_libraries(${TEST_TARGET} ${ENGINE_TARGET})
target_link_libraries(${TEST_TARGET} gtest_main)

