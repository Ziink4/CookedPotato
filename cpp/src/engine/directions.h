#pragma once

#include <array>
#include <optional>

#include <engine/terrain.h>
#include <engine/engine.h>

namespace engine
{

class Directions
{
public:
	struct CardinalDirections
	{
		std::optional<point_type> north;
		std::optional<point_type> east;
		std::optional<point_type> south;
		std::optional<point_type> west;
	};

	std::array<CardinalDirections, terrain_area> data;

	static constexpr CardinalDirections get_directions(point_type pt) noexcept
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
			if (pt.x == 0) return {std::nullopt, std::optional<point_type>{pt.x, pt.y + 1}, std::nullopt, std::nullopt};
			// South and East only (2)
			return {std::nullopt, std::optional<point_type>{pt.x, pt.y + 1}, std::optional<point_type>{pt.x - 1, pt.y + 1}, std::nullopt};
		}

		if (pt.y == terrain_height - 1)
		{
			if constexpr (terrain_height % 2 == 0)
			{
				// West only (7)
				if (pt.x == terrain_width - 1) return {std::nullopt, std::nullopt, std::nullopt, std::optional<point_type>{pt.x, pt.y - 1}};
				// West and North only (6)
				return {std::optional<point_type>{pt.x + 1, pt.y - 1}, std::nullopt, std::nullopt, std::optional<point_type>{pt.x, pt.y - 1}};
			}

			if constexpr (terrain_height % 2 == 1)
			{
				// North only (8)
				if (pt.x == 0) return {std::optional<point_type>{pt.x, pt.y - 1}, std::nullopt, std::nullopt, std::nullopt};
				// West and North only (6)
				return {std::optional<point_type>{pt.x, pt.y - 1}, std::nullopt, std::nullopt, std::optional<point_type>{pt.x - 1, pt.y - 1}};

			}
		}

		if (pt.y % 2 == 0)
		{
			// North and East only (3)
			if (pt.x == 0) return {std::optional<point_type>{pt.x, pt.y - 1}, std::optional<point_type>{pt.x, pt.y + 1}, std::nullopt, std::nullopt};
			// 4-Way (4)
			return {std::optional<point_type>{pt.x, pt.y - 1}, std::optional<point_type>{pt.x, pt.y + 1}, std::optional<point_type>{pt.x - 1, pt.y + 1}, std::optional<point_type>{pt.x - 1, pt.y - 1}};
		}

		if (pt.y % 2 == 1)
		{
			// West and South only (5)
			if (pt.x == terrain_width - 1) return {std::nullopt, std::nullopt, std::optional<point_type>{pt.x, pt.y + 1}, std::optional<point_type>{pt.x, pt.y - 1}};
			// 4-Way (4)
			return {std::optional<point_type>{pt.x + 1, pt.y - 1}, std::optional<point_type>{pt.x + 1, pt.y + 1}, std::optional<point_type>{pt.x, pt.y + 1}, std::optional<point_type>{pt.x, pt.y - 1}};
		}

		// We should not ever get here
		return {std::nullopt, std::nullopt, std::nullopt, std::nullopt};
	}

	constexpr Directions() noexcept
	    : data()
	{
		for (cell_type cell = 0; cell < terrain_area; ++cell)
		{
			data[cell] = get_directions(cell);
		}

	}
};

std::ostream& operator<<(std::ostream& out, const Directions::CardinalDirections& d) noexcept;

} // namespace engine
