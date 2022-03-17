#include <iostream>

//============[ implicit type conversion / automatic type conversion / coercion ]============

// implicit type converions is performed automatically by the compiler

    float doSomething(long l)
    {
        return 3.0;     // double to float (return type is different)
    }

    int main_implicit_type_conversion()
    {
        double d{ 3 };  // int to double
        d = 6;          // int to double

        double division{ 4.0 / 3 };         // int value 3 implicitly converted to double

        if (5)      // int value 5 converted to bool
        {
        }

        doSomething(3);     // doSomething has long as its parameter
                            // int value 3 converted to long
    }




//============[ the standard conversions ]============

// the C++ language standard defines how different types can be converted to other types.
// these conversion rules are called the standard conversions.

// the standard conversions can be divided into 4 categories:
    // 1. numeric promotions
    // 2. numeric conversions
    // 3. arithmetic conversions
    // 4. other conversions (which includes various pointer and reference conversions)

// the full set of rules descriing how type conversions work is both lengthy and complicated,
// and for the most part, type conversion "just works".



//=======================================================================================

int main()
{
    main_implicit_type_conversion();

    return 0;
}