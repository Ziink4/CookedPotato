#include <potato-engine/engine.h>
#include <potato-engine/terrain.h>
#include <potato-engine/rng.h>
#include <potato-engine/obstacle.h>

#include <algorithm>
#include <random>

namespace engine
{

Terrain generate_terrain(RandomNumberGenerator& rng) noexcept
{
	static constexpr auto density = 0.25;
	static std::bernoulli_distribution distribution(density);

	Terrain t = {};

	for (auto& obstacle : t.data())
	{
		if (distribution(rng.rand()))
		{
			if (!obstacle)
			{
				obstacle.reset(new engine::Obstacle());
			}
		}
	}

	return t;
}

void split_field(Terrain& t, std::size_t parts) noexcept
{
	static constexpr double width  = Terrain::width;
	static constexpr double height = Terrain::height;
	static constexpr auto half_width  = width  / 2.0;
	static constexpr auto half_height = height / 2.0;

	static const double pi = 4.0 * std::atan(1.0);
	const double angle_cutoff = 2.0 * pi / parts;

	static constexpr auto radius_y = ((2 * Terrain::width) > Terrain::height) ? half_height : width;
	static constexpr auto radius_x = radius_y / 2.0;

	static constexpr auto start_x = static_cast<point_type::value_type>(half_width  - radius_x);
	static constexpr auto start_y = static_cast<point_type::value_type>(half_height - radius_y);

	static constexpr auto end_x = static_cast<point_type::value_type>(half_width  + radius_x);
	static constexpr auto end_y = static_cast<point_type::value_type>(half_height + radius_y);

	point_type pt;

	for (pt.y = start_y; pt.y < end_y; ++pt.y)
	{
		for (pt.x = start_x; pt.x < end_x; ++pt.x)
		{
			const auto cell = get_cell(pt);

			// Checks if the current cell is available (we don't want anything to spawn on occupied space)
			if (!t.data()[cell])
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
						t.data()[cell].reset(new engine::Obstacle());
					}
				}
			}
		}
	}
}

} // namespace engine
