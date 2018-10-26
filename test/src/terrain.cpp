#include <engine/terrain.h> // For engine::Terrain
#include <engine/directions.h>
#include <engine/rng.h> // For engine::RandomNumberGenerator
#include <engine/engine.h> // For engine::print_fancy
#include <engine/obstacle.h> // For engine::Obstacle
#include <engine/character.h> // For engine::Character
#include <engine/search.h> // For engine::Character

#define CATCH_CONFIG_PREFIX_ALL
#include <catch2/catch.hpp>

#include <iostream>

CATCH_TEST_CASE("Print Point")
{
	constexpr engine::point_type pt{5, 3};
	std::cout << pt << std::endl;
}

CATCH_TEST_CASE("Print Terrain")
{
	const engine::Terrain t{};
	std::cout << t << std::endl;
}

CATCH_TEST_CASE("Generate Terrain")
{
	engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);
	const engine::Terrain t = generate_terrain(rng);
	std::cout << t << std::endl;
}

CATCH_TEST_CASE("Generate Terrain and Split Field")
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

CATCH_TEST_CASE("Connected Components")
{
	const auto cc = engine::connected_components({});

	CATCH_CHECK(cc.size() == 1);

	for (const auto& component : cc)
	{
		std::cout << "Component : ";
		for (const auto& cell : component)
		{
			std::cout << cell << " ";
		}
		std::cout << std::endl;
	}

	CATCH_CHECK(cc[0].size() == 200);

}

CATCH_TEST_CASE("Generate Terrain and CC")
{
	std::cout << "START" << std::endl;

	engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);
	const engine::Terrain t = generate_terrain(rng);
	std::cout << t << std::endl;

	const auto cc = engine::connected_components(t);

	std::cout << cc.size() << " components" << std::endl;

	CATCH_CHECK(cc.size() == 2);

	for (const auto& component : cc)
	{
		std::cout << "Component of size " << component.size() << " : ";
		for (const auto& cell : component)
		{
			std::cout << cell << " ";
		}
		std::cout << std::endl;
	}

	CATCH_CHECK(cc[0].size() == 8);
	CATCH_CHECK(cc[1].size() == 150);
}
