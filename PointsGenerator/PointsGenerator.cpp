//
// Created by felipesfaria on 28/02/16.
//

#include "PointsGenerator.h"
#include <exception>
using namespace std;

// isLeft(): test if a point is Left|On|Right of an infinite line.
//    Input:  three points P0, P1, and P2
//    Return: >0 for P2 left of the line through P0 and P1
//            =0 for P2 on the line
//            <0 for P2 right of the line
//    See: Algorithm 1 on Area of Triangles
inline float
isLeft( Point_2 P0, Point_2 P1, Point_2 P2 )
{
    return (P1.x() - P0.x())*(P2.y() - P0.y()) - (P2.x() - P0.x())*(P1.y() - P0.y());
}

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
double RandomNumberBetween(double min, double max){
    return (max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
}
double RandomDouble(int max = 1){
    return ((double) rand() / (RAND_MAX))*max;
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
        double x = RandomDouble(POINTS_RANGE);
        double y = RandomDouble(POINTS_RANGE);
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
    for(int i =nVertices;i<nPoints;i++){
        double x = RandomDouble(2*POINTS_RANGE-1)-POINTS_RANGE;
        double y = RandomDouble(2*POINTS_RANGE-1)-POINTS_RANGE;
        points[i] = Point_2(x,y);
    }
    return points;
}