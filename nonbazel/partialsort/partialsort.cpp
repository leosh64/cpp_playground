#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <utility>
#include <vector>

#include "../../utils/timeit.h"

/**
 * @brief Get vector with random data
 *
 * @tparam T type of data to be generated
 * @param size number of elements
 * @param seed seed for the random number generator
 * @return std::vector<T> vector of random elements
 */
template <class T> std::vector<T> get_data(std::size_t size, std::size_t seed = 42U)
{
    // Seed engine with seed and size so that the vectors of different size don't all start with the same numbers
    std::mt19937 engine(seed * size);
    std::uniform_int_distribution<T> distrib(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max());

    std::vector<T> result;
    result.reserve(size);

    auto gen = [&distrib, &engine]() { return distrib(engine); };

    std::generate_n(std::back_inserter(result), size, gen);

    return result;
}

/**
 * @brief Run benchmark with all sorting methods for given type and size
 *
 * @tparam ElementType type of the elements to be sorted
 * @param buffer_size number of elements
 */
template <class ElementType> void run_benchmark(std::size_t buffer_size)
{
    std::cerr << "[I] Requiring " << static_cast<double>(sizeof(ElementType) * buffer_size) / 1024. / 1024. << " MB for "
              << buffer_size << " elements of type " << typeid(ElementType).name() << std::endl;

    const double fraction{0.1};

    double const duration_sort = [buffer_size] {
        auto data{get_data<ElementType>(buffer_size)};
        return timeit([&data]() { std::sort(begin(data), end(data)); });
    }();

    double const duration_partial_sort = [buffer_size, fraction] {
        auto data{get_data<ElementType>(buffer_size)};
        auto cutoff = begin(data) + fraction * data.size();
        return timeit([&data, &cutoff]() { std::partial_sort(begin(data), cutoff, end(data)); });
    }();

    double const duration_nth_element_sort = [buffer_size, fraction] {
        auto data{get_data<ElementType>(buffer_size)};
        auto cutoff = begin(data) + fraction * data.size();
        return timeit([&data, &cutoff]() {
            std::nth_element(begin(data), cutoff, end(data));
            std::sort(begin(data), cutoff);
        });
    }();

    std::cerr << "[I] Printing results: buffer_size, sort, partialsort, nthelement" << std::endl;
    std::cout << buffer_size << ", " << duration_sort << ", " << duration_partial_sort << ", "
              << duration_nth_element_sort << std::endl;
}

int main(int argc, const char* argv[])
{
    if (argc != 2 && argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " N [DataType]" << std::endl;
        std::cerr << "  N         buffer size" << std::endl;
        std::cerr << "  DataType  data type (int8, int16, int32, int64, default: int32)" << std::endl;
        return 1;
    }

    /// TODO: Add some error handling here
    std::uint64_t const buffer_size{std::stoul(std::string{argv[1]})};

    std::string datatype{"int32"};

    if (argc == 3)
    {
        datatype = argv[2];
    }

    // Unfortunately cannot switch on string in C++
    if (datatype == "int8")
    {
        run_benchmark<std::int8_t>(buffer_size);
    }
    if (datatype == "int16")
    {
        run_benchmark<std::int16_t>(buffer_size);
    }
    else if (datatype == "int32")
    {
        run_benchmark<std::int32_t>(buffer_size);
    }
    else if (datatype == "int64")
    {
        run_benchmark<std::int64_t>(buffer_size);
    }
    else
    {
        std::cerr << "[E] Unsupported datatype '" << datatype << "'! Aborting..." << std::endl;
        return 1;
    }

    return 0;
}
