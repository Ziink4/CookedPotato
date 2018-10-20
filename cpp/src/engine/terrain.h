#pragma once

#include <engine/entity.h>
#include <engine/engine.h>
#include <engine/point.h>
#include <engine/rng.h>
#include <engine/cell.h>

#include <cstddef> // For std::size_t
#include <array> // For std::array
#include <ostream> // For operator<<

namespace engine
{

template <std::size_t width, std::size_t height>
class GenericTerrain
{
    using element_type = Entity;

    using point_type = Point<std::size_t>;

    std::array<std::unique_ptr<element_type>, width * height> elements;

	static bool is_valid(point_type pt) noexcept
	{
		return pt.x < width && pt.y < height;
	}

	const Entity* get_element(point_type pt) const noexcept
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


};

constexpr std::size_t terrain_width = 10;
constexpr std::size_t terrain_height = 20;
constexpr std::size_t terrain_area = terrain_width * terrain_height;

using Terrain = GenericTerrain<terrain_width, terrain_height>;

std::ostream& operator<<(std::ostream& out, const Terrain& t) noexcept;

Terrain generate_terrain(RandomNumberGenerator& rng) noexcept;

std::vector<std::vector<cell_type>> split_field(Terrain& t, std::size_t parts) noexcept;

} // namespace engine
