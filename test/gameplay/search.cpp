#include <engine/terrain.h>
#include <engine/rng.h>

#include <gameplay/search.h>

#include <gtest/gtest.h>
using GoogleTestFixture = ::testing::Test;

TEST(Terrain, ConnectedComponents)
{
    const auto cc = gameplay::connected_components({});

    EXPECT_EQ(cc.size(), 1);

    for (const auto & component : cc)
    {
        std::cout << "Component : ";
        for (const auto & cell : component)
            std::cout << cell << " ";
        std::cout << "\n";
    }

    EXPECT_EQ(cc[0].size(), 200);
}
