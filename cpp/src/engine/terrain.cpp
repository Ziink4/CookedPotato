#include <engine/terrain.h>
#include <engine/directions.h>
#include <engine/symbol.h>

namespace engine
{

std::ostream& operator<<(std::ostream& out, const Terrain& t) noexcept
{
	cell_type cell{0};

	for (std::size_t y = 0; y < terrain_height; ++y)
	{
		out << " ";

		if (y % 2 == 1) out << "  ";

		for (std::size_t x = 0; x < terrain_width; ++x)
		{
			out << t[cell];
			out << "   ";
			cell++;
		}

		out << std::endl;
	}

	return out << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Directions::CardinalDirections& d) noexcept
{
	out << "Directions(";
	out << "north = " << d.north;
	out << ", ";
	out << "east = " << d.east;
	out << ", ";
	out << "south = " << d.south;
	out << ", ";
	out << "west = " << d.west;
	out << ")";
	return out;
}

} // namespace engine
