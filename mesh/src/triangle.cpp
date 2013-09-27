#include "mesh/itf/triangle.h"

#include <iostream>

using namespace lb::mesh;

Triangle::Triangle(const Vertex &v0, const Vertex &v1, const Vertex &v2):
    a(v0), b(v1), c(v2)
{
}

bool Triangle::operator==(const Triangle &rhs) const
{
    return a == rhs.a && b == rhs.b && c == rhs.c;
}

std::ostream &lb::mesh::operator<<(std::ostream &out, const Triangle &triangle)
{
    out << "Triangle, a: " << triangle.a << ", b: " << triangle.b << ", c: " << triangle.c << std::endl;
    return out;
}
