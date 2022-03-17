#define ALLOW_ADDANDPRINT

#include <iostream>

//============[ type deduction for functions ]============

// consider the following program:

    int add(int x, int y)
    {
        return x + y;
    }

// when this function is compiled, the compiler will determine that [x + y] evaluates to [int],
// then ensure that type of the return value matches the declared return type of the function.

// since the compiler already has to deduce the return type from the return statement, in
// C++14, the [auto] keyword was extended to do functoin return type deduction.

    auto add_auto(int x, int y)
    {
        return x + y;
    }

// when using an auto return type, all return values must be of the same type, otherwise an
// error will result.

    auto someFcn(bool b)
    {
        if (b)
            return 5;       // return type int
        else
            // return 6.7;     // return type double; error
            return 1;
    }

// if such case is desired, you can either explicitly specify a return type for your function,
// or you can explicitly convert all your return statements to the same type.

// a major downside of functions that use an [auto] return type is that such functions must
// be fully defined before they can be used (a forward declaration is not sufficient).

#ifdef ALLOW_ERROR
    auto foo();

    int main_foo()
    {
        std::cout << foo();
        return 0;
    }

    auto foo()
    {
        return 5;
    }
#endif

// this makes sense: a forward declaration does not have enough information fot the compiler
// to deduce the function's return type.
// this means normal functions that return [auto] are typically only callable form within
// the file in which they are declared.

// [ best practice ]
/*---------------------------------------------------------------------------------------
    favor explicit return types over function return type deducition for normal functions
---------------------------------------------------------------------------------------*/




//============[ trailing return type syntax ]============

// the [auto] keyword can also be used to declare functions using a [trailing return syntax],
// where the return type is specified after the rest of the function prototype

    auto add_alt(int x, int y) -> int
    {
        return (x + y);
    }

// in this case, auto does not perform type deduction -- it is just part of the syntax to
// use a trailing return type.

// why would you want this?

// one nice thing is that it makes all your function names line up:

    auto add(int x, int y) -> int;
    auto divide(double x, double y) -> double;
    auto printSomething() -> void;
    auto generateSubstring(const std::string &s, int start, int len) -> std::string;

// the trailing return syntax is also required for some advanced features of C++




//============[ type deduceiont can't be used for function parameter types ]============

#ifdef ALLOW_ADDANDPRINT
    void addAndPrint(auto x, auto y)
    {
        std::cout << x + y << '\n';
    }

    int main_addAndPrint()
    {
        addAndPrint(2, 3);      // case 1: int parameters
        addAndPrint(4.5, 6.7);  // case 2: double parameters
        addAndPrint('#', '>');  // case 3: char parameters

        return 0;
    }
#endif

// prior to C++, the above program won't compile.

// <[ but apparently it is compiled im my computer using gcc 10.2.1, even though i use gnu++17
//    for its standard. it successfully compiled with warning though, it says: use of 'auto'
//    in parameter declaration only available with '-fconcepts-ts' ]>
// - mrizaln

// in C++20, the [auto] keyword was extented so that the above program will compile and function
// correctly -- however, [auto] is not invoking type deduction in this case.
// rather, it is tirggering a different feature called [function templates] that was designed
// to actually handle such cases.




//=======================================================================================

int main()
{
#ifdef ALLOW_ERROR
    main_foo();
#endif
#ifdef ALLOW_ADDANDPRINT
    main_addAndPrint();
#endif

    return 0;
}