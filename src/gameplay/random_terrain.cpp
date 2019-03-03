#include "random_terrain.h"

#include <engine/obstacle.h>

namespace gameplay
{
    engine::Terrain generate_terrain(engine::RandomNumberGenerator & rng) noexcept
    {
        static const auto density = 0.25;
        static std::bernoulli_distribution distribution{ density };

        engine::Terrain t{};

        for (auto & cell : t)
            if (distribution(rng.rand()))
                if (!cell)
                    cell = std::move(std::make_unique<engine::Obstacle>());

        return t;
    }
}
