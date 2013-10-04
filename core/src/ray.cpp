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

bool Ray::intersects(const Triangle &t) const
{
    Vector T = o - t.v0;

    Vector P = cross(d, t.e1);
    Vector Q = cross(T, t.e0);

    // double tt = dot(Q, t.e1) / dot(P, t.e0);
    double u = dot(P, T) / dot(P, t.e0);
    if (u < 0.0 || u > 1.0)
        return false;
    double v = dot(Q, d) / dot(P, t.e0);

    return (1 - u - v >= 0 && u >= 0 && u <= 1 && v >= 0 && v <= 1);
}

std::ostream &lb::operator<<(std::ostream &out, const Ray &r)
{
    out << "Ray, origin: " << r.o << ", direction: " << r.d << std::endl;
    return out;
}
