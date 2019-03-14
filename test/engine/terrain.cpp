#include <engine/terrain.h>
#include <engine/directions.h>
#include <engine/rng.h>
#include <engine/obstacle.h> 
#include <engine/character.h> 

#include <iostream>

#include <gtest/gtest.h>
using GoogleTestFixture = ::testing::Test;

TEST(Terrain, PrintPoint)
{
    constexpr engine::point<std::size_t> pt{5, 3};
    std::cout << pt << "\n";
}

TEST(Terrain, PrintTerrain)
{
    const engine::Terrain t{};
    std::cout << t << "\n";
}
