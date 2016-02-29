//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"

#include "PointsGenerator.h"

class PointsGeneratorFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    PointsGeneratorFixture() : Test() {
    }

    virtual ~PointsGeneratorFixture() {
    }
};

TEST_F(PointsGeneratorFixture, GenerateRandomPoints_OutputSizeIsEqualParameter_Test) {
    int size = 4;
    int expected = size;
    vector<Point_2> points = PointsGenerator::GenerateRandomPoints(size);
    int actual = points.size();
    EXPECT_EQ(expected, actual);
}

TEST_F(PointsGeneratorFixture, GenerateRandomPoints_PointDistributionWithinRange_Test) {
    int size = 1<<10;
    vector<Point_2> points = PointsGenerator::GenerateRandomPoints(size);
    bool allPointsWithinRange = true;
    double minValue = 0;
    double maxValue = POINTS_RANGE;
    for(int i=0;i<points.size();i++){
        double x = points[i].x();
        double y = points[i].y();
        if(x<minValue||x>maxValue||y<minValue||y>maxValue){
            allPointsWithinRange = false;
            break;
        }
    }
    EXPECT_TRUE(allPointsWithinRange);
}

TEST_F(PointsGeneratorFixture, GenerateRandomPoints_DistributionIsRandom_Test) {
    int size = 1<<10;
    vector<Point_2> points = PointsGenerator::GenerateRandomPoints(size);
    double avgX = 0;
    double avgY = 0;
    for(int i=0;i<points.size();i++){
        avgX += points[i].x();
        avgY += points[i].y();
    }
    avgX /=points.size();
    avgY /=points.size();
    double centerDistribution = POINTS_RANGE / 2;
    bool distributionIsRandom = abs(avgX-centerDistribution)<5 && abs(avgY-centerDistribution)<5;
    EXPECT_TRUE(distributionIsRandom);
}

TEST_F(PointsGeneratorFixture, GenerateRandomPoints_NotAllPointAreTheSame_Test) {
    int size = 1<<10;
    vector<Point_2> points = PointsGenerator::GenerateRandomPoints(size);
    double firstX = points[0].x();
    double firstY = points[0].y();
    bool allPointsAreTheSame = true;
    for(int i=0;i<points.size();i++){
        if(points[i].x() != firstX || points[i].y()!=firstY){
            allPointsAreTheSame = false;
            break;
        }
    }
    EXPECT_FALSE(allPointsAreTheSame);
}