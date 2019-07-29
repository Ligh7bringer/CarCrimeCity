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

find_package(Threads)

file(GLOB_RECURSE SOURCE_FILES engine/src/*.cpp engine/src/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/src/" PUBLIC SYSTEM)
target_link_libraries(lib_engine ${CMAKE_THREAD_LIBS_INIT})

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
add_executable(Game ${SOURCES} ${RESOURCE_FILES})
target_link_libraries(Game lib_engine)
set(EXECUTABLES ${EXECUTABLES} Game)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)
endif()
