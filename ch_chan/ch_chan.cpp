//
// Created by felipesfaria on 01/03/16.
//

#include "ch_chan.h"

Point_2* ch_chan::FindHull(Point_2* start, Point_2* end, Point_2* result){
    int size = end-start;
    int t = 0;
    int m = 2 ^(2 ^ t++);
    while(m < size){
        GetSubHulls(start, end, m);


        m = 2 ^(2 ^ t++);
    }

}

vector<vector< Point_2 >> ch_chan::GetSubHulls(Point_2 *start, Point_2 *end, int m) {
    Point_2 *s,*e,*r;
    int size = end-start;
    int nHulls = ceil((double)size / m);
    r = new Point_2[size];
    vector<vector< Point_2 >> hulls;
    for(int j = 0; j < nHulls; j++){
        s = start+j*m;
        e = start + min((j+1)*m, size);
        Point_2* ptr = CGAL::ch_graham_andrew(s, e, r+j*m);
        vector< Point_2 >  V (r+j*m,ptr);
        hulls.push_back(V);
    }
    delete[](r);
    return hulls;
}