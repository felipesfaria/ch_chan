//
// Created by felipesfaria on 28/02/16.
//

#ifndef CALENDAR_POINTSGENERATOR_H
#define CALENDAR_POINTSGENERATOR_H
#define POINTS_RANGE 100
#define PI 3.14159265
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

using namespace std;

class PointsGenerator {
public:
    PointsGenerator();
    ~PointsGenerator();
    static Point_2* GenerateRandomPoints(int size);
    static Point_2* GenerateTriangleHull(int size);
    static Point_2 *GenerateCircleHull(int size);
    static Point_2 *GenerateConvexHull(int nVertices, int nPoints);
};


#endif //CALENDAR_POINTSGENERATOR_H
