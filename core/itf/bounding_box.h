#ifndef LB_BOUNDING_BOX_H
#define LB_BOUNDING_BOX_H

#include "math/itf/vector.h"

namespace lb {

/// Implementation of an axis aligned bounding box.
class BoundingBox
{
    public:
        BoundingBox();
        BoundingBox(const math::Point &p, const math::Point &q);

        void extend(const math::Point &p);
        void extend(const BoundingBox &rhs);

        /// The lower front left corner of this axis aligned bounding box.
        math::Point pMin;
        /// The upper back right corner of this axis aligned bounding box.
        math::Point pMax;
};

std::ostream &operator<<(std::ostream &out, const BoundingBox &boundingBox);

}

#endif
