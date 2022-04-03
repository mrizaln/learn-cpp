// #define ENABLE_ERROR_CONSTEVAL

#include <iostream>

/*---------------------------------------------------------------------------------------
    ============[ constexpr functions can be evaluated at compile-time ]============
---------------------------------------------------------------------------------------*/

/*
  - a constexpr function is a function whose return value may be computed at compile-time.
*/

namespace constexpr_function
{
    constexpr int greater(int x, int y)
    {
        return (x > y ? x : y);
    }

    int main()
    {
        constexpr int x { 5 };
        constexpr int y { 6 };

        // we'll explain why we use variable g here later
        constexpr int g { greater(x, y) };      // will be evaluated at compile-time

        std::cout << g << " is greater!";

        return 0;
    }
}

/*
  - to be eligible for compile-time evaluation, a function must have a constexpr return type
    and not call any non-constexpr functions.
  - additionallly, a call to the function must have constexpr arguments.
*/




/*---------------------------------------------------------------------------------------
        ============[ constexpr functions are implicitly inline ]============
---------------------------------------------------------------------------------------*/

/*
  - because constexpr functions may be evaluated at compile-time, the compiler must be able
    to see the full definition of the constexpr function at all points where the function
    is called
  - this mean that a constexpr function called in multiple files needs to have its definition
    included into each such file.
  - to avoid such problems, constexpr functions are implicitly inline.
  - as a result, constepxr functions are of ten defined in header files.
*/




/*---------------------------------------------------------------------------------------
    ============[ constexpr functions can also be evaluated at runtime ]============
---------------------------------------------------------------------------------------*/

namespace constexpr_function_evaluated_at_runtime
{
    constexpr int greater (int x, int y)
    {
        return (x > y ? x : y);
    }

    int main()
    {
        int x { 5 };        // not constexpr
        int y { 6 };        // not constexpr

        std::cout << greater(x, y) << "is greater!";        // will be evaluated at runtime

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
  ============[ so when is a constexpr function evaluated at compile-time? ]============
---------------------------------------------------------------------------------------*/

/*
  - according to the C++ standard, a consexpr function that is eligible for compile-time
    evaluation /must/ be evaluated at compile-time if the return value is used where a constant
    expression is required.
  - otherwise, the compiler is free to evaluate the function at either compile-time or runtime.
*/

namespace when_constexpr_function_evaluated_compile_time
{
    constexpr int greater(int x, int y)
    {
        return (x > y ? x : y);
    }

    int main()
    {
        constexpr int g { greater(5, 6) };              // case 1: evaluated at compile-time
        std::cout << g << " is greater!";

        int x { 5 };    // not constexpr
        std::cout << greater(x, 6) << " is greater!";   // case 2: evaluated at runtime

        std::cout << greater(5, 6) << " is greater!";   // case 3: may be evaluated at either runtime or compile-time
    }
}




/*---------------------------------------------------------------------------------------
==[ determining if a constexpr function call is evaluating at compile-time or runtime ]==
---------------------------------------------------------------------------------------*/

/*
  - in C++20, [std::is_constant_evaluated()] (defined in the <type_traits> header) returns
    a [bool] indicating whether the current function call is executing in a constant context.
  - this can be combined with a conditional statement to allow a function to behave differently
    when evaluated at compile-time vs runtime
*/

#include <type_traits>      // for std::is_constant_evaluated

namespace determining_evaluation
{
    constexpr int someFunction()
    {
        if (std::is_constant_evaluated())       // if compile-time evaluation
            ;// do something
        else                                    // runtime evaluation        
            ;// do something
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ consteval (C++20) ]============
---------------------------------------------------------------------------------------*/

/*
  - C++20 introduces the keyword [consteval], which is used to indicate that a function
    /must/ evaluate at compile-time, otherwise a compile error will result.
  - such functions are called immediate functions.
*/

namespace immediate_function
{
    consteval int greater(int x, int y)
    {
        return (x > y ? x : y);
    }

    int main()
    {
        constexpr int g { greater(5, 6) };              // ok: will evaluate at compile-time

        std::cout << greater(5, 6) << " is greater!";   // ok: will evaluate at compile-time

        int x { 5 };    // not constexpr
    
    #ifdef ENABLE_ERROR_CONSTEVAL
        std::cout << greater(x, 6) << " is greater!";   // error: consteval functions must evaluate at compile-time
    #endif
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    user [consteval] if you have a function that must run at compile-time for some reason
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
  ========[ using consteval to make constexpr execute at compile-time (C++20)]========
---------------------------------------------------------------------------------------*/

/*
  - the downside of consteval functions is that such functions can't evaluate at runtime,
    making them less flexible than constexpr functions.
*/

// consteval functions provides a way to make this happen, using a neat helper function:

namespace consteval_at_runtime
{
    // use abbreviated function template
    consteval auto compileTime(auto value)
    {
        return value;
    }

    constexpr int greater(int x, int y)     // function is constexpr
    {
        return (x > y ? x : y);
    }

    int main()
    {
        std::cout << greater(5, 6);                 // may or may not execute at compile-time

        std::cout << compileTime(greater(5, 6));    // will execute at compile-time

        int x { 5 };
        std::cout << greater(x, 6);                 // we can still call the constexpr version at runtime if we wish

        return 0;
    }
}
