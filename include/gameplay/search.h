#pragma once

#include <engine/terrain.h>

#include <vector>

namespace gameplay
{
    std::vector<std::vector<engine::point<std::size_t>>> connected_components(const engine::Terrain & t);
}
