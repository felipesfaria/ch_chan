//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"
#include "PointsGenerator.h"
#include <CGAL/convex_hull_2.h>

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

TEST_F(PointsGeneratorFixture, GenerateRandomPoints_NotAllPointAreTheSame_Test) {
    int size = 1<<10;
    Point_2* points = PointsGenerator::GenerateRandomPoints(size);
    double firstX = points[0].x();
    double firstY = points[0].y();
    bool allPointsAreTheSame = true;
    for(int i=1;i<size;i++){
        if(points[i].x() != firstX || points[i].y()!=firstY){
            allPointsAreTheSame = false;
            break;
        }
    }
    EXPECT_FALSE(allPointsAreTheSame);
    free(points);
}

TEST_F(PointsGeneratorFixture, GenerateRandomPoints_PointDistributionWithinRange_Test) {
    int size = 1<<10;
    Point_2* points = PointsGenerator::GenerateRandomPoints(size);
    bool allPointsWithinRange = true;
    double minValue = 0;
    double maxValue = POINTS_RANGE;
    for(int i=0;i<size;i++){
        double x = points[i].x();
        double y = points[i].y();
        if(x<minValue||x>maxValue||y<minValue||y>maxValue){
            allPointsWithinRange = false;
            break;
        }
    }
    EXPECT_TRUE(allPointsWithinRange);
    free(points);
}

TEST_F(PointsGeneratorFixture, GenerateRandomPoints_DistributionIsRandom_Test) {
    int size = 1<<10;
    Point_2* points = PointsGenerator::GenerateRandomPoints(size);
    double avgX = 0;
    double avgY = 0;
    for(int i=0;i<size;i++){
        avgX += points[i].x();
        avgY += points[i].y();
    }
    avgX /=size;
    avgY /=size;
    double centerDistribution = POINTS_RANGE / 2;
    double tolerance = 5;
    bool distributionIsRandom = abs(avgX-centerDistribution)<tolerance && abs(avgY-centerDistribution)<tolerance;
    EXPECT_TRUE(distributionIsRandom);
    free(points);
}

TEST_F(PointsGeneratorFixture, GenerateTriangleHull_NotAllPointAreTheSame_Test) {
    int size = 1<<10;
    Point_2* points = PointsGenerator::GenerateTriangleHull(size);
    double firstX = points[0].x();
    double firstY = points[0].y();
    bool allPointsAreTheSame = true;
    for(int i=1;i<size;i++){
        if(points[i].x() != firstX || points[i].y()!=firstY){
            allPointsAreTheSame = false;
            break;
        }
    }
    EXPECT_FALSE(allPointsAreTheSame);
}

TEST_F(PointsGeneratorFixture, GenerateTriangleHull_ChHasThreePoints_Test) {
    int size = 1<<10;
    Point_2* points = PointsGenerator::GenerateTriangleHull(size);
    Point_2* result = (Point_2*)malloc(size*sizeof(Point_2));

    Point_2 *ptr = CGAL::ch_graham_andrew( points, points+size, result );
    int resultSize = ptr-result;
    int actual = resultSize;
    int expected = 3;
    EXPECT_EQ(expected,actual);
    free(points);
    free(result);
}

TEST_F(PointsGeneratorFixture, GenerateTriangleHull_DistributionIsRandom_Test) {
    int size = 1<<10;
    Point_2* points = PointsGenerator::GenerateTriangleHull(size);
    double avgX = 0;
    double avgY = 0;
    for(int i=0;i<size;i++){
        avgX += points[i].x();
        avgY += points[i].y();
    }
    avgX /=size;
    avgY /=size;
    double centerDistributionX = POINTS_RANGE / 3;
    double centerDistributionY = POINTS_RANGE / 3;
    double tolerance = 5;
    bool distributionIsRandom = abs(avgX-centerDistributionX)<tolerance && abs(avgY-centerDistributionY)<tolerance;
    EXPECT_TRUE(distributionIsRandom);
    free(points);
}

