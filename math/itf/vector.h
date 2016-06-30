#ifndef LB_MATH_VECTOR_H
#define LB_MATH_VECTOR_H

#include <ostream>

namespace lb {
namespace math {

struct Vector
{
    /// Constructor.
    Vector(double ax = 0.0, double ay = 0.0, double az = 0.0): x(ax), y(ay), z(az) { }

    /// Adds the vector \a v to this vector and returns the result vector.
    Vector operator+(const Vector &v) const
    {
        return {x + v.x, y + v.y, z + v.z};
    }
    Vector &operator+=(Vector const &v);

    bool operator==(const Vector &v) const;

    /// Scales this vector by a factor \a f and returns the result vector.
    Vector operator*(double f) const { return {x * f, y * f, z * f}; }
    Vector &operator*=(double f);

    Vector operator/(double f) const;
    Vector &operator/=(double f);

    /// Unary negation operator.
    Vector operator-() const { return {-x, -y, -z}; }
    /// Binary subtraction operator.
    Vector operator-(const Vector &v) const { return {x - v.x, y - v.y, z - v.z}; }

    double length() const;
    double lengthSquared() const;

    Vector normalize() const;

    /// X-component of the vector.
    double x;
    /// Y-component of the vector.
    double y;
    /// Z-component of the vector.
    double z;
};

// For now, define a point as a vector. Once this becomes cumbersome for some
// reason, introduce a separate point class.
typedef Vector Point;

/// Global operator overload for scaling a vector \a v by a factor \a f.
inline Vector operator*(double f, const Vector &v)
{
    return v * f;
}

std::ostream &operator<<(std::ostream &out, const Vector &v);

}}

double absDot(const lb::math::Vector &v, const lb::math::Vector &w);

/// Calculates the cross product between the vectors \a v and \a w and returns
/// it.
///
/// The cross product is a vector perpendicular to both vectors \a v and \a w.
/// The direction of the cross product determines the handedness of the
/// coordinate system. Thus, the handedness of the coordinate system determines
/// the direction of the cross product. This implementation uses the definition
/// of a cross product in a left-handed coordinate system.
inline lb::math::Vector cross(const lb::math::Vector &v, const lb::math::Vector &w)
{
    return {v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x};
}

/// Returns the dot product of the two vectors \a v and \a w.
inline double dot(const lb::math::Vector &v, const lb::math::Vector &w)
{
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

#endif
