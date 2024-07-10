cmake_minimum_required(VERSION 3.14)
project(gameover)

# Disable GLFW build options we don't need
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add subdirectories for dependencies
add_subdirectory(vendors/glfw-3.4)
add_subdirectory(vendors/glad)
add_subdirectory(vendors/imgui_opengl)

# Define the source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/gameover/*.cpp)

# Create the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# Set C++ standard
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Include directories
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

# Link libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad glfw imgui_opengl)
