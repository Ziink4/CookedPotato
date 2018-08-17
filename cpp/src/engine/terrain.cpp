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
				case CellType::Empty:
					out << white;
					break;
				default:
					out << black;
					break;
			}

			out << "   ";
		}

		out << std::endl;
	}

	return out << std::endl;


	/*

	// Loop through every cell from top to bottom and left to right
	for y in 0..terrain::TERRAIN_HEIGHT {
		// Store the current position in the map as Point
		let mut pt = terrain::Point {x: 0, y: y};

		if y % 2 == 1 {
			print!("  ");
		}

		for x in 0..terrain::TERRAIN_WIDTH {
			pt.x = x;
			match t[terrain::get_cell(&pt)] {
				terrain::Cell::Empty    => print!("{}   ", WHITE),
				terrain::Cell::Player   => print!("{}   ", SQUARE),
				terrain::Cell::Monster  => print!("{}   ", DOT),
				terrain::Cell::Decor    => print!("{}   ", BLACK),
				terrain::Cell::Obstacle => print!("{}   ", SPLIT),
			}
		}
		println!("");
	}
	println!("");

	return out << "Point(" << pt.x << ", " << pt.y << ")";
	*/
}

}
