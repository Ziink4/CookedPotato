cmake_minimum_required(VERSION 3.8)

# Set target name
set(TARGET potato-engine)

# Set project name
project(lib${TARGET} VERSION 1.0.0 LANGUAGES CXX)

# Add sources
add_library(${TARGET}
	src/engine/main.cpp
)

# Add include directories
target_include_directories(${TARGET}
	PUBLIC
	    $<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Enable C++17
target_compile_features(${TARGET} PRIVATE cxx_std_17)

# Enable warnings
target_compile_options(${TARGET} PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -pedantic>)

# Add tests
add_subdirectory(test)
