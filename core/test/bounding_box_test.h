#include "core/itf/bounding_box.h"

#include <gtest/gtest.h>

using namespace lb;

TEST(BoundingBoxTest, ExtendBoundingBoxWithPoint)
{
    Point3d p(1.0, 0.0, 0.0);
    Point3d q(-1.0, 1.0, -1.0);
    Point3d r(0.0, 0.5, 2.0);

    BoundingBox b;

    b.extend(p);
    EXPECT_EQ(p, b.pMin);
    EXPECT_EQ(p, b.pMax);

    b.extend(q);
    EXPECT_EQ(Point3d(-1.0, 0.0, -1.0), b.pMin);
    EXPECT_EQ(Point3d(1.0, 1.0, 0.0), b.pMax);

    b.extend(r);
    EXPECT_EQ(Point3d(-1.0, 0.0, -1.0), b.pMin);
    EXPECT_EQ(Point3d(1.0, 1.0, 2.0), b.pMax);
}

TEST(BoundingBoxTest, ExtendBoundingBoxWithBoundingBox)
{
    BoundingBox b(Point3d(-1.0, -1.0, -1.0), Point3d(1.0, 1.0, 1.0));
    BoundingBox c(Point3d(0.5, 0.5, 0.5), Point3d(2.0, 2.0, 2.0));

    b.extend(c);
    EXPECT_EQ(Point3d(-1.0, -1.0, -1.0), b.pMin);
    EXPECT_EQ(Point3d(2.0, 2.0, 2.0), b.pMax);

    c.extend(b);
    EXPECT_EQ(Point3d(-1.0, -1.0, -1.0), c.pMin);
    EXPECT_EQ(Point3d(2.0, 2.0, 2.0), c.pMax);
}
