#include <algorithm>
#include <array>
#include <cstddef>
#include <exception>
#include <initializer_list>

template <typename T, std::size_t capacity_>
class StaticVector
{

public:
    // types
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;

    constexpr StaticVector() noexcept : data_{}, size_(0U) {}
    constexpr StaticVector(std::initializer_list<T> list) : data_{}, size_(list.size())
    {
        if (list.size() > capacity_)
        {
            throw std::bad_array_new_length();
        }

        std::copy(std::cbegin(list), std::cend(list), std::begin(data_));
    }

    constexpr void push_back(const T &element)
    {
        if (size_ >= capacity_)
        {
            throw std::bad_array_new_length();
        }

        data_[size_] = element;
        ++size_;
    }

    template <class... Args>
    constexpr reference emplace_back(Args &&...args)
    {
        if (size_ >= capacity_)
        {
            throw std::bad_array_new_length();
        }

        return data_[size_++] = T(std::forward<Args>(args)...);
    }

    constexpr void pop_back()
    {
        if (size_ <= 0)
        {
            throw std::out_of_range("container empty");
        }

        --size_;
    }

    constexpr reference at(const std::size_t index)
    {
        if (index > size_)
        {
            throw std::out_of_range("out of range");
        }

        return data_[index];
    }

    constexpr const_reference at(const std::size_t index) const
    {
        if (index > size_)
        {
            throw std::out_of_range("out of range");
        }

        return data_[index];
    }

    constexpr reference operator[](const std::size_t index)
    {
        return data_[index];
    }

    constexpr const_reference operator[](const std::size_t index) const
    {
        return data_[index];
    }

    constexpr std::size_t size() const noexcept
    {
        return size_;
    }

    constexpr std::size_t capacity() const noexcept
    {
        return capacity_;
    }

    constexpr bool empty() const noexcept
    {
        return size_ == 0;
    }

    constexpr void clear() noexcept
    {
        size_ = 0;
    }

private:
    std::array<T, capacity_> data_;
    std::size_t size_;
};
