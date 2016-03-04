//
// Created by felipesfaria on 28/02/16.
//

#include "Utils.h"

Utils::Utils(){

};
Utils::~Utils(){

};
// isLeft(): test if a point is Left|On|Right of an infinite line.
//    Input:  three points P0, P1, and P2
//    Return: >0 for P2 left of the line through P0 and P1
//            =0 for P2 on the line
//            <0 for P2 right of the line
//    See: Algorithm 1 on Area of Triangles
float Utils::isLeft( Point_2 P0, Point_2 P1, Point_2 P2 )
{
    return (P1.x() - P0.x())*(P2.y() - P0.y()) - (P2.x() - P0.x())*(P1.y() - P0.y());
}

bool Utils::isInside(Point_2 *points,Point_2 point, int size){
    float isLeft = Utils::isLeft(points[size-1],points[0],point);
    if(isLeft>=0) return false;

    for(int i = 1; i<size;i++){
        isLeft = Utils::isLeft(points[i-1],points[i],point);
        if(isLeft>=0) return false;
    }
    return true;
}

double Utils::RandomNumberBetween(double min, double max){
    return (max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
}

double Utils::RandomDouble(int max = 1){
    return ((double) rand() / (RAND_MAX))*max;
}
