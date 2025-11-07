cmake_minimum_required(VERSION 3.28)
project(newton_fractal LANGUAGES CXX ISPC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ISPC_TARGET_ARCHITECTURE "host")

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)
FetchContent_MakeAvailable(SFML)

add_executable(newton_fractal
        src/main.cpp
        src/AppWindow.cpp
        src/NewtonFractal.cpp
        kernel/fractal.ispc
)

set_source_files_properties(kernel/fractal.ispc PROPERTIES
        ISPC_HEADER_FILE "${CMAKE_CURRENT_BINARY_DIR}/fractal_ispc.h"
)

target_include_directories(newton_fractal PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(newton_fractal PRIVATE
        sfml-graphics
)
