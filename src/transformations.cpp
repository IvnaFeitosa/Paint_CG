#include "transformations.hpp"
#include "polygon.hpp"
#include "line.hpp"

Transform::Transform() {}

void Transform::translade(Object *obj, float tx, float ty) {
    if (Point *p = dynamic_cast<Point*>(obj)) {

    } else if (Line *l = dynamic_cast<Line*>(obj)) {

    } else if (Poly *poly = dynamic_cast<Poly*>(obj)) {
        
    }
}

void Transform::scale(Object *obj, float sx, float sy) {

}

void Transform::rotate(Object *obj, float angle) {

}

void Transform::reflect(Object *obj) {

}

void Transform::shear(Object *obj) {

}
