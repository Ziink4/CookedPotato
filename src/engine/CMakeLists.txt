# Set target name
set(POTATO_TARGET backyard)
message("Configuring ${POTATO_TARGET}")

# Add sources
add_library(${POTATO_TARGET}
    terrain.cpp
    entity.cpp
    character.cpp
    obstacle.cpp
)

potato_setup_compile_options(TARGET ${POTATO_TARGET})

# Include headers
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/include/)
