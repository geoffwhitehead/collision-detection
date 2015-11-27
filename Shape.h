//
// Created by geoff whitehead on 17/11/15.
//

#ifndef COLLISION_DETECTION_SHAPE_H
#define COLLISION_DETECTION_SHAPE_H

#include "Visitor.h"
#include "Vector3D.h"

class Shape {
public:
    //bouncing functions
    // NOTE: when creating any new shapes they must be included here:
    virtual void accept(Visitor& v, Shape& s) = 0;
    virtual void accept(Visitor& v, Square& s) = 0;
    virtual void accept(Visitor& v, Circle& c) = 0;
    virtual void accept(Visitor& v) = 0;

    virtual bool operator==(const Shape &rhs) const = 0;
    virtual ~Shape() {};
    virtual void write(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Shape& s);
    Vector3D dir_v;
    Vector3D pos_v;
    bool collision_flag = false;

protected:
    Shape(Vector3D pos_v, Vector3D dir_v);
};




#endif //COLLISION_DETECTION_SHAPE_H
