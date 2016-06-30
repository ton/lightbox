#include "core/itf/mesh.h"
#include "core/itf/triangle.h"

using namespace lb;

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
