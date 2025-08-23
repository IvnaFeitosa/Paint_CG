#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>

using namespace std;

class ObjContainer;

class Object {
public:
    Object() = default;
    virtual ~Object() = default; 
    virtual bool detection(float mx, float my) = 0;
    virtual bool is_type(string name) = 0;
    virtual Point get_center() = 0;
    virtual list<Point> get_points() = 0;
    virtual void set_points(list<Point> new_points) = 0;
};

#endif