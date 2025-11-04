cmake_minimum_required(VERSION 3.28)
project(newton_fractal)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)

add_executable(newton_fractal
        main.cpp
        AppWindow.cpp
        AppWindow.hpp
        NewtonFractal.cpp
        NewtonFractal.hpp
)
target_link_libraries(newton_fractal sfml-graphics)
