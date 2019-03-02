#pragma once

#include <engine/point.h>
#include <engine/terrain.h>
#include <vector>

namespace gameplay
{
    std::vector<std::vector<engine::Point<std::size_t>>> split_field(engine::Terrain & t, std::size_t parts) noexcept;
}