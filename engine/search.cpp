#include "search.h"
#include "directions.h"

#include <stack>
#include <iostream>

namespace engine
{

std::vector<std::vector<Point<std::size_t>>> connected_components(const Terrain & t)
{
    // Mark all the cells as not visited
    std::array<bool, terrain_area> visited = {};

    // Create output data structure
    std::vector<std::vector<Point<std::size_t>>> components;

    Point<std::size_t> pt;

    for (pt.y = 0; pt.y < terrain_height; ++pt.y)
    {
        for (pt.x = 0; pt.x < terrain_width; ++pt.x)
        {
            if (t.at(pt) || visited[pt.x + pt.y * terrain_width])
            {
                std::cout << "Skipping occupied/visited root cell " << pt << "\n";
            }
            else
            {
                // Create search stack
                std::stack<Point<std::size_t>> cells_to_visit;
                cells_to_visit.push(pt);

                // Allocate current component
                std::vector<Point<std::size_t>> current_component = {};

                while (!cells_to_visit.empty())
                {
                    auto cell = cells_to_visit.top();
                    cells_to_visit.pop();

                    if (t.at(cell) || visited[cell.x + cell.y * terrain_width])
                    {
                        std::cout << "Skipping invalid/occupied/visited cell " << cell << "\n";
                    }
                    else
                    {
                        // Mark the current cell as visited and store it
                        std::cout << "Visited " << cell << "\n";
                        visited[cell.x + cell.y * terrain_width] = true;
                        current_component.push_back(cell);

                        auto neighbors = t.neighbors(cell);
                        auto neighbors2 = get_directions(cell);

                        if (!(neighbors == neighbors2)) throw;

                        std::cout << "Exploring " << neighbors << " from " << cell << "\n";

                        if (neighbors.north) cells_to_visit.push(*neighbors.north);
                        if (neighbors.east)  cells_to_visit.push(*neighbors.east);
                        if (neighbors.south) cells_to_visit.push(*neighbors.south);
                        if (neighbors.west)  cells_to_visit.push(*neighbors.west);

                    }
                }

                if (!current_component.empty())
                    components.push_back(std::move(current_component));
            }
        }
    }

    return components;
}

} // namespace engine
