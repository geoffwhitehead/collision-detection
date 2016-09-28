//
// Created by geoff whitehead on 17/11/2015.
//
#include "CollisionVisitor.h"

// USES THE CARTESIAN COORDINATE SYSTEM

// use bounding box algorithm to check whether edges intersect 
void CollisionVisitor::visit(Square &s1, Square &s2) {
	if (!(s2.pos_v.x > (s1.pos_v.x + s1.size)			// s2.left > s1.right
		|| (s2.pos_v.x + s2.size) < s1.pos_v.x			// s2.right < s1.left
		|| (s2.pos_v.y + s2.size) < s1.pos_v.y			// s2.top < s1.bottom
		|| s2.pos_v.y > (s1.pos_v.y + s1.size)))		// s2.bottom > s1.top
	{
		s2.collision_flag = true;		// set the collision flag for the rhs shape 
		collision_flag = true;			// set the flag for the collision visitor so that the Game knows to use the delete method this round
		std::cout << "\t Collision: Sqyare - Square" << std::endl;
	}

};

void CollisionVisitor::visit(Square &s1, Circle &c2) {
	if (overlapTest(s1, c2)) {								// if shapes are overlapping continue to further check

		if (												// now test to see whether points of square lie inside circle
			pointInCircle(s1.pos_v.x, s1.pos_v.y, c2)								// check square bottom-left
			|| pointInCircle((s1.pos_v.x + s1.size), s1.pos_v.y, c2)				// check square bottom-right
			|| pointInCircle(s1.pos_v.x, (s1.pos_v.y + s1.size), c2)				// check square top-left
			|| pointInCircle((s1.pos_v.x + s1.size), (s1.pos_v.y + s1.size), c2)	// check square top-right
			) {
			c2.collision_flag = true;						// a point from the square lies inside the circle
			collision_flag = true;
			std::cout << "\t Collision: Square - Circle" << std::endl;
		}
		else if (circleInSquare(c2.pos_v.x, c2.pos_v.y, s1)) {					// then check to see if centre of circle lies completely inside the square
			c2.collision_flag = true;
			collision_flag = true;
			std::cout << "\t Collision: Circle - Circle" << std::endl;
		}
	}
	// leave function
};

void CollisionVisitor::visit(Circle &c1, Square &s2) {
	if (overlapTest(s2, c1)) {								// if shapes are overlapping continue to further check

		if (												// now test to see whether points of square lie inside circle
			pointInCircle(s2.pos_v.x, s2.pos_v.y, c1)								// check square bottom-left
			|| pointInCircle((s2.pos_v.x + s2.size), s2.pos_v.y, c1)				// check square bottom-right
			|| pointInCircle(s2.pos_v.x, (s2.pos_v.y + s2.size), c1)				// check square top-left
			|| pointInCircle((s2.pos_v.x + s2.size), (s2.pos_v.y + s2.size), c1)	// check square top-right
			) {
			s2.collision_flag = true;						// a point from the square lies inside the circle
			collision_flag = true;
			std::cout << "\t Collision: Circle - Square" << std::endl;
		}
		else if (circleInSquare(c1.pos_v.x, c1.pos_v.y, s2)) {					// then check to see if centre of circle lies completely inside the square
			s2.collision_flag = true;
			collision_flag = true;
			std::cout << "\t Collision: Circle - Circle" << std::endl;
		}
	}
	// leave function
};

// algorithm to work out that the circle origin is inside square
bool CollisionVisitor::circleInSquare(float x, float y, Square &s) {

	if (
		(s.pos_v.x < x)
		&& ((s.pos_v.x + s.size) > x)
		&& ((s.pos_v.y) < y)
		&& ((s.pos_v.y + s.size) > y)
		) {
		return true;
	}
	return false;
}

bool CollisionVisitor::pointInCircle(float x, float y, Circle &c) {
	float sum_x = powf(x - c.pos_v.x, 2.0f);
	float sum_y = powf(y - c.pos_v.y, 2.0f);
	float sum_r = powf(c.radius, 2.0f);

	return ((sum_x + sum_y) < sum_r) ? true : false;
}

// quicker test to check whether shapes are "close" to each other
bool CollisionVisitor::overlapTest(Square &s1, Circle &c2) {
	if (!
		((c2.pos_v.x - c2.radius) > (s1.pos_v.x + s1.size)			// c2.left > s1.right
			|| (c2.pos_v.x + c2.radius) < s1.pos_v.x				// c2.right < s1.left
			|| (c2.pos_v.y + c2.radius) < s1.pos_v.y				// c2.top < s1.bottom
			|| (c2.pos_v.y - c2.radius) > (s1.pos_v.y + s1.size)))	// c2.bottom > s1.top
	{
		std::cout << "\t Debug: Overlap" << std::endl;
		return true;
	}
}

