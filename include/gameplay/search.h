#pragma once

#include <engine/terrain.h>

#include <vector>

namespace gameplay
{
    std::vector<std::vector<engine::point>> connected_components(const engine::Terrain & t);
}
