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
};

#endif