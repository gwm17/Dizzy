cmake_policy(SET CMP0048 NEW)

cmake_minimum_required(VERSION 3.16)

project(Dizzy VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_BUILD_TYPE "Debug")
    message("Building Debug...")
else()
    message("Building Release...")
endif()

set(DZ_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(DZ_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(Vulkan REQUIRED)

add_subdirectory(vendor/glad)
set(GLFW_INSTALL Off CACHE BOOL "Generate installation target" )
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glm)
add_subdirectory(src)