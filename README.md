# Collision detection using Double Dispatch and Visitor Design Pattern

A console application with no GUI. Simulates a rectangular arena with circles and squares that bounce around within the boundaries at varying velocities. Collisions are detected and resolved using the visitor design pattern. Shapes are removed from the arena after a collision and the game continues until no shapes are left.

## Getting Started

Clone and build with visual studio.

All output is to the console.

## Instructions

Open main.cpp to configure the variables such as:
```
const int AMT_SHAPES		// How many shapes to generate
const float BOARD_X			// Size of the board in the X
const float BOARD_Y 		// Size of the board in the Y
const bool SQUARE_FLAG		// generate squares?
const bool CIRCLE_FLAG 		// generate circles?
const float V_MIN 			// greatest velocity in the - axis
const float V_MAX 			// greatest velocity in the + axis
```


Press ESC to exit the console once output is complete...

## Authors

* **Geoff Whitehead - (https://github.com/geoffwhitehead)

## License

This project is licensed under the MIT License - see the [LICENSE.md](./LICENSE.md) file for details
