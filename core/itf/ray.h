#ifndef LB_RAY_H
#define LB_RAY_H

#include "math/itf/vector_3d.h"

#include <ostream>

namespace lb {

class Triangle;

class Ray
{
    public:
        Ray() = default;
        Ray(const Vector3d &o, const Vector3d &d);

        bool intersectsDidierBadouel(const Triangle &t) const;
        bool intersectsGeometrically(const Triangle &t) const;
        bool intersectsMollerTrumbore(const Triangle &t) const;

        /// Origin of the ray.
        Vector3d o;
        /// Direction of the ray.
        Vector3d d;
};

std::ostream &operator<<(std::ostream &out, const Ray &r);

/// Type definition for an intersection method.
typedef bool (Ray::*IntersectionMethod)(const Triangle &) const;

/// This overload allows gtest to print the name of the given intersection
/// method \a interSectionMethod to the specified output stream \a out in case a
/// test case for a specific intersection method fails.
std::ostream &operator<<(std::ostream &out, const IntersectionMethod &intersectionMethod);

}

#endif
