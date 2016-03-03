include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runch_chanTests
        ch_chan_check.cpp)

target_link_libraries(runch_chanTests gtest gtest_main)
target_link_libraries(runch_chanTests ch_chan)
