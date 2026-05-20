cmake_minimum_required(VERSION 3.20)
project(fileXplorer C)

add_executable(fileXplorer fileXplorer.c)

target_include_directories(fileXplorer PRIVATE include)