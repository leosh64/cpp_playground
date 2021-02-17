#include "data_generator.h"
#include "max_element.h"
#include <iostream>
#include <memory>

int main()
{
    auto data = RandomIntegerArrayGenerator<1000000U>::getInstance().getData();

    std::unique_ptr<IMaxElement<>> impl_p = std::make_unique<StandardLibraryMaxElement<>>();

    const auto max_element = impl_p->Get(data);
    const auto max_value = *max_element;

    std::cout << "Max: " << max_value << std::endl;

    return 0;
}
