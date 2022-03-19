#include <iostream>

namespace constants
{
    inline constexpr double pi { 3.14159 };
}

using degrees_t = double;
using radians_t = double;

double convertToRadians(degrees_t degrees)
{
    return degrees * constants::pi / 180;
}

int main()
{
    std::cout << "Enter a number of degrees: ";
    degrees_t degrees {};
    std::cin >> degrees;

    radians_t radians { convertToRadians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians.\n";

    return 0;
}