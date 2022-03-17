#include <iostream>

//============[ type casting ]============

// C++ supports 5 different type of casts:
    // C-style cast
    // static casts
    // dynamic casts
    // reinterpret casts

// the latter 4 are sometimes referred to as named casts

// [ warning ]
/*---------------------------------------------------------------------------------------
    avoid consts casts and reinterpret casts unless you have a very good reason to use
    them
---------------------------------------------------------------------------------------*/




//============[ C-style casts ]============

// in standard C, casts are done via () operator

    int main_c_style_casting()
    {
        int x { 10 };
        int y { 4 };

        double d { (double)x / y };     //convert x to double
        std::cout << d << '\n';

    // C++ also let you use a C-style cast with a more function-call like syntax:
        double dd { double(x) / y};
        std::cout << dd << '\n';

        return 0;
    }

// although a C-style cast appears to be a single cast, it can actually perform a variety
// of different conversions depending on context.
// this can include a static cast, a cinst cast, or a reinterpret cast.
// as a result, C-style casts are at risk of being inadvertently misused an not producing
// the expected behaviour.

// [ best practice ]
/*---------------------------------------------------------------------------------------
    avoid using C-style casts
---------------------------------------------------------------------------------------*/




//============[ static_cast ]============

// static_cast can be used to convert a value of one type to a value of another type

    int main_static_cast()
    {
        char c { 'a' };
        std::cout << c << ' ' << static_cast<int>(c) << '\n';       // prints 97

        return 0;
    }

// static_cast is best used to conert one fundamental type into another.

// the main advantage of static_cast is that it provides compile-time type checking, making
// it harder to make an inadvertent error.




//=======================================================================================

int main()
{
    main_c_style_casting();
    main_static_cast();

    return 0;
}