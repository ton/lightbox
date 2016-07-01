#include "samplers/itf/simple_sampler.h"

using namespace lb;

SimpleSampler::SimpleSampler(
        const Point2d& upperLeft, const Point2d& bottomRight):
    Sampler(upperLeft, bottomRight)
{
}
