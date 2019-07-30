cmake_minimum_required(VERSION 3.7)

# Compiler flags
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc /Wall" CACHE INTERNAL "" FORCE)
elseif(UNIX)
    message("hello linux!")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic" CACHE INTERNAL "" FORCE)
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(oclPixelGameEngine)

set(THREADS_PREFER_PTHREAD_FLAD ON)
find_package(Threads REQUIRED)

# Find GL and GLX package
find_package(OpenGL REQUIRED)

if (UNIX)
    find_package(X11 REQUIRED)
    find_package(PNG REQUIRED)
    include_directories(${PNG_INCLUDE_DIR})
endif(UNIX)

# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

file(GLOB_RECURSE SOURCE_FILES engine/src/*.cpp engine/src/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/src/" PUBLIC SYSTEM)
target_link_libraries(lib_engine ${CMAKE_THREAD_LIBS_INIT})

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
add_executable(Game ${SOURCES} ${RESOURCE_FILES})
target_link_libraries(Game lib_engine)

target_link_libraries(Game
        Threads::Threads
        OpenGL::OpenGL
        OpenGL::GL
        OpenGL::GLX
        )

if (UNIX)
    target_link_libraries(Game
            ${X11_LIBRARIES}
            PNG::PNG
            )
endif (UNIX)

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)
add_dependencies(Game copy_resources)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)
endif()

