// #define ALLOW_ERROR_ASSIGNMENT

#include <iostream>

/*---------------------------------------------------------------------------------------
    ============[ lvalue reference to const ]============
---------------------------------------------------------------------------------------*/

/*
  - by using the [const] keyword when declaring an lvalue reference, we tell an lvalue reference
    to treat the objects it is referencing as const.
  - such reference is called an [lvalue reference to a const value] ( or [const reference])
*/

// lvalue referenes to const can bind to non-modifiable lvalues.

namespace const_reference
{
    int main()
    {
        const int x { 5 };      // x is a non-modifiable lvalue
        const int& ref { x };   // okay: ref is an lvalue reference to a const value

        std::cout << ref;       // okay: can access

    #ifdef ALLOW_ERROR_ASSIGNMENT
        ref = 6;                // error: can't modify
    #endif

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
==========[ initializing an lvalue reference to const with a modifiable lvalue ]=========
---------------------------------------------------------------------------------------*/

// const reference can also bind to modifiable lvalues
// in such case, the obect being referenced is treated as const

namespace const_reference_modiable_referent
{
    int main()
    {
        int x { 5 };
        const int& ref { x };

        std::cout << ref;   // okay

    #ifdef ALLOW_ERROR_ASSIGNMENT
        ref = 7;            // error
    #endif

        x = 6;              // okay

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
   ============[ initializing an lvalue reference to const with an rvalue ]===========
---------------------------------------------------------------------------------------*/

namespace const_reference_rvalue_referent
{
    int main()
    {
        const int& ref { 5 };

        std::cout << ref;       // prints 5

        return 0;
    }
}

/*
  - when this happens, a temporary object is created and initialized with the rvalue, and
    the reference to const is bound that temporary object
  - temporary objects have no scpoe at all, they can only be used directly at the point where
    it is created
*/

/*
  - tempporary objects are normally destroyed at the end of the expression in which they are
    created.
  - however, there is a special rule: when a const reference is bound to a temporary object,
    the lifetime of the temporary object is extended to match the lifetime of the reference.
*/

namespace const_reference_extends_temporary_objects_lifetime
{
    int main()
    {
        const int& ref { 5 };   // temporary object has its lifetime extended

        std::cout << ref;       // we can safely use it here
    } // ref and the temporary object die here
}