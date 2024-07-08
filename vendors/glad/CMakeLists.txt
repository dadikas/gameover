#glad/CMakelists.txt

cmake_minimum_required(VERSION 3.14)
project(glad)

add_library(glad STATIC ${GLAD_SRC})
target_sources(glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
