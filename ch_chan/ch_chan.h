//
// Created by felipesfaria on 01/03/16.
//
#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/ch_jarvis.h>
#include <vector>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
using namespace std;
class ch_chan {
public:
    static vector<Point_2*> hulls;
    static Point_2* FindHull(Point_2* start, Point_2* end, Point_2* result);
    static vector<vector< Point_2 > > GetSubHulls(Point_2 *start, Point_2 *end, int m);
};
