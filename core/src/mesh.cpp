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

/// Returns the bounding box of this mesh.
///
/// \return the bounding box of this mesh
BoundingBox Mesh::bounds() const
{
    BoundingBox result;

    // Include all triangles in this mesh in the bounding box.
    for (const Triangle &t : triangles_)
    {
        result.extend(t.bounds());
    }

    return result;
}
