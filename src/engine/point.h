#pragma once

#include <iostream>

namespace engine
{

template <class T>
struct Point
{
	T x;
	T y;
};

template <class T>
constexpr bool operator ==(const Point<T>& a, const Point<T>& b) noexcept
{
	return (a.x == b.x) && (a.y == b.y);
}

template <class T>
constexpr bool operator !=(const Point<T>& a, const Point<T>& b) noexcept
{
	return (a.x != b.x) || (a.y != b.y);
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Point<T>& pt) noexcept
{
	    return out << "Point(" << pt.x << ", " << pt.y << ")";
}

} // namespace engine
