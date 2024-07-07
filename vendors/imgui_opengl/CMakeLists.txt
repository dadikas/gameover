#IMGUI/CmakeLists.txt

cmake_minimum_required(VERSION 3.14)

#add imgui source files

set(IMGUI_SRC
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_widgets.cpp
    imgui_tables.cpp
    backends/imgui_impl_glfw.cpp
    backends/imgui_impl_opengl3.cpp
)

#add the library target
add_library(imgui_opengl STATIC ${IMGUI_SRC})

#include directories for imguis
target_include_directories(imgui_opengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(imgui_opengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/backends)
