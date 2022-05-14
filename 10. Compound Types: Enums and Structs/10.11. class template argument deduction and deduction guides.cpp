#include <iostream>

/*---------------------------------------------------------------------------------------
      ============[ class template argument deduction (CTAD) {C++17} ]============
---------------------------------------------------------------------------------------*/
 
// starting in C++17, when instantiating an object from a class template, the compiler can
// deduce the template types from the types of the object's initializer (this called CTAD).

#include <utility>

namespace class_template_argument_deduction
{
    int main()
    {
        std::pair<int, int> p1 { 1, 2 };    // explicitly specify class template argument
        std::pair p2 { 1, 2 };              // CTAD used

        return 0;
    }
}

// CTAD is only performed if no template argument list is present




/*---------------------------------------------------------------------------------------
              ============[ template argument deduction guides ]============
---------------------------------------------------------------------------------------*/

// in certain cases, the compiler may need a little extra help understanding how to deduce
// the template arguments properly.

namespace template_argument_deduction_guides
{
    template <typename T, typename U>
    struct Pair
    {
        T first{};
        U second{};
    };

    // here's a deduction guide for our pair class
    template<typename T, typename U>
    Pair(T, U) -> Pair<T, U>;

    int main()
    {
        Pair<int, int> p1 { 1, 2 };      // ok: we're explicitly specifying the template arguments
        Pair p2 { 1, 2 };                // compile error in C++17

        return 0;
    }
}

/*
    C++20 added the ability for the compiler to automatically generate deduction guides
    for aggregate class types.
    this assumes the compiler supports feature P1816
*/


//=======================================================================================

int main()
{
    class_template_argument_deduction::main();
    template_argument_deduction_guides::main();

    return 0;
}