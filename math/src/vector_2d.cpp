#include "math/itf/vector_2d.h"

#include <cassert>
#include <cmath>

using namespace lb;

/// Adds the vector \a v to this vector.
Vector2d &Vector2d::operator+=(const Vector2d &v)
{
    x += v.x;
    y += v.y;

    return *this;
}

/// Returns whether this vector equals the given vector \a v.
bool Vector2d::operator==(const Vector2d &v) const
{
    return x == v.x && y == v.y;
}

/// Scales this vector by a factor \a f and returns a reference to itself.
Vector2d &Vector2d::operator*=(double f)
{
    x *= f;
    y *= f;

    return *this;
}

/// Divides this vector by a factor \a f and returns the result vector.
Vector2d Vector2d::operator/(double f) const
{
    assert(f != 0);
    double inv = 1.f / f;
    return {x * inv, y * inv};
}

/// Divides this vector by a factor \a f and returns a reference to itself.
Vector2d &Vector2d::operator/=(double f)
{
    assert(f != 0);
    double inv = 1.f / f;
    x *= inv;
    y *= inv;
    return *this;
}

/// Calculates the length of this vector and returns it.
double Vector2d::length() const
{
    return std::sqrt(lengthSquared());
}

/// Calculates the square of the length of this vector and returns it.
double Vector2d::lengthSquared() const
{
    return x * x + y * y;
}

/// Calculates a vector that points in the same direction as this vector with
/// length 1 and returns it.
Vector2d Vector2d::normalize() const
{
    return *this / length();
}

/// Streams a textual representation of the vector \a v to \a out.
std::ostream &lb::operator<<(std::ostream &out, const Vector2d &v)
{
    out << "(" << v.x << ", " << v.y << ")";
}

/// Returns the absolute value of the dot product of the two vectors \a v and \a
/// w.
double absDot(const Vector2d &v, const Vector2d &w)
{
    return std::fabs(dot(v, w));
}
