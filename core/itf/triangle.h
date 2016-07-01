#ifndef LB_TRIANGLE_H
#define LB_TRIANGLE_H

#include "core/itf/bounding_box.h"
#include "math/itf/vector_3d.h"

#include <ostream>

namespace lb {

class Triangle
{
    public:
        Triangle(const Point3d &a, const Point3d &b, const Point3d &c);

        bool operator==(const Triangle &rhs) const;

        BoundingBox bounds() const;

        ///@{
        /// Three vertices uniquely defining the three corners of this triangle.
        Point3d v0;
        Point3d v1;
        Point3d v2;
        ///@}

        /// The edge from point 0 to point 1.
        Vector3d e0;
        /// The edge from point 0 to point 2.
        Vector3d e1;

        /// The edge from point 1 to point 2.
        Vector3d v1v2;
        /// The edge from point 2 to point 0.
        Vector3d v2v0;

        /// Normal of the triangle.
        Vector3d n;

        /// Constant D in the plane equation of this triangle.
        double D;

};

std::ostream &operator<<(std::ostream &out, const Triangle &triangle);

}

#endif
