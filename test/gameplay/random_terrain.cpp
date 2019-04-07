#include <engine/terrain.h>
#include <engine/rng.h>
#include <engine/character.h>

#include <gameplay/search.h>
#include <gameplay/random_terrain.h>
#include <gameplay/split_terrain.h>

#include <gtest/gtest.h>
using GoogleTestFixture = ::testing::Test;

struct RandomlyGeneratedTerrain : public GoogleTestFixture
{
    engine::Terrain terrain = gameplay::generate_terrain(engine::random_number_engine{ engine::random_number_engine::default_seed });
};

TEST_F(RandomlyGeneratedTerrain, CreatePlayerAndTerrain)
{
    std::cout << terrain << "\n";

    engine::Character player1{ engine::Character::type::player };
    engine::Character player2{ engine::Character::type::player };

    std::cout << player1 << "\n";
    std::cout << player2 << "\n";

    player2.use_weapon(0, player1);

    std::cout << player1 << "\n";
    std::cout << player2 << "\n";
}

TEST_F(RandomlyGeneratedTerrain, PrintTerrain)
{
    std::cout << terrain << "\n";
}

TEST_F(RandomlyGeneratedTerrain, SplitField4AndPrint)
{
    const auto spawns = gameplay::split_field(terrain, 4);
    std::cout << terrain << "\n";
}

TEST_F(RandomlyGeneratedTerrain, SplitField6AndPrint)
{
    const auto spawns = gameplay::split_field(terrain, 6);
    std::cout << terrain << "\n";
}

TEST_F(RandomlyGeneratedTerrain, SplitField8AndPrint)
{
    const auto spawns = gameplay::split_field(terrain, 8);
    std::cout << terrain << "\n";
}

TEST_F(RandomlyGeneratedTerrain, ConnectedComponents)
{
    std::cout << terrain << "\n";

    const auto cc = gameplay::connected_components(terrain);

    for (const auto & component : cc)
    {
        for (const auto & cell : component)
            std::cout << cell << " ";
        std::cout << "\n\n";
    }

    ASSERT_EQ(cc.size(), 3);
    EXPECT_EQ(cc[0].size(), 152);
    EXPECT_EQ(cc[1].size(), 2);
    EXPECT_EQ(cc[2].size(), 1);
}
