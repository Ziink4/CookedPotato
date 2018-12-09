#include <engine/terrain.h> // For engine::Terrain
#include <engine/directions.h>
#include <engine/rng.h> // For engine::RandomNumberGenerator
#include <engine/obstacle.h> // For engine::Obstacle
#include <engine/character.h> // For engine::Character
#include <engine/search.h> // For engine::Character

#include <gtest/gtest.h>

TEST(Entity, CreateCharacterPlayer)
{
    engine::Character player(engine::Character::type::player);
    std::cout << player << "\n";
}

TEST(Entity, CreateCharacterNpc)
{
    engine::Character npc(engine::Character::type::npc);
    std::cout << npc << "\n";
}

TEST(Entity, CreateObstacle)
{
    engine::Obstacle obstacle;
    std::cout << obstacle << "\n";
}

TEST(Entity, CreatePlayerAndTerrain)
{
    engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);

    engine::Terrain t = generate_terrain(rng);
    std::cout << t << "\n";

    engine::Character player1(engine::Character::type::player);
    engine::Character player2(engine::Character::type::player);

    std::cout << player1 << "\n";
    std::cout << player2 << "\n";

    player2.use_weapon(0, player1);

    std::cout << player1 << "\n";
    std::cout << player2 << "\n";
}
