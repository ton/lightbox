#ifndef LB_MESH_H
#define LB_MESH_H

#include "math/itf/vector.h"

#include "triangle.h"

#include <fstream>
#include <vector>

namespace lb {

/// Class representing an unstructured triangle mesh.
class Mesh
{
    public:
        /// Adds triangle \a t to this mesh.
        void addTriangle(const Triangle &t) { triangles_.push_back(t); }

        /// Returns all triangles in this mesh.
        const std::vector<Triangle> &triangles() const { return triangles_; }

        /// Returns the bounds of this mesh in world coordinates.
        BoundingBox bounds() const;

    private:
        std::vector<Triangle> triangles_;
};

}

#endif
