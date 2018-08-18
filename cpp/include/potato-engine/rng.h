#pragma once

#include <random>

namespace engine
{

class RandomNumberGenerator
{
private:
    std::mt19937::result_type m_seed;

    std::mt19937 m_rng;

public:
    using seed_type = std::mt19937::result_type;
    /// the default seed produces a different set of random values on each run
    static constexpr seed_type default_seed = 0;
    /// the fixed seed is set to the mt19937 engine default seed (5489)
    static constexpr seed_type fixed_seed = std::mt19937::default_seed;

    /// default constructor uses default seed
    explicit RandomNumberGenerator() noexcept : RandomNumberGenerator(default_seed) {}

    explicit RandomNumberGenerator(seed_type seed) noexcept : m_seed(seed)
    {
        /// a seed of 0 will randomly create a seed
        if (m_seed == default_seed)
        {
            std::random_device rd;
            // create a random value for the seed
            m_seed = rd();
        }
        // seed the mersenne twister
        m_rng = std::mt19937(m_seed);
    }

    std::mt19937& rand() noexcept { return m_rng; }

    seed_type seed() const noexcept { return m_seed; }
};

} // namespace engine
