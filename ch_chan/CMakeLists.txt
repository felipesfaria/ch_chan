cmake_minimum_required(VERSION 2.8)

project(ch_chan)

add_definitions(-std=c++11)

set(HEADER_FILES
        ch_chan.h
        )

set(SOURCE_FILES
        ch_chan.cpp
        SDL.cpp SDL.h)

add_library(ch_chan STATIC ${SOURCE_FILES} ${HEADER_FILES})
