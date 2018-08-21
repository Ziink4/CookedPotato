#include <potato-engine/engine.h>
#include <potato-engine/character.h>
#include <potato-engine/obstacle.h>
#include <potato-engine/entity.h>
#include <potato-engine/terrain.h>
#include <potato-engine/rng.h>

#define CATCH_CONFIG_PREFIX_ALL
#include <catch2/catch.hpp>

CATCH_TEST_CASE("Create entity")
{
	engine::Character player(engine::Character::character_type::player);
	std::cout << player << std::endl;

	engine::Obstacle obstacle;
	std::cout << obstacle << std::endl;
}

CATCH_TEST_CASE("Create player and terrain")
{
	engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixed_seed);

	engine::Terrain t = generate_terrain(rng);
	std::cout << t << std::endl;

	engine::Character player(engine::Character::character_type::player);
	std::cout << player << std::endl;

}
