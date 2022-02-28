// The order of evaluation of expression is mostly unspecified

#include <iostream>

int getValue()
{
    std::cout << "Enter an integer: ";

    int x{};
    std::cin >> x;
    return x;
}

int main()
{
    std::cout << getValue() + (getValue() * getValue()); // a + (b * c)
    return 0;
}

/*
    if you run this program and inputs 1, 2, and 3, you might assume that this prgoram
    would print 7. but that is making the assumption that the calls to getValue() will
    evaluate in left-to-right order. the compiler may choose a different order. for example
    if the compiler choose a right-to-left order instead, the program would print 5 for
    the same set of inputs. 
*/
