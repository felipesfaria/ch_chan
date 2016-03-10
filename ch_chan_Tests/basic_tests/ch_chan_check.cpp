//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"
#include "ch_chan.h"

#include <CGAL/convex_hull_2.h>
#include <vector>
#include <PointsGenerator.h>

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

TEST_F(ch_chanFixture, FindLeftmostHull){
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
    //Square
    points[i++] = Point_2(0,0);
    points[i++] = Point_2(0,-1);
    points[i++] = Point_2(-1,0.32); // This guy is the leftmost!!!
    points[i++] = Point_2(-0.9,-1);
    //Triangle with point in middle
    points[i++] = Point_2(1,0);
    points[i++] = Point_2(1,1);
    points[i++] = Point_2(1,0.1);
    points[i++] = Point_2(2,0);
    vector<vector< Point_2 > > hulls = ch_chan::GetSubHulls(points,points+i,4);
    int hIndex, pIndex;
    ch_chan::FindLeftmostHull(hulls, hIndex, pIndex);
    int expected = 2;
    int actual = hIndex;
    EXPECT_EQ(expected, actual)<<"hIndex";
    expected = 0.32;
    actual = hulls[hIndex][pIndex].y();
    EXPECT_EQ(expected, actual)<<"pIndex";
}

TEST_F(ch_chanFixture, aboveIsAbove){
    Point_2 p(0,1);
    Point_2 vi(0,0);
    Point_2 vj(1,0);
    bool actual = above(p,vi,vj);
    EXPECT_TRUE(actual);
}

TEST_F(ch_chanFixture, aboveIsBelow){
    Point_2 p(0,-1);
    Point_2 vi(0,0);
    Point_2 vj(1,0);
    bool actual = above(p,vi,vj);
    EXPECT_FALSE(actual);
}

TEST_F(ch_chanFixture, belowIsBelow){
    Point_2 p(0,-1);
    Point_2 vi(0,0);
    Point_2 vj(1,0);
    bool actual = below(p,vi,vj);
    EXPECT_TRUE(actual);
}

TEST_F(ch_chanFixture, belowIsAbove){
    Point_2 p(0,1);
    Point_2 vi(0,0);
    Point_2 vj(1,0);
    bool actual = below(p,vi,vj);
    EXPECT_FALSE(actual);
}

TEST_F(ch_chanFixture, Rtangent_PointPolyCTriangle){
    vector<Point_2> v;
    //Triangle
    v.push_back(Point_2(1,1));
    v.push_back(Point_2(1,0));// expected right tangent
    v.push_back(Point_2(2,0));
    Point_2 p(0,1);
    int actual = ch_chan::Rtangent_PointPolyC(p,v);
    int expected = 1;
    EXPECT_EQ(expected,actual);
}

TEST_F(ch_chanFixture, Rtangent_PointPolyCSquare){
    vector<Point_2> v;
    //Triangle with point in middle
    v.push_back(Point_2(1,1));
    v.push_back(Point_2(1,0));
    v.push_back(Point_2(2,0));
    v.push_back(Point_2(2,1));
    Point_2 p(3,3);
    int actual = ch_chan::Rtangent_PointPolyC(p,v);
    int expected = 0;
    EXPECT_EQ(expected,actual);
}

TEST_F(ch_chanFixture, Rtangent_PointPolyCTwoPoints){
    Point_2 p(0,0);
    vector<Point_2> v;
    v.push_back(Point_2(1,1));
    v.push_back(Point_2(1,0));
    int actual = ch_chan::Rtangent_PointPolyC(p,v);
    int expected = 1;
    EXPECT_EQ(expected,actual);
}

TEST_F(ch_chanFixture, Rtangent_PointPolyCSinglePoint){
    Point_2 p(0,0);
    vector<Point_2> v;
    v.push_back(Point_2(4,1));
    int actual = ch_chan::Rtangent_PointPolyC(p,v);
    int expected = 0;
    EXPECT_EQ(expected,actual);
}

TEST_F(ch_chanFixture, rtangentLoopCheck){
    vector<Point_2> v;
    //Triangle with point in middle
    v.push_back(Point_2(27.7775,55.397));
    v.push_back(Point_2(100,0));
    Point_2 p(0,0);
    int actual = ch_chan::Rtangent_PointPolyC(p,v);
    int expected = 1;
    EXPECT_EQ(expected,actual);
}

