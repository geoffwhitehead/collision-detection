//
// Created by geoff_000 on 24/11/2015.
//

#include "Game.h"
#include "CollisionVisitor.h"
#include <algorithm>

Game::Game(int amt_s, float b_x, float b_y, bool s_flag, bool c_flag, float v_max, float v_min)
	: amt_shapes(amt_s), board_x(b_x), board_y(b_y), v_max(v_max),
	v_min(v_min), collision_vis(CollisionVisitor(b_x, b_y)) {

	if (s_flag & c_flag) {
		game_type = BOTH;
	}
	else if (s_flag) {
		game_type = SQUARES;
	}
	else {
		game_type = CIRCLES;
	}
	srand(static_cast <unsigned> (time(0))); // seed random number generator - needs to be done once per run

	createShapes();

	start();

}

Game::~Game() {
	shapes.clear();     // destroys the last shape object if there is one left
}

void Game::checkShapeCollision(CollisionVisitor &v, Shape &s1, Shape &s2) {
	return s2.accept(v, s1);
}

void Game::checkBoundsCollision(CollisionVisitor &v, Shape &s1) {
	s1.accept(v);
}

//************************************************//
//***   START                                  ***//
//************************************************//

void Game::start() {

	// debug: print all the shapes
	int i = 0;
	for (auto &shape : shapes) {

		std::cout << i << " -START: " << *shape << std::endl;
		i++;

	}
	std::cout << std::endl << std::endl << std::endl;

	// need to check for collisions straight away after spawning and call the delete function.


	for (int i = 0; i < 3; i++) { // keep drawing until only 1 or no shapes remain.


		// need to move all the shapes first
		int j = 0;
		for (auto &shape : shapes) {
			std::cout << j << " -- " << *shape << std::endl << std::endl << std::endl;
			move(*shape);
		}
		// then here is need to check for collisions
		for (auto &shape_l : shapes) {
			for (auto &shape_r : shapes) {
				if (shape_l != shape_r) {
					checkShapeCollision(collision_vis, *shape_l, *shape_r);
				}
			}
		}


		/*
		 *	remove_if will find all the shapes where the predicate is true. (collision flag = true). Move these to the back of
		 *	the vector so an expensive sort wont be done. Then erase will remove these shapes and resize the vector.
		 */

		shapes.erase(
			std::remove_if(
				shapes.begin(),
				shapes.end(),
				[](Shape *s) // lambda to get all shapes marked to delete
		{ return s->collision_flag; }
				),
			shapes.end()
			);
	}
}


/*
 * covers a whole turn for a shape from making the initial move, to checking collisions with boundaries
 * and shapes, to deleting all the Shapes it collided with.
 */
void Game::move(Shape &s) {

	// move the shape
	Vector3D unit_v = s.dir_v.unitVector();                      // get the unit vector for the direction
	std::cout << "unit vector: " << unit_v << std::endl;
	s.pos_v = (s.pos_v + unit_v);                               // increment the position of the shape by 1 unit
	std::cout << "new pos: " << s.pos_v << std::endl;
	checkBoundsCollision(collision_vis, s);                       // check that the shape hasn't fallen outside of the game bounds; reset to bounds and adjust direction if yes

}

float Game::getRandFloat(float low, float high) {
	while (true) {
		float f = (low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low))));
		if (f !=
			0) { // won't return in the rare occurrence of 0 float generated - could easily remove this to make game more efficient
			return f;
		}
	}
}

void Game::createShapes() {

	for (int i = 0; i < amt_shapes; i++) {
		Shape *s;
		switch (game_type) {
		case SQUARES: {
			s = new Square(createVector(POS), createVector(DIR), 2.0f);
		}
					  break;
		case CIRCLES: {
			s = new Circle(createVector(POS), createVector(DIR), 2.0f);
		}
					  break;
		case BOTH: {
			if ((rand() % 2) == 0) {
				s = new Square(createVector(POS), createVector(DIR), 2.0f);
			}
			else {
				s = new Circle(createVector(POS), createVector(DIR), 2.0f);
			}
		}
				   break;
		}
		shapes.push_back(s);
	}
}

Vector3D Game::createVector(int type) {
	if (type == POS) {
		return Vector3D(getRandFloat(0.1f, board_x), getRandFloat(0.1f, board_y), V_Z);
	}
	else if (type == DIR) {
		return Vector3D(getRandFloat(v_min, v_max), getRandFloat(v_min, v_max), V_Z);
	}
}



