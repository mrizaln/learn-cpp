#include <iostream>

/*---------------------------------------------------------------------------------------
                            ============[  ]============
---------------------------------------------------------------------------------------*/

// array is used to store many data of the same type through a single identifier.

// in an array variable delaration, we use square brackets to tell the compiler both that
// this is an array variable, as well as how many variables to allocate.

namespace array_declaration
{
    int testScore[30] {};        // allocate 30 int variables in a fixed array
}

// in the above we declared a fixed array named testScore.
// to access element of the array, we use a subscript operator [], and a parameter called
// a subscript or index




/*---------------------------------------------------------------------------------------
                ============[ an example array program ]============
---------------------------------------------------------------------------------------*/

namespace an_example_array
{
    int main()
    {
        int prime[5] {};
        prime[0] = 2;
        prime[1] = 3;
        prime[2] = 5;
        prime[3] = 7;
        prime[4] = 11;

        std::cout << "The lowest prime number is      : " << prime[0] << '\n';
        std::cout << "The sum of the first 5 primes is: " << prime[0] + prime[1] + prime[2] + prime[3] + prime[4] << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ array data types ]============
---------------------------------------------------------------------------------------*/

// array can be made of any type.
// array can also be made from structs

namespace array_from_struct
{
    struct Rectangle
    {
        int length {};
        int width {};
    };

    Rectangle rects[5] {};      // declare an array of 5 Rectangles
}




/*---------------------------------------------------------------------------------------
                    ============[ array subscripts ]=============
---------------------------------------------------------------------------------------*/

// in C++ array subscripts must always be an integral type.
// this include char, short, int, long, long long, bool, etc.
// an array subscripts can be a literal value, a variable, or an expression that evaluates
// to an integral type

namespace array_subscripts
{
    int main()
    {
        int array[5] {};

        // using a literal index
        array[1] = 7;

        // using an enum index
        enum Animals
        {
            animal_cat = 2
        };
        array[animal_cat] = 4;

        // using a variable index
        int index { 3 };
        array [index] = 6;

        // using an expression that evaluates to an integer index
        array[1+3] = 8;

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                  ============[ fixed array declarations ]============
---------------------------------------------------------------------------------------*/

// when declaring a fixed aaray, the length of the array must be a compile-time constant.

namespace fixed_array_declaration
{
    void working()
    {
        // using a literal constant
        int numberOfLessonsPerDay[7]{}; // Ok

        // using a constexpr symbolic constant
        constexpr int daysPerWeek{ 7 };
        int numberOfLessonsPerDay[daysPerWeek]{}; // Ok

        // using an enumerator
        enum DaysOfWeek
        {
            monday,
            tuesday,
            wednesday,
            thursday,
            friday,
            saturday,
            sunday,

            maxDaysOfWeek
        };
        int numberOfLessonsPerDay[maxDaysOfWeek]{}; // Ok

        // using a macro
        #define DAYS_PER_WEEK 7
        int numberOfLessonsPerDay[DAYS_PER_WEEK]{}; // Works, but don't do this (use a constexpr symbolic constant instead)
    }
    
    void not_working()
    {
        // using a non-const variable
        int daysPerWeek{};
        std::cin >> daysPerWeek;
        int numberOfLessonsPerDay[daysPerWeek]{}; // Not ok -- daysPerWeek is not a compile-time constant!

        // using a runtime const variable
        int temp{ 5 };
        const int daysPerWeek{ temp }; // the value of daysPerWeek isn't known until runtime, so this is a runtime constant, not a compile-time constant!
        int numberOfLessonsPerDay[daysPerWeek]{}; // Not ok
    }
}


//=======================================================================================

int main()
{
    an_example_array::main();
    array_subscripts::main();
}
