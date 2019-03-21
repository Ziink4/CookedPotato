#include <engine/vector.h>

#include <iostream>

#include <gtest/gtest.h>
using GoogleTestFixture = ::testing::Test;

TEST(Vector2D, Equals)
{
    constexpr engine::vector_2d<int> a{ 5, 3 };
    constexpr engine::vector_2d<int> b{ 8, -1 };
    constexpr engine::vector_2d<int> c{ 8, -1 };

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(b == c);
}

TEST(Vector2D, NotEquals)
{
    constexpr engine::vector_2d<int> a{ 5, 3 };
    constexpr engine::vector_2d<int> b{ 8, -1 };
    constexpr engine::vector_2d<int> c{ 8, -1 };

    EXPECT_TRUE(a != b);
    EXPECT_FALSE(b != c);
}

TEST(Vector2D, Addition)
{
    constexpr engine::vector_2d<int> a{ 5, 3 };
    constexpr engine::vector_2d<int> b{ 8, -1 };

    constexpr engine::vector_2d<int> c{ 13, 2 };

    EXPECT_EQ(a + b, c);
}

TEST(Vector2D, Substraction)
{
    constexpr engine::vector_2d<int> a{ 5, 3 };
    constexpr engine::vector_2d<int> b{ 8, -1 };

    constexpr engine::vector_2d<int> c{ -3, 4 };

    EXPECT_EQ(a - b, c);
}

TEST(Vector2D, ScalarMultiplication)
{
    constexpr engine::vector_2d<int> a{ 5, -3 };
    constexpr int b = 3;
    constexpr int c = -12;

    constexpr engine::vector_2d<int> ab{ 15, -9 };
    constexpr engine::vector_2d<int> ca{ -60, 36 };

    EXPECT_EQ(a * b, ab);
    EXPECT_EQ(c * a, ca);
}

TEST(Vector2D, ScalarDivision)
{
    constexpr engine::vector_2d<int> a{ 15, -3 };
    constexpr int b = 3;
    constexpr int c = -30;

    constexpr engine::vector_2d<int> ab{ 5, -1 };
    constexpr engine::vector_2d<int> ca{ -2, 10 };

    EXPECT_EQ(a / b, ab);
    EXPECT_EQ(c / a, ca);
}

TEST(Vector2D, CartesianCoordinates)
{
    constexpr engine::cartesian_vector_2d<int> a{ 5, -3 };

    EXPECT_EQ(a.x(), 5);
    EXPECT_EQ(a.y(), -3);
}

TEST(Vector2D, PolarCoordinates)
{
    constexpr engine::polar_vector_2d<int> a{ 5, -3 };

    EXPECT_EQ(a.rho(), 5);
    EXPECT_EQ(a.theta(), -3);
}

constexpr double epsilon = 1e-9;

TEST(Vector2D, PolarToCartesian)
{
    constexpr engine::polar_vector_2d<double> a{ 5.0, -3.0 };

    constexpr engine::cartesian_vector_2d<double> b{ -4.949962483, -0.70560004029 };

    engine::cartesian_vector_2d<double> c = engine::to_cartesian(a);

    EXPECT_NEAR(b.x(), c.x(), epsilon);
    EXPECT_NEAR(b.y(), c.y(), epsilon);
}

TEST(Vector2D, CartesianToPolar)
{
    constexpr engine::cartesian_vector_2d<double> a{ 5.0, -3.0 };

    constexpr engine::polar_vector_2d<double> b{ 5.83095189485, -0.5404195 };

    engine::polar_vector_2d<double> c = engine::to_polar(a);

    EXPECT_NEAR(b.rho(), c.rho(), epsilon);
    EXPECT_NEAR(b.theta(), c.theta(), epsilon);
}