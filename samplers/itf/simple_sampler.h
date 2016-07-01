#ifndef LB_SIMPLE_SAMPLER_H
#define LB_SIMPLE_SAMPLER_H

#include "core/itf/sampling.h"

namespace lb {

class SimpleSampler : public Sampler
{
    public:
        SimpleSampler(const Point2d& upperLeft, const Point2d& bottomRight);

        bool calculateNextSample(Sample& sample) const override
        {
            // Sample the image plane from the upper left corner to the bottom right
            // corner.
            if (sample.imageX < bottomRight_.x - 1)
            {
                sample.imageX++;
            }
            else
            {
                sample.imageX = upperLeft_.x;
                sample.imageY++;
            }

            // As soon as we leave the sampling area, no more samples are available.
            return sample.imageY < bottomRight_.y;
        }
};

}

#endif
