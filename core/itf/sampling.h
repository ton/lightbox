#ifndef LB_SAMPLING_H
#define LB_SAMPLING_H

#include "math/itf/vector_2d.h"

namespace lb {

struct Sample
{
    /// X-coordinate of the sample point for the camera in the image plane.
    int imageX;
    /// Y-coordinate of the sample point for the camera in the image plane.
    int imageY;
};

class Sampler
{
    public:
        Sampler(const Point2d& upperLeft, const Point2d& bottomRight);

        /// Calcultes the next sample, and returns whether a sample was
        /// available and calculated.
        virtual bool calculateNextSample(Sample& sample) const = 0;

    protected:
        /// Upper left point of the rectangle in the xy-plane to sample.
        Point2d upperLeft_;
        /// Bottom right point of the rectangle in the xy-plane to sample.
        Point2d bottomRight_;
};

}

#endif
