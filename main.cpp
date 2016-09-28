
#include "Game.h"
#include "CollisionVisitor.h"

//************************************************//
//***   REFERENCES                             ***//
//************************************************//

//https://sourcemaking.com/design_patterns/visitor/cpp/2
//https://en.wikipedia.org/wiki/Double_dispatch
//https://en.wikipedia.org/wiki/Visitor_pattern
//http://stackoverflow.com/questions/11365741/visitor-pattern-in-c-with-multiple-visitable-parameters
//http://stackoverflow.com/questions/19376943/overload-operator-in-subclass
//http://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position

//************************************************//
//***   MAIN                                   ***//
//************************************************//

const int AMT_SHAPES = 30;			// How many shapes to produce
const float BOARD_X = 100.0f;		// Size of the board in the X
const float BOARD_Y = 100.0f;		// Size of the board in the Y
const bool SQUARE_FLAG = true;		// generate squares?
const bool CIRCLE_FLAG = true;		// generate circles?
const float V_MIN = -2.0f;			// greatest velocity in the - axis
const float V_MAX = 2.0f;			// greatest velocity in the + axis

int main() {
    Game game(AMT_SHAPES,BOARD_X,BOARD_Y,SQUARE_FLAG,CIRCLE_FLAG,V_MIN,V_MAX);
}