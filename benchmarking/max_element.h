#include <algorithm>
#include <future>

/// For reference: std::max_element has the following signature
// template<class ForwardIt>
// ForwardIt std::max_element(ForwardIt first, ForwardIt last)

template <typename ForwardIt>
ForwardIt max_element_homebrew(ForwardIt begin, ForwardIt end)
{
    if (begin == end)
        return end;

    auto max_it = begin;
    for (auto it = ++begin; it != end; ++it)
    {
        if (*it > *max_it)
        {
            max_it = it;
        }
    }
    return max_it;
}

template <typename RandomIt>
RandomIt max_element_parallel(RandomIt begin, RandomIt end)
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

template <typename RandomIt>
RandomIt max_element_divide_and_conquer(RandomIt begin, RandomIt end)
{
    if (begin == end)
        return end;
    if (begin + 1 == end)
        return begin;

    auto len = end - begin;

    RandomIt mid = begin + len / 2;

    auto left = max_element_divide_and_conquer(begin, mid);
    auto right = max_element_divide_and_conquer(mid, end);

    return *left > *right ? left : right;
}
