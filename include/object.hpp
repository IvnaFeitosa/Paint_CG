#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
#include <list>
using namespace std;

class Point;
class ObjContainer;

class Object {
private:
    static unsigned int id_gen;
    unsigned int id;
    
public:
    
    Object();
    virtual ~Object() = default; 
    virtual bool detection(float mx, float my) = 0;
    virtual bool is_type(string name) = 0;
    virtual Point get_center() = 0;
    virtual list<Point> get_points() = 0;
    virtual void set_points(list<Point> new_points) = 0;
    unsigned int get_id();
    bool equals(Object* obj);
};

#endif