#pragma once

#include <iostream>

namespace engine
{

template <class T>
struct Point
{
	using value_type = T;

	T x;
	T y;

	constexpr bool operator==(const Point& other) const noexcept
	{
		return x == other.x && y == other.y;
	}
};

template <class T>
std::ostream& operator<<(std::ostream& out, const Point<T>& pt) noexcept
{
	    return out << "Point(" << pt.x << ", " << pt.y << ")";
}

} // namespace engine
