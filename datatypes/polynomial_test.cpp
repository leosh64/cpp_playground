#include "datatypes/polynomial.h"
#include "gtest/gtest.h"

TEST(PolynomialTest, ConstructWithArray)
{
    const Polynomial<3> p{{4.0, 5.0, 6.0}};

    const auto coeffs = p.getCoeffs();

    EXPECT_EQ(coeffs[0], 4.0);
    EXPECT_EQ(coeffs[1], 5.0);
    EXPECT_EQ(coeffs[2], 6.0);
}

TEST(PolynomialTest, ConstructWithVariadicTemplate)
{
    // Experimental support
    const Polynomial<3> p{1.0, 2.0, 3.0};

    const auto coeffs = p.getCoeffs();

    EXPECT_EQ(coeffs[0], 1.0);
    EXPECT_EQ(coeffs[1], 2.0);
    EXPECT_EQ(coeffs[2], 3.0);
}

TEST(PolynomialTest, ConstantPolynomialEvaluateYieldsCorrectResults)
{
    const Polynomial<1> p{{42.0}};

    const double range = 5.0;
    const double step = 0.1;

    for (double x = -range; x <= range; x += step)
        EXPECT_EQ(p.evaluate(x), 42.0);
}

TEST(PolynomialTest, LinearPolynomialEvaluateYieldsCorrectResults)
{
    const Polynomial<2> p{{2.0, 1.0}};

    const double range = 5.0;
    const double step = 0.1;

    for (double x = -range; x <= range; x += step)
        EXPECT_EQ(p.evaluate(x), 2.0 * x + 1.0);
}

TEST(PolynomialTest, QuadraticPolynomialEvaluateYieldsCorrectResults)
{
    const Polynomial<3> p{{1.0, 0.0, 0.0}};

    const double range = 5.0;
    const double step = 0.1;

    for (double x = -range; x <= range; x += step)
        EXPECT_EQ(p.evaluate(x), x * x);
}

TEST(PolynomialTest, CanBeUsedInConstexpr)
{
    constexpr Polynomial<5> p{{1.0, 2.0, 3.0, 4.0, 5.0}};

    constexpr auto result = p.evaluate(10.0);

    EXPECT_EQ(result, 12345.0);
}
