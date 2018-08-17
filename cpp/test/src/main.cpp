#include <potato-engine/engine.h> // For engine::print_fancy
#include <potato-engine/terrain.h> // For engine::Terrain
#include <potato-engine/rng.h> // For engine::RandomNumberGenerator

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_PREFIX_ALL
#include <catch2/catch.hpp>

CATCH_TEST_CASE("Print Test")
{
	CATCH_CHECK_NOTHROW(engine::print_fancy());
}

CATCH_TEST_CASE("Point-Cell Transforms")
{
	constexpr engine::Point pt{5, 3};
	constexpr engine::Point pt_2 = engine::terrain::get_pt(engine::terrain::get_cell(pt));
	static_assert(pt == pt_2);
	CATCH_CHECK(pt == pt_2);

	constexpr std::size_t cell{37};
	constexpr std::size_t cell_2 = engine::terrain::get_cell(engine::terrain::get_pt(cell));
	static_assert(cell == cell_2);
	CATCH_CHECK(cell == cell_2);
}

CATCH_TEST_CASE("Check Valid Cell")
{
	// Invalid cell
	constexpr std::size_t cell_invalid{engine::terrain::area + 1};
	static_assert(!engine::terrain::is_valid(cell_invalid));
	CATCH_CHECK_FALSE(engine::terrain::is_valid(cell_invalid));

	// Valid cell
	constexpr std::size_t cell_valid{engine::terrain::area - 1};
	static_assert(engine::terrain::is_valid(cell_valid));
	CATCH_CHECK(engine::terrain::is_valid(cell_valid));
}

CATCH_TEST_CASE("Print Point")
{
	constexpr engine::Point pt{5, 3};
	CATCH_CHECK_NOTHROW(std::cout << pt << std::endl);
}

CATCH_TEST_CASE("Print Terrain")
{
	constexpr engine::terrain::Terrain t{};
	CATCH_CHECK_NOTHROW(std::cout << t << std::endl);
}

CATCH_TEST_CASE("Generate Terrain")
{
	engine::RandomNumberGenerator rng(engine::RandomNumberGenerator::fixedSeed);
	const engine::terrain::Terrain t = generate_terrain(rng);
	CATCH_CHECK_NOTHROW(std::cout << t << std::endl);
}

