
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

using namespace std;



const int AMT_SHAPES = 5;
const float BOARD_X = 20.0f;
const float BOARD_Y = 20.0f;
const bool SQUARE_FLAG = false;
const bool CIRCLE_FLAG = true;
const float V_MIN = -2.0f;
const float V_MAX = 2.0f;

int main() {

    Game game(AMT_SHAPES,BOARD_X,BOARD_Y,SQUARE_FLAG,CIRCLE_FLAG,V_MIN,V_MAX);
    /*
          CollisionVisitor v(BOARD_X, BOARD_Y);

          Vector3D v1;
          Vector3D v2;
          Circle c(v1, v1, 4);
          Square s(v2, v2, 2, 2);
       visit(v, c, s);
       visit(v, c);
   void visit(Visitor &v, Shape& s1, Shape& s2){
    s2.accept(v,s1);
}
void visit(Visitor &v, Shape& s1){
    s1.accept(v);
}
     */

}