#include "core/itf/mesh.h"

#include "core/itf/ray.h"
#include "core/itf/triangle.h"

#include <iostream>

using namespace lb;

/// Returns the bounding box of this mesh.
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

/// Calculates whether the given \a ray intersects with this mesh.
bool Mesh::intersects(const Ray& ray) const
{
    for (const Triangle& t : triangles_)
    {
        if (ray.intersectsMollerTrumbore(t))
        {
            return true;
        }
    }

    return false;
}
