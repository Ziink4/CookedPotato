#include <engine/point.h>
#include <engine/size.h>
#include <engine/terrain.h>

#include <gtest/gtest.h>

#include <iostream>

TEST(Terrain, PrintPoint)
{
    constexpr engine::point pt{5, 3};
    std::cout << pt << "\n";
}

TEST(Terrain, PrintSize)
{
    constexpr engine::size sz{ 5, 3 };
    std::cout << sz << "\n";
}

TEST(Terrain, PrintTerrain)
{
    const engine::Terrain t{};
    std::cout << t << "\n";
}
