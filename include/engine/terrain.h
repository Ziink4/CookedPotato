#pragma once

#include <engine/rng.h>
#include <engine/point.h>
#include <engine/entity.h>

#include <array>
#include <ostream>
#include <optional>

namespace engine
{

template <unsigned width, unsigned height>
class GenericTerrain
{
public:
    using element_type = Entity;

    std::array<std::unique_ptr<element_type>, width * height> elements;

    const auto at(const point & pt) const noexcept
    {
        return elements.at(pt.x + pt.y * width).get();
    }

    void place_entity(std::unique_ptr<element_type>&& other, const point & pt)
    {
        elements.at(pt.x + pt.y * width) = std::move(other);
    }

    void remove_entity(const point & pt)
    {
        elements.at(pt.x + pt.y * width).reset();
    }

    auto begin() { return elements.begin(); }
    auto cbegin() const { return elements.cbegin(); }

    auto end() { return elements.end(); }
    auto cend() const { return elements.cend(); }

	CardinalDirections neighbors(const point & pt) const noexcept
	{
		return get_directions_2(pt);
	}
};

constexpr unsigned terrain_width = 10;
constexpr unsigned terrain_height = 20;
constexpr unsigned terrain_area = terrain_width * terrain_height;

class Terrain : public GenericTerrain<terrain_width, terrain_height> {};

std::ostream & operator<<(std::ostream & out, const Terrain & t) noexcept;

} // namespace engine
