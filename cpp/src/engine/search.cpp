#include <engine/search.h>

#include <stack>

namespace engine
{

std::vector<std::vector<cell_type>> connected_components(const Directions& d, const Terrain& t)
{
    // Mark all the cells as not visited
    std::array<bool, terrain_area> visited = {};

    // Create output data structure
    std::vector<std::vector<cell_type>> components;

    for (cell_type root_cell = 0; root_cell < terrain_area; ++root_cell)
    {
        if (t[root_cell].occupied() || visited[root_cell])
        {
            std::cout << "Skipping occupied/visited root cell " << root_cell << std::endl;
        }
        else
        {
            // Create search stack
            std::stack<cell_type> cells_to_visit;
            cells_to_visit.push(root_cell);

            // Allocate current component
            std::vector<cell_type> current_component = {};

            while (!cells_to_visit.empty())
            {
                auto cell = cells_to_visit.top();
                cells_to_visit.pop();

                if (!is_valid(cell) || t[cell].occupied() || visited[cell])
                {
                    std::cout << "Skipping invalid/occupied/visited cell " << cell << std::endl;
                }
                else
                {
                    // Mark the current cell as visited and store it
                    std::cout << "Visited " << cell << std::endl;
                    visited[cell] = true;
                    current_component.push_back(cell);

                    std::cout << "Exploring " << d.data[cell].north << " " << d.data[cell].east << " " << d.data[cell].south << " " << d.data[cell].west << " from " << cell << std::endl;

                    cells_to_visit.push(d.data[cell].north);
                    cells_to_visit.push(d.data[cell].east);
                    cells_to_visit.push(d.data[cell].south);
                    cells_to_visit.push(d.data[cell].west);
                }
            }

            if (!current_component.empty())
            {
                components.push_back(std::move(current_component));
            }
        }
    }

    return components;
}


}
