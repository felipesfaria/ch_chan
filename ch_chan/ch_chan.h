//
// Created by felipesfaria on 01/03/16.
//
#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include "../Utils/Utils.h"
#include <CGAL/convex_hull_2.h>
#include <CGAL/ch_jarvis.h>
#include <vector>

// tests for polygon vertex ordering relative to a fixed point P
#define above(P,Vi,Vj)  (Utils::isLeft(P,Vi,Vj) > 0)   // true if Vi is above Vj
#define below(P,Vi,Vj)  (Utils::isLeft(P,Vi,Vj) < 0)   // true if Vi is below Vj

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
using namespace std;
class ch_chan {
public:
    static vector<Point_2*> hulls;
    static Point_2* FindHull(Point_2* start, Point_2* end, Point_2* result);
    static vector<vector< Point_2 > > GetSubHulls(Point_2 *start, Point_2 *end, int m);
    static void FindLeftmostHull(const vector<vector<Point_2> > &hulls, int &hIndex, int &pIndex);
    static int Rtangent_PointPolyC(const Point_2 P, vector<Point_2> V);
    static void NextPair(const vector<vector<Point_2> > &hulls, int &hIndex, int &pIndex);
};
