cmake_minimum_required(VERSION 3.16)

project(Miyo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_DIR "src")
set(SHADERS, "shaders")
set(EXECUTABLE_OUTPUT_PATH "bin")
set(Qt6_USE_STATIC_LIBS TRUE)
set(BUILD_SHARED_LIBS OFF)

string(TOLOWER "${PROJECT_NAME}" BIN_NAME)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)

if(NOT Qt6_FOUND)
  message(FATAL_ERROR "Could not find Qt6 - Required components: [Core,Gui,OpenGL,OpenGLWidgets,Widgets]")
  message()
endif()

include_directories(include lib)
add_executable("${BIN_NAME}" "${SRC_DIR}/miyo.cpp" "${SRC_DIR}/app_window.cc")
target_compile_options("${BIN_NAME}" PRIVATE -Wall -Wextra -Wpedantic -static)
target_link_libraries("${BIN_NAME}" PRIVATE Qt6::Core Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets Qt6::Gui)
