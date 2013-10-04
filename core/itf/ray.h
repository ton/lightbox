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

        bool intersects(const Triangle &t) const;

        /// Origin of the ray.
        math::Vector o;
        /// Direction of the ray.
        math::Vector d;
};

std::ostream &operator<<(std::ostream &out, const Ray &r);

}

#endif
