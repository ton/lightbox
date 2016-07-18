#ifndef LB_MATH_VECTOR_3D_H
#define LB_MATH_VECTOR_3D_H

#include <ostream>

namespace lb {

struct Vector3d
{
    /// Constructor.
    Vector3d(double ax = 0.0, double ay = 0.0, double az = 0.0): x(ax), y(ay), z(az) { }

    /// Adds the vector \a v to this vector and returns the result vector.
    Vector3d operator+(const Vector3d &v) const
    {
        return {x + v.x, y + v.y, z + v.z};
    }
    Vector3d &operator+=(Vector3d const &v);

    bool operator==(const Vector3d &v) const;

    /// Scales this vector by a factor \a f and returns the result vector.
    Vector3d operator*(double f) const { return {x * f, y * f, z * f}; }
    Vector3d &operator*=(double f);

    Vector3d operator/(double f) const;
    Vector3d &operator/=(double f);

    /// Unary negation operator.
    Vector3d operator-() const { return {-x, -y, -z}; }
    /// Binary subtraction operator.
    Vector3d operator-(const Vector3d &v) const { return {x - v.x, y - v.y, z - v.z}; }

    double length() const;
    double lengthSquared() const;

    void normalize();
    Vector3d normalized() const;

    /// X-component of the vector.
    double x;
    /// Y-component of the vector.
    double y;
    /// Z-component of the vector.
    double z;
};

// For now, define a point as a vector. Once this becomes cumbersome for some
// reason, introduce a separate point class.
typedef Vector3d Point3d;

/// Global operator overload for scaling a vector \a v by a factor \a f.
inline Vector3d operator*(double f, const Vector3d &v)
{
    return v * f;
}

std::ostream &operator<<(std::ostream &out, const Vector3d &v);

}

double absDot(const lb::Vector3d &v, const lb::Vector3d &w);

/// Calculates the cross product between the vectors \a v and \a w and returns
/// it.
///
/// The cross product is a vector perpendicular to both vectors \a v and \a w.
/// The direction of the cross product determines the handedness of the
/// coordinate system. Thus, the handedness of the coordinate system determines
/// the direction of the cross product. This implementation uses the definition
/// of a cross product in a left-handed coordinate system.
inline lb::Vector3d cross(const lb::Vector3d &v, const lb::Vector3d &w)
{
    return {v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x};
}

/// Returns the dot product of the two vectors \a v and \a w.
inline double dot(const lb::Vector3d &v, const lb::Vector3d &w)
{
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

#endif
