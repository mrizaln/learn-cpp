#include <iostream>
#include "constants.h"

int main()
{
    std::cout << "How many student are in you class? ";
    int students {};
    std::cin >> students;

    if (students > constants::max_class_size)
        std::cout << "There are too many students in this class\n";
    else
        std::cout << "This class isn't too large\n";

    return 0;
}