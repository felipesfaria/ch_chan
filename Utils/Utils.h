//
// Created by felipesfaria on 28/02/16.
//
#pragma once

#define PI 3.14159265
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

using namespace std;

class Utils {
public:
    Utils();
    ~Utils();
    static float isLeft( Point_2 P0, Point_2 P1, Point_2 P2 );

    static bool isInside(Point_2 *points, Point_2 point, int size);

    static double RandomDouble(int max);

    static double RandomNumberBetween(double min, double max);

    static bool isInside(vector<Point_2> points, Point_2 point);
};
