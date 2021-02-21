#include <algorithm>
#include <limits>
#include <random>
#include <vector>

template <std::size_t size_>
class RandomIntegerArrayGenerator
{
public:
    using ContainerType = std::vector<int>;

    // Delete copy constructor and assignment operator to prevent copies
    RandomIntegerArrayGenerator(RandomIntegerArrayGenerator const &) = delete;
    void operator=(RandomIntegerArrayGenerator const &) = delete;

    static RandomIntegerArrayGenerator &getInstance()
    {
        static RandomIntegerArrayGenerator instance;

        return instance;
    }

    const ContainerType &getData() const
    {
        return data_;
    }

private:
    RandomIntegerArrayGenerator() : data_(size_, 0)
    {
        std::default_random_engine rnd(123);
        std::uniform_int_distribution<int> dist{std::numeric_limits<int>::min(), std::numeric_limits<int>::max()};

        auto gen = [&dist, &rnd]() {
            return dist(rnd);
        };

        std::generate(std::begin(data_), std::end(data_), gen);
    }

    ContainerType data_;
};
