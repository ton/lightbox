#include "mesh/itf/mesh.h"

#include <fstream>

namespace lb {
namespace mesh {

/// Loads an unstructured triangle mesh in OBJ format from the given input
/// stream \a objFile, and returns it.
///
/// \param objFile input stream containing mesh data in the OBJ format
/// \return unstructured triangle mesh
Mesh Mesh::loadFromObj(const std::ifstream &objFile)
{
    while (!objFile.eof())
    {
    }

    return Mesh();
}

}}
