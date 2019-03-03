#include <engine/terrain.h>
#include <engine/directions.h>
#include <engine/rng.h>
#include <engine/obstacle.h>
#include <engine/character.h>

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
