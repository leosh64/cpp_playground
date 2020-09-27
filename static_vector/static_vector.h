#include <array>
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <algorithm>

template <typename T, std::size_t capacity_>
class StaticVector
{

public:
    StaticVector() : size_(0) {}
    StaticVector(std::initializer_list<T> list) : size_(list.size())
    {
        if (list.size() > size_)
        {
            throw std::bad_array_new_length();
        }
        std::size_t counter = 0;
        std::for_each(list.begin(), list.end(), [&](T element) { data_[counter] = element; ++counter; });
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

    T &operator[](const std::size_t index)
    {
        if (index > size_)
        {
            throw std::out_of_range("out of range");
        }
        return data_[index];
    }

    std::size_t size() const
    {
        return size_;
    }

    std::size_t capacity() const
    {
        return capacity_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    void clear()
    {
        size_ = 0;
    }

private:
    std::array<T, capacity_> data_;
    std::size_t size_;
};
