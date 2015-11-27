//
// Created by geoff whitehead on 17/11/2015.
//

#ifndef COLLISION_DETECTION_COLLISIONVISITOR_H
#define COLLISION_DETECTION_COLLISIONVISITOR_H


#include <iostream>
#include "Circle.h"
#include "Square.h"
#include "Visitor.h"

#define UP_R 1
#define DOWN_R 2
#define UP_L 3
#define DOWN_L 4




/*
 * Add new class methods here and new behaviors will be applied to the
 * object at runtime through polymorphism.
 */

class CollisionVisitor : public Visitor {

public:

    CollisionVisitor(float b_x, float b_y) : bounds_x(b_x), bounds_y(b_y){}

    // NOTE: when creating any new shapes they must be included here:
    virtual void visit(Square &s1, Square &s2);
    virtual void visit(Square &s1, Circle &c2);
    virtual void visit(Circle &c1, Square &s2);
    virtual void visit(Circle &c1, Circle &c2);

    virtual void visit(Circle &c);
    virtual void visit(Square &s);

    int findHeading(Vector3D v);

    void collisionXPlus(Shape& s, float offset);
    void collisionXMinus(Shape& s, float offset);
    void collisionYPlus(Shape& s, float offset);
    void collisionYMinus(Shape& s, float offset);


private:
    const float bounds_x;
    const float bounds_y;
};


#endif //COLLISION_DETECTION_COLLISIONVISITOR_H
