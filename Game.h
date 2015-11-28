//
// Created by geoff_000 on 24/11/2015.
//

#ifndef COLLISION_DETECTION_GAME_H
#define COLLISION_DETECTION_GAME_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Shape.h"
#include "Vector3D.h"
#include "Square.h"
#include "Circle.h"
#include "CollisionVisitor.h"

//************************************************//
//***   GAME CONST VARS                        ***//
//************************************************//
#define V_Z 0.0f                                        // Z value of vector is not used in this 2D board game so always set to 0.
#define POS 0                                           // defines a position vector when creating vectors
#define DIR 1

class Game {

public:
    Game (int amt_s, float b_x, float b_y, bool s_flag, bool c_flag, float v_max, float v_min);
    ~Game();
    void start();

private:
    CollisionVisitor collision_vis;                           // stores all the shape and bounds collision algorithms
    enum game_types{SQUARES, CIRCLES, BOTH};            // possible game types
    game_types game_type;                               // the type of game
    const float board_x;                                // size of board
    const float board_y;                                // size of board
    const int amt_shapes;                               // set flag to determine whether game includes circles
    const float v_max;                                  // maximum size of vector
    const float v_min;                                  // minimum size of vector
    std::vector <Shape*> shapes;                        // vector to hold all of the shapes
    std::vector <int> collisions;                       // a list of indexes where collisions occured for a single move
    Vector3D createVector(int);                         // returns a random vector sized between v_max & v_min
    float static getRandFloat(float low, float high);   // returns a rand float between low & high
    void createShapes();                                // function to populate vector array with shapes
    void checkShapeCollision(CollisionVisitor &v, Shape &s1, Shape &s2);       // used to call collision function on 2 shapes
    void checkBoundsCollision(CollisionVisitor &v, Shape &s1);
	void removeCollisions();
	void printShapes();
};


#endif //COLLISION_DETECTION_GAME_H
