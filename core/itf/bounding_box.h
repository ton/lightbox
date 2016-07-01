#ifndef LB_BOUNDING_BOX_H
#define LB_BOUNDING_BOX_H

#include "math/itf/vector_3d.h"

namespace lb {

/// Implementation of an axis aligned bounding box in 3d space.
class BoundingBox
{
    public:
        BoundingBox();
        BoundingBox(const Point3d &p, const Point3d &q);

        void extend(const Point3d &p);
        void extend(const BoundingBox &rhs);

        /// The lower front left corner of this axis aligned bounding box.
        Point3d pMin;
        /// The upper back right corner of this axis aligned bounding box.
        Point3d pMax;
};

std::ostream &operator<<(std::ostream &out, const BoundingBox &boundingBox);

}

#endif
