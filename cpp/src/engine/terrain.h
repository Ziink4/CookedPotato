#pragma once

#include <engine/entity.h>
#include <engine/engine.h>
#include <engine/point.h>
#include <engine/rng.h>
#include <engine/cell.h>


#include <cstddef> // For std::size_t
#include <array> // For std::array
#include <ostream> // For operator<<
#include <memory>

namespace engine
{

using Terrain = std::array<Cell, terrain_area>;

std::ostream& operator<<(std::ostream& out, const Terrain& t) noexcept;

constexpr bool is_valid(cell_type cell) noexcept
{
	return cell < terrain_area;
}

constexpr bool is_valid(const point_type& pt) noexcept
{
	return pt.x < terrain_width && pt.y < terrain_height;
}

constexpr point_type::value_type get_x(cell_type cell) noexcept
{
	return cell % terrain_width;
}

constexpr point_type::value_type get_y(cell_type cell) noexcept
{
	return cell / terrain_width;
}

constexpr point_type get_pt(cell_type cell) noexcept
{
	return {get_x(cell), get_y(cell)};
}

constexpr cell_type get_cell(const point_type& pt) noexcept
{
	return pt.x + pt.y * terrain_width;
}

Terrain generate_terrain(RandomNumberGenerator& rng) noexcept;

std::vector<std::vector<cell_type>> split_field(Terrain& t, std::size_t parts) noexcept;

} // namespace engine
