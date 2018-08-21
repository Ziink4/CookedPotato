# Set target name
set(TEST_TARGET test_${TARGET})

message("Configuring ${TEST_TARGET}")

# Add sources
add_executable(${TEST_TARGET}
    src/main.cpp
    src/terrain.cpp
    src/entity.cpp
)

# Include external directories
target_include_directories(${TEST_TARGET} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../external)

# Link to main target
target_link_libraries(${TEST_TARGET} ${TARGET})
