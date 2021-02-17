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

class MaxElementTestSuite : public testing::TestWithParam<std::shared_ptr<IMaxElement<>>>
{
};

TEST_P(MaxElementTestSuite, WhenCallingGetOnManualContainer_MaxElementIsReturned)
{
    const std::vector<int> data{1, 2, 3, 4, 5};

    auto max_element_instance = GetParam();
    const auto max_element = max_element_instance->Get(data);

    EXPECT_EQ(*max_element, 5);
}

TEST_P(MaxElementTestSuite, WhenCallingGetOnRandomContainer_MaxElementIsReturned)
{
    const auto data = RandomIntegerArrayGenerator<100000U>::getInstance().getData();

    // Reference data
    const auto ref_max_element = std::max_element(std::cbegin(data), std::cend(data));

    // Test the function
    auto max_element_instance = GetParam();
    const auto max_element = max_element_instance->Get(data);

    EXPECT_EQ(*max_element, *ref_max_element);
}

INSTANTIATE_TEST_SUITE_P(
    TestGroup,
    MaxElementTestSuite,
    ::testing::Values(
        std::make_shared<StandardLibraryMaxElement<>>(),
        std::make_shared<HomebrewMaxElement<>>(),
        std::make_shared<ParallelMaxElement<>>()));
