include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runPointsGeneratorTests
        pointGenerator_check.cpp)

target_link_libraries(runPointsGeneratorTests gtest gtest_main)
target_link_libraries(runPointsGeneratorTests PointsGenerator)
target_link_libraries(runPointsGeneratorTests Utils)
