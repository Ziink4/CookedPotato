#pragma once

namespace engine
{

class random_number_engine;
class Terrain;

} // namespace engine

namespace gameplay
{

engine::Terrain generate_terrain(engine::random_number_engine & rng, double density = 0.25) noexcept;

} // namespace gameplay
