## Google Test
# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(
    ${PROJECT_SOURCE_DIR}/external/googletest
    ${PROJECT_BINARY_DIR}/external/googletest
    EXCLUDE_FROM_ALL
)

add_subdirectory(engine)
add_subdirectory(gameplay)
