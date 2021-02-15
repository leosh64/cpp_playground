#include "static_vector.h"
#include "gtest/gtest.h"

TEST(StaticVectorTest, WhenUsingDefaultConstructor_SizeAndCapacityAreCorrect)
{
    const std::size_t cap = 10;
    const StaticVector<int, cap> vec;

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), cap);
}

TEST(StaticVectorTest, WhenUsingInitializerList_ElementsAreAdded)
{
    const StaticVector<int, 10> vec{1, 2, 3};

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(StaticVectorTest, WhenInitializingWithCorrectNumberOfElements_NoExceptionIsThrown)
{
    EXPECT_NO_THROW((StaticVector<int, 2>{1, 2}));
}

TEST(StaticVectorTest, WhenInitializingWithTooManyElements_BadArrayNewLengthExceptionIsThrown)
{
    EXPECT_THROW((StaticVector<int, 2>{1, 2, 3}), std::bad_array_new_length);
}

TEST(StaticVectorTest, WhenCallingPushBack_NewElementsAreAddedInBack)
{
    StaticVector<int, 10> vec{1, 2, 3};

    vec.push_back(4);

    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[3], 4);

    vec.push_back(5);

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
}

TEST(StaticVectorTest, WhenAddingMoreElementsThanCapacity_BadArrayNewLengthExceptionIsThrown)
{
    StaticVector<int, 5> vec{1, 2, 3, 4};

    EXPECT_NO_THROW(vec.push_back(5));

    EXPECT_THROW(vec.push_back(6), std::bad_array_new_length);
}

TEST(StaticVectorTest, WhenCallingPopBack_ElementsAreRemovedFromBack)
{
    StaticVector<int, 10> vec{1, 2, 3};

    vec.pop_back();

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);

    vec.pop_back();

    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec.size(), 1);
}

TEST(StaticVectorTest, WhenRemovingMoreElementsThanSize_OutOfRangeExceptionIsThrown)
{
    StaticVector<int, 5> vec{1, 2};

    EXPECT_NO_THROW(vec.pop_back());
    EXPECT_NO_THROW(vec.pop_back());

    EXPECT_THROW(vec.pop_back(), std::out_of_range);
}

TEST(StaticVectorTest, WhenUsingBracketOperator_ElementsCanBeModified)
{
    StaticVector<int, 10> vec{1, 2, 3};

    vec[0]++;
    vec[1] += 5;

    EXPECT_EQ(vec[0], 2);
    EXPECT_EQ(vec[1], 7);
}

TEST(StaticVectorTest, WhenCallingEmpty_EmptyVectorsReturnTrue)
{
    const StaticVector<int, 10> vec{1, 2, 3};
    const StaticVector<int, 10> vec2;

    EXPECT_FALSE(vec.empty());
    EXPECT_TRUE(vec2.empty());
}

TEST(StaticVectorTest, WhenCallingCapacity_CapacityIsReturnedCorrectly)
{
    const StaticVector<int, 10> vec10_nonempty{1, 2, 3};
    const StaticVector<int, 10> vec10_empty;
    const StaticVector<int, 100> vec100_nonempty{4, 5, 6, 7};
    const StaticVector<int, 100> vec100_empty;

    EXPECT_EQ(vec10_nonempty.capacity(), 10U);
    EXPECT_EQ(vec10_empty.capacity(), 10U);
    EXPECT_EQ(vec100_nonempty.capacity(), 100U);
    EXPECT_EQ(vec100_empty.capacity(), 100U);
}

TEST(StaticVectorTest, WhenCallingClear_VectorIsEmptyAndElementsCanBeAddedAgain)
{
    StaticVector<int, 10> vec{1, 2, 3};

    vec.clear();

    EXPECT_EQ(vec.size(), 0);

    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);

    EXPECT_EQ(vec[0], 4);
    EXPECT_EQ(vec[1], 5);
    EXPECT_EQ(vec[2], 6);
}
