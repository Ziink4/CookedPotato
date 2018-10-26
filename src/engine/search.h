#pragma once

#include <engine/engine.h>
#include <engine/directions.h>
#include <engine/terrain.h>

#include <array>
#include <vector>

namespace engine
{

std::vector<std::vector<point_type>> connected_components(const Terrain& t);

}
