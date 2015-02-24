#include "math/itf/vector.h"

#include <cmath>
#include <boost/assert.hpp>

using namespace lb::math;

/// Adds the vector \a v to this vector.
///
/// \param v vector to add to this vector
/// \returns a reference to this vector after adding vector \a v
Vector &Vector::operator+=(const Vector &v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

/// Equality operator.
///
/// \param v vector to compare this vector with
/// \returns \c true in case this vector is equal to \a v, \c false
///   otherwise
bool Vector::operator==(const Vector &v) const
{
    return x == v.x && y == v.y && z == v.z;
}

/// Scales this vector by a factor \a f and returns a reference to itself.
///
/// \param f factor to scale this vector with
/// \returns a reference to this vector after scaling it by a factor \a f
Vector &Vector::operator*=(double f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

/// Divides this vector by a factor \a f and returns the result vector.
///
/// \param f factor to divide this vector with
/// \returns the vector that results from dividing this vector with \a f
Vector Vector::operator/(double f) const
{
    BOOST_ASSERT(f != 0);
    double inv = 1.f / f;
    return {x * inv, y * inv, z * inv};
}

/// Divides this vector by a factor \a f and returns a reference to itself.
///
/// \param f factor to divide this vector with
/// \returns a reference to this vector after dividing it by a factor \a f
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
///
/// \returns the length of this vector
double Vector::length() const
{
    return std::sqrt(lengthSquared());
}

/// Calculates the square of the length of this vector and returns it.
///
/// \returns the square of the length of this vector
double Vector::lengthSquared() const
{
    return x * x + y * y + z * z;
}

/// Calculates a vector that points in the same direction as this vector with length 1 and returns it.
///
/// \returns a vector that points in the same direction as this vector with length 1
Vector Vector::normalize() const
{
    return *this / length();
}

/// Streams a textual representation of the vector \a v to \a out.
///
/// \param out output stream to send the textual representation of \a v to
/// \param v vector to create a textual representation for
std::ostream &lb::math::operator<<(std::ostream &out, const Vector &v)
{
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

/// Returns the absolute value of the dot product of the two vectors \a v and \a
/// w.
///
/// \param v left-hand side argument of the dot product
/// \param w right-hand side argument of the dot product
/// \return the absolute value of the dot product of two vectors \a v and \a w
double absDot(const Vector &v, const Vector &w)
{
    return std::fabs(dot(v, w));
}
