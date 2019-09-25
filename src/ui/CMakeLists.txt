# Set target name
set(POTATO_TARGET frontyard)
message("Configuring ${POTATO_TARGET}")

# Add sources
add_executable(${POTATO_TARGET}
    hello_application.cpp
    main.cpp
)

potato_setup_compile_options(TARGET ${POTATO_TARGET})

# Include headers
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/src/)
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/include/)

# Add Boost for Wt
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost REQUIRED)

target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${POTATO_TARGET} ${Boost_LIBRARIES})

# Add Wt
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${WT_ROOT}")

find_package(Wt REQUIRED COMPONENTS wt wthttp)

target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${Wt_INCLUDE_DIRS})

target_link_libraries(${POTATO_TARGET} $<$<CONFIG:Debug>:${Wt_WT_LIBRARY_DEBUG}>)
target_link_libraries(${POTATO_TARGET} $<$<CONFIG:Debug>:${Wt_WTHTTP_LIBRARY_DEBUG}>)

target_link_libraries(${POTATO_TARGET} $<$<CONFIG:Release>:${Wt_WT_LIBRARY_RELEASE}>)
target_link_libraries(${POTATO_TARGET} $<$<CONFIG:Release>:${Wt_WTHTTP_LIBRARY_RELEASE}>)
