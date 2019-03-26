#pragma once

#include <engine/rng.h>
#include <engine/point.h>
#include <engine/entity.h>
#include <engine/directions.h>

#include <array>
#include <ostream>
#include <optional>

namespace engine
{

template <unsigned TerrainWidth, unsigned TerrainHeight>
class GenericTerrain
{
public:
    std::array<std::unique_ptr<Entity>, TerrainWidth * TerrainHeight> elements;

    const Entity * const at(const point & pt) const noexcept
    {
        return elements.at(pt.x + pt.y * TerrainWidth).get();
    }

    void place_entity(std::unique_ptr<Entity>&& other, const point & pt)
    {
        elements.at(pt.x + pt.y * TerrainWidth) = std::move(other);
    }

    void remove_entity(const point & pt)
    {
        elements.at(pt.x + pt.y * TerrainWidth).reset();
    }

    auto begin() { return elements.begin(); }
    auto cbegin() const { return elements.cbegin(); }

    auto end() { return elements.end(); }
    auto cend() const { return elements.cend(); }

	constexpr CardinalDirections neighbors(const point & pt) const noexcept
	{
		return get_directions_2(pt, { TerrainWidth, TerrainHeight });
	}

	constexpr size size() const noexcept { return { TerrainWidth, TerrainHeight }; }
	constexpr unsigned width() const noexcept { return TerrainWidth; }
	constexpr unsigned height() const noexcept { return TerrainHeight; }
	constexpr unsigned area() const noexcept { return TerrainWidth * TerrainHeight; }
};

class Terrain : public GenericTerrain<10, 20> {};

std::ostream & operator<<(std::ostream & out, const Terrain & t) noexcept;

} // namespace engine
