#include "math/itf/vector_3d.h"

#include <cmath>
#include <boost/assert.hpp>

using namespace lb;

/// Adds the vector \a v to this vector.
Vector3d &Vector3d::operator+=(const Vector3d &v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

/// Returns whether this vector equals the given vector \a v.
bool Vector3d::operator==(const Vector3d &v) const
{
    return x == v.x && y == v.y && z == v.z;
}

/// Scales this vector by a factor \a f and returns a reference to itself.
Vector3d &Vector3d::operator*=(double f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

/// Divides this vector by a factor \a f and returns the result vector.
Vector3d Vector3d::operator/(double f) const
{
    BOOST_ASSERT(f != 0);
    double inv = 1.f / f;
    return {x * inv, y * inv, z * inv};
}

/// Divides this vector by a factor \a f and returns a reference to itself.
Vector3d &Vector3d::operator/=(double f)
{
    BOOST_ASSERT(f != 0);
    double inv = 1.f / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

/// Calculates the length of this vector and returns it.
double Vector3d::length() const
{
    return std::sqrt(lengthSquared());
}

/// Calculates the square of the length of this vector and returns it.
double Vector3d::lengthSquared() const
{
    return x * x + y * y + z * z;
}

/// Normalizes this vector to a vector with the same direction and magnitude
/// one.
void Vector3d::normalize()
{
    double oneOverLength = 1.0 / length();
    x *= oneOverLength;
    y *= oneOverLength;
    z *= oneOverLength;
}

/// Calculates a vector that points in the same direction as this vector with
/// length 1 and returns it.
Vector3d Vector3d::normalized() const
{
    return *this / length();
}

/// Streams a textual representation of the vector \a v to \a out.
std::ostream &lb::operator<<(std::ostream &out, const Vector3d &v)
{
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

/// Returns the absolute value of the dot product of the two vectors \a v and \a
/// w.
double absDot(const Vector3d &v, const Vector3d &w)
{
    return std::fabs(dot(v, w));
}
