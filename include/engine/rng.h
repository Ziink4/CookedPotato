#pragma once

#include <random>

namespace engine
{
/*brief Basic random number engine, with random seed by default.
\details Defines a random number engine, fulfilling the UniformRandomBitGenerator concept.
         (See : https://en.cppreference.com/w/cpp/numeric/random/UniformRandomBitGenerator)
	     This engine can use any standard random engine and will be constructed with a random seed by default.
	     Users can use this class' fixed seed to instantiate several random engines with the same seed.
	     This engine can be used with standard random distributions.
\tparam Type of random number generator to use.
*/
template <class RandomNumberEngine = std::mt19937_64>
class random_number_engine
{
public:
	/// \brief result_type is an unsigned integer type
	using result_type = RandomNumberEngine::result_type;

	/// \brief Returns the smallest value that random_number_engine's operator() may return. The value is strictly less than random_number_engine::max().
	static constexpr result_type min() { return RandomNumberEngine::min(); }

	/// \brief Returns the largest value that random_number_engine's operator() may return. The value is strictly greater than random_number_engine::min().
	static constexpr result_type max() { return RandomNumberEngine::max(); };

	static constexpr result_type default_seed = 0;
	static constexpr result_type fixed_seed = RandomNumberEngine::default_seed;

	/*!
	\brief Creates a random number engine, with random seed by default.
	\details Creates a random number engine.
	         If the seed is not set (or set to default_seed) the generator will generate
	*/
	explicit random_number_generator(result_type seed = default_seed) noexcept
	{
		if (seed == default_seed)
			seed = std::random_device{}();

		m_rne = RandomNumberEngine{ seed };
	}

	/// \brief Returns a value in the closed interval [random_number_engine::min(), random_number_engine::max()]. Has amortized constant complexity.
	result_type operator()() { return m_rne(); }

private:
	RandomNumberEngine m_rne;
};
} // namespace engine
