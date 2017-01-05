#ifndef LB_MATH_QUATERNION_H
#define LB_MATH_QUATERNION_H

#include <cassert>
#include <ostream>

namespace lb {

/// Represents a quaternion, represented as a four-tuple:
///
///    q = (w, x, y, z)
///
/// where (x, y, z) together form a vector in R3. An alternative notation is:
///
///    q = (w, v)
///
/// In general, a quaternion can be represented as follows:
///
///    q = cos(a) + sin(a)v
///
/// where v is a unit vector representing the axis of rotation, and a is the
/// angle of rotation in radians. We store the four-tuple representing the
/// quaternion given above for an axis and angle of rotation specified by the
/// user.
struct Quaternion
{
public:
    /// Constructs a quaternion, given an axis of rotation, and a rotation
    /// angle.
    Quaternion(const Vector3d& v, double a)
    {
        double s = std::sin(0.5 * a);

        q[0] = std::cos(0.5 * a);
        q[1] = v.x * s;
        q[2] = v.y * s;
        q[3] = v.z * s;
    }

    /// Constructs a quaternion from the give 4-tuple.
    Quaternion(double q0, double q1, double q2, double q3):
        q{q0, q1, q2, q3}
    {
    }

    /// Constructs a quaternion from the given quaternion.
    Quaternion(const Quaternion& rhs)
    {
        std::copy(rhs.q, rhs.q + 4, q);
    }

    /// Returns the complex conjugate quaternion.
    Quaternion conjugate() const
    {
        return Quaternion{q[0], -q[1], -q[2], -q[3]};
    }

    /// Returns the squared norm of this quaternion (similar to the squared
    /// length of a vector).
    double normSquared() const
    {
        return q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
    }

    /// Calculates the quaternion product of this quaternion with the given
    /// quaternion.
    Quaternion operator*(const Quaternion& rhs) const
    {
        // The product of two quaternions p and q, with:
        //
        //      p = (p0, v),
        //      q = (q0, w)
        //
        // is defined as:
        //
        //      p0q0 - v . w + p0w + q0v + v x w
        //
        // Note: only 16 multiplications, contrary to 27 when using matrix
        // algebra!
        return {
            q[0] * rhs.q[0] - q[1] * rhs.q[1] - q[2] * rhs.q[2] - q[3] * rhs.q[3],
            q[0] * rhs.q[1] + rhs.q[0] * q[1] + q[2] * rhs.q[3] - q[3] * rhs.q[2],
            q[0] * rhs.q[2] + rhs.q[0] * q[2] - q[1] * rhs.q[3] + q[3] * rhs.q[1],
            q[0] * rhs.q[3] + rhs.q[0] * q[3] + q[1] * rhs.q[2] - q[2] * rhs.q[1]
        };
    }

    /// Calculates the quaternion product of this quaternion with the given
    /// vector from R3. The vector is treated as a pure quaternion, i.e., a
    /// quaternion for which the real part is zero.
    Quaternion operator*(const Vector3d& v) const
    {
        // See quaternion product above for the definition of the quaternion
        // product. Note that v is treated as the quaterion q = (0, v).
        return {
            -q[1] * v.x - q[2] * v.y - q[3] * v.z,
            q[0] * v.x + q[2] * v.z - q[3] * v.y,
            q[0] * v.y - q[1] * v.z + q[3] * v.x,
            q[0] * v.z + q[1] * v.y - q[2] * v.x,
        };
    }

    /// Rotates the given input vector using this quaternion, evaluates the
    /// quaternion products qvq*, where q* is the conjugate of q, and returns
    /// the vector part of the resulting pure quaternion.
    Vector3d rotate(const Vector3d& v) const
    {
        Quaternion pure = (*this) * v * conjugate();
        return {pure[1], pure[2], pure[3]};
    }

    /// Convenience operator, access the i-th value of this quaternion.
    double operator[](int i) const
    {
        assert(i >= 0 && i < 4);
        return q[i];
    }

private:
    /// Four-tuple representing the quaterion.
    double q[4];
};

std::ostream& operator<<(std::ostream& os, const Quaternion& q)
{
    return os << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3];
}

}

#endif
