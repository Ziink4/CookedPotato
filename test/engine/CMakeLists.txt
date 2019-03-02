# Set target name
set(POTATO_TARGET backyard_test)
message("Configuring ${POTATO_TARGET}")

# Add sources
add_executable(${POTATO_TARGET}
    terrain.cpp
    entity.cpp
)

potato_setup_compile_options(TARGET ${POTATO_TARGET})

# Include headers
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link to tested library
target_link_libraries(${POTATO_TARGET} backyard)

# Include Google Test
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/external/googletest/googletest/include)

# Link to main target
target_link_libraries(${POTATO_TARGET} gtest_main)
