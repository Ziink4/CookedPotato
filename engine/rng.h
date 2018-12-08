#pragma once

#include <random>

namespace engine
{

class RandomNumberGenerator
{
private:
	using generator = std::mt19937;

	generator::result_type m_seed;

	generator m_rng;

public:
	using seed_type = generator::result_type;
	/// the default seed produces a different set of random values on each run
	static constexpr seed_type default_seed = 0;
	/// the fixed seed is set to the generator default seed
	static constexpr seed_type fixed_seed = generator::default_seed;

	explicit RandomNumberGenerator(seed_type seed = default_seed) noexcept : m_seed(seed)
	{
		/// a seed of 0 will randomly create a seed
		if (m_seed == default_seed)
		{
			std::random_device rd;
			// create a random value for the seed
			m_seed = rd();
		}
		// seed the generator
		m_rng = generator(m_seed);
	}

	generator& rand() noexcept { return m_rng; }
};

} // namespace engine
