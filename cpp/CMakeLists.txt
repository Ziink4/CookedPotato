cmake_minimum_required(VERSION 3.8)

# Set target name
set(ENGINE_TARGET potato-engine)
message("Configuring ${ENGINE_TARGET}")

# Set project name
project(lib${ENGINE_TARGET} VERSION 1.0.0 LANGUAGES CXX)

# Add sources
add_library(${ENGINE_TARGET}
	src/engine/main.cpp
	src/engine/terrain.cpp
	src/engine/entity.cpp
	src/engine/character.cpp
	src/engine/obstacle.cpp
	src/engine/search.cpp
)

# Add include directories
#target_include_directories(${ENGINE_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${ENGINE_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
#target_include_directories(${ENGINE_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Include external directories
target_include_directories(${ENGINE_TARGET} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external)

# Enable warnings and C++17
target_compile_options(${ENGINE_TARGET} PUBLIC $<$<CXX_COMPILER_ID:GNU>:-std=c++17 -Wall -Wextra -pedantic>)
target_compile_options(${ENGINE_TARGET} PUBLIC $<$<CXX_COMPILER_ID:Clang>:-std=c++17 -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic>)

# Add tests
add_subdirectory(test)
