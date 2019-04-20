#include <engine/obstacle.h>
#include <engine/character.h>

#include <gtest/gtest.h>

#include <iostream>

TEST(Entity, CreateCharacterPlayer)
{
    const engine::Character player(engine::Character::type::player);
    std::cout << player << "\n";
}

TEST(Entity, CreateCharacterNpc)
{
    const engine::Character npc(engine::Character::type::npc);
    std::cout << npc << "\n";
}

TEST(Entity, CreateObstacle)
{
    const engine::Obstacle obstacle;
    std::cout << obstacle << "\n";
}
