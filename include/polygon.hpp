#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <list>

using namespace std;

#include "point.hpp"

class Poly : public Object {
private:
    list<Point> vertices;
    Point center;

public:

    Poly(list<Point> points);

    list<Point>& getVertices();
    bool is_type(string name) override;
    bool detection(float mx, float my) override;
    Point get_center() override;
    list<Point> get_points() override;
    void set_points(list<Point> new_points) override;
};

#endif