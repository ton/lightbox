#include "core/itf/mesh.h"
#include "core/itf/triangle.h"

#include "obj_reader.h"

using namespace lb;

/// Loads an unstructured triangle mesh in OBJ format from the given input
/// stream \a objFile, and returns it.
///
/// \param objFile input stream containing mesh data in the OBJ format
/// \return unstructured triangle mesh
Mesh Mesh::loadFromObj(std::ifstream &objFile)
{
    ObjReader objReader(objFile);
    return objReader.mesh();
}
