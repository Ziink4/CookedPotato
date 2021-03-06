#pragma once

#include <engine/size.h>
#include <engine/point.h>

#include <optional>

namespace engine
{

struct CardinalDirections
{
    std::optional<point> north;
    std::optional<point> east;
    std::optional<point> south;
    std::optional<point> west;
};

constexpr bool operator==(const CardinalDirections & lhs, const CardinalDirections & rhs) noexcept
{
    return (lhs.north == rhs.north)
        && (lhs.east == rhs.east)
        && (lhs.south == rhs.south)
        && (lhs.west == rhs.west);
}

constexpr bool operator!=(const CardinalDirections & lhs, const CardinalDirections & rhs) noexcept
{
    return !(lhs == rhs);
}

inline std::ostream & operator<<(std::ostream & out, const CardinalDirections & d) noexcept
{
    out << "Directions(";
    if (d.north) out << "north = " << *d.north;
    out << ", ";
    if (d.east) out << "east = " << *d.east;
    out << ", ";
    if (d.south) out << "south = " << *d.south;
    out << ", ";
    if (d.west) out << "west = " << *d.west;
    out << ")";
    return out;
}

constexpr CardinalDirections get_directions(const point & pt, const size & sz) noexcept
{
    /* The map can be split into different cell types depending on the oddity of the height
        * With even height
        * 1 2 2 2
        *  4 4 4 5
        * 3 4 4 4
        *  6 6 6 7
        *
        * 1 2 2 2 2
        *  4 4 4 4 5
        * 3 4 4 4 4
        *  6 6 6 6 7
        *
        * With odd height
        * 1 2 2 2
        *  4 4 4 5
        * 3 4 4 4
        *  4 4 4 5
        * 8 6 6 6
        *
        * 1 2 2 2 2
        *  4 4 4 4 5
        * 3 4 4 4 4
        *  4 4 4 4 5
        * 8 6 6 6 6
        *
        * There are 8 different types of cell :
        * 1 = East only
        * 2 = South and East only
        * 3 = North and East only
        * 4 = 4-Way
        * 5 = West and South only
        * 6 = West and North only
        * 7 = West only
        * 8 = North only
        *
        * There is no South only cells because of the way the terrain is setup.
        */

    if (pt.y == 0)
    {
        // East only (1)
        if (pt.x == 0) return {std::nullopt, {{pt.x, pt.y + 1}}, std::nullopt, std::nullopt};
        // South and East only (2)
        return {std::nullopt, {{pt.x, pt.y + 1}}, {{pt.x - 1, pt.y + 1}}, std::nullopt};
    }

    if (pt.y == sz.height - 1)
    {
        if (sz.height % 2 == 0)
        {
            // West only (7)
            if (pt.x == sz.width - 1) return {std::nullopt, std::nullopt, std::nullopt, {{pt.x, pt.y - 1}}};
            // West and North only (6)
            return {{{pt.x + 1, pt.y - 1}}, std::nullopt, std::nullopt, {{pt.x, pt.y - 1}}};
        }

        if (sz.height % 2 == 1)
        {
            // North only (8)
            if (pt.x == 0) return {{{pt.x, pt.y - 1}}, std::nullopt, std::nullopt, std::nullopt};
            // West and North only (6)
            return {{{pt.x, pt.y - 1}}, std::nullopt, std::nullopt, {{pt.x - 1, pt.y - 1}}};

        }
    }

    if (pt.y % 2 == 0)
    {
        // North and East only (3)
        if (pt.x == 0) return {{{pt.x, pt.y - 1}}, {{pt.x, pt.y + 1}}, std::nullopt, std::nullopt};
        // 4-Way (4)
        return {{{pt.x, pt.y - 1}}, {{pt.x, pt.y + 1}}, {{pt.x - 1, pt.y + 1}}, {{pt.x - 1, pt.y - 1}}};
    }

    if (pt.y % 2 == 1)
    {
        // West and South only (5)
        if (pt.x == sz.width - 1) return {std::nullopt, std::nullopt, {{pt.x, pt.y + 1}}, {{pt.x, pt.y - 1}}};
        // 4-Way (4)
        return {{{pt.x + 1, pt.y - 1}}, {{pt.x + 1, pt.y + 1}}, {{pt.x, pt.y + 1}}, {{pt.x, pt.y - 1}}};
    }

    // We should not ever get here
    return {std::nullopt, std::nullopt, std::nullopt, std::nullopt};
}

constexpr CardinalDirections get_directions_2(const point & pt, const size & sz) noexcept
{
    CardinalDirections d;

    if (pt.y % 2 == 0)
    {
        d = { {{pt.x, pt.y - 1}}, {{pt.x, pt.y + 1}}, {{pt.x - 1, pt.y + 1}}, {{pt.x - 1, pt.y - 1}} };

        if (pt.x == 0)
        {
            d.south.reset();
            d.west.reset();
        }
    }
    else // pt.y % 2 == 1
    {
        d = { {{pt.x + 1, pt.y - 1}}, {{pt.x + 1, pt.y + 1}}, {{pt.x, pt.y + 1}}, {{pt.x, pt.y - 1}} };

        if (pt.x == sz.width - 1)
        {
            d.north.reset();
            d.east.reset();
        }
    }

    if (pt.y == 0)
    {
        d.north.reset();
        d.west.reset();
    }

    if (pt.y == sz.height - 1)
    {
        d.east.reset();
        d.south.reset();
    }

    return d;
}

} // namespace engine
