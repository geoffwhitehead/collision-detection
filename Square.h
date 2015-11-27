//
// Created by geoff whitehead on 17/11/15.
//

#ifndef A2_COLLISION_DETECTION_SQUARE_H
#define A2_COLLISION_DETECTION_SQUARE_H


#include "Shape.h"

class Square: public Shape{

public:
    Square(const Vector3D pos_v, const Vector3D dir_v, const float size);

    virtual ~Square();

    virtual void accept(Visitor &v, Shape& s);
    virtual void accept(Visitor &v, Square& s);
    virtual void accept(Visitor &v, Circle& c);
    virtual void accept(Visitor & v);
    virtual void write(std::ostream& os) const;
    const float size;
    virtual bool operator==(const Shape &rhs) const {
        return (this == &rhs);
    }
};





#endif //A2_COLLISION_DETECTION_SQUARE_H
