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

class RandomlyGeneratedTerrain : public ::testing::Test
{
protected:
    RandomlyGeneratedTerrain() : m_rng(engine::RandomNumberGenerator::fixed_seed), m_terrain(generate_terrain(m_rng))
    {
    }

    auto& get_terrain() { return m_terrain; }

private:
    engine::RandomNumberGenerator m_rng;
    engine::Terrain m_terrain;
};

TEST_F(RandomlyGeneratedTerrain, PrintTerrain)
{
    std::cout << get_terrain() << "\n";
}

TEST_F(RandomlyGeneratedTerrain, SplitField4AndPrint)
{
    auto& t = get_terrain();
    const auto spawns = engine::split_field(t, 4);
    std::cout << t << "\n";
}

TEST_F(RandomlyGeneratedTerrain, SplitField6AndPrint)
{
    auto& t = get_terrain();
    const auto spawns = engine::split_field(t, 6);
    std::cout << t << "\n";
}

TEST_F(RandomlyGeneratedTerrain, SplitField8AndPrint)
{
    auto& t = get_terrain();
    const auto spawns = engine::split_field(t, 8);
    std::cout << t << "\n";
}

TEST_F(RandomlyGeneratedTerrain, ConnectedComponents)
{
    const auto& t = get_terrain();
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
