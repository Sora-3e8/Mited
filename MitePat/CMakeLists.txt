cmake_minimum_required(VERSION 3.16)

project(MitePat VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_DIR "src")
set(SHADERS, "shaders")
set(EXECUTABLE_OUTPUT_PATH "bin")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets OpenGL)

include_directories(include lib)

add_executable(MitePat "${SRC_DIR}/MitePat.cpp" "${SRC_DIR}/app_window.cc")
target_compile_options(MitePat PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(MitePat PRIVATE Qt6::Core)
target_link_libraries(MitePat PRIVATE Qt6::Widgets)
target_link_libraries(MitePat PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(MitePat PRIVATE Qt6::OpenGL)
target_link_libraries(MitePat PRIVATE Qt6::Gui)
