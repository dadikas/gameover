#glad/CMakelists.txt

cmake_minimum_required(VERSION 3.14)

set(GLAD_SRC
    src/glad.c
)

add_library(glad STATIC ${GLAD_SRC})

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
