#include "point.hpp"
#include <list>

Point::Point(float largura, float altura): x(largura), y(altura){}

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

void Point::setX(float largura) {
    this->x=largura;
}

void Point::setY(float altura) {
    this->y=altura;
}

bool Point::detection(float mx, float my) {
    return true;
}

Point Point::get_center() {
    return Point(0, 0);
}

list<Point> Point::get_points() {
    return list<Point>();
}

void Point::set_points(list<Point> new_points) {
    
}
