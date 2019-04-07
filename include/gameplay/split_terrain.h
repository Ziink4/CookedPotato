#pragma once

#include <vector>

namespace engine
{

class Terrain;
struct point;

}

namespace gameplay
{

std::vector<std::vector<engine::point>> split_field(engine::Terrain & t, std::size_t parts) noexcept;

}
