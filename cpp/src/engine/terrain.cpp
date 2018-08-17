#include <potato-engine/terrain.h>

namespace engine
{

std::ostream& operator<<(std::ostream& out, const Point& pt) noexcept
{
	return out << "Point(" << pt.x << ", " << pt.y << ")";
}

std::ostream& operator<<(std::ostream& out, const terrain::Terrain& t) noexcept
{
	static constexpr auto white  = "\xE2\x97\x86"; // white diamond
	static constexpr auto black  = "\xE2\x97\x87"; // black diamond
	static constexpr auto square = "\xE2\x97\x88"; // white diamond containing black small diamond
	static constexpr auto split  = "\xE2\x9D\x96"; // black diamond minus white x
	static constexpr auto dot    = "\xE2\x9F\x90"; // white diamond with centred dot

	for (std::size_t row = 0; row < terrain::height; ++row)
	{
		Point pt{0, row};

		if (row % 2 == 1) out << "  ";

		for (std::size_t col = 0; col < terrain::width; ++col)
		{
			pt.x = col;
			switch (t[terrain::get_cell(pt)].type)
			{
				case CellType::empty:
					out << white;
					break;
				case CellType::player:
					out << square;
					break;
				case CellType::monster:
					out << dot;
					break;
				case CellType::decor:
					out << black;
					break;
				case CellType::obstacle:
					out << split;
					break;
			}

			out << "   ";
		}

		out << std::endl;
	}

	return out << std::endl;
}

}
