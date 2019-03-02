#include "terrain.h"
#include "rng.h"
#include "obstacle.h"

#include <algorithm>
#include <random>

namespace engine
{

Terrain generate_terrain(RandomNumberGenerator & rng) noexcept
{
    static const auto density = 0.25;
    static std::bernoulli_distribution distribution(density);

    Terrain t{};

    for (auto& cell : t)
        if (distribution(rng.rand()))
            if (!cell)
                cell = std::move(std::make_unique<engine::Obstacle>());

    return t;
}

} // namespace engine
