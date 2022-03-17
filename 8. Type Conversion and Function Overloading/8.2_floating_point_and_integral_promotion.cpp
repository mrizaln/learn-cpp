#include <iostream>

//============[ numeric promotion ]============

// a numeric promotion is the type conversion of a narrower numeric type to a wider numeric
// type that can be processed efficiently and is less likely to have a result that overflows.

// all numeric promotions are value-preserving, which means that all values in the original
// type are representable without loss of data or precision in the new type.
// because such promotions are safe, the compiler will freely use numeric promotion as needed,
// and will not issue a warning when doing so.




//============[ numeric promotion reduces redundancy ]============

// consider the case where you wanted to write a function to print a value of type int:

    void printInt(int x)
    {
        std::cout << x;
    }

// what happens of we want to also be able to print a value of type short, ot type char?
// if type conversions did not exist, we'd have to write a different print function for short, 
// then for char, then unsigned char, signed char, unsigned short, wchar_t, char8_t, char16_t,
// and char32_t.

// numeric promotion comes to the rescue here:
// we can write functions that have int and/or double parameters (such as above).
// that same code can the be called with an arguments of types that can be numerically promoted
// to match the types of the function parameters.




//============[ numeric promotion categories ]============

// the numeric promotion rules are divided into two categories:
    // 1. integral promotions
    // 2. floating point promotions




//============[ floating point promotions ]============

// a value of float can be converted to a value of type double.

    void printDouble( double d)
    {
        std::cout << d <<'\n';
    }

    int main_printDouble()
    {
        printDouble(5.0);   // no conversion necessary
        printDouble(5.0f);  // numeric promotion of float to double

        return 0;
    }




//============[ integral promotion ]============

// using this rules, the following can be made:
    // 1. signed char or signed short can be converted to int
    
    // 2. unsigned char, char8_t, and unsigned short can be converted to int f int can hold the
    //    entire range of the type, or unsigned int otherwise

    // 3. if char is signed by default, it follows the signed char conversion above. if it
    //    is unsigned by default, it follows the unsigned char conversion above.

    // 4. bool can be converted to int, with false bacoming 0 and true becoming 1.

    // 5. other:[https://en.cppreference.com/w/cpp/language/implicit_conversion#Integral_promotion]


    void printInt_too(int x)
    {
        std::cout << x << '\n';
    }

    int main_printInt_too()
    {
        printInt_too(2);        // int
        short s{ 3 };           // to short literal suffix, so we use variable
        printInt_too(s);        // short to int
        printInt_too('a');      // char to int
        printInt_too(true);     // bool to int

        return 0;
    }

// two things to note:
    // 1. on some systems, some of the integral types may be converted to unsigned int rather
    //    that int.

    // 2. some narrower unsigned types (such as unsigned char) will be converted to larger
    //    signed types (such as int).

// so while integral promotion is value-preserving, it is not necessarily sign-preserving.




//============[ not all value-preserving onversions are numeric promotions ]============

// some value preserving type conversions (such as char to short, int to long, or int to double)
// are not considered to be numeric promotions in C++ (they are numeric conversions).
// this is because such conversions do not assist in the goal of converting smaller types to
// larger types that can be processed more efficiently.


//=======================================================================================

int main()
{
    main_printDouble();
    main_printInt_too();

    return 0;
}