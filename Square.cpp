//
// Created by geoff whitehead on 17/11/15.
//

#include "Square.h"


Square::Square(const Vector3D pos_v, const Vector3D dir_v, const float size)
        : Shape(pos_v, dir_v), size(size) {

}

Square::~Square() { }

void Square::accept(Visitor &v, Shape &s) {
    s.accept(v, *this);
}

void Square::accept(Visitor &v, Square &s) {
    v.visit(*this, s);
}

void Square::accept(Visitor &v, Circle &c) {
    v.visit(*this, c);
}

void Square::accept(Visitor & v){
    v.visit(*this);
}

void Square::write(std::ostream& os) const{
    os << "SQUARE: " <<"[Size: " << size <<"] [POS_Vec:" << this->pos_v <<"] [DIR_Vec: " << this->dir_v <<"]" <<"]";

}