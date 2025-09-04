#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>

using namespace std;

#include "point.hpp"

class Poly : public Object {
private:
    vector<Point> verticies;
    Point center;
    bool fill;

public:

    Poly(list<Point> points);
    Poly(list<Point> points, bool fill);

    vector<Point>& get_verticies();
    bool is_type(string name) override;
    bool detection(float mx, float my) override;
    Point get_center() override;
    list<Point> get_points() override;
    void set_points(list<Point> new_points) override;
    void set_vertices(const vector<Point>& novosVertices);
    bool is_fill();
};

#endif