# Set target name
set(POTATO_TARGET starch)
message("Configuring ${POTATO_TARGET}")

# Add sources
add_library(${POTATO_TARGET}
    main.cpp
    terrain.cpp
    entity.cpp
    character.cpp
    obstacle.cpp
    search.cpp
)

potato_setup_compile_options(TARGET ${POTATO_TARGET})

# Include headers
target_include_directories(${POTATO_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Include external headers
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external)
