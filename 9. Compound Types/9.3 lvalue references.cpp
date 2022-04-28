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

// once initialized, a reference in C++ cannot be reseated, meaning it cannot be changed to
// reference with another variable to reference.

// consider this:

namespace cant_reseat_reference
{
    int main()
    {
        int x { 5 };
        int y { 6 };

        int& ref { x };
        
        ref = y;            // assign 6 (the value of y) to x (the object being referenced by ref)
                            // above line does NOT change ref into a reference to variable y!
        std::cout << x;

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
            ============[ lvalue reference scope and duration ]============
---------------------------------------------------------------------------------------*/

// reference variables follow the same scoping and duration rules that normal variables do.




/*---------------------------------------------------------------------------------------
     ============[ references and referents have independent lifetimes ]============
---------------------------------------------------------------------------------------*/

/*
  - with one exception, the lifetime of a reference and the lifetime of its referent are
    independent:
      > a reference can be destroyed before the object it is referencing.
      > the object being referenced can be destroyed before the reference.
*/

// when a reference destroyed, before the referent, the referent is no impacted

namespace destroy_reference_before_referent
{
    int main()
    {
        int x { 5 };

        {
            int& ref { x };
            std::cout << ref;
        } // ref is destroyed here -- x is unaware of this

        std::cout << x;

        return 0;
    } // x destroyed here
}




/*---------------------------------------------------------------------------------------
                   ============[ dangling references ]============
---------------------------------------------------------------------------------------*/

/*
  - when an object being referenced is destroyed before a reference to it, the reference is
    left referencing an object that no longer exist.
  - such a reference is called a [dangling reference].
  - accessing a dangling reference leads to undefined behaviour.
*/




/*---------------------------------------------------------------------------------------
                ============[ references aren't objects ]============
---------------------------------------------------------------------------------------*/

/*
  - a reference is not required to exist or occupy storage.
  - if possible, the compiler will optimize references away be replacing all occurences of
    a reference with the referent.
  - however, this isn't always possible, and in such cases, references may require storage.

  - because references aren't objects, they can't be used anywhere an object is required.
  - in cases where you need a referece that is an object or a reference that can ve reseated,
    [std::reference_wrapper] (ch 16) provides a solution.
*/


// [ as an aside... ]
//---------------------------------------------------------------------------------------
    // consider the following variables:
    namespace as_an_aside
    {    
        int var {};
        int& ref1 { var };      // lvalue reference bound to var
        int& ref2 { ref1 };     // lvalue reference bound to var
    }
    /*
      - because [ref2] is initialized with [ref1], you might be tempted to conclude that [ref2]
        is a reference to a reference.
      - it is NOT
    
      - when used in an expression (such as an initializer), [ref1] evalueates to [var]
      - so [ref2] is just a normal lvalue reference
    */
//---------------------------------------------------------------------------------------






//=======================================================================================

int main()
{
    lvalue_reference_variable::main();
    modifying_value_via_reference::main();

    return 0;
}