cmake_minimum_required(VERSION 3.8)

# Include utility functions
add_subdirectory(cmake)

# Set project name
project(potato VERSION 1.0.0 LANGUAGES CXX)

# Add targets
add_subdirectory(engine)
add_subdirectory(engine-test)
