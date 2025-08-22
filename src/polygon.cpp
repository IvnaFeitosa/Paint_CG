#include "polygon.hpp"


Poly::Poly(const std::vector<Point>& pts) {
    vertices = pts;
}

bool Poly::is_type(string name) {
    if (name == "Poly")
        return true;
    return false;
}

const std::vector<Point>& Poly::getVertices() {
    return vertices;
}

bool Poly::detection(float mx, float my) {
    return true;
}
