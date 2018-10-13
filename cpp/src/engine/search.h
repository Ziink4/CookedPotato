#pragma once

#include <engine/engine.h>
#include <engine/directions.h>
#include <engine/terrain.h>

#include <array>
#include <vector>

namespace engine
{

std::vector<std::vector<cell_type>> connected_components(const Directions& d, const Terrain& t);

}
