#ifndef POINT_HPP
#define POINT_HPP

#include "object.hpp"

class Point : public Object{
private:
    float x;
    float y;

public:
    Point(float n_x, float n_y);

    float getX();
    float getY();
    void setX(float n_x);
    void setY(float n_y);
    bool is_type(string name) override;
    bool detection(float mx, float my) override;
};

#endif