//
// Created by geoff whitehead on 17/11/2015.
//
#include "CollisionVisitor.h"

void CollisionVisitor::visit(Square &s1, Square &s2) {
   // std::cout << "square square derived" << std::endl;
};

void CollisionVisitor::visit(Square &s1, Circle &c2) {
   // std::cout << "square circle derived" << std::endl;
};

void CollisionVisitor::visit(Circle &c1, Square &s2) {

};
/*
 * this function will check for a collision between 2 circles; if true, set the collision flag to true
 */
void CollisionVisitor::visit(Circle &c1, Circle &c2) {

   float sum_c1 = powf(c2.pos_v.x - c1.pos_v.x, 2.0f);
    float sum_c2 = powf(c1.pos_v.y - c2.pos_v.y, 2.0f);
    float sum_rad = powf(c1.radius + c2.radius, 2.0f);
	std::cout << "sum is: " << sum_c1 + sum_c2 << std::endl;
	if ((sum_c1 + sum_c2) <= sum_rad) {

		c2.collision_flag = true;
		std::cout << "circle circle COLLISION" << std::endl;
		std::cout << "collision flag" << c2.collision_flag << std::endl;
		
	}
};
/*
 * this function will check over the four cases and looks for the position vector falling outside
 * of the bounds of the board. If the vector does - it will reset the vector to the closest bound and
 * flip the corresponding X or Y value of the direction vetor. This will give a perpendicular direction.
 */

void CollisionVisitor::visit(Circle &c) {

    int heading = findHeading(c.dir_v);                                     // find the shape the vector is heading in
    float offset = c.radius;
    if (heading == UP_R) { // 1

        if (c.pos_v.x > (bounds_x - c.radius)) {
            collisionXPlus(c, offset);
        }
        if (c.pos_v.y > (bounds_y - c.radius)) {
            collisionYPlus(c, offset);
        }

    } else if (heading == DOWN_R) { // 2
        if (c.pos_v.x >(bounds_x - c.radius)) {
            collisionXPlus(c, offset);
        }
        if (c.pos_v.y < (0.0f + c.radius)) {
            collisionYMinus(c, offset);
        }
    } else if (heading == UP_L) { // 3

        if (c.pos_v.x < (0.0f + c.radius)) {
            collisionXMinus(c, offset);
        }
        if (c.pos_v.y > (bounds_y - c.radius)) {
            collisionYPlus(c, offset);
        }

    } else if (heading == DOWN_L) { // 4

        if (c.pos_v.x < (0.0 + c.radius)) {
            collisionXMinus(c, offset);
        }
        if (c.pos_v.y < (0.0f + c.radius)) {
            collisionYMinus(c, offset);
        }
    }
};

/*
 * check whether a square has collided with the edges of the screen. The pos_v of a shape relates to the bottom-left corner of the shape.
 * The offset is how far we want to place the square from the border (ie . the size).
 * So when comparing the pos on a NEGATIVE axis the offset will be 0. But when comparing the size of the square in the
 * POSITIVE axis. We need to factor in the size of the square.
 */

void CollisionVisitor::visit(Square &s) {

    // defined the offsets to make the code a little more readable.
    float pos_offset = s.size;
    float neg_offset = 0.01f;

    int heading = findHeading(s.dir_v);                   // find the shape the vector is heading in

    if (heading == UP_R) {                              // 1

        if (s.pos_v.x >(bounds_x - s.size)) {
            collisionXPlus(s, pos_offset);
        }
        if (s.pos_v.y >(bounds_y - s.size)) {
            collisionYPlus(s, pos_offset);
        }
    } else if (heading == DOWN_R) {                     // 2
        if (s.pos_v.x >(bounds_x - s.size)) {
            collisionXPlus(s, pos_offset);
        }
        if (s.pos_v.y < (0.0f)) {
            collisionYMinus(s, neg_offset);
        }
    } else if (heading == UP_L) {                       // 3
        if (s.pos_v.x < (0.0f)) {
            collisionXMinus(s, neg_offset);
        }
        if (s.pos_v.y > (bounds_y - s.size)) {
            collisionYPlus(s, pos_offset);
        }
    } else if (heading == DOWN_L) {                     // 4

        if (s.pos_v.x < (0.0)) {
            collisionXMinus(s, neg_offset);
        }
        if (s.pos_v.y < (0.0f)) {
            collisionYMinus(s, neg_offset);
        }
    }
};


void CollisionVisitor::collisionXPlus(Shape& s, float offset){
    std::cout << "COLLIDED WITH +X" << std::endl;
    s.pos_v = Vector3D(bounds_x - offset, s.pos_v.y, s.pos_v.z);
    s.dir_v = s.dir_v.flipX();
}
void CollisionVisitor::collisionXMinus(Shape& s, float offset){
    std::cout << "COLLIDED WITH -X"<< std::endl;
    s.pos_v = Vector3D(0.0f + offset, s.pos_v.y, s.pos_v.z);
    s.dir_v = s.dir_v.flipX();
}
void CollisionVisitor::collisionYPlus(Shape& s, float offset){
    std::cout << "COLLIDED WITH +Y"<< std::endl;
    s.pos_v = Vector3D(s.pos_v.x, bounds_y - offset, s.pos_v.z);
    s.dir_v = s.dir_v.flipY();
}
void CollisionVisitor::collisionYMinus(Shape& s, float offset){
    std::cout << "COLLIDED WITH -Y"<< std::endl;
    s.pos_v = Vector3D(s.pos_v.x, 0.0f + offset, s.pos_v.z);
    s.dir_v = s.dir_v.flipY();
}

/*
 * short function to find the current heading of the direction vector. Makes the code a little easier to read.
 * Could merge with the visit method to make slightly more effecient.
 */

int CollisionVisitor::findHeading(Vector3D v) {
    if (v.x > 0) {
        if (v.y > 0) {                           // if X+ Y+
            return UP_R;
        } else {
            return DOWN_R;                        // if X+ Y-
        }
    } else if (v.y > 0) {                        // if X- Y+
        return UP_L;
    } else {                                    // if X- Y-
        return DOWN_L;
    }
}