#pragma once

#include <random>

namespace engine
{

/// Basic random number engine, with random seed by default.
/// @details Defines a random number engine, fulfilling the UniformRandomBitGenerator concept.
/// (See : https://en.cppreference.com/w/cpp/numeric/random/UniformRandomBitGenerator)
/// This engine can use any standard random engine and will be constructed with a random seed by default.
/// Users can use this class' fixed seed to instantiate several random engines with the same seed.
/// This engine can be used with standard random distributions.
/// @tparam RandomNumberEngine The type of random number generator to use.
template <class RandomNumberEngine = std::mt19937_64>
class random_number_engine
{
public:
	/// An unsigned integer type.
	using result_type = typename RandomNumberEngine::result_type;

	/// Retrieves the smallest value that @ref operator()() may return. The value is strictly less than @ref max().
	/// @return The smallest value that @ref operator()() may return.
	static constexpr result_type min() noexcept { return RandomNumberEngine::min(); }

	/// Retrieves the largest value that @ref operator()() may return. The value is strictly greater than @ref min().
	/// @return The largest value that @ref operator()() may return.
	static constexpr result_type max() noexcept { return RandomNumberEngine::max(); }

	/// Use this seed to initialize the generator with a random seed.
	static constexpr result_type default_seed = 0;

	/// Use this seed to initialize the generator with a fixed seed.
	static constexpr result_type fixed_seed = RandomNumberEngine::default_seed;

	/// Creates a random number engine, with random seed by default.
	/// @details Creates a random number engine.
	/// If the seed is not set (or set to @ref default_seed) the generator will generate a random seed instead.
	/// Users can use this class' @ref fixed_seed to instantiate several random engines with the same seed.
	/// @param seed The seed value to use in the initialization of the internal state.
	explicit random_number_engine(result_type seed = default_seed) noexcept
	{
		if (seed == default_seed)
			seed = std::random_device{}();

		m_rne = RandomNumberEngine{ seed };
	}

	/// Advances the engine's state and returns the generated value .
	/// @return A random value in the closed interval [@ref min(), @ref max()]. Has amortized constant complexity.
	result_type operator()() noexcept { return m_rne(); }

private:
	RandomNumberEngine m_rne;
};

} // namespace engine
