#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "object.hpp"
#include <array>
#include <list>

using namespace std;

typedef array<array<float, 3>, 3> Operation;

class Transform {
private:
    static Operation matrix;
    static list<Operation> operations; 

    static void add_operation(Operation new_matrix);
    static void aply_to_points(list<Point>& points);
    static void multiply(Operation operation);
    
public:
    
    Transform();
    
    static void load_identity();
    static void translade(float tx, float ty);
    static void scale(float sx, float sy, Point center);
    static void rotate(float angle, Point center);
    static void reflect(bool rx, bool ry);
    static void shear_x(float shx, Point center);
    static void shear_y(float shy, Point center);
    static void aply_transformations(Object *obj);
};

#endif