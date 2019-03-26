#pragma once

#include <ostream>

namespace engine
{

struct point
{
	unsigned x;
	unsigned y;
};

constexpr bool operator==(const point & a, const point & b) noexcept
{
	return (a.x == b.x) && (a.y == b.y);
}

inline std::ostream & operator<<(std::ostream & out, const point & pt) noexcept
{
    return out << "point(" << pt.x << ", " << pt.y << ")";
}

} // namespace engine
