#include <iostream>
#include <iomanip>      // for std::setprecision

//============[  ]============

    void types_of_numeric_conversions()
    {
    // 1. converting an integral type to any other integral type (excluding integral promotions)
        short s = 3;            // int to short
        long l = 3;             // int to long
        char ch = s;            // short to char

    // 2. converting a floating pont type to any other floating point type (excl. floating point promotions)
        float f = 3.0;          // double to float
        long double ld = 3.0;   // double to long double

    // 3. converting a floating point type to any integral type
        int i = 3.5;            // double to int

    // 4. converting an integral type to any floating point type
        double d = 3;           // int to double

    // 5. converting an integral type or floating point type to bool
        bool b1 = 3;            // int to bool
        bool b2 = 3.0;          // double to bool
    }




//============[ narrowing conversions ]============

// unlike a numeric promotion (which is always safe), a numeric conversion may (or may not)
// result in the loss of data or precision.

// always safe                    : int to long, int to double
// may result in the loss of data : double to int.

    void narrowing_conversions()
    {
        int i1 = 3.5;   // the 0.5 is dropped, resulting in the lost of data
        int i2 = 3.0;   // okay, safe no data lost
    }

// in C++ a narrowing conversion is a numeric converseion that may result in the loss of data:
    // 1. floating point to integral type

    // 2. wider floating point to narrower floating point; unless the value being converted
    //    is constexpr and is in range of the destinarion typ (even if the narrower type
    //    doesn't have the presicion to store the whole number).

    // 3. integer to floating point type; unless the value being converted is constexpr and
    //    is in range of the destination type and can be converted back into the original
    //    type without data loss.

    // 4. wider integer to narrower integer; unless the value being converted is constexpr
    //    and after integral promotion will fit into the destination type.

// you don't need to remember these.
// you compiler will usually issue a warning (or error) when it determines that an implicit
// narrowing conversion is required.


// [ warning ]
/*---------------------------------------------------------------------------------------
    compilers will often [not warn] when converting a signed int to an unsigned int, or vice-
    versa, even though these are narrowing conversions. be extra careful of inadvertent conversions
    between these types.
---------------------------------------------------------------------------------------*/


// in general, narrowing conversions should be avided, but there are situational cases when
// you might need to do one.
// in such cases, you should make the implicit narrowing conversion explicit using static_cast

    void someFcn(int i)
    {
        std::cout << i;
    }

    int main_narrowing()
    {
        double d { 5.0 };

        someFcn(d);                     // bad: will generate compiler warning about narrowing conversion
        someFcn(static_cast<int>(d));   // good: explicitly telling the compiler this narrowing is expected

        return 0;
    }


// [ best practice ]
/*---------------------------------------------------------------------------------------
    avoid narrowing conversions whenever possible. if you need to perform one, use static_cast
    to make it an explicit conversion.
---------------------------------------------------------------------------------------*/




//============[ more on numeric conversions ]============

// in all cases, converting a value into a type whose range doesn't support that value will
// lead to results that are probably unexpected.

    int main_unexpected()
    {
        int i { 30000 };
        char c = i;         // chars have range -128 to 127

        std::cout << static_cast<int>(c) <<'\n';

        return 0;
    }


// converting from a larger integral or floating point type to a smaller type from the same
// family will generally work so long as the value fits the range of the smaller type

    int main_expected()
    {
        int i { 2 };
        short s = i;        // 2 is still in range of short
        std::cout << s << '\n';

        double d { 0.1234 };
        float f = d;
        std::cout << f << '\n';

    // in the case of floating point values, some rounding may occur due to a loss of precision
    // in the smaller type
        float f1 = 0.123456789;     // float can only support 7 significant digits
        std::cout << std::setprecision(9) << f1 << '\n';

    // converting from an integer to a floating point number generally works as long as the
    // value fits within the range of the floating point type.
        int i1 { 10 };
        float f2 = i1;
        std::cout << f2 << '\n';

    // converting from a floating point to an integer works as long as the value fits within
    // the range of the integer, but any fractional values are lost
        int i2 = 3.5;
        std::cout << i2 << '\n';

        return 0;
    }


//=======================================================================================

int main()
{
    main_unexpected();
    main_expected();

    return 0;
}