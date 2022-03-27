#include "timeit.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "gtest/gtest.h"

TEST(TimeitSanityTest, VoidReturnNoArguments)
{
    auto const fcn = []() { std::cout << "[D] Side effect!" << std::endl; };

    double const duration = timeit(fcn);

    EXPECT_GT(duration, 0.);
}

TEST(TimeitSanityTest, VoidReturnWithArguments)
{
    auto const fcn = [](int a) { std::cout << "[D] Side effect: " << a << "!" << std::endl; };

    double const duration = timeit(fcn, 3);

    EXPECT_GT(duration, 0.);
}

TEST(TimeitSanityTest, HasReturnNoArguments)
{
    auto const fcn = []() { return 1; };

    auto const result = timeit(fcn);

    double const duration = result.first;
    double const value = result.second;

    EXPECT_GT(duration, 0.);
    EXPECT_EQ(value, 1);
}

TEST(TimeitSanityTest, HasReturnWithArguments)
{
    int const x = 1;
    int const y = 2;

    auto const fcn = [](int a, int b) { return a + b; };

    auto const result = timeit(fcn, x, y);

    double const duration = result.first;
    double const value = result.second;

    EXPECT_GT(duration, 0.);
    EXPECT_EQ(value, x + y);
}

auto get_data(std::size_t n, int max_val)
{
    std::vector<int> vec;
    vec.reserve(n);
    // Add largest value in the front
    vec.push_back(max_val);
    // Then fill with zeros
    std::fill_n(std::back_inserter(vec), n - 1, 0);
    return vec;
}

TEST(TimeitTimingTest, SlowerCallsHaveLongerDuration)
{
    int const max_val{5};

    auto const tiny_vec = get_data(10U, max_val);
    auto const huge_vec = get_data(10000U, max_val);

    auto const sorter = [](auto v) { std::sort(begin(v), end(v)); };

    auto const short_duration = timeit(sorter, tiny_vec);
    auto const long_duration = timeit(sorter, huge_vec);

    EXPECT_LT(short_duration, long_duration);
}

TEST(TimeitTimingTest, CanSetRatio)
{
    int const max_val{5};

    auto const vec1 = get_data(1000U, max_val);
    auto const vec2{vec1};

    auto const sorter = [](auto v) { std::sort(begin(v), end(v)); };

    auto const nanosecs = timeit<std::nano>(sorter, vec1);
    auto const decisecs = timeit<std::deci>(sorter, vec2);

    EXPECT_LT(decisecs, nanosecs);
}
