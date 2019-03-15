cmake_minimum_required(VERSION 3.8)

# Include utility functions
add_subdirectory(cmake)

# Set project name
project(potato VERSION 1.0.0 LANGUAGES CXX)

# Add uptions
option(POTATO_GENERATE_DOC "Generate Doxygen documentation" OFF)

# Add targets
add_subdirectory(src)
add_subdirectory(test)

if(POTATO_GENERATE_DOC)
    add_subdirectory(doc)
endif()
