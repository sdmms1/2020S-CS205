cmake_minimum_required(VERSION 3.14)
project(utf2)

set(CMAKE_CXX_STANDARD 14)

add_executable(utf2 testUTF8string.cpp UTF8string.cpp utf8.c)