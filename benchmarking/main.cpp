#include "data_generator.h"
#include "max_element.h"
#include <iostream>
#include <vector>

int main()
{
    auto data = RandomIntegerArrayGenerator<1000000U>::getInstance().getData();

    using iterator_t = decltype(std::cbegin(data));
    using fcn_type = decltype(&max_element_homebrew<iterator_t>);

    // List of functions to be tested
    std::vector<fcn_type> funcs{std::max_element<iterator_t>, max_element_homebrew<iterator_t>, max_element_parallel<iterator_t>, max_element_divide_and_conquer<iterator_t>};

    for (auto func : funcs)
    {
        const auto max_element = func(std::cbegin(data), std::cend(data));
        const auto max_value = *max_element;

        std::cout << "Max: " << max_value << std::endl;
    }

    return 0;
}
