cmake_minimum_required(VERSION 2.8)

project(PointsGenerator)

add_definitions(-std=c++11)

set(HEADER_FILES
        PointsGenerator.h
        )

set(SOURCE_FILES
        PointsGenerator.cpp
        )

add_library(PointsGenerator STATIC ${SOURCE_FILES} ${HEADER_FILES})
