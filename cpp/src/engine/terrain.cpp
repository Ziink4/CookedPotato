#include <potato-engine/terrain.h>

namespace engine
{

constexpr const char* get_symbol(CellType type)
{
	/* static */ constexpr auto white  = "\xE2\x97\x86"; // white diamond
	/* static */ constexpr auto black  = "\xE2\x97\x87"; // black diamond
	/* static */ constexpr auto square = "\xE2\x97\x88"; // white diamond containing black small diamond
	/* static */ constexpr auto split  = "\xE2\x9D\x96"; // black diamond minus white x
	/* static */ constexpr auto dot    = "\xE2\x9F\x90"; // white diamond with centred dot

	switch (type)
	{
		case CellType::empty:    return black;
		case CellType::player:   return square;
		case CellType::monster:  return dot;
		case CellType::decor:    return white;
		case CellType::obstacle: return split;
	}
}

constexpr const char* get_name(CellType type)
{
	switch (type)
	{
		case CellType::empty:    return "Empty";
		case CellType::player:   return "Player";
		case CellType::monster:  return "Monster";
		case CellType::decor:    return "Decor";
		case CellType::obstacle: return "Obstacle";
	}
}

std::ostream& operator<<(std::ostream& out, const Terrain& t) noexcept
{
	out << "           | ";

	out << get_symbol(CellType::decor)    << " " << get_name(CellType::decor)    << " | ";
	out << get_symbol(CellType::empty)    << " " << get_name(CellType::empty)    << " | ";
	out << get_symbol(CellType::player)   << " " << get_name(CellType::player)   << " | ";
	out << get_symbol(CellType::obstacle) << " " << get_name(CellType::obstacle) << " | ";
	out << get_symbol(CellType::monster)  << " " << get_name(CellType::monster)  << " | ";

	out << std::endl;

	Terrain::size_type cell{0};

	for (Terrain::size_type y = 0; y < Terrain::height; ++y)
	{
		out << " ";

		if (y % 2 == 1) out << "  ";

		for (Terrain::size_type x = 0; x < Terrain::width; ++x)
		{
			const auto entity = t.data()[cell].get();
			if (entity)
			{
				entity->print_symbol(out);
				out << "   ";
			}
			else
			{
				out << get_symbol(CellType::empty) << "   ";
			}

			cell++;
		}

		out << std::endl;
	}

	return out << std::endl;
}

} // namespace engine
