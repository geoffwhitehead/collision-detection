//
// Created by geoff whitehead on 17/11/15.
//

#include "Shape.h"
Shape::Shape(Vector3D pos_v, Vector3D dir_v) : pos_v(pos_v), dir_v(dir_v) {}

std::ostream &operator<<(std::ostream &os, const Shape &s) {
    s.write(os);
    return os;
}