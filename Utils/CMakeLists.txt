cmake_minimum_required(VERSION 2.8)

project(Utils)

add_definitions(-std=c++11)

set(HEADER_FILES
        Utils.h
        )

set(SOURCE_FILES
        Utils.cpp
        )

add_library(Utils STATIC ${SOURCE_FILES} ${HEADER_FILES})
