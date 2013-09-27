#include "math/itf/vector.h"

#include <cmath>
#include <boost/assert.hpp>

using namespace lb::math;

/// Constructor.
///
/// \param ax x component of the vector
/// \param ay y component of the vector
/// \param az z component of the vector
Vector::Vector(double ax, double ay, double az):
    x(ax),
    y(ay),
    z(az)
{
}

/// Adds the vector \a v to this vector and returns the result vector.
///
/// \param v vector to add to this vector
/// \returns the vector that results from adding v to this vector
Vector Vector::operator+(const Vector &v) const
{
    return Vector(x + v.x, y + v.y, z + v.z);
}

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

/// Scales this vector by a factor \a f and returns the result vector.
///
/// \param f factor to scale this vector with
/// \returns the vector that results from scaling this vector with \a f
Vector Vector::operator*(double f) const
{
    return Vector(x * f, y * f, z * f);
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
    return Vector(x * inv, y * inv, z * inv);
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

/// Unary negation operator.
///
/// \returns a vector that points in the opposite direction of this vector
Vector Vector::operator-() const
{
    return Vector(-x, -y, -z);
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

/// Global operator overload for scaling a vector \a v by a factor \a f.
///
/// \param f factor to scale \a v with
/// \param v vector to scale
/// \return \a v scaled with factor \a f
Vector lb::math::operator*(double f, const Vector &v)
{
    return v * f;
}

/// Streams a textual representation of the vector \a v to \a out.
///
/// \param out output stream to send the textual representation of \a v to
/// \param v vector to create a textual representation for
std::ostream &lb::math::operator<<(std::ostream &out, const Vector &v)
{
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

/// Calculates the cross product between the vectors \a v and \a w and returns
/// it.
///
/// The cross product is a vector perpendicular to both vectors \a v and \a w.
/// The direction of the cross product determines the handedness of the
/// coordinate system. Thus, the handedness of the coordinate system determines
/// the direction of the cross product. This implementation uses the definition
/// of a cross product in a left-handed coordinate system.
///
/// \param v left-hand side argument of the cross product
/// \param w right-hand side argument of the cross product
/// \returns the cross product between the vectors \a v and \a w
Vector cross(const Vector &v, const Vector &w)
{
    return Vector(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x);
}

/// Returns the dot product of the two vectors \a v and \a w.
///
/// \param v left-hand side argument for the dot product
/// \param w right-hand side argument for the dot product
/// \returns the dot product of the two vectors \a v and \a w
double dot(const Vector &v, const Vector &w)
{
    return v.x * w.x + v.y * w.y + v.z * w.z;
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
