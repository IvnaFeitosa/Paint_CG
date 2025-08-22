#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "point.hpp"

class Poly : public Object {
public:
    std::vector<Point> vertices;

    Poly(const std::vector<Point>& pts);

    const std::vector<Point>& getVertices();
    bool is_type(string name) override;
    bool detection(float mx, float my) override;
};

#endif