#pragma once

#include <ostream>

namespace engine
{

struct point
{
    unsigned x;
    unsigned y;
};

constexpr bool operator==(const point & lhs, const point & rhs) noexcept
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

constexpr bool operator!=(const point & lhs, const point & rhs) noexcept
{
    return !(lhs == rhs);
}

inline std::ostream & operator<<(std::ostream & out, const point & pt) noexcept
{
    return out << "point(" << pt.x << ", " << pt.y << ")";
}

} // namespace engine
