cmake_minimum_required(VERSION 3.25)
project(Fuse)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

#Global cmake properties
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -DDISABLE_SIGHT)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Rose)

if(NOT Rose_FOUND)
  message(FATAL_ERROR "Rose compiler NOT found ${Rose_ROOT}")
endif()

add_subdirectory(src)
