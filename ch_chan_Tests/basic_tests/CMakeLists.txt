include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runch_chanTests
        ch_chan_check.cpp ../../ch_chan/SDL.cpp ../../ch_chan/SDL.h)

target_link_libraries(runch_chanTests gtest gtest_main)
target_link_libraries(runch_chanTests ch_chan)
target_link_libraries(runch_chanTests Utils)
target_link_libraries(runch_chanTests PointsGenerator)
