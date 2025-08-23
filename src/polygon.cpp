#include "polygon.hpp"
#include <list>


Poly::Poly(std::vector<Point>& pts) {
    vertices = pts;
}

bool Poly::is_type(string name) {
    if (name == "Poly")
        return true;
    return false;
}

std::vector<Point>& Poly::getVertices() {
    return vertices;
}

bool Poly::detection(float mx, float my) {
    return true;
}

Point Poly::get_center() {
    return Point(0, 0);
}

list<Point> Poly::get_points() {
    return list<Point>();
}

void Poly::set_points(list<Point> new_points) {
    
}

