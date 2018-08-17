#include <potato-engine/engine.h>
#include <potato-engine/terrain.h>
#include <potato-engine/rng.h>

#include "main.h"

#include <algorithm>
#include <random>

namespace engine
{

void print_fancy()
{
	std::cerr << "WOOO" << std::endl;
	std::cerr << terrain::width << std::endl;
	print();
}

terrain::Terrain generate_terrain(RandomNumberGenerator& rng) noexcept
{
	static constexpr auto density = 0.2f;
	static constexpr auto decor_count = static_cast<std::size_t>(terrain::area * density);

	static std::uniform_int_distribution<> distribution(0, terrain::area + 1);

	static std::array<terrain::Terrain::size_type, decor_count> obstacles{};

	std::generate(obstacles.begin(), obstacles.end(), [&] { return distribution(rng.rand()); });

	terrain::Terrain t = {};

	for (auto obstacle : obstacles)
	{
		t[obstacle].type = CellType::decor;
	}

	return t;
}

}
