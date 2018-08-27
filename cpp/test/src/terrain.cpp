#include <potato-engine/terrain.h> // For engine::Terrain
#include <potato-engine/directions.h>
#include <potato-engine/rng.h> // For engine::RandomNumberGenerator
#include <potato-engine/engine.h> // For engine::print_fancy
#include <potato-engine/obstacle.h> // For engine::Obstacle
#include <potato-engine/character.h> // For engine::Character
#include <potato-engine/search.h> // For engine::Character

#define CATCH_CONFIG_PREFIX_ALL
#include <catch2/catch.hpp>

#include <iostream>

CATCH_TEST_CASE("Point-Cell Transforms")
{
	constexpr engine::point_type pt{5, 3};
	constexpr engine::point_type pt_2 = engine::get_pt(engine::get_cell(pt));
	static_assert(pt == pt_2);
	CATCH_CHECK(pt == pt_2);

	constexpr engine::cell_type cell{37};
	constexpr engine::cell_type cell_2 = engine::get_cell(engine::get_pt(cell));
	static_assert(cell == cell_2);
	CATCH_CHECK(cell == cell_2);
}

CATCH_TEST_CASE("Check Valid Cell")
{
	// Invalid cell
	constexpr std::size_t cell_invalid{engine::terrain_area + 1};
	static_assert(!engine::is_valid(cell_invalid));
	CATCH_CHECK_FALSE(engine::is_valid(cell_invalid));

	// Valid cell
	constexpr std::size_t cell_valid{engine::terrain_area - 1};
	static_assert(engine::is_valid(cell_valid));
	CATCH_CHECK(engine::is_valid(cell_valid));
}

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
	for (const auto& team : spawns)
	{
		for (const auto& cell : team)
		{
			t[cell].reset(new engine::Character(engine::Character::type::npc));
		}
		std::cout << t << std::endl;
	}

	std::cout << t << std::endl;

	t = generate_terrain(rng);
	engine::split_field(t, 6);
	std::cout << t << std::endl;

	t = generate_terrain(rng);
	engine::split_field(t, 8);
	std::cout << t << std::endl;
}

CATCH_TEST_CASE("Generate Directions map")
{
	constexpr engine::Directions d = {};
	std::cout << d.data[0] << std::endl;
}

CATCH_TEST_CASE("Connected Components")
{
	constexpr engine::Directions d = {};
	const auto cc = engine::connected_components(d, {});
	for (const auto& component : cc)
	{
		std::cout << "Component : ";
		for (const auto& cell : component)
		{
			std::cout << cell << " ";
		}
		std::cout << std::endl;
	}
}

CATCH_TEST_CASE("Generate Terrain and CC")
{
	std::cout << "START" << std::endl;

	engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);
	const engine::Terrain t = generate_terrain(rng);
	std::cout << t << std::endl;

	constexpr engine::Directions d = {};
	const auto cc = engine::connected_components(d, t);

	std::cout << cc.size() << " components" << std::endl;

	for (const auto& component : cc)
	{
		std::cout << "Component of size " << component.size() << " : ";
		for (const auto& cell : component)
		{
			std::cout << cell << " ";
		}
		std::cout << std::endl;
	}
}
