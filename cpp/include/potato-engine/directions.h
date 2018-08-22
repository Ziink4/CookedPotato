#pragma once

#include <array>

#include <potato-engine/terrain.h>
#include <potato-engine/engine.h>

namespace engine
{

class Directions
{
public:
	struct DirectionsItem
	{
		cell_type north;
		cell_type east;
		cell_type south;
		cell_type west;

		constexpr bool operator==(const DirectionsItem& other) const noexcept
		{
			return north == other.north &&
			       east == other.east &&
			       south == other.south &&
			       west == other.west;
		}
	};

	using value_type = DirectionsItem;
	using storage_type = std::array<value_type, Terrain::area>;

	static constexpr value_type get_directions(cell_type cell) noexcept
	{
		/* static */ constexpr auto invalid = Terrain::area + 1;

		const auto pt = get_pt(cell);

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
			// East only
			if (pt.x == 0) return {invalid, get_cell({pt.x, pt.y + 1}), invalid, invalid};
			// South and East only
			return {invalid, get_cell({pt.x, pt.y + 1}), get_cell({pt.x - 1, pt.y + 1}), invalid};
		}

		if (pt.y == Terrain::height - 1)
		{
			if (Terrain::height % 2 == 0)
			{
				// West only
				if (pt.x == Terrain::width - 1) return {invalid, invalid, invalid, get_cell({pt.x, pt.y - 1})};
				// West and North only
				return {get_cell({pt.x + 1, pt.y - 1}), invalid, invalid, get_cell({pt.x, pt.y - 1})};
			}

			if (Terrain::height % 2 == 1)
			{
				// North only
				if (pt.x == 0) return {get_cell({pt.x, pt.y - 1}), invalid, invalid, invalid};
				// West and North only
				return {get_cell({pt.x, pt.y - 1}), invalid, invalid, get_cell({pt.x - 1, pt.y - 1})};

			}
		}

		if (pt.y % 2 == 0)
		{
			return {get_cell({pt.x, pt.y - 1}), get_cell({pt.x, pt.y + 1}), get_cell({pt.x - 1, pt.y + 1}), get_cell({pt.x - 1, pt.y - 1})};
		}

		if (pt.y % 2 == 1)
		{
			return {get_cell({pt.x + 1, pt.y - 1}), get_cell({pt.x + 1, pt.y + 1}), get_cell({pt.x, pt.y + 1}), get_cell({pt.x, pt.y - 1})};
		}

		// We should not ever get here
		return {invalid, invalid, invalid, invalid};
	}

	constexpr Directions() noexcept
	    : m_data()
	{
		for (cell_type cell = 0; cell < Terrain::area; ++cell)
		{
			m_data[cell] = get_directions(cell);
		}

	}

	constexpr storage_type& data() noexcept
	{
		return m_data;
	}

	constexpr const storage_type& data() const noexcept
	{
		return m_data;
	}

private:
	storage_type m_data;
};

std::ostream& operator<<(std::ostream& out, const Directions::value_type& d) noexcept;

} // namespace engine
