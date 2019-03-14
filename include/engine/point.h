#pragma once

#include <ostream>

namespace engine
{

template <class T>
struct point
{
	T x;
	T y;
};

template <class T>
constexpr bool operator==(const point<T> & a, const point<T> & b) noexcept
{
    return (a.x == b.x) && (a.y == b.y);
}

template <class T>
std::ostream & operator<<(std::ostream & out, const point<T> & pt) noexcept
{
        return out << "point(" << pt.x << ", " << pt.y << ")";
}

} // namespace engine
