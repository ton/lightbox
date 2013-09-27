#ifndef LB_MATH_VECTOR_H
#define LB_MATH_VECTOR_H

#include <ostream>

namespace lb {
namespace math {

class Vector
{
    public:
        Vector(double ax = 0, double ay = 0, double az = 0);

        Vector operator+(Vector const &v) const;
        Vector &operator+=(Vector const &v);

        bool operator==(const Vector &v) const;

        Vector operator*(double f) const;
        Vector &operator*=(double f);

        Vector operator/(double f) const;
        Vector &operator/=(double f);

        Vector operator-() const;

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

Vector operator*(double f, const Vector &v);
std::ostream &operator<<(std::ostream &out, const Vector &v);

}}

lb::math::Vector cross(const lb::math::Vector &v, const lb::math::Vector &w);
double dot(const lb::math::Vector &v, const lb::math::Vector &w);
double absDot(const lb::math::Vector &v, const lb::math::Vector &w);

#endif
