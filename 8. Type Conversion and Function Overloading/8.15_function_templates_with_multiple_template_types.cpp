#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x > y) ? x : y;
}

// we want to call something like max(int, double)
// spoiler: it won't work, because we use only one template type: T.

// unless:

/*---------------------------------------------------------------------------------------
  ============[ use static_cast to convert the arguments to matching types ]============
---------------------------------------------------------------------------------------*/

// the first solution is to put the burden on the caller to convert the arguments into matching
// types.

namespace using_static_cast
{
    int main()
    {
        std::cout << max(static_cast<double>(2), 3.5) << '\n';  // call max(double, double)

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
    ============[ provide an actual type ]============
---------------------------------------------------------------------------------------*/

namespace provide_actual_type
{
    int main()
    {
        std::cout << max<double>(2, 3.5) << '\n';   // we've provided actual type double, so the compiler won't use template argument deduction

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
  ============[ functions templates with multiple template type parameters ]============
---------------------------------------------------------------------------------------*/

// the root of our problem is that we've only defined the single template type (T) for our
// function template.
// the best way to solve this problem is to rewrite our function template in such a way that
// our parameters can resolve to different types

namespace multiple_template_type
{
    template <typename T, typename U>
    auto maxx(T x, U y)
    {
        return (x > y) ? x : y;
    }

    int main()
    {
        std::cout << maxx(2, 3.5);

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
           ============[ abbreviated function templates (C++20) ]============
---------------------------------------------------------------------------------------*/

// C++20 introduces a new use of the [auto] keyword: when the [auto] keyword is used as a
// parameter type in a normal funtion, the compiler will automatically convert the function
// into a function template with each auto parameter becoming an independent template type
// parameter. 

// this method for creating a function template is called an [abbreviated function templates]

namespace abbreviated_function_template
{
    // this function:
    auto maxxx(auto x, auto y)
    {
        return (x > y) ? x : y;
    }
    // is shorthand in C++20 for the following:

    template <typename T, typename U>
    auto maxxx(T x, U y)
    {
        return (x > y) ? x : y;
    }
}

// in cases where you want each template type parameter to be an independent type, this form
// is preferred as the removal of the template parameter declaration line makes your code
// more concise and readable.

// [ best practice ]
/*---------------------------------------------------------------------------------------
    feel free to use abbreviated function templates if each auto parameter should be an
    independent template type (and your language standard is set to C++20 or newer).
---------------------------------------------------------------------------------------*/




//=======================================================================================

int main()
{
    using_static_cast::main();
    provide_actual_type::main();

    return 0;
}