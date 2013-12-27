#include "core/itf/triangle.h"

#include "math/itf/vector.h"

#include <iostream>

using namespace lb;
using namespace lb::math;

Triangle::Triangle(const Point &a, const Point &b, const Point &c):
    v0(a),
    v1(b),
    v2(c),
    e0(v1 - v0),
    e1(v2 - v0),
    v1v2(v2 - v1),
    v2v0(v0 - v2),
    n(cross(e0, e1)),
    D(dot(n, v0))
{
}

/// Returns the bounding box of this triangle.
///
/// \returns the bounding box of this triangle
BoundingBox Triangle::bounds() const
{
    BoundingBox result;
    result.extend(v0);
    result.extend(v1);
    result.extend(v2);
    return result;
}

bool Triangle::operator==(const Triangle &rhs) const
{
    return v0 == rhs.v0 && v1 == rhs.v1 && v2 == rhs.v2;
}

/// Prints a textual representation of the given \a triangle to \a out.
///
/// \param out the output stream
/// \param triangle the triangle to print to \a out
/// \return the output stream
std::ostream &lb::operator<<(std::ostream &out, const Triangle &triangle)
{
    out << "Triangle, v0: " << triangle.v0 << ", v1: " << triangle.v1 << ", v2: " << triangle.v2 << std::endl;
    return out;
}
