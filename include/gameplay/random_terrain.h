#pragma once

#include <engine/terrain.h>

class engine::RandomNumberGenerator;

namespace gameplay
{
    engine::Terrain generate_terrain(engine::RandomNumberGenerator & rng) noexcept;
} // namespace gameplay
