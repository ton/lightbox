#ifndef LB_MESH_TRIANGLE_H
#define LB_MESH_TRIANGLE_H

#include "math/itf/vector.h"

#include <ostream>

namespace lb {
namespace mesh {

/// A vertex is represented by a vector.
typedef math::Vector Vertex;

class Triangle
{
    public:
        Triangle(const Vertex &v0, const Vertex &v1, const Vertex &v2);

        bool operator==(const Triangle &rhs) const;

        ///@{
        /// Three vertices uniquely defining the three corners of this triangle.
        Vertex a;
        Vertex b;
        Vertex c;
        ///@}
};

std::ostream &operator<<(std::ostream &out, const Triangle &triangle);

}}

#endif
