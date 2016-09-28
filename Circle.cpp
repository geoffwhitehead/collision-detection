//
// Created by geoff whitehead on 17/11/15.
//


#include "Circle.h"

Circle::Circle(const Vector3D pos_v, const Vector3D dir_v, const float rad) : Shape(pos_v, dir_v), radius(rad) {
}

Circle::~Circle() {}

void Circle::accept(Visitor &v, Shape& s)
{
    return s.accept(v, *this);
}
void  Circle::accept(Visitor &v, Square& s)
{
    return v.visit(*this, s);
}
void  Circle::accept(Visitor &v, Circle& c)
{
    return v.visit(*this, c);
}
void Circle::accept(Visitor & v){
    v.visit(*this);
}
void Circle::write(std::ostream& os) const{
    os << "CIRCLE: " <<"[Radius: " << radius <<"] [POS_Vec:" << this->pos_v <<"] [DIR_Vec: " << this->dir_v <<"] ";
}