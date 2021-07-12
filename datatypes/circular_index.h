#include <array>
#include <cstddef>

#ifndef DATATYPES_CIRCULAR_INDEX_H
#define DATATYPES_CIRCULAR_INDEX_H
template <std::size_t limit_>
class CircularIndex
{

    using external_type = std::size_t;
    using internal_type = int32_t;

public:
    constexpr CircularIndex() : CircularIndex{0U} {}

    constexpr CircularIndex(external_type initial_value) : value_{static_cast<internal_type>(initial_value)}
    {
        static_assert(limit_ > 0U, "Limit must be greater than zero!");
    }

    constexpr external_type value() const { return static_cast<external_type>(value_); }

    // prefix increment
    constexpr CircularIndex &operator++()
    {
        setValue(value_ + 1);
        return *this;
    }

    // postfix increment
    constexpr CircularIndex operator++(int)
    {
        auto old = *this;
        operator++();
        return old;
    }

    constexpr CircularIndex &operator--()
    {
        setValue(value_ - 1);
        return *this;
    }

    constexpr CircularIndex operator--(int)
    {
        auto old = *this;
        operator--();
        return old;
    }

    constexpr friend CircularIndex operator+(CircularIndex lhs,
                                             CircularIndex rhs)
    {
        lhs.setValue(lhs.value_ + rhs.value_);
        return lhs;
    }

    constexpr friend CircularIndex operator+(CircularIndex lhs,
                                             external_type rhs)
    {
        lhs.setValue(lhs.value_ + static_cast<internal_type>(rhs));
        return lhs;
    }

    constexpr friend CircularIndex operator-(CircularIndex lhs,
                                             CircularIndex rhs)
    {
        lhs.setValue(lhs.value_ - rhs.value_);

        return lhs;
    }

    constexpr friend CircularIndex operator-(CircularIndex lhs,
                                             external_type rhs)
    {
        lhs.setValue(lhs.value_ - static_cast<internal_type>(rhs));
        return lhs;
    }

    constexpr CircularIndex &operator+=(const CircularIndex &rhs)
    {
        setValue(value_ + rhs.value_);
        return *this;
    }

    constexpr CircularIndex &operator+=(external_type rhs)
    {
        setValue(value_ + static_cast<internal_type>(rhs));
        return *this;
    }

    constexpr CircularIndex &operator-=(const CircularIndex &rhs)
    {
        setValue(value_ - rhs.value_);
        return *this;
    }

    constexpr CircularIndex &operator-=(external_type rhs)
    {
        setValue(value_ - static_cast<internal_type>(rhs));
        return *this;
    }

    constexpr friend bool operator==(const CircularIndex &lhs, const CircularIndex &rhs) { return lhs.value_ == rhs.value_; }

private:
    constexpr void setValue(internal_type value)
    {
        if (value >= 0)
            value_ = value % static_cast<internal_type>(limit_);
        else
            value_ = value + static_cast<internal_type>(limit_);
    }

    internal_type value_;
};

#endif // DATATYPES_CIRCULAR_INDEX_H
