#include <iostream>
#include "static_vector.h"

int main()
{
    StaticVector<int, 10> vec{1, 2, 3};

    vec.push_back(5);
    vec.push_back(6);
    vec.push_back(7);

    vec.pop_back();

    std::cout << "Container contents:" << std::endl;
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << std::endl;
    }

    return 0;
}