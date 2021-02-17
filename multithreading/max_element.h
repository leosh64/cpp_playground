#include <algorithm>
#include <future>
#include <vector>

template <typename ContainerType = std::vector<int>>
class IMaxElement
{
public:
    virtual typename ContainerType::const_iterator Get(const ContainerType &data) const = 0;
};

template <typename ContainerType = std::vector<int>>
class StandardLibraryMaxElement : public IMaxElement<ContainerType>
{
public:
    typename ContainerType::const_iterator Get(const ContainerType &data) const override
    {
        return std::max_element(std::cbegin(data), std::cend(data));
    }
};

template <typename ContainerType = std::vector<int>>
class HomebrewMaxElement : public IMaxElement<ContainerType>
{
public:
    typename ContainerType::const_iterator Get(const ContainerType &data) const override
    {
        auto max_it = std::cbegin(data);
        for (auto it = std::cbegin(data) + 1; it != data.end(); ++it)
        {
            if (*it > *max_it)
            {
                max_it = it;
            }
        }
        return max_it;
    }
};

// template <typename RandomIt>
// RandomIt parallel_max(RandomIt beg, RandomIt end)
// {
//     auto len = end - beg;
//     if (len < 1000)
//         return std::max_element(beg, end);

//     RandomIt mid = beg + len / 2;
//     auto right_handle = std::async(std::launch::async,
//                                    parallel_max<RandomIt>, mid, end);
//     auto left = parallel_max(beg, mid);
//     auto right = right_handle.get();

//     return *left > *right ? left : right;
// }

template <typename RandomIt>
RandomIt dual_parallel_max(RandomIt begin, RandomIt end)
{
    auto len = end - begin;

    RandomIt mid = begin + len / 2;

    // Run max_element on two threads
    auto left_handle = std::async(std::launch::async,
                                  std::max_element<RandomIt>, begin, mid);
    auto right_handle = std::async(std::launch::async,
                                   std::max_element<RandomIt>, mid, end);
    auto left = left_handle.get();
    auto right = right_handle.get();

    return *left > *right ? left : right;
}

template <typename ContainerType = std::vector<int>>
class ParallelMaxElement : public IMaxElement<ContainerType>
{
public:
    typename ContainerType::const_iterator Get(const ContainerType &data) const override
    {
        return dual_parallel_max(std::cbegin(data), std::cend(data));
    }
};
