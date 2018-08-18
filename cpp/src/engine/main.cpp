#include <potato-engine/engine.h>
#include <potato-engine/terrain.h>
#include <potato-engine/rng.h>

#include "main.h"

#include <algorithm>
#include <random>

namespace engine
{

void print_fancy()
{
	std::cerr << "WOOO" << std::endl;
	std::cerr << terrain::width << std::endl;
	print();
}

terrain::Terrain generate_terrain(RandomNumberGenerator& rng) noexcept
{
    static constexpr auto density = 0.1;
    static std::bernoulli_distribution distribution(density);

    terrain::Terrain t = {};

    for (auto& obstacle : t)
	{
        if (distribution(rng.rand()))
        {
            obstacle.type = CellType::decor;
        }
	}

	return t;
}

void split_field(terrain::Terrain& t, std::size_t parts) noexcept
{
    static constexpr double width  = terrain::width;
    static constexpr double height = terrain::height;
    static constexpr auto half_width  = width  / 2.0;
    static constexpr auto half_height = height / 2.0;

    static const double pi = 4.0 * std::atan(1.0);
    const double angle_cutoff = 2.0 * pi / parts;

    static constexpr auto radius_y = ((2 * terrain::width) > terrain::height) ? half_height : width;
    static constexpr auto radius_x = radius_y / 2.0;

    static constexpr auto start_x = static_cast<std::size_t>(half_width  - radius_x);
    static constexpr auto start_y = static_cast<std::size_t>(half_height - radius_y);

    static constexpr auto end_x = static_cast<std::size_t>(half_width  + radius_x);
    static constexpr auto end_y = static_cast<std::size_t>(half_height + radius_y);

    Point pt;

    for (pt.y = start_y; pt.y < end_y; ++pt.y)
    {
        for (pt.x = start_x; pt.x < end_x; ++pt.x)
        {
            const auto cell = terrain::get_cell(pt);

            // Checks if the current cell is available (we don't want anything to spawn on occupied space)
            if (t[cell].type == CellType::empty)
            {
                // Translates the coordinates to the center of the terrain
                const auto fx = pt.x - half_width;
                const auto fy = pt.y - half_height;

                // Checks if the current cell is inside the circle
                const auto radius = std::pow(fx / radius_x, 2) + std::pow(fy / radius_y, 2);
                if (radius <= 1.0 && radius > 0.2)
                {
                    // Computes this cell's angle using atan2
                    const auto angle = std::atan2(fy / 2.0, fx) + pi;
                    // Computes with split of the board this cell belongs to
                    const auto part = static_cast<std::size_t>(angle / angle_cutoff) % parts;

                    if (part % 2 == 0)
                    {
                        t[cell].type = CellType::monster;
                    }
                }
            }
        }
    }
}

} // namespace engine
