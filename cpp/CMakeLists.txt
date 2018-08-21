cmake_minimum_required(VERSION 3.8)

# Set target name
set(TARGET potato-engine)
message("Configuring ${TARGET}")

# Set project name
project(lib${TARGET} VERSION 1.0.0 LANGUAGES CXX)

# Add sources
add_library(${TARGET}
	src/engine/main.cpp
	src/engine/terrain.cpp
        src/engine/entity.cpp
)

# Add include directories
target_include_directories(${TARGET}
	PUBLIC
	    ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
	    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Enable warnings and C++17
target_compile_options(${TARGET} PUBLIC $<$<CXX_COMPILER_ID:GNU>:-std=c++17 -Wall -Wextra -pedantic>)
target_compile_options(${TARGET} PUBLIC $<$<CXX_COMPILER_ID:Clang>:-std=c++17 -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic>)

# Add tests
add_subdirectory(test)
