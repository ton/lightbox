#include "core/itf/ray.h"

#include "core/itf/triangle.h"
#include "math/itf/constants.h"

#include <iostream>

using namespace lb;
using namespace lb::math;

Ray::Ray(const Vector &origin, const Vector &direction):
    o(origin),
    d(direction)
{
}

bool Ray::intersectsGeometrically(const Triangle &triangle) const
{
    double k = dot(triangle.n, d);

    // In case the ray and the triangle are parallel, the ray does not intersect
    // the triangle.
    if (k == 0)
    {
        return false;
    }

    double t = -(dot(triangle.n, o) + triangle.D) / k;

    // In case the intersection point lies behind the ray's origin, the ray does
    // not intersect the triangle.
    if (t < 0)
    {
        return false;
    }

    // Find the intersection point P.
    Vector P = o + t * d;

    // The ray intersects the plane of the triangle. Now determine whether the
    // intersection point lies within the triangle.
    return (dot(triangle.n, cross(triangle.e0, P - triangle.v0)) > 0 &&
            dot(triangle.n, cross(triangle.v1v2, P - triangle.v1)) > 0 &&
            dot(triangle.n, cross(triangle.v2v0, P - triangle.v2)) > 0);
}

bool Ray::intersectsMollerTrumbore(const Triangle &triangle) const
{
    Vector T = o - triangle.v0;
    Vector P = cross(d, triangle.e1);

    double determinant = dot(P, triangle.e0);
    if (determinant < EPSILON)
    {
        return false;
    }

    // Now calculate the barycentric coordinates u and v.
    double u = dot(P, T);
    if (u < EPSILON || u > determinant)
    {
        return false;
    }

    // In case v lies between 0 and 1, we have an intersection.
    double v = dot(cross(T, triangle.e0), d);
    if (v < EPSILON || v > determinant)
    {
        return false;
    }

    return v >= EPSILON && (determinant - u - v) >= EPSILON;
}

std::ostream &lb::operator<<(std::ostream &out, const Ray &r)
{
    out << "Ray, origin: " << r.o << ", direction: " << r.d << std::endl;
    return out;
}
