//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"
#include "Utils.h"
#include <CGAL/convex_hull_2.h>

class UtilsFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    UtilsFixture() : Test() {
    }

    virtual ~UtilsFixture() {
    }
};

TEST_F(UtilsFixture, isLeft_pointIsLeft){
    Point_2 base(0,0);
    Point_2 top(0,2);
    Point_2 left(-1,2);
    float actual = Utils::isLeft(base,top,left);
    EXPECT_TRUE(actual>0);
}

TEST_F(UtilsFixture, isLeft_pointIsRight){
    Point_2 base(0,0);
    Point_2 top(0,2);
    Point_2 left(1,2);
    float actual = Utils::isLeft(base,top,left);
    EXPECT_TRUE(actual<0);
}

TEST_F(UtilsFixture, isLeft_pointIsOnTheLine){
    Point_2 base(0,0);
    Point_2 top(0,2);
    Point_2 left(0,3);
    float actual = Utils::isLeft(base,top,left);
    EXPECT_TRUE(actual==0);
}

TEST_F(UtilsFixture, isInside_TrueWhenPointIsInside){
    Point_2 convexHull[4] = {
            Point_2(0,0),
            Point_2(0,1),
            Point_2(1,1),
            Point_2(1,0)
    };
    Point_2 insidePoint(0.5,0.5);
    bool actual = Utils::isInside(convexHull,insidePoint,4);
    EXPECT_TRUE(actual);
}

TEST_F(UtilsFixture, isInside_TrueWhenPointIsOutside){
    Point_2 convexHull[4] = {
            Point_2(0,0),
            Point_2(0,1),
            Point_2(1,1),
            Point_2(1,0)
    };
    Point_2 insidePoint(0.5,2);
    bool actual = Utils::isInside(convexHull,insidePoint,4);
    EXPECT_FALSE(actual);
}