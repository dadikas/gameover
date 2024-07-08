#IMGUI/CmakeLists.txt

cmake_minimum_required(VERSION 3.14)
project(imgui_opengl)

add_library(imgui_opengl)
target_sources(imgui_opengl PRIVATE
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    backends/imgui_impl_glfw.cpp
    backends/imgui_impl_opengl3.cpp
)

#include directories for imguis
target_include_directories(imgui_opengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(imgui_opengl PUBLIC glad glfw)