#include "math/itf/matrix4x4.h"

#include <gtest/gtest.h>

using namespace lb;

/// Tests constructing a matrix given an axis of rotation and a rotation
/// angle.
TEST(Matrix4x4Test, TestMatrixConstruction)
{
    // Test default constructing a matrix.
    {
        Matrix4x4 m;

        // Default construction results in an identity matrix.
        EXPECT_EQ(1.0, m(0, 0));
        EXPECT_EQ(1.0, m(1, 1));
        EXPECT_EQ(1.0, m(2, 2));
        EXPECT_EQ(1.0, m(3, 3));

        EXPECT_EQ(0.0, m(0, 1));
        EXPECT_EQ(0.0, m(0, 2));
        EXPECT_EQ(0.0, m(0, 3));

        EXPECT_EQ(0.0, m(1, 0));
        EXPECT_EQ(0.0, m(1, 2));
        EXPECT_EQ(0.0, m(1, 3));

        EXPECT_EQ(0.0, m(2, 0));
        EXPECT_EQ(0.0, m(2, 1));
        EXPECT_EQ(0.0, m(2, 3));

        EXPECT_EQ(0.0, m(3, 0));
        EXPECT_EQ(0.0, m(3, 1));
        EXPECT_EQ(0.0, m(3, 2));
    }

    // Test constructing a matrix from a two-dimensional array.
    {
        double m[4][4] =
            {{0.0, 1.0, 2.0, 3.0},
             {10.0, 11.0, 12.0, 13.0},
             {20.0, 21.0, 22.0, 23.0},
             {30.0, 31.0, 32.0, 33.0}};

        Matrix4x4 n(m);

        EXPECT_EQ(m[0][0], n(0, 0));
        EXPECT_EQ(m[0][1], n(0, 1));
        EXPECT_EQ(m[0][2], n(0, 2));
        EXPECT_EQ(m[0][3], n(0, 3));

        EXPECT_EQ(m[1][0], n(1, 0));
        EXPECT_EQ(m[1][1], n(1, 1));
        EXPECT_EQ(m[1][2], n(1, 2));
        EXPECT_EQ(m[1][3], n(1, 3));

        EXPECT_EQ(m[2][0], n(2, 0));
        EXPECT_EQ(m[2][1], n(2, 1));
        EXPECT_EQ(m[2][2], n(2, 2));
        EXPECT_EQ(m[2][3], n(2, 3));

        EXPECT_EQ(m[3][0], n(3, 0));
        EXPECT_EQ(m[3][1], n(3, 1));
        EXPECT_EQ(m[3][2], n(3, 2));
        EXPECT_EQ(m[3][3], n(3, 3));
    }
}
