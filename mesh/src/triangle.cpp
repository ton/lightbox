#include "mesh/itf/triangle.h"

using namespace lb;
using namespace lb::mesh;

Triangle::Triangle(const math::Vector &v0, const math::Vector &v1, const math::Vector &v2):
    _v0(v0), _v1(v1), _v2(v2)
{
}
