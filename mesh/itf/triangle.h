#ifndef LB_MESH_TRIANGLE_H
#define LB_MESH_TRIANGLE_H

#include "math/itf/vector.h"

#include "triangle.h"

namespace lb {
namespace mesh {

class Triangle
{
    public:
        Triangle(const math::Vector &v0, const math::Vector &v1, const math::Vector &v2);

    private:
        /// Three vectors uniquely defining the three corners of this triangle.
        /// FIXME: Make this a Doxygen group comment.
        math::Vector _v0;
        math::Vector _v1;
        math::Vector _v2;
};

}}

#endif
