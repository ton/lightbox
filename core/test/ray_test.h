#include "core/itf/ray.h"
#include "core/itf/triangle.h"

#include "math/itf/vector.h"

#include "tests/base_test.h"

#include <gtest/gtest.h>
#include <fstream>

using namespace lb;
using namespace lb::math;

class TriangleIntersectionTest: public ::testing::TestWithParam<IntersectionMethod>
{
    protected:
        TriangleIntersectionTest(): triangle_(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0.25)) { };

        Triangle triangle_;
};

INSTANTIATE_TEST_CASE_P(RayTest, TriangleIntersectionTest, ::testing::Values(
            &lb::Ray::intersectsDidierBadouel,
            &lb::Ray::intersectsGeometrically,
            &lb::Ray::intersectsMollerTrumbore));

/// Tests various scenarios where a ray and triangle do not intersect.
TEST_P(TriangleIntersectionTest, TestNoIntersection)
{
    Ray ray(Point(0.0, 0.1, 1.0), Vector(0.0, 0.0, 1.0));
    EXPECT_FALSE((ray.*GetParam())(triangle_));
}

/// Tests that a ray shooting through the triangle intersects it.
TEST_P(TriangleIntersectionTest, TestIntersection)
{
    Ray ray(Point(0.1, 0.1, 1.0), Vector(0.1, 0.1, -1.0));
    EXPECT_TRUE((ray.*GetParam())(triangle_));
}

/// Tests that a ray running through an edge of the triangle intersects it.
TEST_P(TriangleIntersectionTest, TestIntersectionEdge)
{
    Ray ray(Point(0.0, 0.1, 1.0), Vector(0.0, 0.0, -1.0));
    EXPECT_TRUE((ray.*GetParam())(triangle_));
}

/// Tests that a ray running through a vertex of a triangle intersects it.
TEST_P(TriangleIntersectionTest, TestIntersectionPoint)
{
    Ray ray(Point(0.0, 0.0, 1.0), Vector(0.0, 0.0, -1.0));
    EXPECT_TRUE((ray.*GetParam())(triangle_));
}

/// Tests that a ray that originates on the triangle intersects it.
TEST_P(TriangleIntersectionTest, TestRayOriginOnTriangle)
{
    Ray ray(Point(0.2, 0.0, 0.0), Vector(0.0, 0.0, -1.0));
    EXPECT_TRUE((ray.*GetParam())(triangle_));
}

/// Tests that a ray that runs through the triangle does not intersect it.
TEST_P(TriangleIntersectionTest, TestParallelRay)
{
    Ray ray(Point(0.5, 0.0, 0.0), Vector(0, 1, 0.25));
    EXPECT_FALSE((ray.*GetParam())(triangle_));
}

/// Tests that intersecting a backfacing triangle does not result in an
/// intersection.
TEST_P(TriangleIntersectionTest, TestCulling)
{
    Ray ray(Point(0.5, 0.0, -1.0), Vector(0.1, 0.1, 1.0));
    EXPECT_FALSE((ray.*GetParam())(triangle_));
}
