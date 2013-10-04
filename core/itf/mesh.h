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
        static Mesh loadFromObj(std::ifstream &objFile);

        /// Adds triangle \a t to this mesh.
        ///
        /// \param t triange to add to this mesh
        void addTriangle(const Triangle &t) { _triangles.push_back(t); }

        /// Returns all triangles in this mesh.
        ///
        /// \return all trianges in this mesh
        const std::vector<Triangle> &triangles() { return _triangles; }

    private:
        std::vector<Triangle> _triangles;
};

}

#endif
