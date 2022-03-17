#include <iostream>

//============[ introduction to function overloading ]============

// function overloading allows us to create multiple functions with the samme name, so long
// as each identically named function has different parameters.
// each function sharing a name (in the same scope) is called an [overloaded function]

    int add(int x, int y)
    {
        return x + y;
    }

    double add(double x, double y)
    {
        return x + y;
    }




//============[ introduction to overload resolution ]============

// additionally, when a function call is made to function that has been overloaded, the compiler
// will try to match the function call to the appropiate overload based on the arguments used
// in the function call.
// this is called [overload resolution].

    int main_add()
    {
        std::cout << add(1, 5) << '\n';         // calls add(int, int)
        std::cout << add(2.5, 11.6) << '\n';    // calls add(double, double)

        return 0;
    }




//============[ making it compile ]============

// in order for a program using overloaded functions to compile, two things have to be true:
    // 1. each overloaded function has to be differentiated from the others.
    // 2. each call to an overloaded function has to resolve to an overloaded function.

// [ best practice ]
/*---------------------------------------------------------------------------------------
    use function overloading to make your program simpler.
---------------------------------------------------------------------------------------*/




//=======================================================================================

int main()
{
    main_add();

    return 0;
}