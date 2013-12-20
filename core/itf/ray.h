#ifndef LB_RAY_H
#define LB_RAY_H

#include "math/itf/vector.h"

#include <ostream>

namespace lb {

class Triangle;

class Ray
{
    public:
        Ray(const math::Vector &o, const math::Vector &d);

        bool intersectsGeometrically(const Triangle &t) const;
        bool intersectsMollerTrumbore(const Triangle &t) const;

        /// Origin of the ray.
        math::Vector o;
        /// Direction of the ray.
        math::Vector d;
};

std::ostream &operator<<(std::ostream &out, const Ray &r);

/// Type definition for an intersection method.
typedef bool (Ray::*IntersectionMethod)(const Triangle &) const;

/// This overload allows gtest to print the name of the given intersection
/// method \a interSectionMethod to the specified output stream \a out in case a
/// test case for a specific intersection method fails.
///
/// \param out output stream
/// \param intersectionMethod the intersection method to print
/// \return the output stream
std::ostream &operator<<(std::ostream &out, const IntersectionMethod &intersectionMethod);

}

#endif
