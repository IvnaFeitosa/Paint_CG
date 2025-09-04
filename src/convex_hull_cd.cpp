#include "convex_hull_dc.hpp"

#include <algorithm>
#include <limits>
#include <iostream>

float orientation(const Point &A, const Point &B, const Point &C) {
    return (B.getY() - A.getY()) * (C.getX() - B.getX()) -
           (B.getX() - A.getX()) * (C.getY() - B.getY());
}

vector<Point> mergeHulls(const vector<Point> &left, const vector<Point> &right) {
    
    int li = 0; 
    int ri = 0; 
    for(int i=1; i<left.size(); i++) if(left[i].getX() > left[li].getX()) li=i;
    for(int i=1; i<right.size(); i++) if(right[i].getX() < right[ri].getX()) ri=i;

 
    int l = li, r = ri;
    bool done = false;
    while(!done){
        done = true;
        while(orientation(right[r], left[l], left[(l+1)%left.size()]) > 0) l = (l+1)%left.size();
        while(orientation(left[l], right[r], right[(r-1+right.size())%right.size()]) < 0) r = (r-1+right.size())%right.size(), done=false;
    }
    int upper_l = l, upper_r = r;


    l = li; r = ri; done = false;
    while(!done){
        done = true;
        while(orientation(left[l], right[r], right[(r+1)%right.size()]) > 0) r = (r+1)%right.size();
        while(orientation(right[r], left[l], left[(l-1+left.size())%left.size()]) < 0) l = (l-1+left.size())%left.size(), done=false;
    }
    int lower_l = l, lower_r = r;


    vector<Point> newHull;
    int i = upper_l;
    newHull.push_back(left[i]);
    while(i != lower_l){
        i = (i+1)%left.size();
        newHull.push_back(left[i]);
    }

    i = lower_r;
    newHull.push_back(right[i]);
    while(i != upper_r){
        i = (i+1)%right.size();
        newHull.push_back(right[i]);
    }

    return newHull;
}

vector<Point> divideAndConquerHull(vector<Point> points) {
    if(points.size() <= 1) return points;

    sort(points.begin(), points.end(), [](const Point &a, const Point &b){ return a.getX() < b.getX(); });

    int mid = points.size()/2;
    vector<Point> left(points.begin(), points.begin() + mid);
    vector<Point> right(points.begin() + mid, points.end());

    vector<Point> leftHull = divideAndConquerHull(left);
    vector<Point> rightHull = divideAndConquerHull(right);

    return mergeHulls(leftHull, rightHull);
}
