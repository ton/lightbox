#ifndef LB_MESH_MESH_H
#define LB_MESH_MESH_H

#include "math/itf/vector.h"

#include "triangle.h"

#include <fstream>
#include <vector>

namespace lb {
namespace mesh {

/// For now, a vertex is represented by a vector, but this might change in the
/// future.
typedef math::Vector Vertex;

/// Class representing an unstructured triangle mesh.
class Mesh
{
    public:
        static Mesh loadFromObj(const std::ifstream &objFile);

    private:
        std::vector<mesh::Vertex> _vertices;
        std::vector<mesh::Triangle> _triangles;
};

}}

#endif
