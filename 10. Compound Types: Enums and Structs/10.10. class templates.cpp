// #define IGNORE_ERROR

#include <iostream>

// we already know the challenge of having to create a separate (overloaded) function for
// each different set of types we want to work with.

// it turns out that:

/*---------------------------------------------------------------------------------------
           ============[ aggregate types have similar challenges ]============
---------------------------------------------------------------------------------------*/

// for example: we're writing a program where we need to work with pairs of [int] values,
// and need to determine which of the two numbers is larger.
// later we discover that we also need pairs of double values.

#ifdef IGNORE_ERROR
namespace challenge
{
    struct Pair
    {
        int first{};
        int second{};
    };

    struct Pair // compile error: erroneous redefinition of Pair
    {
        double first{};
        double second{};
    };

    constexpr int max(Pair p)
    {
        return (p.first > p.second ? p.first : p.second);
    }

    constexpr double max(Pair p) // compile error: overloaded function differs only by return type
    {
        return (p.first > p.second ? p.first : p.second);
    }

    int main()
    {
        Pair p1{ 5, 6 };
        std::cout << max(p1) << " is larger\n";

        Pair p2{ 1.2, 3.4 };
        std::cout << max(p2) << " is larger\n";

        return 0;
    }
}
#endif

// first,  type definition can't be overloaded
// second, our max(Pair) functions only differ by return type
// third,  there is a lot of redudancy




/*---------------------------------------------------------------------------------------
                    ============[ class templates ]============
---------------------------------------------------------------------------------------*/

// a [class template] is a template definition for instantiating class types.

namespace class_templates
{
    template <typename T>
    struct Pair
    {
        T first {};
        T second {};
    };

    int main()
    {
        Pair<int> p1 { 5, 6 };                                  // create a Pair of int
        std::cout << p1.first << ' ' << p1.second << '\n';

        Pair<double> p2 { 1.2, 3.4 };                           // create a Pair of double
        std::cout << p2.first << ' ' << p2.second << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
            ============[ using our class template in a function ]============
---------------------------------------------------------------------------------------*/

// back to the challenge of making our max() function to work with differenct types

namespace using_class_templates_in_a_function
{
    template <typename T>
    struct Pair
    {
        T first {};
        T second {};
    };

    template <typename T>
    constexpr T max (Pair<T> p)
    {
        return (p.first > p.second ? p.first : p.second);
    }

    int main()
    {
        Pair<int> p1 { 5, 6 };
        std::cout << max<int>(p1) << " is larger\n";    // explicit call to max<int>

        Pair<double> p2 { 1.2, 3.4 };
        std::cout << max(p2) << " is larger\n";         // call to max<double> using template argument deduction (prefer this)

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
         ============[ class templates with multiple template types ]============
---------------------------------------------------------------------------------------*/

// class templates can have some members using a template type and other members using a
// normal type




/*---------------------------------------------------------------------------------------
        ============[ class templates with multiple template types ]=============
---------------------------------------------------------------------------------------*/

namespace class_template_multiple_template_types
{
    template <typename T, typename U>
    struct Pair
    {
        T first {};
        U second {};
    };

    template <typename T, typename U>
    void print(Pair<T, U> p)
    {
        std::cout << '[' << p.first << ", " << p.second << ']' << '\n';
    }

    int main()
    {
        Pair<int, double> p1 { 1, 2.3 };
        Pair<double, int> p2 { 4.5, 6 };
        Pair<int, int> p3 { 7, 8 };

        print(p2);

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                        =============[ std::pair ]============
---------------------------------------------------------------------------------------*/

// because working with pairs of data is common, the C++ standard library contains a class
// template named [std::pair] in the <utility> header

#include <utility>

namespace std_pair
{
    template <typename T, typename U>
    void print(std::pair<T, U> p)
    {
        std::cout << '[' << p.first << ", " << p.second << ']' << '\n';
    }

    int main()
    {
        std::pair<int, double> p1 { 1, 2.3 };
        std::pair<double, int> p2 { 4.5, 6 };
        std::pair<int, int> p3 { 7, 8 };

        print(p1);

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
           ============[ using class templates in multiple files ]============
---------------------------------------------------------------------------------------*/

// just like function templates, class templates are typically defined in header files so
// they can be included into any code file that needs them.

namespace using_class_templates_in_multiple_files
{
    // inside pair.h file:
    #ifndef PAIR_H
    #define PAIR_H

    template <typename T>
    struct Pair
    {
        T first{};
        T second{};
    };

    template <typename T>
    constexpr T max(Pair<T> p)
    {
        return (p.first > p.second ? p.first : p.second);
    }

    #endif
}




//=======================================================================================

int main()
{
    class_templates::main();
    using_class_templates_in_a_function::main();
    class_template_multiple_template_types::main();
    std_pair::main();

    return 0;
}