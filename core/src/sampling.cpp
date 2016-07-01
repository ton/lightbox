#include "core/itf/sampling.h"

using namespace lb;

Sampler::Sampler(const Point2d& upperLeft, const Point2d& bottomRight):
    upperLeft_(upperLeft),
    bottomRight_(bottomRight)
{
}
