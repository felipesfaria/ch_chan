include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUtilsTests
        utils_check.cpp)

target_link_libraries(runUtilsTests gtest gtest_main)
target_link_libraries(runUtilsTests Utils)
