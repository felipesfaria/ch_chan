//
// Created by felipesfaria on 28/02/16.
//

#include "PointsGenerator.h"

PointsGenerator::PointsGenerator() {

};
PointsGenerator::~PointsGenerator() {

};

vector<Point_2> PointsGenerator::GenerateRandomPoints(int size) {
    vector<Point_2> points;
    for(int i=0;i<size;i++){
        double x = rand() % POINTS_RANGE;
        double y = rand() % POINTS_RANGE;
        points.push_back(Point_2(x,y));
    }
    return points;
}
