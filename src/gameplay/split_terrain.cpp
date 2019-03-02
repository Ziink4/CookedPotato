#include "split_terrain.h"

namespace gameplay
{
    std::vector<std::vector<engine::Point<std::size_t>>> split_field(engine::Terrain & t, std::size_t parts) noexcept
    {
        std::vector<std::vector<engine::Point<std::size_t>>> spawns(parts);

        static const double width = engine::terrain_width;
        static const double height = engine::terrain_height;
        static const auto half_width = width / 2.0;
        static const auto half_height = height / 2.0;

        static const double pi = 4.0 * std::atan(1.0);
        const double angle_cutoff = 2.0 * pi / parts;

        static const auto radius_y = ((2 * engine::terrain_width) > height) ? half_height : width;
        static const auto radius_x = radius_y / 2.0;

        static const auto start_x = static_cast<std::size_t>(half_width - radius_x);
        static const auto start_y = static_cast<std::size_t>(half_height - radius_y);

        static const auto end_x = static_cast<std::size_t>(half_width + radius_x);
        static const auto end_y = static_cast<std::size_t>(half_height + radius_y);

        engine::Point<std::size_t> pt{ 0, 0 };

        for (pt.y = start_y; pt.y < end_y; ++pt.y)
        {
            for (pt.x = start_x; pt.x < end_x; ++pt.x)
            {
                // Checks if the current cell is available (we don't want anything to spawn on occupied space)
                if (!t.at(pt))
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

                        spawns[part].push_back(pt);
                    }
                }
            }
        }

        return spawns;
    }
}
