#pragma once

#include <engine/terrain.h>
#include <engine/rng.h>

namespace gameplay
{
    engine::Terrain generate_terrain(engine::RandomNumberGenerator & rng) noexcept;
}
