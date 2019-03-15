/// @file vector.h

#pragma once

#include <array>

namespace engine
{
/// A 2D vector
/// @tparam CoordinateType The type of the coordinates.
template <class CoordinateType>
class vector_2d
{
public:
    /// Creates an empty @ref vector_2d.
    constexpr vector_2d() = default;

    /// Creates and initializes a @ref vector_2d.
    /// @param v0 Initialization value of the first coordinate.
    /// @param v1 Initialization value of the second coordinate.
    constexpr vector_2d(const CoordinateType & v0, const CoordinateType & v1) : m_values{ v0, v1 } {};

    /// Element-wise equality check.
    /// @param lhs Left operand.
    /// @param rhs Right operand.
    /// @return true if all the coordinates are identical, false otherwise.
    friend constexpr bool operator==(const vector_2d & lhs, const vector_2d & rhs) noexcept { return (lhs.m_values[0] == rhs.m_values[0]) && (lhs.m_values[1] == rhs.m_values[1]); }

    /// Element-wise inequality check.
    /// @param lhs Left operand.
    /// @param rhs Right operand.
    /// @return true if one or more of the coordinates are not identical, false otherwise.
    friend constexpr bool operator!=(const vector_2d & lhs, const vector_2d & rhs) noexcept { return !(lhs == rhs); }

    /// Element-wise addition.
    /// @param lhs Left operand.
    /// @param rhs Right operand.
    /// @return A new @ref vector_2d with the result of the addition.
    friend constexpr vector_2d operator+(const vector_2d & lhs, const vector_2d & rhs) noexcept { return { lhs.m_values[0] + rhs.m_values[0], lhs.m_values[1] + rhs.m_values[1] }; }
    
    /// Element-wise substraction.
    /// @param lhs Left operand.
    /// @param rhs Right operand.
    /// @return A new @ref vector_2d with the result of the substraction.
    friend constexpr vector_2d operator-(const vector_2d & lhs, const vector_2d & rhs) noexcept { return { lhs.m_values[0] - rhs.m_values[0], lhs.m_values[1] - rhs.m_values[1] }; }

    /// Scalar multiplication.
    /// @param val A scalar (of type @ref CoordinateType) to multiply the @ref vector_2d with.
    /// @param rhs A @ref vector_2d.
    /// @return A new @ref vector_2d with the result of the multiplication.
    friend constexpr vector_2d operator*(const CoordinateType & val, const vector_2d & rhs) noexcept { return { val * rhs.m_values[0], val * rhs.m_values[1] }; }

    /// Scalar multiplication.
    /// @param lhs A @ref vector_2d.
    /// @param val A scalar (of type @ref CoordinateType) to multiply the @ref vector_2d with.
    /// @return A new @ref vector_2d with the result of the multiplication.
    friend constexpr vector_2d operator*(const vector_2d & lhs, const CoordinateType & val) noexcept { return val * lhs; }

    /// Scalar division.
    /// @param val A scalar (of type @ref CoordinateType) to divide the @ref vector_2d with.
    /// @param rhs A @ref vector_2d.
    /// @return A new @ref vector_2d with the result of the division.
    friend constexpr vector_2d operator/(const CoordinateType & val, const vector_2d & rhs) noexcept { return { val / rhs.m_values[0], val / rhs.m_values[1] }; }

    /// Scalar division.
    /// @param lhs A @ref vector_2d.
    /// @param val A scalar (of type @ref CoordinateType) to divide the @ref vector_2d with.
    /// @return A new @ref vector_2d with the result of the division.
    friend constexpr vector_2d operator/(const vector_2d & lhs, const CoordinateType & val) noexcept { return { lhs.m_values[0] / val, lhs.m_values[1] / val }; }

    /// Hadamard (element-wise) product.
    /// @param lhs Left operand.
    /// @param rhs Right operand.
    /// @return A new @ref vector_2d with its coordinates resulting of the element-wise multiplication of the parameters.
    friend constexpr vector_2d hadamard_product(const vector_2d & lhs, const vector_2d & rhs) noexcept { return { lhs.m_values[0] * rhs.m_values[0], lhs.m_values[1] * rhs.m_values[1] }; }
    
    /// Stream output.
    /// @param out The output stream.
    /// @param vec The vector to output.
    /// @return The modified output stream.
    friend std::ostream & operator<<(std::ostream & out, const vector_2d & vec) noexcept { return out << "vector_2d(" << vec.m_values[0] << ", " << vec.m_values[1] << ")"; }

protected:
    /// The actual values
    CoordinateType m_values[2];
};

/// A 2D vector in cartesian space.
/// @tparam CoordinateType The type of the coordinates.
template <class CoordinateType>
class cartesian_vector_2d : public vector_2d<CoordinateType>
{
public:
    using vector_2d<CoordinateType>::vector_2d;

    /// Gets the x coordinate.
    /// @return The x coordinate.
    constexpr const CoordinateType & x() const noexcept { return m_values[0]; }

    /// Gets the y coordinate.
    /// @return The y coordinate.
    constexpr const CoordinateType & y() const noexcept { return m_values[1]; }

    /// Sets a new x coordinate.
    /// @param x The new coordinate.
    constexpr void x(const CoordinateType & x) noexcept { m_values[0] = x; }

    /// Sets a new y coordinate.
    /// @param y The new coordinate.
    constexpr void y(const CoordinateType & y) noexcept { m_values[1] = y; }
};

/// A 2D vector in polar space.
/// @tparam CoordinateType The type of the coordinates.
template <class CoordinateType>
class polar_vector_2d : public vector_2d<CoordinateType>
{
public:
    using vector_2d<CoordinateType>::vector_2d;

    /// Gets the rho coordinate.
    /// @return The rho coordinate.
    constexpr const CoordinateType & rho() const noexcept { return m_values[0]; }

    /// Gets the theta coordinate.
    /// @return The theta coordinate.
    constexpr const CoordinateType & theta() const noexcept { return m_values[1]; }

    /// Sets a new rho coordinate.
    /// @param rho The new coordinate.
    constexpr void rho(const CoordinateType & rho) noexcept { m_values[0] = rho; }

    /// Sets a new theta coordinate.
    /// @param theta The new coordinate.
    constexpr void theta(const CoordinateType & theta) noexcept { m_values[1] = theta; }
};

/// Converts a @ref cartesian_vector_2d to a @ref polar_vector_2d.
/// @tparam CoordinateType The type of the coordinates.
/// @param vec The @ref cartesian_vector_2d to convert.
/// @return A new @ref polar_vector_2d representing @ref vec in polar space.
template <class CoordinateType>
constexpr polar_vector_2d<CoordinateType> to_polar(cartesian_vector_2d<CoordinateType> vec) noexcept
{
    // TODO : Implement this
    return { vec.x(), vec.y() };
}

/// Converts a @ref polar_vector_2d to a @ref cartesian_vector_2d.
/// @tparam CoordinateType The type of the coordinates.
/// @param vec The @ref polar_vector_2d to convert.
/// @return A new @ref cartesian_vector_2d representing @ref vec in cartesian space.
template <class CoordinateType>
constexpr cartesian_vector_2d<CoordinateType> to_cartesian(polar_vector_2d<CoordinateType> vec) noexcept
{
    // TODO : Implement this
    return { vec.rho(), vec.theta() };
}

} // namespace engine