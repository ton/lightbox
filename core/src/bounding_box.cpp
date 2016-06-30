#include "core/itf/bounding_box.h"

using namespace lb;

/// Constructs an empty bounding box.
BoundingBox::BoundingBox():
    pMin(1., 1., 1.),
    pMax(0., 0., 0.)
{
}

/// Constructs an axis aligned bounding box from the given points \a p
/// and \a q.
///
/// \param p either the front lower left or back upper right corner of
///     the new bounding box
/// \param q either the front lower left or back upper right corner of
///     the new bounding box
BoundingBox::BoundingBox(const math::Point &p, const math::Point &q):
    pMin(std::min(p.x, q.x), std::min(p.y, q.y), std::min(p.z, q.z)),
    pMax(std::max(p.x, q.x), std::max(p.y, q.y), std::max(p.z, q.z))
{
}

/// Extends this bounding box to contain the given point \a p in case \a p is
/// not yet contained in this bounding box.
void BoundingBox::extend(const math::Point &p)
{
    pMin.x = std::min(pMin.x, p.x);
    pMin.y = std::min(pMin.y, p.y);
    pMin.z = std::min(pMin.z, p.z);

    pMax.x = std::max(pMax.x, p.x);
    pMax.y = std::max(pMax.y, p.y);
    pMax.z = std::max(pMax.z, p.z);
}

/// Extends this bounding box to fully include the given bounding box \a rhs.
/// The dimensions of the bounding box will be modified to include the given
/// bounding box.
///
/// \param rhs the bounding box to include in this bounding box
void BoundingBox::extend(const BoundingBox &rhs)
{
    pMin.x = std::min(pMin.x, rhs.pMin.x);
    pMin.y = std::min(pMin.y, rhs.pMin.y);
    pMin.z = std::min(pMin.z, rhs.pMin.z);

    pMax.x = std::max(pMax.x, rhs.pMax.x);
    pMax.y = std::max(pMax.y, rhs.pMax.y);
    pMax.z = std::max(pMax.z, rhs.pMax.z);
}

/// Prints a textual representation of the given \a boundingBox to \a out.
std::ostream &lb::operator<<(std::ostream &out, const BoundingBox &boundingBox)
{
    out << "Bounding box, pMin: " << boundingBox.pMin << ", pMax: " << boundingBox.pMax << std::endl;
    return out;
}
