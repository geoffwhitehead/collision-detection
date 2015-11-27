//
// Created by geoff whitehead on 17/11/15.
//

#ifndef A2_COLLISION_DETECTION_CIRCLE_H
#define A2_COLLISION_DETECTION_CIRCLE_H

#include "Square.h"

class Circle: public Shape {

public:

    Circle(const Vector3D pos_v, const Vector3D dir_v, const float rad);

    virtual~Circle();

    // friend std::ostream &operator<<(std::ostream &os, const Circle &c);

    virtual void accept(Visitor &v, Shape &s);

    virtual void accept(Visitor &v, Square &s);

    virtual void accept(Visitor &v, Circle &c);

    virtual void accept(Visitor &v);

    virtual void write(std::ostream &os) const;

    const float radius;

    virtual bool operator==(const Shape &rhs) const {
        return (this == &rhs);
    }
};

#endif //A2_COLLISION_DETECTION_CIRCLE_H
