#ifndef LB_MATRIX_4X4_H
#define LB_MATRIX_4X4_H

#include <algorithm>
#include <iosfwd>

namespace lb {

/// Implements a four-by-four matrix of doubles. Supports basic matrix
/// operations like matrix multiplication, addition, and scaling. This is a
/// straightforward implementation, not using any special hardware intrinsics
/// for the moment.
struct Matrix4x4
{
public:
    /// Constructs an identity matrix.
    Matrix4x4()
        : m_{0.0}
    {
        m_[0][0] = m_[1][1] = m_[2][2] = m_[3][3] = 1.0;
    }
    /// Initializes a 4x4 matrix from the given 4-by-4 array of doubles.
    Matrix4x4(double m[4][4])
    {
        std::copy(&m[0][0], &m[0][0] + 16, &m_[0][0]);
    }

    /// Returns whether this matrix equals the given matrix \a m.
    bool operator==(const Matrix4x4& m)
    {
        return std::equal(&m_[0][0], &m_[0][0] + 16, &m.m_[0][0]);
    }

    /// Retrieves the element at row \a i, column \a j. No bounds checking is
    /// performed (zero-cost overhead abstraction).
    double operator()(int i, int j) const
    {
        return m_[i][j];
    }

private:
    /// Elements of the matrix.
    double m_[4][4];
};

std::ostream& operator<<(std::ostream& out, const Matrix4x4& m);

}

#endif
