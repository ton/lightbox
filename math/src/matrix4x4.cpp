#include "math/itf/matrix4x4.h"

#include <ostream>

using namespace lb;

/// Streams a textual representation of the vector \a v to \a out.
std::ostream& lb::operator<<(std::ostream& out, const Matrix4x4& m)
{
    return out <<
        "|" << m(0, 0) << ", " << m(0, 1) << ", " << m(0, 2) << ", " << m(0, 3) << "|\n" <<
        "|" << m(1, 0) << ", " << m(1, 1) << ", " << m(1, 2) << ", " << m(1, 3) << "|\n" <<
        "|" << m(2, 0) << ", " << m(2, 1) << ", " << m(2, 2) << ", " << m(2, 3) << "|\n" <<
        "|" << m(3, 0) << ", " << m(3, 1) << ", " << m(3, 2) << ", " << m(3, 3) << "|\n";
}
