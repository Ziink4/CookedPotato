#include <potato-engine/terrain.h>
#include <potato-engine/directions.h>
#include <potato-engine/symbol.h>

namespace engine
{

std::ostream& operator<<(std::ostream& out, const Terrain& t) noexcept
{
	cell_type cell{0};

	for (std::size_t y = 0; y < Terrain::height; ++y)
	{
		out << " ";

		if (y % 2 == 1) out << "  ";

		for (std::size_t x = 0; x < Terrain::width; ++x)
		{
			const auto entity = t.data()[cell].get();

			if (entity)
			{
				entity->print_symbol(out);
			}
			else
			{
				out << black_symbol;
			}

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
