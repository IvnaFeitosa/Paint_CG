#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "object.hpp"

class Transform {
public:

    Transform();

    static void translade(Object *obj, float tx, float ty);
    static void scale(Object *obj, float sx, float sy);
    static void rotate(Object *obj, float angle);
    static void reflect(Object *obj);
    static void shear(Object *obj);
};

#endif