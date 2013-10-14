#ifndef LB_TRIANGLE_H
#define LB_TRIANGLE_H

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

        ///@{
        /// Three vertices uniquely defining the three corners of this triangle.
        Vertex v0;
        Vertex v1;
        Vertex v2;
        ///@}

        ///@{
        /// Two edges originating from vertex 0 to vertex 1 and 2 respectively.
        math::Vector e0;
        math::Vector e1;
        ///@}
};

std::ostream &operator<<(std::ostream &out, const Triangle &triangle);

}

#endif
