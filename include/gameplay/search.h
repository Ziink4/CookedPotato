#pragma once

#include <vector>

namespace engine
{

class Terrain;
struct point;

} // namespace engine

namespace gameplay
{

std::vector<std::vector<engine::point>> connected_components(const engine::Terrain & t);

} // namespace gameplay
