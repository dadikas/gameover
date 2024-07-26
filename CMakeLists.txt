cmake_minimum_required(VERSION 3.16)

project(gameover_workspace)

#Disable GLFW build options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directories for binaries and object files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_OBJECT_PATH_MAX 250)

#set platform android
# include_directories(${CMAKE_SOURCE_DIR}/ndk/android-ndk-r27/toolchains/llvm/prebuilt/linux-x86_64/lib64/clang/9.0.9/include)
# set(CMAKE_C_COMPILER ${CMAKE_SOURCE_DIR}/ndk/android-ndk-r27/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android28-clang)
# set(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/ndk/android-ndk-r27/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android28-clang++)
# ​
# add_executable(perf_test ${DIR_SRCS})
# target_link_libraries(perf_test "log")
# target_link_libraries(perf_test "z")
# target_link_libraries(perf_test "dl")
# target_link_libraries(perf_test "m")

# Include the subdirectories
add_subdirectory(gameover)
add_subdirectory(gameovereditor)
add_subdirectory(vendors/glad)
add_subdirectory(vendors/glfw-3.4)
add_subdirectory(vendors/imgui_opengl)


