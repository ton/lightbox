#ifndef LB_MATH_CONSTANTS_H
#define LB_MATH_CONSTANTS_H

#include <cmath>
#include <limits>

namespace lb {
namespace math {

/// Double comparison epsilon.
static const double EPSILON = std::sqrt(std::numeric_limits<double>::epsilon());

}}

#endif
