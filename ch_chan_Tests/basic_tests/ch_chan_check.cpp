//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"
#include "ch_chan.h"
#include <CGAL/convex_hull_2.h>
#include <vector>

class ch_chanFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    ch_chanFixture() : Test() {
    }

    virtual ~ch_chanFixture() {
    }
};

TEST_F(ch_chanFixture, Point_OverLoads_LessThan_OnX){
    Point_2 p1(0,0),p2(0,1);
    EXPECT_TRUE(p1<p2);
    EXPECT_FALSE(p1>p2);
}

TEST_F(ch_chanFixture, Point_OverLoads_LessThan_OnY){
    Point_2 p1(0,0),p2(1,0);
    EXPECT_TRUE(p1<p2);
    EXPECT_FALSE(p1>p2);
}

TEST_F(ch_chanFixture, Point_OverLoads_LessThan_OnXY){
    Point_2 p1(0,0),p2(1,1);
    EXPECT_TRUE(p1<p2);
    EXPECT_FALSE(p1>p2);
}

TEST_F(ch_chanFixture, ConvexHullOfSinglePoint){
    Point_2 points[1],result[1];
    points[0] = Point_2(0,0);
    Point_2 *ptr = CGAL::ch_graham_andrew(points,points+1,result);
    int expected = 1;
    int actual = ptr-result;
    EXPECT_EQ(expected,actual);
}

TEST_F(ch_chanFixture, ConvexHullOfTwoPoints){
    const int size = 2;
    Point_2 points[size],result[size];
    points[0] = Point_2(0,0);
    points[1] = Point_2(1,1);
    Point_2 *ptr = CGAL::ch_graham_andrew(points,points+size,result);
    int expected = size;
    int actual = ptr-result;
    EXPECT_EQ(expected,actual);
}

TEST_F(ch_chanFixture, CheckSubHulls){
    Point_2 points[8];
    int i =0;
    points[i++] = Point_2(0,0);
    points[i++] = Point_2(0,1);
    points[i++] = Point_2(0,0.1);
    points[i++] = Point_2(1,0);
    points[i++] = Point_2(1,0);
    points[i++] = Point_2(1,1);
    points[i++] = Point_2(1,0.1);
    points[i++] = Point_2(2,0);
    vector<vector< Point_2 > > hulls = ch_chan::GetSubHulls(points,points+8,4);
    int actual = hulls[0].size();
    int expected = 3;
    EXPECT_EQ(actual,expected);
    actual = hulls[1].size();
    expected = 3;
    EXPECT_EQ(actual,expected);
}

TEST_F(ch_chanFixture, CheckSubHullsOddNumberOfPoints){
    Point_2 points[16];
    int i =0;
    //Single Point
    points[i++] = Point_2(1,0);
    points[i++] = Point_2(1,0);
    points[i++] = Point_2(1,0);
    points[i++] = Point_2(1,0);
    //Two Points
    points[i++] = Point_2(1,0);
    points[i++] = Point_2(1,0);
    points[i++] = Point_2(1,1);
    points[i++] = Point_2(1,1);
    //Triangle with point in middle
    points[i++] = Point_2(1,0);
    points[i++] = Point_2(1,1);
    points[i++] = Point_2(1,0.1);
    points[i++] = Point_2(2,0);
    //Square
    points[i++] = Point_2(0,0);
    points[i++] = Point_2(0,1);
    points[i++] = Point_2(1,0);
    points[i++] = Point_2(1,1);
    vector<vector< Point_2 > > hulls = ch_chan::GetSubHulls(points,points+i,4);
    for(int i =0;i<4;i++){
        int expected = i+1;
        int actual = hulls[i].size();
        EXPECT_EQ(expected, actual);
    }
}