TEST_F(PointsGeneratorFixture, GenerateCircleHull_NotAllPointAreTheSame_Test) {
    int size = 10;
    Point_2* points = PointsGenerator::GenerateCircleHull(size);
    double firstX = points[0].x();
    double firstY = points[0].y();
    bool allPointsAreTheSame = true;
    for(int i=1;i<size;i++){
        if(points[i].x() != firstX || points[i].y()!=firstY){
            allPointsAreTheSame = false;
            break;
        }
    }
    EXPECT_FALSE(allPointsAreTheSame);
    free(points);
}

TEST_F(PointsGeneratorFixture, GenerateCircleHull_AllPointsArePartOfConvexHull_Test) {
    int size = 10;
    Point_2* points = PointsGenerator::GenerateCircleHull(size);
    Point_2* result = (Point_2*)malloc(size*sizeof(Point_2));

    Point_2 *ptr = CGAL::ch_graham_andrew( points, points+size, result );
    int resultSize = ptr-result;
    int actual = resultSize;
    int expected = size;
    EXPECT_EQ(expected,actual);
    free(points);
    free(result);
}

TEST_F(PointsGeneratorFixture, GenerateCircleHull_DistributionIsRegular_Test) {
    int size = 10;
    Point_2* points = PointsGenerator::GenerateCircleHull(size);
    double avgX = 0;
    double avgY = 0;
    for(int i=0;i<size;i++){
        avgX += points[i].x();
        avgY += points[i].y();
    }
    avgX /=size;
    avgY /=size;
    double centerDistributionX = 0;
    double centerDistributionY = 0;
    double tolerance = 5;
    bool DistributionIsRegular = abs(avgX-centerDistributionX)<tolerance && abs(avgY-centerDistributionY)<tolerance;
    EXPECT_TRUE(DistributionIsRegular);
    free(points);
}

TEST_F(PointsGeneratorFixture, GenerateConvexHull_NotAllPointAreTheSame_Test) {
    int nVertices = 10;
    int nPoints = 10;
    Point_2* points = PointsGenerator::GenerateConvexHull(nVertices,nPoints);
    double firstX = points[0].x();
    double firstY = points[0].y();
    bool allPointsAreTheSame = true;
    for(int i=1;i<nPoints;i++){
        if(points[i].x() != firstX || points[i].y()!=firstY){
            allPointsAreTheSame = false;
            break;
        }
    }
    EXPECT_FALSE(allPointsAreTheSame);
    free(points);
}

TEST_F(PointsGeneratorFixture, GenerateConvexHull_ConvexHullSizeIsCorrect_Test) {
    int nVertices = 10;
    int nPoints = 10;
    Point_2* points = PointsGenerator::GenerateConvexHull(nVertices,nPoints);
    Point_2* result = (Point_2*)malloc(nPoints*sizeof(Point_2));

    Point_2 *ptr = CGAL::ch_graham_andrew( points, points+nPoints, result );
    int resultSize = ptr-result;
    int actual = resultSize;
    int expected = nVertices;
    EXPECT_EQ(expected,actual);
    free(points);
    free(result);
}

TEST_F(PointsGeneratorFixture, GenerateConvexHull_DistributionIsRegular_Test) {
    int nVertices = 3;
    int nPoints = 1<<10;
    Point_2* points = PointsGenerator::GenerateConvexHull(nVertices,nPoints);
    double avgX = 0;
    double avgY = 0;
    for(int i=0;i<nPoints;i++){
        avgX += points[i].x();
        avgY += points[i].y();
    }
    avgX /=nPoints;
    avgY /=nPoints;
    double centerDistributionX = 0;
    double centerDistributionY = 0;
    double tolerance = 5;
    bool DistributionIsRegular = abs(avgX-centerDistributionX)<tolerance && abs(avgY-centerDistributionY)<tolerance;
    EXPECT_TRUE(DistributionIsRegular);
    free(points);
}