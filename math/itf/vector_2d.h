#ifndef LB_MATH_VECTOR_2D_H
#define LB_MATH_VECTOR_2D_H

#include <ostream>

namespace lb {

struct Vector2d
{
    /// Constructor.
    Vector2d(double ax = 0.0, double ay = 0.0): x(ax), y(ay) { }

    /// Adds the vector \a v to this vector and returns the result vector.
    Vector2d operator+(const Vector2d &v) const
    {
        return {x + v.x, y + v.y};
    }
    Vector2d &operator+=(Vector2d const &v);

    bool operator==(const Vector2d &v) const;

    /// Scales this vector by a factor \a f and returns the result vector.
    Vector2d operator*(double f) const { return {x * f, y * f}; }
    Vector2d &operator*=(double f);

    Vector2d operator/(double f) const;
    Vector2d &operator/=(double f);

    /// Unary negation operator.
    Vector2d operator-() const { return {-x, -y}; }
    /// Binary subtraction operator.
    Vector2d operator-(const Vector2d &v) const { return {x - v.x, y - v.y}; }

    double length() const;
    double lengthSquared() const;

    Vector2d normalize() const;

    /// X-component of the 2d vector.
    double x;
    /// Y-component of the 2d vector.
    double y;
};

// For now, define a 2d point as a vector. Once this becomes cumbersome for some
// reason, introduce a separate point class.
typedef Vector2d Point2d;

/// Global operator overload for scaling a vector \a v by a factor \a f.
inline Vector2d operator*(double f, const Vector2d &v)
{
    return v * f;
}

std::ostream &operator<<(std::ostream &out, const Vector2d &v);

}

double absDot(const lb::Vector2d &v, const lb::Vector2d &w);

/// Returns the dot product of the two vectors \a v and \a w.
inline double dot(const lb::Vector2d &v, const lb::Vector2d &w)
{
    return v.x * w.x + v.y * w.y;
}

#endif
