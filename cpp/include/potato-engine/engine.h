#pragma once

#include <potato-engine/point.h>

namespace engine
{

using cell_type = std::size_t;
using point_type = Point<std::size_t>;

constexpr std::size_t terrain_width = 10;
constexpr std::size_t terrain_height = 20;
constexpr std::size_t terrain_area = terrain_width * terrain_height;

} // namespace engine
