#pragma once

#include <potato-engine/terrain.h>
#include <potato-engine/rng.h>

namespace engine
{

void print_fancy();

terrain::Terrain generate_terrain(RandomNumberGenerator& rng) noexcept;

void split_field(terrain::Terrain& t, std::size_t parts) noexcept;

} // namespace engine
