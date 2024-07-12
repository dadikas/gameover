project(gameover)

# Create a static library
add_library(${PROJECT_NAME} STATIC
    src/engine.cpp
    include/gameover/engine.h
)

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include/gameover
)

# Set compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror>
)

# Set platform-specific defines
if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC GAMEOVER_PLATFORM_WINDOWS)
elseif (UNIX)
    target_compile_definitions(${PROJECT_NAME} PUBLIC GAMEOVER_PLATFORM_LINUX)
endif()

# Set configurations
target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<CONFIG:Debug>:GAMEOVER_CONFIG_DEBUG>
    $<$<CONFIG:Release>:GAMEOVER_CONFIG_RELEASE>
)

# Set runtime library and symbols for Debug and Release
set_target_properties(${PROJECT_NAME} PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)
