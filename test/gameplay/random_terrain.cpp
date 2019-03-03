#include <engine/terrain.h>
#include <engine/rng.h>
#include <engine/character.h>

#include <gameplay/search.h>
#include <gameplay/random_terrain.h>
#include <gameplay/split_terrain.h>

#include <gtest/gtest.h>
using GoogleTestFixture = ::testing::Test;

TEST(Entity, CreatePlayerAndTerrain)
{
    engine::RandomNumberGenerator rng{ engine::RandomNumberGenerator::fixed_seed };

    engine::Terrain t = gameplay::generate_terrain(rng);
    std::cout << t << "\n";

    engine::Character player1{ engine::Character::type::player };
    engine::Character player2{ engine::Character::type::player };

    std::cout << player1 << "\n";
    std::cout << player2 << "\n";

    player2.use_weapon(0, player1);

    std::cout << player1 << "\n";
    std::cout << player2 << "\n";
}


class RandomlyGeneratedTerrain : public GoogleTestFixture
{
protected:
    RandomlyGeneratedTerrain()
        : m_rng{ engine::RandomNumberGenerator::fixed_seed }
        , m_terrain{ gameplay::generate_terrain(m_rng) }
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
    auto & t = get_terrain();
    const auto spawns = gameplay::split_field(t, 4);
    std::cout << t << "\n";
}

TEST_F(RandomlyGeneratedTerrain, SplitField6AndPrint)
{
    auto & t = get_terrain();
    const auto spawns = gameplay::split_field(t, 6);
    std::cout << t << "\n";
}

TEST_F(RandomlyGeneratedTerrain, SplitField8AndPrint)
{
    auto & t = get_terrain();
    const auto spawns = gameplay::split_field(t, 8);
    std::cout << t << "\n";
}

TEST_F(RandomlyGeneratedTerrain, ConnectedComponents)
{
    const auto & t = get_terrain();
    std::cout << t << "\n";

    const auto cc = gameplay::connected_components(t);

    EXPECT_EQ(cc.size(), 2);

    for (const auto & component : cc)
    {
        for (const auto & cell : component)
            std::cout << cell << " ";
        std::cout << "\n";
    }

    EXPECT_EQ(cc[0].size(), 8);
    EXPECT_EQ(cc[1].size(), 150);
}
