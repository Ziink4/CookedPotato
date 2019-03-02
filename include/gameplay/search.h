#pragma once

#include <engine/terrain.h>

#include <vector>

namespace engine
{

std::vector<std::vector<Point<std::size_t>>> connected_components(const Terrain& t);

}
