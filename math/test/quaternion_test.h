#include "math/itf/constants.h"
#include "math/itf/quaternion.h"

#include <gtest/gtest.h>

using namespace lb;

/// Tests constructing a quaternion given an axis of rotation and a rotation
/// angle.
TEST(QuaternionTest, TestQuaternionConstruction)
{
    Vector3d v(1, 1, 1);
    Quaternion q(v.normalized(), 0.25 * lb::PI);

    // The norm of the quaternion should be 1.
    EXPECT_EQ(1.0, q.normSquared());

    // The norm of a quaternion whose axis of rotation vector is not the unit
    // vector, is not 1.
    EXPECT_NE(1.0, Quaternion(v, 0.25 * lb::PI).normSquared());
}

/// Tests the conjugate operation on a quaternion.
TEST(QuaternionTest, TestQuaternionConjugate)
{
    Vector3d v(1, 1, 1);
    Quaternion q(v.normalized(), 0.25 * lb::PI);

    Quaternion qc = q.conjugate();

    // Test that the conjugate operation was performed.
    EXPECT_EQ(q[0], qc[0]);
    EXPECT_EQ(q[1], -qc[1]);
    EXPECT_EQ(q[2], -qc[2]);
    EXPECT_EQ(q[3], -qc[3]);
}

TEST(QuaternionTest, TestQuaternionProduct)
{
    Vector3d v(1, 1, 1);

    // The product of a quaternion and its conjugate should yield 1.
    Quaternion q(v.normalized(), 0.25 * lb::PI);
    Quaternion i = q * q.conjugate();

    EXPECT_EQ(1.0, i[0]);
    EXPECT_EQ(0.0, i[1]);
    EXPECT_EQ(0.0, i[2]);
    EXPECT_EQ(0.0, i[3]);
}

TEST(QuaternionTest, TestQuaternionRotation)
{
    // Test rotation the vector (1, 0, 0) around the y-axis (0, 1, 0), by 45
    // degrees.
    Quaternion q(Vector3d{0, 1, 0}, 0.25 * lb::PI);
    Quaternion r = q * Vector3d{1, 0, 0} * q.conjugate();

    // r is a pure quaternion representing the rotated vector.
    EXPECT_EQ(0.0, r[0]);
    EXPECT_DOUBLE_EQ(0.5 * std::sqrt(2.0), r[1]);
    EXPECT_EQ(0.0, r[2]);
    EXPECT_DOUBLE_EQ(-0.5 * std::sqrt(2.0), r[3]);

    // Test that using the rotate() method yields the same result.
    Vector3d vr = q.rotate(Vector3d{1, 0, 0});
    EXPECT_EQ(r[1], vr.x);
    EXPECT_EQ(r[2], vr.y);
    EXPECT_EQ(r[3], vr.z);
}

TEST(QuaternionTest, TestQuaternionRotationComposition)
{
    // Test rotating the i-axis into a certain direction v, using tracking
    // rotations.

    // Perform two rotations over the principal axes as depicted below.
    //
    //        | y
    //        |
    //        |___ x
    //       /
    //    z /
    //
    {
        // Perform a frame rotation, such that (1, 0, 0) is transformed into (0,
        // 0, -1). First rotate over the z-axis by 90 degrees, then over the new
        // y-axis by 90 degrees.
        Quaternion p(Vector3d{0, 0, 1}, lb::PI / 2);
        Quaternion q(Vector3d{0, 1, 0}, lb::PI / 2);

        // Using a so-called frame rotation, the transformation from the new
        // coordinate frame to the reference frame is given by:
        //
        //    q*p* (0, 0, -1) pq = (pq)* (0, 0, -1) pq = (1, 0, 0)
        //
        // The transformation from the reference frame to the new coordinate
        // frame is then given by:
        //
        //   ((pq)*)* (1, 0, 0) (pq)* = pq (1, 0, 0) (pq)* = (0, 0, -1)
        //
        Quaternion pq = p * q;

        EXPECT_EQ(Vector3d(1, 0, 0), pq.conjugate().rotate(Vector3d(0, 0, -1)));
        EXPECT_EQ(Vector3d(0, 0, -1), pq.rotate(Vector3d(1, 0, 0)));
    }

    {
        // Perform a frame rotation, such that (1, 0, 0) is transformed into (0,
        // 1, 0). First, rotate over the y-axis by -90 degrees, then over the
        // new z-axis by 90 degrees.
        Quaternion p(Vector3d{0, 1, 0}, -lb::PI / 2);
        Quaternion q(Vector3d{0, 0, 1}, lb::PI / 2);

        // For details, see above.
        Quaternion pq = p * q;

        EXPECT_EQ(Vector3d(1, 0, 0), pq.conjugate().rotate(Vector3d(0, 1, 0)));
        EXPECT_EQ(Vector3d(0, 1, 0), pq.rotate(Vector3d(1, 0, 0)));
    }
}
