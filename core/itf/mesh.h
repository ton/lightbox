#ifndef LB_MESH_H
#define LB_MESH_H

#include "triangle.h"

#include <fstream>
#include <vector>

namespace lb {

class Ray;

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

        bool intersects(const Ray& ray) const;

    private:
        std::vector<Triangle> triangles_;
};

}

#endif
