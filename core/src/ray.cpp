#include "core/itf/ray.h"

#include "core/itf/triangle.h"
#include "math/itf/constants.h"

#include <iostream>

using namespace lb;
using namespace lb::math;

Ray::Ray(const Vector3d &origin, const Vector3d &direction):
    o(origin),
    d(direction)
{
}

/// Implements the 'Efficient Ray-Polygon Intersection' algorithm as described
/// by Didier Badouel in Graphics Gems I, first published in 1990.
bool Ray::intersectsDidierBadouel(const Triangle &triangle) const
{
    double k = dot(triangle.n, d);

    // In case the ray and the triangle are parallel, or the triangle is
    // backwards facing, the ray does not intersect the triangle.
    if (k >= 0)
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
    Vector3d P = o + t * d;

    // Project the triangle on either the XY, XZ, or YZ plane, such that the
    // projection is as large as possible, and not a flat line (in case the
    // normal of the triangle is parallel to the projection plane). The decision
    // on which plane to project is taken by taking the largest component of the
    // triangle's normal, and using the plane perpendicular to that axis as the
    // projection plane.
    double u0, u1, u2, v0, v1, v2;

    if (triangle.n.x >= triangle.n.y && triangle.n.x >= triangle.n.z)
    {
        // Project on the YZ plane.
        u0 = P.y - triangle.v0.y;
        u1 = triangle.e0.y;
        u2 = triangle.e1.y;

        v0 = P.z - triangle.v0.z;
        v1 = triangle.e0.z;
        v2 = triangle.e1.z;
    }
    else if (triangle.n.y >= triangle.n.z)
    {
        // Project on the XZ plane.
        u0 = P.x - triangle.v0.x;
        u1 = triangle.e0.x;
        u2 = triangle.e1.x;

        v0 = P.z - triangle.v0.z;
        v1 = triangle.e0.z;
        v2 = triangle.e1.z;
    }
    else
    {
        // Project on the XY plane.
        u0 = P.x - triangle.v0.x;
        u1 = triangle.e0.x;
        u2 = triangle.e1.x;

        v0 = P.y - triangle.v0.y;
        v1 = triangle.e0.y;
        v2 = triangle.e1.y;
    }

    double beta = (v0 * u1 - u0 * v1) / (u1 * v2 - u2 * v1);
    if (beta < 0.0 || beta > 1.0)
    {
        return false;
    }

    double alpha = (u0 * v2 - u2 * v0) / (u1 * v2 - u2 * v1);
    return alpha >= 0.0 && alpha + beta <= 1.0;
}

/// Implements a straight up geometrical approach to solve the ray/triangle
/// intersection problem. The intersection point P with the plane the triangle
/// lies in is first determined. Subsequently, the algorithm checks whether P
/// lies within the triangle boundaries.
bool Ray::intersectsGeometrically(const Triangle &triangle) const
{
    double k = dot(triangle.n, d);

    // In case the ray and the triangle are parallel, or the triangle is
    // backwards facing, the ray does not intersect the triangle.
    if (k >= 0)
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
    Vector3d P = o + t * d;

    // The ray intersects the plane of the triangle. Now determine whether the
    // intersection point lies within the triangle.
    return (dot(triangle.n, cross(triangle.e0, P - triangle.v0)) >= 0 &&
            dot(triangle.n, cross(triangle.v1v2, P - triangle.v1)) >= 0 &&
            dot(triangle.n, cross(triangle.v2v0, P - triangle.v2)) >= 0);
}

/// Implementation of the Moller/Trumbore algorithm, described in their paper
/// 'Fast Minimum-Storage Ray-Triangle Intersection', published in 1997.
bool Ray::intersectsMollerTrumbore(const Triangle &triangle) const
{
    Vector3d P = cross(d, triangle.e1);

    double determinant = dot(P, triangle.e0);
    if (determinant < EPSILON)
    {
        return false;
    }

    Vector3d T = o - triangle.v0;

    // Now calculate the barycentric coordinates u and v.
    double u = dot(P, T);
    if (u < 0.0 || u > determinant)
    {
        return false;
    }

    // In case v lies between 0 and 1, we have an intersection.
    double v = dot(cross(T, triangle.e0), d);
    if (v < 0.0 || v > determinant)
    {
        return false;
    }

    return (determinant - u - v) >= 0.0;
}

std::ostream &lb::operator<<(std::ostream &out, const Ray &r)
{
    return out << "Ray, origin: " << r.o << ", direction: " << r.d << "\n";
}

std::ostream &lb::operator<<(std::ostream &out, const IntersectionMethod &intersectionMethod)
{
    if (intersectionMethod == &lb::Ray::intersectsDidierBadouel)
    {
        out << "Didier-Badouel";
    }
    else if (intersectionMethod == &lb::Ray::intersectsMollerTrumbore)
    {
        out << "Moller-Trumbore";
    }
    else if (intersectionMethod == &lb::Ray::intersectsGeometrically)
    {
        out << "Geometrically";
    }
    else
    {
        out << "Unknown";
    }
}
