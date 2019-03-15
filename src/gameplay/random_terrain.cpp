#include "random_terrain.h"

#include <random>

#include <engine/rng.h>
#include <engine/terrain.h>
#include <engine/obstacle.h>

namespace gameplay
{

engine::Terrain generate_terrain(engine::random_number_engine & rng, double density) noexcept
{
    std::bernoulli_distribution distribution{ density };

    engine::Terrain t;

    for (auto & cell : t)
        if (distribution(rng))
            if (!cell)
                cell = std::move(std::make_unique<engine::Obstacle>());

    return t;
}

} // namespace gameplay
