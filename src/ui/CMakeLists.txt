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
target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/include/)

# Add Boost for Wt
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost REQUIRED)

target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${POTATO_TARGET} ${Boost_LIBRARIES})

# Add Wt
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${WT_ROOT}/include")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${WT_ROOT}/lib")

find_package(Wt REQUIRED)

target_include_directories(${POTATO_TARGET} SYSTEM PRIVATE ${Wt_INCLUDE_DIR})

target_link_libraries(${POTATO_TARGET} $<$<CONFIG:Debug>:${Wt_DEBUG_LIBRARY}>)
target_link_libraries(${POTATO_TARGET} $<$<CONFIG:Debug>:${Wt_HTTP_DEBUG_LIBRARY}>)

target_link_libraries(${POTATO_TARGET} $<$<CONFIG:Release>:${Wt_LIBRARY}>)
target_link_libraries(${POTATO_TARGET} $<$<CONFIG:Release>:${Wt_HTTP_LIBRARY}>)
