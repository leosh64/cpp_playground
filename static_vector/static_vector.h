#include <algorithm>
#include <array>
#include <cstddef>
#include <exception>
#include <initializer_list>

template <typename T, std::size_t capacity_>
class StaticVector
{

public:
    constexpr StaticVector() : size_(0) {}
    StaticVector(std::initializer_list<T> list)
    {
        if (list.size() > capacity_)
        {
            throw std::bad_array_new_length();
        }

        std::copy(std::cbegin(list), std::cend(list), std::begin(data_));
        size_ = list.size();
    }

    void push_back(const T &element)
    {
        if (size_ < capacity_)
        {
            data_[size_] = element;
            ++size_;
        }
        else
        {
            throw std::bad_array_new_length();
        }
    }

    void pop_back()
    {
        if (size_ > 0)
        {
            --size_;
        }
        else
        {
            throw std::out_of_range("container empty");
        }
    }

    T &at(const std::size_t index)
    {
        if (index > size_)
        {
            throw std::out_of_range("out of range");
        }
        return data_[index];
    }

    const T &at(const std::size_t index) const
    {
        if (index > size_)
        {
            throw std::out_of_range("out of range");
        }
        return data_[index];
    }

    T &operator[](const std::size_t index)
    {
        return data_[index];
    }

    const T &operator[](const std::size_t index) const
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

    void clear() noexcept
    {
        size_ = 0;
    }

private:
    std::array<T, capacity_> data_;
    std::size_t size_;
};