TEST_F(ch_chanFixture, NextPair){
    vector<Point_2> square;
    //square
    square.push_back(Point_2(0,0));
    square.push_back(Point_2(1,-0.1));
    square.push_back(Point_2(1,1.2));
    square.push_back(Point_2(0.1,1));

    vector<Point_2> triangle;
    //Triangle
    triangle.push_back(Point_2(2,-0.2));
    triangle.push_back(Point_2(3,0));
    triangle.push_back(Point_2(2,1.1));

    vector<vector<Point_2> > hulls;
    hulls.push_back(square);
    hulls.push_back(triangle);
    int hIndex = 0;
    int pIndex = 0;
    int counter = 1;
    ch_chan::NextPair(hulls,hIndex,pIndex);
    int actualH = hIndex;
    int expectedH = 0;
    int actualP = pIndex;
    int expectedP = 1;
    EXPECT_EQ(expectedH,actualH)<<"Point("<<counter<<"): h";
    EXPECT_EQ(expectedP,actualP)<<"Point("<<counter<<"): p";
    counter++;
    ch_chan::NextPair(hulls,hIndex,pIndex);
    actualH = hIndex;
    expectedH = 1;
    actualP = pIndex;
    expectedP = 0;
    EXPECT_EQ(expectedH,actualH)<<"Point("<<counter<<"): h";
    EXPECT_EQ(expectedP,actualP)<<"Point("<<counter<<"): p";
    counter++;
    ch_chan::NextPair(hulls,hIndex,pIndex);
    actualH = hIndex;
    expectedH = 1;
    actualP = pIndex;
    expectedP = 1;
    EXPECT_EQ(expectedH,actualH)<<"Point("<<counter<<"): h";
    EXPECT_EQ(expectedP,actualP)<<"Point("<<counter<<"): p";
    counter++;
    ch_chan::NextPair(hulls,hIndex,pIndex);
    actualH = hIndex;
    expectedH = 1;
    actualP = pIndex;
    expectedP = 2;
    EXPECT_EQ(expectedH,actualH)<<"Point("<<counter<<"): h";
    EXPECT_EQ(expectedP,actualP)<<"Point("<<counter<<"): p";
    counter++;
    ch_chan::NextPair(hulls,hIndex,pIndex);
    actualH = hIndex;
    expectedH = 0;
    actualP = pIndex;
    expectedP = 2;
    EXPECT_EQ(expectedH,actualH)<<"Point("<<counter<<"): h";
    EXPECT_EQ(expectedP,actualP)<<"Point("<<counter<<"): p";
    counter++;
    ch_chan::NextPair(hulls,hIndex,pIndex);
    actualH = hIndex;
    expectedH = 0;
    actualP = pIndex;
    expectedP = 3;
    EXPECT_EQ(expectedH,actualH)<<"Point("<<counter<<"): h";
    EXPECT_EQ(expectedP,actualP)<<"Point("<<counter<<"): p";
    counter++;
}

TEST_F(ch_chanFixture, FindHullTriangle){
    int nPoints = 16;
    Point_2 *points = PointsGenerator::GenerateTriangleHull(nPoints);
    Point_2 *result = new Point_2[nPoints];
    Point_2 *resultEnd = ch_chan::FindHull(points,points+nPoints,result);
    int expected = 3;
    int actual = resultEnd-result;
    EXPECT_EQ(expected,actual);
    free(points);
    delete(result);
}

TEST_F(ch_chanFixture, FindHullSquare){
    int nVertices = 4;
    int nPoints = 16;
    Point_2 *points = PointsGenerator::GenerateConvexHull(nVertices,nPoints);
    Point_2 *result = new Point_2[nPoints];
    Point_2 *resultEnd = ch_chan::FindHull(points,points+nPoints,result);
    int expected = nVertices;
    int actual = resultEnd-result;
    EXPECT_EQ(expected,actual);
    free(points);
    delete(result);
}

TEST_F(ch_chanFixture, FindHullLotsOfPoints){
    int nVertices = 1<<5;
    int nPoints = 1<<10;
    Point_2 *points = PointsGenerator::GenerateConvexHull(nVertices,nPoints);
    Point_2 *result = new Point_2[nPoints];
    Point_2 *resultEnd = ch_chan::FindHull(points,points+nPoints,result);
    int expected = nVertices;
    int actual = resultEnd-result;
    EXPECT_EQ(expected,actual);
    free(points);
    delete(result);
}

TEST_F(ch_chanFixture, FindHullWorstCase){
    int nVertices = 1<<10;
    int nPoints = nVertices;
    Point_2 *points = PointsGenerator::GenerateConvexHull(nVertices,nPoints);
    Point_2 *result = new Point_2[nPoints];
    Point_2 *resultEnd = ch_chan::FindHull(points,points+nPoints,result);
    int expected = nVertices;
    int actual = resultEnd-result;
    EXPECT_EQ(expected,actual);
    free(points);
    delete(result);
}