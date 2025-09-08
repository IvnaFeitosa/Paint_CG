#include "obj_container.hpp"

ObjContainer::ObjContainer() {
    this->points.clear();
    this->polygons.clear();
    this->lines.clear();
}

void ObjContainer::clear() {
    this->points.clear();
    this->lines.clear();
    this->polygons.clear();
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
    for (auto it = points.rbegin(); it != points.rend(); it++) {
        if (it->detection(mx, my))
        return &(*it);
    }
    
    for (auto it = lines.rbegin(); it != lines.rend(); it++) {
        if (it->detection(mx, my))
            return &(*it);
    }
    
    for (auto it = polygons.rbegin(); it != polygons.rend(); it++) {
        if (it->detection(mx, my))
            return &(*it);
    }

    return nullptr;
}

void ObjContainer::search_for_deletion(Object* obj) {
    for (auto it = points.begin(); it != points.end(); it++) {
        if (obj->equals(&(*it))) {
            it = points.erase(it);
            return;
        }
    }

    for (auto it = lines.begin(); it != lines.end(); it++) {
        if (obj->equals(&(*it))) {
            it = lines.erase(it);
            return;
        }
    }

    for (auto it = polygons.begin(); it != polygons.end(); it++) {
        if (obj->equals(&(*it))) {
            it = polygons.erase(it);
            return;
        }
    }
}
