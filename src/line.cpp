#include "line.hpp"
#include <list>

Line::Line(Point primeiro, Point segundo): p1(primeiro), p2(segundo) {}

bool Line::is_type(string name) {
    if (name == "Line")
        return true;
    return false;
}

bool Line::detection(float mx, float my) {
    return true;
}

Point Line::getp1() {
    return p1;
}

Point Line::getp2(){
    return p2;
}

Point Line::get_center() {
    float xm = (this->getp1().getX() + this->getp2().getX()) / 2.0;
    float ym = (this->getp1().getY() + this->getp2().getY()) / 2.0;
    return Point(xm, ym);
}
    
list<Point> Line::get_points() {
    return list<Point>{this->getp1(), this->getp2()};
}

void Line::set_points(list<Point> new_points) {
    for (int i = 0; i < 3; i++) {
        this->getp1().set(i, new_points.front().get(i));
        this->getp2().set(i, new_points.back().get(i));
    }
}