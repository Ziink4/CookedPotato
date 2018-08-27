#pragma once

#include <potato-engine/engine.h>
#include <potato-engine/directions.h>
#include <potato-engine/terrain.h>

#include <array>
#include <vector>

namespace engine
{

void recursive_search(cell_type cell, std::array<bool, terrain_area>& visited, std::vector<cell_type>& component, const Directions& d, const Terrain& t);

std::vector<std::vector<cell_type>> connected_components(const Directions& d, const Terrain& t);

}
