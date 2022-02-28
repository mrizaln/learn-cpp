//========[ explicit type conversion using static_cast ]========
// syntax:      static_cast<new_type>(expression)

#include <iostream>

void print(int x)
{
    std::cout << x;
}

int main_0()
{
    print( static_cast<int>(5.5) );

    char ch{97};
    std::cout << ch << " has value " << static_cast<int>(ch) << '\n';

    return 0;
}

/*
    static_cast operator does'n do any range checking, so if you cast a value to a type whose
    range doesn't contain that value, undefined behaviour will result
*/


//========[ std::int8_t and std::uint8_t likely behave like chars instead of integers ]========

#include <cstdint>
#include <iostream>

int main_1()
{
    std::int8_t myint{65}; // initialize myint with value 65
    std::cout << myint << '\n';    // you're probably expecting this to print 65, but print A instead
    std::cout << static_cast<int>( myint ) << '\n';     // will always print 65

    std::cout << "Enter a number between 0 and 255: ";
    std::cin >> myint;
    std::cout << "You entered (static casted)   : " << static_cast<int>( myint ) << '\n';
    std::cout << "You entered (not being casted): " << myint << '\n';

    return 0;
}

int main()
{
    main_1();
}