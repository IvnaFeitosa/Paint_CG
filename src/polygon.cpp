#include "polygon.hpp"


Poly::Poly(list<Point> points) {
    verticies = points;

    float x_sum = 0.0, y_sum = 0.0;
    int num_verticies = (float) verticies.size();

    for (auto it = verticies.begin(); it != verticies.end(); it++) {
        x_sum += it->getX();
        y_sum += it->getY();
    }

    center.setX(x_sum / num_verticies);
    center.setY(y_sum / num_verticies);
}

bool Poly::is_type(string name) {
    if (name == "Poly")
        return true;
    return false;
}

list<Point>& Poly::get_verticies() {
    return verticies;
}

bool Poly::detection(float mx, float my) {
    return true;
}

Point Poly::get_center() {
    return this->center;
}

list<Point> Poly::get_points() {
    return verticies;
}

void Poly::set_points(list<Point> new_points) {
    auto it = verticies.begin();
    for (Point new_p: new_points) {
        for (int i = 0; i < 3; i++)
            it->set(i, new_p.get(i));
        it++;
    }
}

