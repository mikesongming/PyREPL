cmake_minimum_required(VERSION 3.22.0)

project(py_embed_world CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(Python_ROOT_DIR "/Users/mike/opt/anaconda3/envs/youtube/")

find_package(Python REQUIRED Interpreter Development)
if (NOT ${Python_FOUND})
    message(FATAL_ERROR "Python is not found")
    exit(1)
endif()

# Fetch third-party libraries
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Disable updating fetched content")
# include(GitPybind11)

include(CMakePrintHelpers)
find_package(pybind11 CONFIG REQUIRED)
if (NOT pybind11_FOUND)
    message(FATAL_ERROR "pybind11 not found")
    exit(1)
else()
    if (pybind11_VERSION VERSION_LESS 2.11.1)
        message(FATAL_ERROR "pybind11 version should be greater than 2.11.1")
        exit(1)
    endif()
    message(STATUS "pybind11 found")
endif()

pybind11_add_module(py_animal bind.cpp animal.cpp)
target_link_libraries(py_animal PRIVATE pybind11::pybind11)

add_executable(test_repl main.cpp world.cpp animal.cpp)
target_link_libraries(test_repl PRIVATE pybind11::embed)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/repl.py ${CMAKE_CURRENT_BINARY_DIR}/repl.py COPYONLY)