/*
 * this function will check for a collision between 2 circles; if true, set the collision flag to true
 */
void CollisionVisitor::visit(Circle &c1, Circle &c2) {

	float sum_c1 = powf(c2.pos_v.x - c1.pos_v.x, 2.0f);
	float sum_c2 = powf(c1.pos_v.y - c2.pos_v.y, 2.0f);
	float sum_rad = powf(c1.radius + c2.radius, 2.0f);

	if ((sum_c1 + sum_c2) <= sum_rad) {
		c2.collision_flag = true;
		collision_flag = true;
		std::cout << "\t Collision: Circle - Circle" << std::endl;
	}
};
/*
 * this function will check over the four cases and looks for the position vector falling outside
 * of the bounds of the board. If the vector does - it will reset the vector to the closest bound and
 * flip the corresponding X or Y value of the direction vetor. ie. bounces off the edge
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
	}
	else if (heading == DOWN_R) { // 2
		if (c.pos_v.x > (bounds_x - c.radius)) {
			collisionXPlus(c, offset);
		}
		if (c.pos_v.y < (0.0f + c.radius)) {
			collisionYMinus(c, offset);
		}
	}
	else if (heading == UP_L) { // 3
		if (c.pos_v.x < (0.0f + c.radius)) {
			collisionXMinus(c, offset);
		}
		if (c.pos_v.y > (bounds_y - c.radius)) {
			collisionYPlus(c, offset);
		}
	}
	else if (heading == DOWN_L) { // 4
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

		if (s.pos_v.x > (bounds_x - s.size)) {
			collisionXPlus(s, pos_offset);
		}
		if (s.pos_v.y > (bounds_y - s.size)) {
			collisionYPlus(s, pos_offset);
		}
	}
	else if (heading == DOWN_R) {                     // 2
		if (s.pos_v.x > (bounds_x - s.size)) {
			collisionXPlus(s, pos_offset);
		}
		if (s.pos_v.y < (0.0f)) {
			collisionYMinus(s, neg_offset);
		}
	}
	else if (heading == UP_L) {                       // 3
		if (s.pos_v.x < (0.0f)) {
			collisionXMinus(s, neg_offset);
		}
		if (s.pos_v.y > (bounds_y - s.size)) {
			collisionYPlus(s, pos_offset);
		}
	}
	else if (heading == DOWN_L) {                     // 4

		if (s.pos_v.x < (0.0)) {
			collisionXMinus(s, neg_offset);
		}
		if (s.pos_v.y < (0.0f)) {
			collisionYMinus(s, neg_offset);
		}
	}
};

/* CARTESIAN COORDS SYSTEM: flip the corresponding axis depending on which side of the boundary shape collided with*/

void CollisionVisitor::collisionXPlus(Shape& s, float offset) { // COLLIDED WITH +X
	s.pos_v = Vector3D(bounds_x - offset, s.pos_v.y, s.pos_v.z);
	s.dir_v = s.dir_v.flipX();
}
void CollisionVisitor::collisionXMinus(Shape& s, float offset) { // COLLIDED WITH -X
	s.pos_v = Vector3D(0.0f + offset, s.pos_v.y, s.pos_v.z);
	s.dir_v = s.dir_v.flipX();
}
void CollisionVisitor::collisionYPlus(Shape& s, float offset) { // COLLIDED WITH +Y
	s.pos_v = Vector3D(s.pos_v.x, bounds_y - offset, s.pos_v.z);
	s.dir_v = s.dir_v.flipY();
}
void CollisionVisitor::collisionYMinus(Shape& s, float offset) { // COLLIDED WITH -Y
	s.pos_v = Vector3D(s.pos_v.x, 0.0f + offset, s.pos_v.z);
	s.dir_v = s.dir_v.flipY();
}

/*short function to find the current heading of the direction vector. Makes the code a little easier to read.
  Could merge with the visit method to make slightly more effecient.*/

int CollisionVisitor::findHeading(const Vector3D v) {
	if (v.x > 0) {
		if (v.y > 0) return UP_R;                  // if X+ Y+
		else return DOWN_R;                        // else X+ Y-
	}
	else if (v.y > 0) return UP_L;                        // if X- Y+
	else return DOWN_L;                                    // if X- Y-
}