#ifndef LB_CONSTANTS_H
#define LB_CONSTANTS_H

#include <cmath>
#include <limits>

namespace lb {

/// Double comparison epsilon.
static const double EPSILON = std::sqrt(std::numeric_limits<double>::epsilon());
/// Pi.
static const double PI = M_PI;

}

#endif
