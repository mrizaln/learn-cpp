#include <iostream>
#include <string>       // for std::string
#include <string_view>

//============[  ]============

// because C++ is a strongly-typed language, we are required to provide an explicit type
// for all objects.
// thus, we've specified that variable [d] is type of double:

    double d { 5.0 };

// however, the literal value [5.0] used to initialize [d] also has type double (implicitly
// determined via the format of the literal).

// in cases where we want a variable and its initializer to have the same type, we're effectively
// providing the same type information twice.




//============[ type deduction for initialized variables ]============

// type deduction is feature that allows the compiler to deduce the type of an object from
// the object's initializer.
// to use it, the [auto] keyword is used in place of the variable's type

    int add(int x, int y)
    {
        return x + y;
    }

    int main_type_deduction()
    {
        auto d { 5.0 };     // 5.0 is a double literal, so d will be type double
        auto i { 1 + 2 };   // 1 + 2 evaluates to int, so i will be type int
        auto x { i };       // i is an int, so x will be type int

        auto sum { add(5, 6) };     // add() returns an int, so sum will be type int

        return 0;
    }

// type deduction will not work for objects that do not have initializers or empty initializers

// although using type deduction for fundamental types only saves a few (if any) keystrokes,
// in future lessons we will see examples where the types get complex and lengthy.
// in those cases, using [auto] can save a lot og typing (and types).




//============[ type deduction drops const qualifiers ]============

// in most cases, type deduction will drop the [const] qualifier from deduced types

    int main_const_dropped()
    {
        const int x { 5 };      // x has type const int
        auto y { x };           // y will be type int (const is dropped)

        // if you want a deduced type to be const, you must supply the const yourself:
        const auto z { x };     // z will be type const int
    }




//============[ type deduction for string literals ]============

// for historical reasons, string leterals in C++ have strange type.
// therefore, the following probably won't work as expected:

    auto s { "Hello world!" };      // s will be type const char*, not std::string

// if you want the type deduced from a string literal to be [std::string] or [std::string_view],
// you'll need to use the [s] or [sv] literal suffixes

    int main_string_type_deduction()
    {
        using namespace std::literals;      // easiest way to access the s and sv suffixes

        auto s1 { "goo"s };     // "goo"s is a std::string literal, so s1 wiil be deduced as string literals
        auto s2 { "goo"sv };

        return 0;
    }




//============[ type deduction benefits and downsides ]============

// benefits:
    // 1. if two or more variables are defined on sequential lines, the names of the variables
    //    will be lined up, helping to increase readability

        // harder to read
        int a { 5 };
        double b { 6.7 };

        // easier to read
        auto aa { 5 };
        auto bb { 6.7 };

    // 2. type deduction only works on variables that have initializers, so if you are in
    //    the habit of using type deduction, it can help avoid unintentionally uninitialized
    //    variables

// downsides:
    // 1. type deduction obscures an object's type information in the code.
    // 2. if the type of an initializer changes, the type of a variable using type deduction
    //    will also change.

// [ best practice ]
/*---------------------------------------------------------------------------------------
    use type deduction for your variables, unless you need to commit to a specific type.
---------------------------------------------------------------------------------------*/




//=======================================================================================

int main()
{
    main_type_deduction();
    main_const_dropped();
    main_string_type_deduction();

    return 0;
}