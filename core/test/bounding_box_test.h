#include "core/itf/bounding_box.h"

#include <gtest/gtest.h>

using namespace lb;
using namespace lb::math;

TEST(BoundingBoxTest, ExtendBoundingBoxWithPoint)
{
    Point p(1.0, 0.0, 0.0);
    Point q(-1.0, 1.0, -1.0);
    Point r(0.0, 0.5, 2.0);

    BoundingBox b;

    b.extend(p);
    EXPECT_EQ(p, b.pMin);
    EXPECT_EQ(p, b.pMax);

    b.extend(q);
    EXPECT_EQ(Point(-1.0, 0.0, -1.0), b.pMin);
    EXPECT_EQ(Point(1.0, 1.0, 0.0), b.pMax);

    b.extend(r);
    EXPECT_EQ(Point(-1.0, 0.0, -1.0), b.pMin);
    EXPECT_EQ(Point(1.0, 1.0, 2.0), b.pMax);
}

TEST(BoundingBoxTest, ExtendBoundingBoxWithBoundingBox)
{
    BoundingBox b(Point(-1.0, -1.0, -1.0), Point(1.0, 1.0, 1.0));
    BoundingBox c(Point(0.5, 0.5, 0.5), Point(2.0, 2.0, 2.0));

    b.extend(c);
    EXPECT_EQ(Point(-1.0, -1.0, -1.0), b.pMin);
    EXPECT_EQ(Point(2.0, 2.0, 2.0), b.pMax);

    c.extend(b);
    EXPECT_EQ(Point(-1.0, -1.0, -1.0), c.pMin);
    EXPECT_EQ(Point(2.0, 2.0, 2.0), c.pMax);
}
