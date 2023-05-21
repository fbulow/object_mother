cmake_minimum_required(VERSION 3.20)

project(om)

find_package(GTest REQUIRED)

add_library(object_mother INTERFACE)
target_include_directories(object_mother INTERFACE src)


add_subdirectory(test)
