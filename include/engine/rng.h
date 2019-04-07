/// @file rng.h

#pragma once

#include <random>

namespace engine
{

/// Basic random number engine, with random seed by default.
/// @details Defines a random number engine, fulfilling the UniformRandomBitGenerator concept.
/// (See : https://en.cppreference.com/w/cpp/numeric/random/UniformRandomBitGenerator)
/// This engine will be constructed with a random seed by default.
/// This engine can be used with standard random distributions.
class random_number_engine : public std::mt19937_64
{
public:
    /// Creates a random number engine, with random seed by default.
    /// @details Creates a random number engine.
    /// If the seed is not set the generator will generate a random seed instead.
    /// Users can use this class' default seed to instantiate several random engines with the same seed.
    random_number_engine() noexcept : std::mt19937_64{ std::random_device{}() } {}

    using std::mt19937_64::mt19937_64;
};

} // namespace engine
