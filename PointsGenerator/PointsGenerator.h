//
// Created by felipesfaria on 28/02/16.
//

#ifndef CALENDAR_POINTSGENERATOR_H
#define CALENDAR_POINTSGENERATOR_H
#define POINTS_RANGE 100
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

using namespace std;

class PointsGenerator {
public:
    PointsGenerator();
    ~PointsGenerator();
    static vector<Point_2> GenerateRandomPoints(int size);
};


#endif //CALENDAR_POINTSGENERATOR_H
