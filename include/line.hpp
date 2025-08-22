#ifndef LINE_HPP
#define LINE_HPP

#include "point.hpp"
#include "object.hpp"

class Line : public Object{
private:
    Point p1;
    Point p2;

public:
    Line(Point primeiro, Point segundo);
    bool is_type(string name) override;
    bool detection(float mx, float my) override;
    Point getp1();
    Point getp2();
};

#endif