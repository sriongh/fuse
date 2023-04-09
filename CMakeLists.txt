cmake_minimum_required(VERSION 3.25)
project(Fuse)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

find_package(Boost)
find_package(Rose)

if(NOT Rose_FOUND)
  message(FATAL_ERROR "Rose compiler NOT found ${Rose_ROOT}")
endif()

if(NOT Boost_FOUND)
  message(FATAL_ERROR "Boost NOT found ${Boost_ROOT}")
endif()

add_subdirectory(src)
