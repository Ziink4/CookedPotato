#include <potato-engine/search.h>
#include <potato-engine/logger.h>

namespace engine
{

void recursive_search(cell_type cell, std::array<bool, terrain_area>& visited, std::vector<cell_type>& component, const Directions& d, const Terrain& t)
{
	if (!is_valid(cell))
	{
		LOG_TRACE(Logger::console, "Skipped invalid {}", cell);
		return;
	}

	if (t[cell].occupied())
	{
		LOG_TRACE(Logger::console, "Skipped occupied {}", cell);
		return;
	}

	if (visited[cell])
	{
		LOG_TRACE(Logger::console, "Skipped visited {}", cell);
		return;
	}

	// Mark the current node as visited and print it
	std::cout << "Visited " << cell << std::endl;
	visited[cell] = true;
	component.push_back(cell);

	std::cout << "Exploring " << d.data[cell].north << " " << d.data[cell].east << " " << d.data[cell].south << " " << d.data[cell].west << " from " << cell << std::endl;

	recursive_search(d.data[cell].north, visited, component, d, t);
	recursive_search(d.data[cell].east, visited, component, d, t);
	recursive_search(d.data[cell].south, visited, component, d, t);
	recursive_search(d.data[cell].west, visited, component, d, t);

}

std::vector<std::vector<cell_type>> connected_components(const Directions& d, const Terrain& t)
{
	// Mark all the vertices as not visited
	std::array<bool, terrain_area> visited = {};
	std::vector<std::vector<cell_type>> components;

	for (cell_type cell = 0; cell < terrain_area; ++cell)
	{
		std::vector<cell_type> current_component = {};
		recursive_search(cell, visited, current_component, d, t);

		if (!current_component.empty())
		{
			components.push_back(std::move(current_component));
		}
	}

	return components;
}

}
