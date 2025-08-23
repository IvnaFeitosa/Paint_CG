#include "point.hpp"
#include <list>
#include <stdexcept>

Point::Point(float x_coord, float y_coord): x(x_coord), y(y_coord), h(1.0) {}
Point::Point() : x(0.0), y(0.0), h(1.0) {}

bool Point::is_type(string name) {
    if (name == "Point")
        return true;
    return false;
}

float Point::getX() {
    return this->x;
}

float Point::getY() {
    return this->y;
}

float Point::getH() {
    return this->h;
}

float Point::get(int i) {
    switch (i) {
        case 0:
            return this->getX();
        case 1:
            return this->getY();
        case 2:
            return this->getH();
        default:
            throw std::out_of_range("Index inválido em Point::get()");
    }
}

void Point::setX(float n_x) {
    this->x = n_x;
}

void Point::setY(float n_y) {
    this->y = n_y;
}

void Point::setH(float n_h) {
    this->h = n_h;
}

void Point::set(int i, float value) {
    switch (i) {
        case 0:
            this->setX(value);
            break;
        case 1:
            this->setY(value);
            break;
        case 2:
            this->setH(value);
            break;
        default:
            throw std::out_of_range("Index inválido em Point::set()");
    }
}

bool Point::detection(float mx, float my) {
    return true;
}

Point Point::get_center() {
    return *this;
}

list<Point> Point::get_points() {
    return list<Point>{*this};
}

void Point::set_points(list<Point> new_points) {
    for (int i = 0; i < 3; i++)
        this->set(i, new_points.front().get(i));
}
