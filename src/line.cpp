#include "line.hpp"

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
