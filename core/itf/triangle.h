#ifndef LB_TRIANGLE_H
#define LB_TRIANGLE_H

#include "core/itf/bounding_box.h"
#include "math/itf/vector.h"

#include <ostream>

namespace lb {

class Triangle
{
    public:
        Triangle(const math::Point &a, const math::Point &b, const math::Point &c);

        bool operator==(const Triangle &rhs) const;

        BoundingBox bounds() const;

        ///@{
        /// Three vertices uniquely defining the three corners of this triangle.
        math::Point v0;
        math::Point v1;
        math::Point v2;
        ///@}

        /// The edge from point 0 to point 1.
        math::Vector e0;
        /// The edge from point 0 to point 2.
        math::Vector e1;

        /// The edge from point 1 to point 2.
        math::Vector v1v2;
        /// The edge from point 2 to point 0.
        math::Vector v2v0;

        /// Normal of the triangle.
        math::Vector n;

        /// Constant D in the plane equation of this triangle.
        double D;

};

std::ostream &operator<<(std::ostream &out, const Triangle &triangle);

}

#endif
