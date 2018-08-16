# Set target name
set(TEST_TARGET test_${TARGET})

# Add sources
add_executable(${TEST_TARGET} src/main.cpp)

# Enable C++17
target_compile_features(${TEST_TARGET} PRIVATE cxx_std_17)

# Enable warnings
target_compile_options(${TARGET} PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -pedantic>)

# Include external directories
target_include_directories(${TEST_TARGET} PRIVATE SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/../external)

# Link to main target
target_link_libraries(${TEST_TARGET} ${TARGET})
