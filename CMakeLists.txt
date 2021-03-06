cmake_minimum_required(VERSION 3.7...3.21)

# CMake versions < 3.12 do not support .., so policy is manually set here if needed
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Configure build directory
if(NOT "${ROOT}/build")
  file(MAKE_DIRECTORY "${ROOT}/build")
endif()

# C++ configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

message("CMAKE CXX STANDARD = 20")

set(ENABLE_DEVELOPER_MODE
    TRUE
    CACHE BOOL "Enable 'developer mode'")

set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT FALSE)

# Variables
set(PROJ_NAME "Chip8Emulator" CACHE STRING "")
set(PROJ_VERSION 1.0 CACHE STRING "")
set(PROJ_DESCRIPTION "Learning CMake & C++" CACHE STRING "")

project(CppLearn VERSION ${PROJ_VERSION} DESCRIPTION ${PROJ_DESCRIPTION} LANGUAGES CXX)

# List of source files
set(HEADER_FILES
  src/chip8.hpp
  src/cpu.hpp
  src/screen.hpp)

set(SRC_FILES 
  src/main.cpp
  src/chip8.cpp
  src/cpu.cpp
  src/screen.cpp)

add_executable(${PROJ_NAME} ${SRC_FILES} ${HEADER_FILES})