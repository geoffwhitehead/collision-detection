//
// Created by geoff whitehead on 20/10/15.
//


#include "Vector3D.h"

// constructor and destructor - NOTE: const variables are initialised before constructor call for a slight performance
// increase. This is due to only 1 assignment occuring. If variables initialised inside constructor they would be
// defaulted to NULL before actual assignment .

Vector3D::Vector3D() : x(0.0f), y(0.0f), z(0.0f) { }

Vector3D::Vector3D(const float x1, const float y1, const float z1) : x(x1), y(y1), z(z1) { }

// copy constructor, variables created with values from the rhs Vector.
Vector3D::Vector3D(const Vector3D &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) { }

Vector3D::~Vector3D() { };

// math operations with vectors
Vector3D Vector3D::operator+(const Vector3D &rhs) const {

    return Vector3D(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3D Vector3D::operator-(const Vector3D &rhs) const {

    return Vector3D(x - rhs.x, y - rhs.y, z - rhs.z);
}

// math operations with scalar value
Vector3D Vector3D::operator*(const float scalar) const {

    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::operator/(const float scalar) const {

    // I've decided it would be down to the user to check for division by zero or just not send in 0's as constantly checking here wouldn't be efficient and too slow.

    return Vector3D(x / scalar, y / scalar, z / scalar);
}

// compute the magnitude of a vector - returns the calculated magnitude
float Vector3D::magnitude() const {

    //TODO :: find more effecient way to calculate than using sqrt?
    return sqrtf(fabsf((x * x) + (y * y) + (z * z))); // NOTE: not using the getters here to improve performance.

}

// compute the product of 2 vectors
float Vector3D::operator*(const Vector3D &rhs) const {

    return ((x * rhs.x) + (y * rhs.y) + (z * rhs.z));

}

// compute the vector product of 2 vectors (aka the cross product)
Vector3D Vector3D::operator%(const Vector3D &rhs) const {

    float newX = ((y * rhs.z) - (z * rhs.y));
    float newY = ((z * rhs.x) - (x * rhs.z));
    float newZ = ((x * rhs.y) - (y * rhs.x));

    // create and return the new vector
    return Vector3D(newX, newY, newZ);

}

// compute a unit vector pointing in the same direction as given vector
Vector3D Vector3D::unitVector() const {
    // I've decided it would be down to the user to check for division by zero or just not send in 0's as constantly checking here wouldn't be efficient and too slow.
    float m = magnitude();
    return Vector3D(x / m, y / m, z / m);
}

Vector3D Vector3D::flipX() {
    return Vector3D(-x, y, z);
}
Vector3D Vector3D::flipY() {
    return Vector3D(x, -y, z);
}
Vector3D Vector3D::orthVector(const Vector3D &rhs) const {
    Vector3D v = (*this) % rhs;
    return v;
}

// compute a unit vector orthoganal to the given vector
Vector3D Vector3D::orthUnitVector(const Vector3D &rhs) const {
    Vector3D v = (*this) % rhs;
    return v.unitVector();
}

// overloaded equality operator
bool Vector3D::operator==(const Vector3D &rhs) const {

    return (x == rhs.x
            && y == rhs.y
            && z == rhs.z);
}

// overloaded equality operator
bool Vector3D::operator!=(const Vector3D &rhs) const {

    return (x != rhs.x
            || y != rhs.y
            || z != rhs.z);
}

//perhaps a slight improvement in speed could be gained by introducing some code duplication instead of making a function call to the + - * / methods?
Vector3D Vector3D::operator+=(const Vector3D &rhs) {
    *this = *this + rhs;
    return *this;
}

Vector3D Vector3D::operator-=(const Vector3D &rhs) {
    *this = *this - rhs;
    return *this;
}

Vector3D Vector3D::operator*=(const float scalar) {
    *this = *this * scalar;
    return *this;
}

Vector3D Vector3D::operator/=(const float scalar) {
   // I've decided it would be down to the user to check for division by zero or just not send in 0's as constantly checking here wouldn't be efficient and too slow.
    *this = *this / scalar;
    return *this;
}


Vector3D Vector3D::operator++() {
    x++;
    y++;
    z++;
    return *this;
}

Vector3D Vector3D::operator--() {
    x--;
    y--;
    z--;
    return *this;
}
Vector3D Vector3D::operator++(int) {

    //incremenents this q -  returns the old quaternion allowing function to continue with old vals.
    Vector3D temp = *this;
    ++*this;
    return temp;
}

Vector3D Vector3D::operator--(int) {

    //incremenents this q -  returns the old quaternion allowing function to continue with old vals.
    Vector3D temp = *this;
    --*this;
    return temp;
}

// *** getters ***
float Vector3D::getX() const { return x; }

float Vector3D::getY() const { return y; }

float Vector3D::getZ() const { return z; }


// overloading the << operator to enable printing of a vector
std::ostream &operator<<(std::ostream &os, const Vector3D &v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}