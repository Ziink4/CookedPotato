#include <engine/vector.h>

#include <iostream>

#include <gtest/gtest.h>
using GoogleTestFixture = ::testing::Test;

TEST(Vector, Arithmetic)
{
    constexpr engine::vector_2d<int> pt1{ 5, 3 };
    constexpr engine::vector_2d<int> pt2{ 8, 1 };

    constexpr engine::vector_2d<int> pt3 = pt1 + pt2;
    std::cout << pt3 << "\n";

    constexpr engine::vector_2d<int> pt4 = pt1 - pt2;
    std::cout << pt4 << "\n";

    constexpr engine::vector_2d<int> pt5 = 3 * pt1;
    std::cout << pt5 << "\n";
    constexpr engine::vector_2d<int> pt6 = pt2 * 4;
    std::cout << pt6 << "\n";

    constexpr engine::vector_2d<int> pt8 = -1 * pt3;
    std::cout << pt8 << "\n";

    constexpr engine::vector_2d<int> pt9 = 3 / pt1;
    std::cout << pt9 << "\n";

    constexpr engine::vector_2d<int> pt10 = pt2 / 2;
    std::cout << pt10 << "\n";

    engine::polar_vector_2d<int> p1 { 42, 88 };
    engine::cartesian_vector_2d<int> p3 = to_cartesian(p1);
    std::cout << p3 << "\n";
}
