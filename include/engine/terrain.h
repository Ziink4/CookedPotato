#pragma once

#include "entity.h"
#include "point.h"

#include "rng.h"

#include <array>
#include <ostream>
#include <optional>


namespace engine
{

struct CardinalDirections
{
    std::optional<point<std::size_t>> north;
    std::optional<point<std::size_t>> east;
    std::optional<point<std::size_t>> south;
    std::optional<point<std::size_t>> west;

    bool operator==(const CardinalDirections & other) const noexcept
    {
        return (north == other.north)
            && (east == other.east)
            && (south == other.south)
            && (west == other.west);
    }
};


template <std::size_t width, std::size_t height>
class GenericTerrain
{
public:
    using element_type = Entity;

    using point_type = point<std::size_t>;

    std::array<std::unique_ptr<element_type>, width * height> elements;

    const auto at(point_type pt) const noexcept
    {
        return elements.at(pt.x + pt.y * width).get();
    }

    void place_entity(std::unique_ptr<element_type>&& other, point_type pt)
    {
        elements.at(pt.x + pt.y * width) = std::move(other);
    }

    void remove_entity(point_type pt)
    {
        elements.at(pt.x + pt.y * width).reset();
    }

    auto begin() { return elements.begin(); }
    auto cbegin() const { return elements.cbegin(); }

    auto end() { return elements.end(); }
    auto cend() const { return elements.cend(); }

    CardinalDirections neighbors(point_type pt) const noexcept
    {
        CardinalDirections d;

        if (pt.y % 2 == 0)
        {
            d = {{{pt.x, pt.y - 1}}, {{pt.x, pt.y + 1}}, {{pt.x - 1, pt.y + 1}}, {{pt.x - 1, pt.y - 1}}};

            if (pt.x == 0)
            {
                d.south.reset();
                d.west.reset();
            }
        }
        else
        {
            d = {{{pt.x + 1, pt.y - 1}}, {{pt.x + 1, pt.y + 1}}, {{pt.x, pt.y + 1}}, {{pt.x, pt.y - 1}}};

            if (pt.x == width - 1)
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

        if (pt.y == height - 1)
        {
            d.east.reset();
            d.south.reset();
        }

        return d;
    }
};

constexpr std::size_t terrain_width = 10;
constexpr std::size_t terrain_height = 20;
constexpr std::size_t terrain_area = terrain_width * terrain_height;

using Terrain = GenericTerrain<terrain_width, terrain_height>;

std::ostream & operator<<(std::ostream & out, const Terrain & t) noexcept;

} // namespace engine
