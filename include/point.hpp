#ifndef POINT_HPP
#define POINT_HPP

#include "object.hpp"

class Point : public Object{
private:
    float x;
    float y;
    float h;

public:
    Point();
    Point(float n_x, float n_y);

    float getX();
    float getY();
    float getH();
    float get(int i);
    void setX(float n_x);
    void setY(float n_y);
    void setH(float n_h);
    void set(int i, float value);
    bool is_type(string name) override;
    bool detection(float mx, float my) override;
    Point get_center() override;
    list<Point> get_points() override;
    void set_points(list<Point> new_points) override;
};

#endif