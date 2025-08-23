#include "obj_container.hpp"

ObjContainer::ObjContainer() {
    this->points.clear();
    this->polygons.clear();
    this->lines.clear();
}

void ObjContainer::addPoint(Point p) {
    this->points.push_back(p);
}

void ObjContainer::addLine(Line l) {
    this->lines.push_back(l);
}

void ObjContainer::addPoly(Poly poly) {
    this->polygons.push_back(poly);
}

list<Point>& ObjContainer::get_points() {
    return this->points;
}

list<Line>& ObjContainer::get_lines() {
    return this->lines;
}

list<Poly>& ObjContainer::get_polygons() {
    return this->polygons;
}

Object* ObjContainer::searchDetections() {
    Object *obj = nullptr;
    return obj;
}
