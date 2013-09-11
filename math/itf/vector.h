#ifndef LB_MATH_VECTOR_H
#define LB_MATH_VECTOR_H

namespace lb {
namespace math {

class Vector
{
    public:
        /// Constructor.
        ///
        /// \param ax x component of the vector
        /// \param ay y component of the vector
        /// \param az z component of the vector
        Vector(float ax = 0, float ay = 0, float az = 0);

        /// Adds the vector \a v to this vector and returns the result vector.
        ///
        /// \param v vector to add to this vector
        /// \returns the vector that results from adding v to this vector
        Vector operator+(Vector const &v) const;

        /// Adds the vector \a v to this vector.
        ///
        /// \param v vector to add to this vector
        /// \returns a reference to this vector after adding vector \a v
        Vector &operator+=(Vector const &v);

        /// Scales this vector by a factor \a f and returns the result vector.
        ///
        /// \param f factor to scale this vector with
        /// \returns the vector that results from scaling this vector with \a f
        Vector operator*(float f) const;

        /// Scales this vector by a factor \a f and returns a reference to itself.
        ///
        /// \param f factor to scale this vector with
        /// \returns a reference to this vector after scaling it by a factor \a f
        Vector &operator*=(float f);

        /// Divides this vector by a factor \a f and returns the result vector.
        ///
        /// \param f factor to divide this vector with
        /// \returns the vector that results from dividing this vector with \a f
        Vector operator/(float f) const;

        /// Divides this vector by a factor \a f and returns a reference to itself.
        ///
        /// \param f factor to divide this vector with
        /// \returns a reference to this vector after dividing it by a factor \a f
        Vector &operator/=(float f);

        /// Unary negation operator.
        ///
        /// \returns a vector that points in the opposite direction of this vector
        Vector operator-() const;

        /// Calculates the length of this vector and returns it.
        ///
        /// \returns the length of this vector
        float length() const;

        /// Calculates the square of the length of this vector and returns it.
        ///
        /// \returns the square of the length of this vector
        float lengthSquared() const;

        /// Calculates a vector that points in the same direction as this vector with length 1 and returns it.
        ///
        /// \returns a vector that points in the same direction as this vector with length 1
        Vector normalize() const;

        /// X-component of the vector.
        float x;

        /// Y-component of the vector.
        float y;

        /// Z-component of the vector.
        float z;
};

}}

/// Global operator overload for scaling a vector \a v by a factor \a f.
///
/// \param f factor to scale \a v with
/// \param v vector to scale
/// \return \a v scaled with factor \a f
lb::math::Vector operator*(float f, lb::math::Vector const &v);

/// Calculates the cross product between the vectors \a v and \a w and returns
/// it.
///
/// The cross product is a vector perpendicular to both vectors \a v and \a w.
/// The direction of the cross product determines the handedness of the
/// coordinate system. Thus, the handedness of the coordinate system determines
/// the direction of the cross product. This implementation uses the definition
/// of a cross product in a left-handed coordinate system.
///
/// \param v left-hand side argument of the cross product
/// \param w right-hand side argument of the cross product
/// \returns the cross product between the vectors \a v and \a w
lb::math::Vector cross(lb::math::Vector const &v, lb::math::Vector const &w);

/// Returns the absolute value of the dot product of the two vectors \a v and \a
/// w.
///
/// \param v left-hand side argument of the dot product
/// \param w right-hand side argument of the dot product
/// \return the absolute value of the dot product of two vectors \a v and \a w
float absDot(lb::math::Vector const &v, lb::math::Vector const &w);

/// Returns the dot product of the two vectors \a v and \a w.
///
/// \param v left-hand side argument for the dot product
/// \param w right-hand side argument for the dot product
/// \returns the dot product of the two vectors \a v and \a w
float dot(lb::math::Vector const &v, lb::math::Vector const &w);

#endif
