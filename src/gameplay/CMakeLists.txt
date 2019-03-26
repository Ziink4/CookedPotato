# Set target name
set(POTATO_TARGET kitchen)
message("Configuring ${POTATO_TARGET}")

# Add sources
add_library(${POTATO_TARGET}
    search.cpp
    split_terrain.cpp
    random_terrain.cpp
)

potato_setup_compile_options(TARGET ${POTATO_TARGET})

# Include headers
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/src/)
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/include/)

# Link to required modules
target_link_libraries(${POTATO_TARGET} backyard)
