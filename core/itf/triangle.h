#ifndef LB_TRIANGLE_H
#define LB_TRIANGLE_H

#include "core/itf/bounding_box.h"
#include "math/itf/vector.h"

#include <ostream>

namespace lb {

/// A vertex is represented by a vector.
typedef math::Vector Vertex;

class Triangle
{
    public:
        Triangle(const Vertex &a, const Vertex &b, const Vertex &c);

        bool operator==(const Triangle &rhs) const;

        BoundingBox bounds() const;

        ///@{
        /// Three vertices uniquely defining the three corners of this triangle.
        Vertex v0;
        Vertex v1;
        Vertex v2;
        ///@}

        /// The edge from vertex 0 to vertex 1.
        math::Vector e0;
        /// The edge from vertex 0 to vertex 2.
        math::Vector e1;

        /// The edge from vertex 1 to vertex 2.
        math::Vector v1v2;
        /// The edge from vertex 2 to vertex 0.
        math::Vector v2v0;

        /// Normal of the triangle.
        math::Vector n;

        /// Constant D in the plane equation of this triangle.
        double D;

};

std::ostream &operator<<(std::ostream &out, const Triangle &triangle);

}

#endif
