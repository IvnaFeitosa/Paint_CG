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

Object* ObjContainer::search_detection(float mx, float my) {

    for (auto it = lines.begin(); it != lines.end(); it++) {
        if (it->detection(mx, my))
            return &(*it);
    }

    for (auto it = points.begin(); it != points.end(); it++) {
        if (it->detection(mx, my))
            return &(*it);
    }

    

    for (auto it = polygons.begin(); it != polygons.end(); it++) {
        if (it->detection(mx, my))
            return &(*it);
    }

    return nullptr;
}
