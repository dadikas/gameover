#CMakelists.txt

cmake_minimum_required(VERSION 3.14)   
project(gameover)

#set c++ standard 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include the nescessary moduls
include(ExternalProject)

#add subdictionary for imgui
add_subdirectory(vendors/imgui_opengl)

#find and include glfw
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

#include glad
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendors/glad)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendors/glad/include)

#add your executable
add_executable(gameover src/main.cpp)

#link the libraries
target_link_libraries(gameover imgui_opengl ${GLFW_LIBRARIES} GL glad pthread dl X11)