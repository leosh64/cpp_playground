#include "datatypes/polynomial.h"
#include <array>
#include <iostream>

int main()
{
    constexpr Polynomial<3> p{{1.0, 0.0, 0.0}};

    std::cout << "Evaluated polynomial points:" << std::endl;
    for (double x = 0; x < 10.0; x += 1.0)
    {
        std::cout << "p(" << x << ")=" << p.evaluate(x) << std::endl;
    }

    // Test if result in evaluate can be used where a constexpr must be used
    std::cout << "Use p(3) as array size:" << std::endl;
    std::array<int, static_cast<std::size_t>(p.evaluate(3.))> arr;
    std::cout << "arr.size() = " << arr.size() << std::endl;

    return 0;
}
