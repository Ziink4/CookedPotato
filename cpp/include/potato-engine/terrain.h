#pragma once

#include <potato-engine/entity.h>

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

class Terrain
{
public:
    using value_type = Entity *;

    using size_type = std::size_t;
    using point_type = Point<size_type>;

    static constexpr size_type width = 20;
    static constexpr size_type height = 40;
    static constexpr size_type area = width * height;

    using storage_type = std::array<value_type, area>;

    static constexpr bool is_valid(size_type cell) noexcept
    {
        return cell < area;
    }

    static constexpr bool is_valid(const point_type& pt) noexcept
    {
        return pt.x < width && pt.y < height;
    }

    static constexpr size_type get_x(size_type cell) noexcept
    {
        return cell % width;
    }

    static constexpr size_type get_y(size_type cell) noexcept
    {
        return cell / width;
    }

    static constexpr point_type get_pt(size_type cell) noexcept
    {
        return {get_x(cell), get_y(cell)};
    }

    static constexpr size_type get_cell(const point_type& pt) noexcept
    {
        return pt.x + pt.y * width;
    }

    constexpr storage_type& data() noexcept
    {
        return m_data;
    }

    constexpr const storage_type& data() const noexcept
    {
        return m_data;
    }

    friend std::ostream& operator<<(std::ostream& out, const Terrain& t) noexcept;

private:
    storage_type m_data;
};

} // namespace engine
