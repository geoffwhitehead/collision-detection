//
// Created by geoff whitehead on 17/11/2015.
//

#ifndef COLLISION_DETECTION_VISITOR_H
#define COLLISION_DETECTION_VISITOR_H

#include <iostream>

// NOTE: BE CAREFUL WITH INCLUDES TO AVOID CIRCULAR REFERENCES.
class Square;       // forward declarations used instead of #include to avoid circular references.
class Circle;

/*
 * Derive classes from this class that have a function: In this game collisions are the only interactions so i have created a collisionVisitor derived class.
 * Other derived classes could be attack, or combine etc etc
 *
 * Pure abstract base class used to define possible combinations of shape interactions. If a new shape is created add its possible interactions here
 */

class Visitor {

public:
    virtual void visit(Square &s1, Square &s2) = 0;  // Square interacts with a square
    virtual void visit(Square &s1, Circle &c2) = 0;  // Square interacts with a circle
    virtual void visit(Circle &c1, Square &s2) = 0;  // Circle interacts with a square
    virtual void visit(Circle &c1, Circle &c2) = 0;  // Circle interacts with a circle
    virtual void visit(Circle &c) = 0;
    virtual void visit(Square &s) = 0;
};


#endif //COLLISION_DETECTION_VISITOR_H
