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

    static constexpr seed_type default_seed = 0;

    static constexpr seed_type fixed_seed = generator::default_seed;

    explicit RandomNumberGenerator(seed_type seed = default_seed) noexcept : m_seed(seed)
    {
        if (m_seed == default_seed)
            m_seed = std::random_device{}();

        m_rng = generator(m_seed);
    }

    generator& rand() noexcept { return m_rng; }
};

} // namespace engine
