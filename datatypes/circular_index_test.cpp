#include "datatypes/circular_index.h"
#include "gtest/gtest.h"

TEST(CircularIndexTest, WhenDefaultConstructed_ValueIsInitializedToZero)
{
    constexpr std::size_t limit = 5U;
    constexpr CircularIndex<limit> idx;

    EXPECT_EQ(0U, idx.value());
}

TEST(CircularIndexTest, WhenValueConstructed_ValueIsInitializedToSetValue)
{
    constexpr std::size_t limit = 5U;
    constexpr std::size_t value = 3U;
    constexpr CircularIndex<limit> idx{value};

    EXPECT_EQ(value, idx.value());
}

TEST(CircularIndexTest, WhenIncremented_ValueIsIncremented)
{
    constexpr std::size_t limit = 5U;
    CircularIndex<limit> idx;

    ++idx;

    EXPECT_EQ(1U, idx.value());

    idx++;

    EXPECT_EQ(2U, idx.value());

    idx += 1U;

    EXPECT_EQ(3U, idx.value());
}

TEST(CircularIndexTest, WhenDecremented_ValueIsDecremented)
{
    constexpr std::size_t limit = 5U;
    CircularIndex<limit> idx{3U};

    --idx;

    EXPECT_EQ(2U, idx.value());

    idx--;

    EXPECT_EQ(1U, idx.value());

    idx -= 1U;

    EXPECT_EQ(0U, idx.value());
}

TEST(CircularIndexTest, WhenIncrementingOverLimit_OverflowIsHandled)
{
    constexpr std::size_t limit = 5U;
    constexpr std::size_t initial_value = 3U;

    CircularIndex<limit> idx{initial_value};

    idx += limit - initial_value;

    EXPECT_EQ(0U, idx.value());

    idx += limit + 1;

    EXPECT_EQ(1U, idx.value());
}

TEST(CircularIndexTest, WhenDecrementingBelowZero_UnderflowIsHandled)
{
    constexpr std::size_t limit = 5U;
    constexpr std::size_t initial_value = 3U;

    CircularIndex<limit> idx{initial_value};

    idx -= initial_value + 1;

    EXPECT_EQ(limit - 1U, idx.value());

    idx -= limit;

    EXPECT_EQ(limit - 1U, idx.value());
}

TEST(CircularIndexTest, WhenAddingAndAssigning_ResultIsStoredCorrectly)
{
    constexpr std::size_t limit = 5U;

    constexpr CircularIndex<limit> idx{2U};

    constexpr auto new_idx = idx + 2U;

    EXPECT_EQ(4U, new_idx.value());
}

TEST(CircularIndexTest, WhenSubtractingAndAssigning_ResultIsStoredCorrectly)
{
    constexpr std::size_t limit = 5U;

    constexpr CircularIndex<limit> idx{2U};

    constexpr auto new_idx = idx - 3U;

    EXPECT_EQ(4U, new_idx.value());
}

TEST(CircularIndexTest, WhenAddingCircularIndices_ValueIsSetCorrectly)
{
    constexpr std::size_t limit = 5U;

    constexpr CircularIndex<limit> idx1{1U};
    constexpr CircularIndex<limit> idx2{2U};
    constexpr CircularIndex<limit> idx3{4U};

    constexpr auto sum_idx = idx1 + idx2;

    EXPECT_EQ(3U, sum_idx.value());

    constexpr auto overflow_sum_idx = idx2 + idx3;

    EXPECT_EQ(1U, overflow_sum_idx.value());
}

TEST(CircularIndexTest, WhenSubtractingCircularIndices_ValueIsSetCorrectly)
{
    constexpr std::size_t limit = 5U;

    constexpr CircularIndex<limit> idx1{1U};
    constexpr CircularIndex<limit> idx2{2U};
    constexpr CircularIndex<limit> idx3{4U};

    constexpr auto subtr_idx = idx3 - idx1;

    EXPECT_EQ(3U, subtr_idx.value());

    constexpr auto underflow_subtr_idx = idx2 - idx3;

    EXPECT_EQ(3U, underflow_subtr_idx.value());
}

TEST(CircularIndexTest, WhenCheckingForEquality_EqualsReturnTrue)
{
    constexpr std::size_t limit = 5U;

    constexpr CircularIndex<limit> idx1{1U};
    constexpr CircularIndex<limit> idx2{2U};
    constexpr CircularIndex<limit> idx3{1U};

    constexpr bool one_and_two_are_equal = idx1 == idx2;

    EXPECT_FALSE(one_and_two_are_equal);

    constexpr bool one_and_three_are_equal = idx1 == idx3;

    EXPECT_TRUE(one_and_three_are_equal);
}
