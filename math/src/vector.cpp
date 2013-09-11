#include "math/itf/vector.h"

#include <cmath>
#include <boost/assert.hpp>

using namespace lb::math;

Vector::Vector(float ax, float ay, float az):
    x(ax),
    y(ay),
    z(az)
{
}

Vector Vector::operator+(Vector const &v) const
{
    return Vector(x + v.x, y + v.y, z + v.z);
}

Vector &Vector::operator+=(Vector const &v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vector Vector::operator*(float f) const
{
    return Vector(x * f, y * f, z * f);
}

Vector &Vector::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

Vector Vector::operator/(float f) const
{
    BOOST_ASSERT(f != 0);
    float inv = 1.f / f;
    return Vector(x * inv, y * inv, z * inv);
}

Vector &Vector::operator/=(float f)
{
    BOOST_ASSERT(f != 0);
    float inv = 1.f / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

Vector Vector::operator-() const
{
    return Vector(-x, -y, -z);
}

float Vector::length() const
{
    return std::sqrt(lengthSquared());
}

float Vector::lengthSquared() const
{
    return x * x + y * y + z * z;
}

Vector Vector::normalize() const
{
    return *this / length();
}

Vector operator*(float f, Vector const &v)
{
    return v * f;
}

Vector cross(Vector const &v, Vector const &w)
{
    return Vector(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x);
}

float absDot(Vector const &v, Vector const &w)
{
    return std::fabs(dot(v, w));
}

float dot(Vector const &v, Vector const &w)
{
    return v.x * w.x + v.y * w.y + v.z * w.z;
}
