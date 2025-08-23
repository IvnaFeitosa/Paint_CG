#include <cmath>
#include "transformations.hpp"
#include "polygon.hpp"
#include "line.hpp"

Operation Transform::matrix;
list<Operation> Transform::operations;

Transform::Transform() {
    load_identity();
    operations.clear();
}

void Transform::add_operation(Operation new_matrix) {
    operations.push_front(new_matrix);
}

void Transform::multiply(Operation operation) {
    Operation temp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                temp[i][j] += operation[i][k] * matrix[k][j];
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = temp[i][j];
        }
    }
}

void Transform::load_identity() {
    matrix = {
        {{1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}}
    };
}

void Transform::translade(float tx, float ty) {
    Operation mat_translade = {
        {{1, 0, tx},
        {0, 1, ty},
        {0, 0, 1}}
    };
    add_operation(mat_translade);
}

void Transform::scale(float sx, float sy, Point center) {
    translade(-center.getX(), -center.getY());

    Operation mat_scale = {
        {{sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}}
    };
    add_operation(mat_scale);

    translade(center.getX(), center.getY());
}

void Transform::rotate(float angle, Point center) {
    translade(-center.getX(), -center.getY());
    
    float rad = angle * M_PI / 180;
    Operation mat_rotate = {
        {{cos(rad), -sin(rad), 0},
        {sin(rad), cos(rad), 0},
        {0, 0, 1}}
    };
    add_operation(mat_rotate);
    
    translade(center.getX(), center.getY());
}

void Transform::reflect(bool rx, bool ry) {
    float sx = rx ? -1.0f : 1.0f;
    float sy = ry ? -1.0f : 1.0f;

    Operation mat_reflect = {
        {{sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}}
    };
    add_operation(mat_reflect);
}

void Transform::shear_x(float shx, Point center) {
    translade(-center.getX(), -center.getY());
    Operation mat_shear = {
        {{1, shx, 0},
        {0, 1, 0},
        {0, 0, 1}}
    };
    add_operation(mat_shear);
    translade(-center.getX(), -center.getY());
}

void Transform::shear_y(float shy, Point center) {
    translade(-center.getX(), -center.getY());
    Operation mat_shear = {
        {{1, 0, 0},
        {shy, 1, 0},
        {0, 0, 1}}
    };
    add_operation(mat_shear);
    translade(-center.getX(), -center.getY());
}

void Transform::aply_transformations(Object *obj) {
    while (!operations.empty()) {
        multiply(operations.front());
        operations.pop_front();
    }

    list<Point> points = obj->get_points();
    aply_to_points(points);

    obj->set_points(points);

    load_identity();
}

void Transform::aply_to_points(list<Point>& points) {
    for(Point p: points) {
        float res[3];

        for (int i = 0; i < 3; i++)
            res[i] = matrix[i][0] * p.get(0) + matrix[i][1] * p.get(1) + matrix[i][2] * p.get(2);

        for (int i = 0; i < 3; i++)
            p.set(i, res[i]);
    }
}
