# Set target name
set(POTATO_TARGET kitchen_test)
message("Configuring ${POTATO_TARGET}")

# Add sources
add_executable(${POTATO_TARGET}
    search.cpp
    random_terrain.cpp
	game_flow.cpp
)

potato_setup_compile_options(TARGET ${POTATO_TARGET})

# Include headers
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link to tested library
target_link_libraries(${POTATO_TARGET} kitchen)

# Include Google Test
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/external/googletest/googletest/include)

# Link to main target
target_link_libraries(${POTATO_TARGET} gtest_main)
