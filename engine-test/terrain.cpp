#include <engine/terrain.h>
#include <engine/directions.h>
#include <engine/rng.h>
#include <engine/obstacle.h> 
#include <engine/character.h> 
#include <engine/search.h>

#include <gtest/gtest.h>

#include <iostream>

TEST(Terrain, PrintPoint)
{
    constexpr engine::Point<std::size_t> pt{5, 3};
    std::cout << pt << "\n";
}

TEST(Terrain, PrintTerrain)
{
    const engine::Terrain t{};
    std::cout << t << "\n";
}

TEST(Terrain, GenerateTerrain)
{
    engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);
    const engine::Terrain t = generate_terrain(rng);
    std::cout << t << "\n";
}

TEST(Terrain, GenerateTerrainAndSplitField)
{
    engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);

    engine::Terrain t = generate_terrain(rng);
    const auto spawns = engine::split_field(t, 4);

    /*
    for (const auto& team : spawns)
    {
        for (const auto& cell : team)
        {
            t.at(cell) = set_entity(std::make_unique<engine::Character>(engine::Character::type::npc));
        }
        std::cout << t << std::endl;
    }
    */

    std::cout << t << "\n";

    t = generate_terrain(rng);
    engine::split_field(t, 6);
    std::cout << t << "\n";

    t = generate_terrain(rng);
    engine::split_field(t, 8);
    std::cout << t << "\n";
}

TEST(Terrain, ConnectedComponents)
{
    const auto cc = engine::connected_components({});

    EXPECT_EQ(cc.size(), 1);

    for (const auto& component : cc)
    {
        std::cout << "Component : ";
        for (const auto& cell : component)
            std::cout << cell << " ";
        std::cout << "\n";
    }

    EXPECT_EQ(cc[0].size(), 200);

}

TEST(Terrain, GenerateTerrainAndCC)
{
    engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);
    const engine::Terrain t = generate_terrain(rng);
    std::cout << t << "\n";

    const auto cc = engine::connected_components(t);

    EXPECT_EQ(cc.size(), 2);

    for (const auto& component : cc)
    {
        for (const auto& cell : component)
            std::cout << cell << " ";
        std::cout << "\n";
    }

    EXPECT_EQ(cc[0].size(), 8);
    EXPECT_EQ(cc[1].size(), 150);
}
