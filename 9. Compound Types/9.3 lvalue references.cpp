#define IGNORE_ERROR_DECLARATION
// #define ALLOW_ERROR_INITIALIZATION

#include <iostream>

/*-------------------------------------------------------------------------------------*/

/*
  - in C++, a [reference] is an alias for an existing object.
  - once a reference has been defined, any operation on the reference is applied to the object
    being referenced.

  - modern C++ contains two types of references: [lvalue references], and [rvalue references].
*/




/*---------------------------------------------------------------------------------------
                ============[ lvalue reference types ]============
---------------------------------------------------------------------------------------*/

/*
  - an [lvalue reference] (or just reference) acts as an alias for an existing lvalue (such
    as variable).
*/

// to declare an lvalue reference type, we use an ampersand (&) in the type declaration:

#ifndef IGNORE_ERROR_DECLARATION
namespace reference_declaration
{
    int               // a normal int type
    double            // a normal double type
    int&              // an lvalue reference to an int object
    double&           // an lvalue reference to a double object
}
#endif



/*---------------------------------------------------------------------------------------
               ============[ lvalue reference variables ]============
---------------------------------------------------------------------------------------*/

/*
  - one of the things we can do with an lvalue reference types is to create an lvalue reference
    variable.
  - an [lvalue reference variable] is a variable that acts as a reference to an lvalue (usually
    another variable).
*/

namespace lvalue_reference_variable
{
    int main()
    {
        int x { 5 };                // x is a normal int variable
        int& ref { x };             // ref is an lvalue reference variable that can now be used as an alias for variable x

        std::cout << x << '\n';     // print the value of x (5)
        std::cout << ref << '\n';   // print the value of x via ref (5)

        return 0;
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    when defining a reference, place the ampersand next to the type (not the reference
    variable's name).
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
        ============[ modifying values through an lvalue reference ]============
---------------------------------------------------------------------------------------*/

namespace modifying_value_via_reference
{
    int main()
    {
        int x { 5 };
        int& ref { x };

        std::cout << x << ref;      // prints 55

        x = 6;      // x now has value 6
        std::cout << x << ref;      // prints 66

        ref = 7;    // x via ref changed to 7
        std::cout << x << ref;      // prints 77

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
            ============[ initialization of lvalue references ]============
---------------------------------------------------------------------------------------*/

// much like constants, all references must be initialized

namespace initialize_reference
{
    int main()
    {
    #ifdef ALLOW_ERROR_INITIALIZATION
        int& invalidRef;    // error: references must be initialized
    #endif

        int x { 5 };
        int& ref { x };     // okay: reference to int is bound to int variable
    }
}

/*
  - when a reference is initialized with an object (or function), we say it is [bound] to
    that object (or function).
  - the process by which such a reference is bound is called [reference binding].
  - the object (or function) being referenced is sometimes called the [referent].
*/

// lvalue references must be bound to a /modifiable/ lvalue

namespace lvalue_bound
{
    int main()
    {
        int x { 5 };
        int& ref { x };     // valid: lvalue reference bound to a modifiable lvalue

        const int y { 5 };

    #ifdef ALLOW_ERROR_INITIALIZATION
        int& invalidRef { y };      // invalid: can't bind to a non-modifiable
        int& invalidRef2 { 0 };     // invalid: can't bind to an rvalue
    #endif

        return 0;
    }
}

// in most cases, the type of the reference must match the type of the referent (there are
// some exceptions to this rule)

namespace reference_type_equal_referent_type
{
    int main()
    {
        int x { 5 };
        int& ref { x };     // okay

        double y { 6.0 };

    #ifdef ALLOW_ERROR_INITIALIZATION
        int& invalidRef { y };          // invalid: reference to int can't bind to double
        double& invalidRef2 { x };      // invalid: reference to double can't bind to int
    #endif
    }
}

// lvalue references to [void] are disallowed (what would be the point?).




/*---------------------------------------------------------------------------------------
==========[ references can't be reseated (changed to refer to another object) ]==========
---------------------------------------------------------------------------------------*/





//=======================================================================================

int main()
{
    lvalue_reference_variable::main();
    modifying_value_via_reference::main();

    return 0;
}