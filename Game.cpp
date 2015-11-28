//
// Created by geoff_000 on 24/11/2015.
//

#include "Game.h"
#include "CollisionVisitor.h"
#include <algorithm>

Game::Game(int amt_s, float b_x, float b_y, bool s_flag, bool c_flag, float v_max, float v_min)
	: amt_shapes(amt_s), board_x(b_x), board_y(b_y), v_max(v_max),
	v_min(v_min), collision_vis(CollisionVisitor(b_x, b_y)) {

	// sets the game types which will determine what shapes are generated
	if (s_flag & c_flag) {
		game_type = BOTH;
	}
	else if (s_flag) {
		game_type = SQUARES;
	}
	else {
		game_type = CIRCLES;
	}
	srand(static_cast <unsigned> (time(0)));	// seed random number generator - needs to be done once per run
	createShapes();								// populate the vector with random shapes
	start();									// start the main game loop
}

Game::~Game() {
	shapes.clear();     // destroys the last shape object if there is one left
}

//************************************************//
//***   START                                  ***//
//************************************************//

void Game::start() {
	int counter = 0;
	while (shapes.size() > 1) {						// 1. MAIN GAME LOOP : keep drawing until only 1 or no shapes remain.
		counter++;
		std::cout << "ROUND: " << counter << std::endl;
		printShapes();
		for (auto &shape : shapes) {												//First move all the shapes 1 frame. During this process if the shape hits a boundary its directions vector is adjusted.
			Vector3D unit_v = shape->dir_v.unitVector();							// get the unit vector for the direction
			shape->pos_v = (shape->pos_v + unit_v);									// increment the position of the shape by 1 unit
			checkBoundsCollision(collision_vis, *shape);							// check that the shape hasn't fallen outside of the game bounds; reset to bounds and adjust direction if yes
		}
		printShapes();
		for (auto &shape_l : shapes) {				// 2. after moving all shapes 1 frame... check for collisions
			for (auto &shape_r : shapes) {
				if (shape_l != shape_r && !(shape_r->collision_flag)) {				// dont compare against itself AND dont compare with a shape that has already been collided with this round
					checkShapeCollision(collision_vis, *shape_l, *shape_r);			// check for collisions. if yes delete flag will be set for (shape_r), shape_l flag will be set on shape_r iteration
				}
			}
		}
		removeCollisions();							// 3. remove all the shapes with their delete flags set
	}
}

/*remove_if will find all the shapes where the predicate is true. (collision flag = true). Move these to the back of
		the vector so an expensive sort wont be done. Then erase will remove these shapes and resize the vector.*/
void Game::removeCollisions() {
	shapes.erase(
		std::remove_if(
			shapes.begin(),
			shapes.end(),
			[](Shape *s) { return s->collision_flag; }
			),
		shapes.end()
		);
}

// debug: print all the shapes
void Game::printShapes() {							
	int i = 0;
	for (auto &shape : shapes) {
		std::cout << i << " -: " << *shape << std::endl;
		i++;
	}
	std::cout << std::endl << std::endl << std::endl;
}

//retuns a random float
float Game::getRandFloat(float low, float high) {
	while (true) {
		float f = (low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low))));
		if (f !=
			0) { // won't return in the rare occurrence of 0 float generated - could easily remove this to make game more efficient
			return f;
		}
	}
}

// populates the shapes vector with random shapes based on game preferences
void Game::createShapes() {

	for (int i = 0; i < amt_shapes; i++) {
		Shape *s;
		switch (game_type) {
		case SQUARES: {
			s = new Square(createVector(POS), createVector(DIR), 2.0f);
		}break;
		case CIRCLES: {
			s = new Circle(createVector(POS), createVector(DIR), 1.0f);
		} break;
		case BOTH: {
			if ((rand() % 2) == 0) {
				s = new Square(createVector(POS), createVector(DIR), 2.0f);
			}
			else {
				s = new Circle(createVector(POS), createVector(DIR), 1.0f);
			}
		} break;
		}
		shapes.push_back(s);
	}
}

// returns a random vector for either a position or a directions
Vector3D Game::createVector(int type) {
	if (type == POS) {
		return Vector3D(getRandFloat(0.1f, board_x), getRandFloat(0.1f, board_y), V_Z);
	}
	else if (type == DIR) {
		return Vector3D(getRandFloat(v_min, v_max), getRandFloat(v_min, v_max), V_Z);
	}
}

// uses the collision visitor class to determine shape types and check shape collisions
void Game::checkShapeCollision(CollisionVisitor &v, Shape &s1, Shape &s2) {
	return s2.accept(v, s1);
}
// uses the collision visitor class to determine shape types and check boundary collisions
void Game::checkBoundsCollision(CollisionVisitor &v, Shape &s1) {
	s1.accept(v);
}


