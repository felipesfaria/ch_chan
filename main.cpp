#include <ctime>
#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/ch_jarvis.h>
#include "PointsGenerator/PointsGenerator.h"
#include "ch_chan/ch_chan.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

using namespace std;
void CompareConvexHullAlgorithms(Point_2* points, int size){
    int start, elapsed;
    Point_2* result = new Point_2[size];
    Point_2 *ptr;
    start = clock();
    ptr = CGAL::ch_graham_andrew( points, points+size, result );
    elapsed = clock()-start;
    cout<<"ch_graham_andrew\t"<<size<<"\t"<<ptr-result<<"\t"<<elapsed<<endl;
    start = clock();
    ptr = CGAL::ch_jarvis( points, points+size, result );
    elapsed = clock()-start;
    cout<<"ch_jarvis\t"<<size<<"\t"<<ptr-result<<"\t"<<elapsed<<endl;
    start = clock();
    ptr = CGAL::convex_hull_2( points, points+size, result );
    elapsed = clock()-start;
    cout<<"convex_hull_2\t"<<size<<"\t"<<ptr-result<<"\t"<<elapsed<<endl;
    start = clock();
    ptr = ch_chan::FindHull( points, points+size, result );
    elapsed = clock()-start;
    cout<<"ch_chan\t"<<size<<"\t"<<ptr-result<<"\t"<<elapsed<<endl;
}
int main()
{
    //Header
    cout<<"algorithm\tn\th\tt"<<endl;
    Point_2* points;
    int n, h;
    n = 300;
    for(int i = 0; i<4;i++) {
        points = PointsGenerator::GenerateRandomPoints(n);
        CompareConvexHullAlgorithms(points, n);
        h = 3;
        points = PointsGenerator::GenerateConvexHull(h, n);
        CompareConvexHullAlgorithms(points, n);
        h = n;
        points = PointsGenerator::GenerateConvexHull(h, n);
        CompareConvexHullAlgorithms(points, n);
        n+=50;
    }

    return 0;
}
