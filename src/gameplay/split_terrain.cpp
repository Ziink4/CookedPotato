#include <gameplay/split_terrain.h>

#include <engine/point.h>
#include <engine/terrain.h>
#include <engine/vector.h>

namespace gameplay
{
    std::vector<std::vector<engine::point>> split_field(engine::Terrain & t, std::size_t parts) noexcept
    {
        std::vector<std::vector<engine::point>> spawns(parts);

        const double half_width = t.width() / 2.0;
        const double half_height = t.height() / 2.0;

        const double angle_cutoff = 2.0 * engine::pi / parts;

        const double radius_y = ((2 * t.width()) > t.height()) ? half_height : t.width();
        const double radius_x = radius_y / 2.0;

        const unsigned start_x = static_cast<unsigned>(half_width - radius_x);
        const unsigned start_y = static_cast<unsigned>(half_height - radius_y);

        const unsigned end_x = static_cast<unsigned>(half_width + radius_x);
        const unsigned end_y = static_cast<unsigned>(half_height + radius_y);

        engine::point pt{ 0, 0 };

        for (pt.y = start_y; pt.y < end_y; ++pt.y)
        {
            for (pt.x = start_x; pt.x < end_x; ++pt.x)
            {
                // Checks if the current cell is available (we don't want anything to spawn on occupied space)
                if (!t.at(pt))
                {
                    // Translates the coordinates to the center of the terrain
                    const double fx = pt.x - half_width;
                    const double fy = pt.y - half_height;

                    // Checks if the current cell is inside the circle
                    const double radius = std::pow(fx / radius_x, 2) + std::pow(fy / radius_y, 2);
                    if (radius <= 1.0 && radius > 0.2)
                    {
                        // Computes this cell's angle using atan2
                        const double angle = std::atan2(fy / 2.0, fx) + engine::pi;
                        // Computes with split of the board this cell belongs to
                        const unsigned part = static_cast<unsigned>(angle / angle_cutoff) % parts;

                        spawns[part].push_back(pt);
                    }
                }
            }
        }

        return spawns;
    }
}
