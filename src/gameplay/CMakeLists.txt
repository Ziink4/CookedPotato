# Set target name
set(POTATO_TARGET kitchen)
message("Configuring ${POTATO_TARGET}")

# Add sources
add_library(${POTATO_TARGET}
    search.cpp
)

potato_setup_compile_options(TARGET ${POTATO_TARGET})

# Include headers
target_include_directories(${POTATO_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${POTATO_TARGET} PRIVATE ${PROJECT_SOURCE_DIR}/include/gameplay/)
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/include/)

# Link to required modules
target_link_libraries(${POTATO_TARGET} backyard)
