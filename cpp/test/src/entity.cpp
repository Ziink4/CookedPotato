#include <potato-engine/engine.h>
#include <potato-engine/entity.h>
#include <potato-engine/terrain.h>
#include <potato-engine/rng.h>

#define CATCH_CONFIG_PREFIX_ALL
#include <catch2/catch.hpp>

CATCH_TEST_CASE("Create entity")
{
    engine::Entity player({5, 3}, engine::Entity::entity_type::player, 0);
    std::cout << player << std::endl;

    engine::Entity npc({4, 2}, engine::Entity::entity_type::npc, 1);
    std::cout << npc << std::endl;
}

CATCH_TEST_CASE("Create player and terrain")
{
    engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);

    engine::Terrain t = generate_terrain(rng);
    std::cout << t << std::endl;

    engine::Entity player({5, 3}, engine::Entity::entity_type::player, 0);
    std::cout << player << std::endl;

}
