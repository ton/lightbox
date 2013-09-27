#include "mesh/itf/mesh.h"
#include "mesh/itf/triangle.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace lb {
namespace mesh {

/// Loads an unstructured triangle mesh in OBJ format from the given input
/// stream \a objFile, and returns it.
///
/// \param objFile input stream containing mesh data in the OBJ format
/// \return unstructured triangle mesh
Mesh Mesh::loadFromObj(std::ifstream &objFile)
{
    Mesh result;

    // The list of vertices making up the mesh.
    std::vector<Vertex> vertices;

    while (objFile.good())
    {
        std::string line;
        std::getline(objFile, line);

        // In case the line starts with a 'v', a vertex is defined.
        if (!line.empty())
        {
            std::stringstream ss(line.substr(1));

            switch (line.front())
            {
                case 'v':
                    {
                        Vertex v;
                        ss >> v.x >> v.y >> v.z;

                        vertices.push_back(v);
                    }
                    break;
                case 'f':
                    {
                        unsigned int v0, v1, v2;
                        ss >> v0 >> v1 >> v2;

                        // Note that vertex indices in the OBJ format start
                        // counting at one.
                        result.addTriangle(Triangle(vertices[v0 - 1], vertices[v1 - 1], vertices[v2 - 1]));
                    }
                    break;
                default:
                    break;
            }
        }
    }

    return result;
}

}}
