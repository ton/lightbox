#include "core/itf/triangle.h"

#include <iostream>

using namespace lb;

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c):
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

bool Triangle::operator==(const Triangle &rhs) const
{
    return v0 == rhs.v0 && v1 == rhs.v1 && v2 == rhs.v2;
}

std::ostream &lb::operator<<(std::ostream &out, const Triangle &triangle)
{
    out << "Triangle, v0: " << triangle.v0 << ", v1: " << triangle.v1 << ", v2: " << triangle.v2 << std::endl;
    return out;
}
