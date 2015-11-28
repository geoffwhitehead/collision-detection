//
// Created by geoff whitehead on 20/10/15.
// A Vector3 class
//

#ifndef COLLISION_DETECTION_VECTOR3D_H
#define COLLISION_DETECTION_VECTOR3D_H

#include <ostream>
#include <stdlib.h>
#include <math.h>

class Vector3D {

public:

    // constructor and destructor
    Vector3D();

    Vector3D(const float x1, const float y1, const float z1);

    Vector3D(const Vector3D &rhs);

    ~Vector3D();

    // math operations with vectors
    Vector3D operator+(const Vector3D &rhs) const;

    Vector3D operator-(const Vector3D &rhs) const;

    // math operations with scalar value
    Vector3D operator*(const float scalar) const;

    Vector3D operator/(const float scalar) const;

    // compute the magnitude of a vector - returns the calculated magnitude
    float magnitude() const;

    // compute the product of 2 vectors
    float operator*(const Vector3D &rhs) const;

    // compute the vector product of 2 vectors (cross)
    Vector3D operator%(const Vector3D &rhs) const;

    // compute a unit vector pointing in the same direction as given vector (assumption: the "given" vector is the vector the function is being called on)
    Vector3D unitVector() const;

    // compute orthogonal vector
    Vector3D orthVector(const Vector3D &rhs) const;

    // compute a unit vector orthoganal to the given vector (assumption: the "given" vector is the vector the function is being called on)
    Vector3D orthUnitVector(const Vector3D &rhs) const;

    //compute the perpendicular 2d angle. Basically just flips the x coord.
    Vector3D flipX();

    //compute the perpendicular 2d angle. Basically just flips the y coord.
    Vector3D flipY();

    //getters
    float getX() const;

    float getY() const;

    float getZ() const;

    // function to overload output stream
    friend std::ostream &operator<<(std::ostream &os, const Vector3D &v);

    // overload the equality operator
    bool operator==(const Vector3D &rhs) const;

    // overload the inequality operator
    bool operator!=(const Vector3D &rhs) const;

    Vector3D operator+=(const Vector3D &rhs);

    Vector3D operator-=(const Vector3D &rhs);

    Vector3D operator*=(const float scalar);

    Vector3D operator/=(const float scalar);

    // this method increments each value in vector by 1
    Vector3D operator++();

    Vector3D operator++(int);

    // this method decrements each value in vector by 1
    Vector3D operator--();

    Vector3D operator--(int);

// coordinates
    float x;
    float y;
    float z;
private:


};


#endif //COLLISION_DETECTION_VECTOR3D_H
