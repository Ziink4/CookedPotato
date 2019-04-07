#include <engine/terrain.h>
#include <engine/point.h>

#include <gameplay/search.h>

#include <gtest/gtest.h>
using GoogleTestFixture = ::testing::Test;

#include <iostream>

TEST(Terrain, ConnectedComponents)
{
    const auto cc = gameplay::connected_components({});

    for (const auto & component : cc)
    {
        std::cout << "Component : ";
        for (const engine::point & cell : component)
            std::cout << cell << " ";
        std::cout << "\n\n";
    }

    ASSERT_EQ(cc.size(), 1);
    EXPECT_EQ(cc[0].size(), 200);
}
