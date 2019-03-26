#include <gameplay/search.h>

#include <engine/directions.h>

#include <stack>
#include <iostream>

namespace gameplay
{
    std::vector<std::vector<engine::point>> connected_components(const engine::Terrain & t)
    {
        // Mark all the cells as not visited
		std::vector<bool> visited(t.area());

        // Create output data structure
        std::vector<std::vector<engine::point>> components;

        engine::point pt;

        for (pt.y = 0; pt.y < t.height(); ++pt.y)
        {
            for (pt.x = 0; pt.x < t.width(); ++pt.x)
            {
                if (t.at(pt) || visited[pt.x + pt.y * t.width()])
                {
                    std::cout << "Skipping occupied/visited root cell " << pt << "\n";
                }
                else
                {
                    // Create search stack
                    std::stack<engine::point> cells_to_visit;
                    cells_to_visit.push(pt);

                    // Allocate current component
                    std::vector<engine::point> current_component;

                    while (!cells_to_visit.empty())
                    {
                        auto cell = cells_to_visit.top();
                        cells_to_visit.pop();

                        if (t.at(cell) || visited[cell.x + cell.y * t.width()])
                        {
                            std::cout << "Skipping invalid/occupied/visited cell " << cell << "\n";
                        }
                        else
                        {
                            // Mark the current cell as visited and store it
                            std::cout << "Visited " << cell << "\n";
                            visited[cell.x + cell.y * t.width()] = true;
                            current_component.push_back(cell);

                            const engine::CardinalDirections neighbors = t.neighbors(cell);
							const engine::CardinalDirections neighbors2 = engine::get_directions(cell, t.size());

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
