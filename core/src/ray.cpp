#include "core/itf/ray.h"

#include "core/itf/triangle.h"

#include <iostream>

using namespace lb;
using namespace lb::math;

Ray::Ray(const Vector &origin, const Vector &direction):
    o(origin),
    d(direction)
{
}

bool Ray::intersects(const Triangle &triangle) const
{
    Vector T = o - triangle.v0;
    Vector P = cross(d, triangle.e1);

    double s = 1.0 / dot(P, triangle.e0);

    // Now calculate the barycentric coordinates u and v.

    // In case u does not lie between 0 and 1, we already know the ray does not
    // intersect the triangle.
    double u = dot(P, T) * s;
    if (u < 0 || u > 1)
    {
        return false;
    }

    // In case v lies between 0 and 1, we have an intersection.
    double v = dot(cross(T, triangle.e0), d) * s;
    return (1 - u - v) >= 0 && v >= 0;
}

std::ostream &lb::operator<<(std::ostream &out, const Ray &r)
{
    out << "Ray, origin: " << r.o << ", direction: " << r.d << std::endl;
    return out;
}
