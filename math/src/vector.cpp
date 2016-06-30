#include "math/itf/vector.h"

#include <cmath>
#include <boost/assert.hpp>

using namespace lb::math;

/// Adds the vector \a v to this vector.
Vector &Vector::operator+=(const Vector &v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

/// Returns whether this vector equals the given vector \a v.
bool Vector::operator==(const Vector &v) const
{
    return x == v.x && y == v.y && z == v.z;
}

/// Scales this vector by a factor \a f and returns a reference to itself.
Vector &Vector::operator*=(double f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

/// Divides this vector by a factor \a f and returns the result vector.
Vector Vector::operator/(double f) const
{
    BOOST_ASSERT(f != 0);
    double inv = 1.f / f;
    return {x * inv, y * inv, z * inv};
}

/// Divides this vector by a factor \a f and returns a reference to itself.
Vector &Vector::operator/=(double f)
{
    BOOST_ASSERT(f != 0);
    double inv = 1.f / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

/// Calculates the length of this vector and returns it.
double Vector::length() const
{
    return std::sqrt(lengthSquared());
}

/// Calculates the square of the length of this vector and returns it.
double Vector::lengthSquared() const
{
    return x * x + y * y + z * z;
}

/// Calculates a vector that points in the same direction as this vector with
/// length 1 and returns it.
Vector Vector::normalize() const
{
    return *this / length();
}

/// Streams a textual representation of the vector \a v to \a out.
std::ostream &lb::math::operator<<(std::ostream &out, const Vector &v)
{
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

/// Returns the absolute value of the dot product of the two vectors \a v and \a
/// w.
double absDot(const Vector &v, const Vector &w)
{
    return std::fabs(dot(v, w));
}
