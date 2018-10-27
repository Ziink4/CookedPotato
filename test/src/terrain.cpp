#include <engine/terrain.h> // For engine::Terrain
#include <engine/directions.h>
#include <engine/rng.h> // For engine::RandomNumberGenerator
#include <engine/engine.h> // For engine::print_fancy
#include <engine/obstacle.h> // For engine::Obstacle
#include <engine/character.h> // For engine::Character
#include <engine/search.h> // For engine::Character

#include <gtest/gtest.h>

#include <iostream>

TEST(Terrain, PrintPoint)
{
	constexpr engine::point_type pt{5, 3};
	std::cout << pt << std::endl;
}

TEST(Terrain, PrintTerrain)
{
	const engine::Terrain t{};
	std::cout << t << std::endl;
}

TEST(Terrain, GenerateTerrain)
{
	engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);
	const engine::Terrain t = generate_terrain(rng);
	std::cout << t << std::endl;
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

	std::cout << t << std::endl;

	t = generate_terrain(rng);
	engine::split_field(t, 6);
	std::cout << t << std::endl;

	t = generate_terrain(rng);
	engine::split_field(t, 8);
	std::cout << t << std::endl;
}

TEST(Terrain, ConnectedComponents)
{
	const auto cc = engine::connected_components({});

	EXPECT_EQ(cc.size(), 1);

	for (const auto& component : cc)
	{
		std::cout << "Component : ";
		for (const auto& cell : component)
		{
			std::cout << cell << " ";
		}
		std::cout << std::endl;
	}

	EXPECT_EQ(cc[0].size(), 200);

}

TEST(Terrain, GenerateTerrainAndCC)
{
	std::cout << "START" << std::endl;

	engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);
	const engine::Terrain t = generate_terrain(rng);
	std::cout << t << std::endl;

	const auto cc = engine::connected_components(t);

	std::cout << cc.size() << " components" << std::endl;

	EXPECT_EQ(cc.size(), 2);

	for (const auto& component : cc)
	{
		std::cout << "Component of size " << component.size() << " : ";
		for (const auto& cell : component)
		{
			std::cout << cell << " ";
		}
		std::cout << std::endl;
	}

	EXPECT_EQ(cc[0].size(), 8);
	EXPECT_EQ(cc[1].size(), 150);
}
