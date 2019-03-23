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
    /// Creates and initializes a @ref vector_2d.
    /// @param v0 Initialization value of the first coordinate.
    /// @param v1 Initialization value of the second coordinate.
    constexpr vector_2d(const CoordinateType & v0, const CoordinateType & v1) noexcept : m_values{ v0, v1 } {};

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

    /// Stream output.
    /// @param out The output stream.
    /// @param vec The vector to output.
    /// @return The modified output stream.
    friend std::ostream & operator<<(std::ostream & out, const vector_2d & vec) noexcept { return out << "vector_2d(" << vec.m_values[0] << ", " << vec.m_values[1] << ")"; }

protected:
    /// Default constructor
    constexpr vector_2d() noexcept = default;

    /// The actual values
    CoordinateType m_values[2];
};

/// A 2D vector in cartesian space.
/// @tparam CoordinateType The type of the coordinates.
template <class CoordinateType>
class cartesian_vector_2d : public vector_2d<CoordinateType>
{
public:
    /// Creates and initializes a @ref cartesian_vector_2d.
    /// @param v0 Initialization value of the first coordinate.
    /// @param v1 Initialization value of the second coordinate.
    constexpr explicit cartesian_vector_2d(const CoordinateType & v0, const CoordinateType & v1) noexcept : vector_2d{ v0, v1 } {};

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

/// Cartesian vector magnitude.
/// @tparam CoordinateType The type of the coordinates.
/// @param vec The @ref cartesian_vector_2d to calculate the magnitude of.
/// @return The magnitude of the @ref cartesian_vector_2d.
template <class CoordinateType>
CoordinateType magnitude(const cartesian_vector_2d<CoordinateType> & vec) noexcept { return static_cast<CoordinateType>(std::sqrt(vec.x() * vec.x() + vec.y() * vec.y())); }

/// The Pi constant
const double pi = std::acos(-1.0);

/// A 2D vector in polar space.
/// @tparam CoordinateType The type of the coordinates.
template <class CoordinateType>
class polar_vector_2d : public vector_2d<CoordinateType>
{
public:
    /// Creates and initializes a @ref polar_vector_2d.
    /// @param v0 Initialization value of the first coordinate.
    /// @param v1 Initialization value of the second coordinate.
    explicit polar_vector_2d(const CoordinateType & v0, const CoordinateType & v1) noexcept
    {
        rho(v0);
        theta(v1);
    }

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
    void theta(const CoordinateType & theta) noexcept { m_values[1] = std::fmod(theta, (2 * pi)); }
};

/// Polar vector magnitude.
/// @tparam CoordinateType The type of the coordinates.
/// @param vec The @ref polar_vector_2d to calculate the magnitude of.
/// @return The magnitude of the @ref polar_vector_2d.
template <class CoordinateType>
CoordinateType magnitude(const polar_vector_2d<CoordinateType> & vec) noexcept { return std::abs(vec.rho()); }

/// Converts a @ref cartesian_vector_2d to a @ref polar_vector_2d.
/// @tparam CoordinateType The type of the coordinates.
/// @param vec The @ref cartesian_vector_2d to convert.
/// @return A new @ref polar_vector_2d representing @ref vec in polar space.
template <class CoordinateType>
polar_vector_2d<CoordinateType> to_polar(const cartesian_vector_2d<CoordinateType> & vec) noexcept
{
    const CoordinateType rho = magnitude(vec);
    const CoordinateType theta = std::atan2(vec.y(), vec.x());
    return polar_vector_2d{ rho, theta };
}

/// Converts a @ref polar_vector_2d to a @ref cartesian_vector_2d.
/// @tparam CoordinateType The type of the coordinates.
/// @param vec The @ref polar_vector_2d to convert.
/// @return A new @ref cartesian_vector_2d representing @ref vec in cartesian space.
template <class CoordinateType>
cartesian_vector_2d<CoordinateType> to_cartesian(const polar_vector_2d<CoordinateType> & vec) noexcept
{
    const CoordinateType x = vec.rho() * std::cos(vec.theta());
    const CoordinateType y = vec.rho() * std::sin(vec.theta());
    return cartesian_vector_2d{ x, y };
}

/// Cartesian vector specialization for integer type.
using car_vec2i = cartesian_vector_2d<int>;

/// Cartesian vector specialization for unsigned integer type.
using car_vec2u = cartesian_vector_2d<unsigned int>;

/// Cartesian vector specialization for single-precision floating point type.
using car_vec2f = cartesian_vector_2d<float>;

/// Cartesian vector specialization for double-precision floating point type.
using car_vec2d = cartesian_vector_2d<double>;

/// Polar vector specialization for single-precision floating point type.
using pol_vec2f = polar_vector_2d<float>;

/// Polar vector specialization for double-precision floating point type.
using pol_vec2d = polar_vector_2d<double>;

} // namespace engine