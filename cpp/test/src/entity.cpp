#include <engine/terrain.h> // For engine::Terrain
#include <engine/directions.h>
#include <engine/rng.h> // For engine::RandomNumberGenerator
#include <engine/engine.h> // For engine::print_fancy
#include <engine/obstacle.h> // For engine::Obstacle
#include <engine/character.h> // For engine::Character
#include <engine/search.h> // For engine::Character

#define CATCH_CONFIG_PREFIX_ALL
#include <catch2/catch.hpp>

CATCH_TEST_CASE("Create entity")
{
	engine::Character player(engine::Character::type::player);
	std::cout << player << std::endl;

	engine::Obstacle obstacle;
	std::cout << obstacle << std::endl;
}

CATCH_TEST_CASE("Create player and terrain")
{
	engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);

	engine::Terrain t = generate_terrain(rng);
	std::cout << t << std::endl;

	engine::Character player1(engine::Character::type::player);
	engine::Character player2(engine::Character::type::player);

	std::cout << player1 << std::endl;
	std::cout << player2 << std::endl;

	player2.use_weapon(0, player1);

	std::cout << player1 << std::endl;
	std::cout << player2 << std::endl;

}
