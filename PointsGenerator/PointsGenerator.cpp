//
// Created by felipesfaria on 28/02/16.
//

#include "PointsGenerator.h"
using namespace std;

PointsGenerator::PointsGenerator() {

};
PointsGenerator::~PointsGenerator() {

};

Point_2* PointsGenerator::GenerateRandomPoints(int size) {
    Point_2* points = (Point_2*)malloc(size*sizeof(Point_2));
    for(int i=0;i<size;i++){
        double x = rand() % POINTS_RANGE;
        double y = rand() % POINTS_RANGE;
        points[i] = Point_2(x,y);
    }
    return points;
}

//Smallest convex hull possible
Point_2* PointsGenerator::GenerateTriangleHull(int size) {
    Point_2 bottomLeft(0,0);
    Point_2 bottomRight(0,POINTS_RANGE);
    Point_2 topMiddle(POINTS_RANGE,0);

    Point_2* points = (Point_2*)malloc(size*sizeof(Point_2));
    int idx = 0;
    points[idx++] = bottomLeft;
    points[idx++] = bottomRight;
    points[idx++] = topMiddle;
    while(idx<size){
        double x = Utils::RandomDouble(POINTS_RANGE);
        double y = Utils::RandomDouble(POINTS_RANGE);
        if(x+y<POINTS_RANGE)
            points[idx++] = Point_2(x,y);
    }
    return points;
}

//All points belong to convex hull
Point_2* PointsGenerator::GenerateCircleHull(int size) {
    Point_2* points = (Point_2*)malloc(size*sizeof(Point_2));

    double delta = 2*PI/size;
    double theta = 0;
    double r = POINTS_RANGE;
    for(int i = 0; i< size;i++){
        points[i] = Point_2(r*cos(theta),r*sin(theta));
        theta-=delta;
    }
    return points;
}

//All points belong to convex hull
Point_2* PointsGenerator::GenerateConvexHull(int nVertices, int nPoints) {
    Point_2* points = (Point_2*)malloc(nPoints*sizeof(Point_2));

    double delta = 2*PI/nVertices;
    double theta = 0;
    double r = POINTS_RANGE;
    for(int i = 0; i< nVertices;i++){
        points[i] = Point_2(r*cos(theta),r*sin(theta));
        theta-=delta;
    }
    int i = nVertices;
    while(i<nPoints){
        double x = Utils::RandomDouble(2*POINTS_RANGE-1)-POINTS_RANGE;
        double y = Utils::RandomDouble(2*POINTS_RANGE-1)-POINTS_RANGE;
        Point_2 point(x,y);
        if(Utils::isInside(points,point,nVertices))
            points[i++] = Point_2(x,y);
    }
    return points;
}