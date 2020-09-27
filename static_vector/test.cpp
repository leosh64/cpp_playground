#include "gtest/gtest.h"
#include "static_vector.h"

TEST(StaticVectorTest, EmptyWhenUsingDefaultConstructor)
{
    const std::size_t cap = 10;
    StaticVector<int, cap> vec;

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), cap);
}

TEST(StaticVectorTest, CanUseInitializerLists)
{
    StaticVector<int, 10> vec{1, 2, 3};

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(StaticVectorTest, PushBackAddsNewElements)
{
    StaticVector<int, 10> vec{1, 2, 3};

    vec.push_back(4);
    vec.push_back(5);

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
}

TEST(StaticVectorTest, PopBackRemovesElements)
{
    StaticVector<int, 10> vec{1, 2, 3};

    vec.pop_back();
    vec.pop_back();

    EXPECT_EQ(vec.size(), 1);
}

TEST(StaticVectorTest, CanModifyElements)
{
    StaticVector<int, 10> vec{1, 2, 3};

    vec[0]++;

    EXPECT_EQ(vec[0], 2);
}

TEST(StaticVectorTest, EmptyFunctionCorrect)
{
    StaticVector<int, 10> vec{1, 2, 3};
    StaticVector<int, 10> vec2;

    EXPECT_FALSE(vec.empty());
    EXPECT_TRUE(vec2.empty());
}