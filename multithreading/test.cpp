#include "data_generator.h"
#include "max_element.h"
#include "gtest/gtest.h"
#include <array>
#include <memory>

TEST(RandomIntegerArrayGeneratorTest, WhenCallingGetData_DataContainerIsReturned)
{
    constexpr std::size_t size = 1000U;

    const auto data = RandomIntegerArrayGenerator<size>::getInstance().getData();

    EXPECT_EQ(data.size(), size);
    // Not all elements should be the same
    EXPECT_FALSE(std::equal(std::cbegin(data) + 1, std::cend(data), std::cbegin(data)));
}

/// TODO: Avoid specifying here, use either from data_generator or via decltype
using iterator_t = std::vector<int>::const_iterator;
using function_t = decltype(&max_element_homebrew<iterator_t>);

class MaxElementTestSuite : public testing::TestWithParam<function_t>
{
};

TEST_P(MaxElementTestSuite, WhenCallingGetOnManualContainer_MaxElementIsReturned)
{
    const std::vector<int> data{1, 2, 3, 4, 5};

    auto func = GetParam();
    const auto max_element = func(std::cbegin(data), std::cend(data));

    EXPECT_EQ(*max_element, 5);
}

TEST_P(MaxElementTestSuite, WhenCallingGetOnRandomContainer_MaxElementIsReturned)
{
    const auto data = RandomIntegerArrayGenerator<100000U>::getInstance().getData();

    // Reference data
    const auto ref_max_element = std::max_element(std::cbegin(data), std::cend(data));

    // Test the function
    auto func = GetParam();
    const auto max_element = func(std::cbegin(data), std::cend(data));

    EXPECT_EQ(*max_element, *ref_max_element);
}

INSTANTIATE_TEST_SUITE_P(
    TestGroup,
    MaxElementTestSuite,
    ::testing::Values(
        std::max_element<iterator_t>,
        max_element_homebrew<iterator_t>,
        max_element_parallel<iterator_t>,
        max_element_divide_and_conquer<iterator_t>));
