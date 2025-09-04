#ifndef CONVEX_HULL_DC_HPP
#define CONVEX_HULL_DC_HPP

#include <vector>
#include "point.hpp"

using namespace std;


float orientation(const Point &A, const Point &B, const Point &C);


vector<Point> mergeHulls(const vector<Point> &left, const vector<Point> &right);


vector<Point> divideAndConquerHull(vector<Point> points);

#endif
