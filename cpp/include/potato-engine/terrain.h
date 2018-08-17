#pragma once

#include <cstddef> // For std::size_t
#include <array> // For std::array
#include <unordered_set> // For std::unordered_set
#include <ostream> // For operator<<

namespace engine
{

enum class CellType
{
    empty,
    player,
    monster,
    decor,
    obstacle,
};

struct Cell
{
    CellType type;
};

struct Point
{
    std::size_t x;
    std::size_t y;

    constexpr bool operator==(const Point& other) const noexcept
    {
        return x == other.x && y == other.y;
    }

    constexpr bool operator!=(const Point& other) const noexcept
    {
        return x != other.x || y != other.y;
    }
};

namespace terrain
{

constexpr std::size_t width = 20;
constexpr std::size_t wh_ratio = 2;
constexpr std::size_t height = wh_ratio * width;
constexpr std::size_t area = width * height;

using Terrain = std::array<Cell, area>;

constexpr bool is_valid(std::size_t cell) noexcept
{
    return cell < area;
}

constexpr bool is_valid(const Point& pt) noexcept
{
    return pt.x < width && pt.y < height;
}

constexpr std::size_t get_x(std::size_t cell) noexcept
{
    return cell % width;
}

constexpr std::size_t get_y(std::size_t cell) noexcept
{
    return cell / width;
}

constexpr Point get_pt(std::size_t cell) noexcept
{
    return {get_x(cell), get_y(cell)};
}

constexpr std::size_t get_cell(const Point& pt) noexcept
{
    return pt.x + pt.y * width;
}

}

std::ostream& operator<<(std::ostream& out, const Point& pt) noexcept;

std::ostream& operator<<(std::ostream& out, const terrain::Terrain& t) noexcept;

}
