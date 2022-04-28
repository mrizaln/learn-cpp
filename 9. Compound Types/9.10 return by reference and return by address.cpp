// #define ALLOW_UNDEFINED_BEHAVIOR

#include <iostream>
#include <string>

// we can avoid expensive copy on passing an argument to a function by using pass by reference
// or pass by address

// we encounter a similar situation when returning by value: a copy of the return value is
// passed back to the caller (it can be expensive).


/*---------------------------------------------------------------------------------------
                    ============[ return by reference ]============
---------------------------------------------------------------------------------------*/

// return by reference returns a reference that is bound to the object being returned, which
// avoids making a copy of the return value.

namespace return_by_reference_example
{
    const std::string& getProgramName()     // returns a const reference
    {
        static const std::string s_programName { "Calculator" };    // static duration

        return s_programName;
    }

    int main()
    {
        std::cout << "This program is named " << getProgramName() << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
=====[ the object being returned by reference must exist after the function returns ]====
---------------------------------------------------------------------------------------*/

// this is the major caveat of using this, if not, the reference will be left dangling.
// that is the reason why we use [static] keyword on the example above.

// if not:

#ifdef ALLOW_UNDEFINED_BEHAVIOR
namespace return_by_reference_dangling
{
    const std::string& getProgramName()
    {
        const std::string programName { "Calculator" };     // now a local variable, destroyed when function ends

        return programName;
    }

    int main()
    {
        std::cout << "This program is named " << getProgramName() << '\n';
        
        return 0;
    }
}
#endif

// the result of this program is undefined.


// [ warning ]
/*---------------------------------------------------------------------------------------
    objects returned by reference must live beyond the scope of the function returning
    the reference, or a dangling reference will result. never return a local variable by
    reference
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
  ============[ don't return non-const local static variables by reference ]============
---------------------------------------------------------------------------------------*/

// returning non-const static variables by reference is fairly non-idiomatic, and should
// generally be avoided.

namespace return_non_const_by_reference
{
    const int& getNextId()
    {
        static int s_x { 0 };       // variable is non-const
        ++s_x;                      // generate the next id
        return s_x;                 // adn return a reference to it
    }

    int main()
    {
        const int& id1 { getNextId() };     // id1 is a reference
        const int& id2 { getNextId() };     // id2 is a reference

        std::cout << id1 << id2;        // prints 22

        return 0;
    }
}

// [id1] and [id2] are referencing the same object (the static variable s_x), so when anything
// modifies that value, all references are now accessing the modified value.




/*---------------------------------------------------------------------------------------
===[ assigning/initializing a normal variable with a returned reference makes a copy ]===
---------------------------------------------------------------------------------------*/

// if a function returns a reference, and that reference is used to initialize or assigne
// to non-reference variable, the return value will be copied.

namespace assign_normal_variable_with_returned_reference
{
    const int& getNextId()
    {
        static int s_x { 0 };
        ++s_x;
        return s_x;
    }

    int main()
    {
        const int id1 { getNextId() };      // id1 is a normal variable, receives a copy of value returned by reference
        const int id2 { getNextId() };      // id2 is a normal variable, receives a copy of value returned by reference

        std::cout << id1 << id2;        // prints 12

        return 0;
    }
}

// this defeats the purpose of returning a value by reference




/*---------------------------------------------------------------------------------------
    ============[ it's okay to return reference parameters by reference ]============
---------------------------------------------------------------------------------------*/

// if a parameter is passed into a function by reference, it's safe to return that parameter
// by reference

namespace return_reference_parameters_by_reference
{
    // takes two std::string, returns the one that comes first alphabetically
    const std::string& firstAlphabetical(const std::string& a, const std::string& b)
    {
        return (a < b ? a : b);
    }

    int main()
    {
        std::string hello { "Hello" };
        std::string world { "World" };

        std::cout << firstAlphabetical(hello, world) << '\n';
        std::cout << firstAlphabetical(world, hello) << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
     ============[ the caller can modify values through the reference ]============
---------------------------------------------------------------------------------------*/

// like pass by reference can modify the value being refenced, return by reference can modify
// the value through the reference

namespace modify_returned_value_by_reference
{
    int& max(int& x, int& y)
    {
        return (x > y ? x : y);
    }
    
    int main()
    {
        int x { 5 };
        int y { 6 };

        max(x, y) = 7;      // sets the greater of x or y to 7

        std::cout << x << y;    // prints 57

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ return by address ]============
---------------------------------------------------------------------------------------*/

/*
  - return by address works almost identically to return by reference, except a pointer to
    an object is returned instad of a reference to an object.

  - the major advantage of return by address over return by reference is that we can have
    the function return [nullptr] if there is no valid object to return.

  - the major disadvantage of return by address is that the caller has to remember to do a
    [nullptr] check before dereferencing the return value, otherwise null pointer dereference
    may occur.
  - because of this, return by reference should be preferred over returb by address.
*/

// [ best practice ]
/*---------------------------------------------------------------------------------------
    prefer return by reference over return by address unless the ability to return "no
    object" (sing [nullptr]) is important.
---------------------------------------------------------------------------------------*/





//=======================================================================================

int main()
{
    return_by_reference_example::main();

#ifdef ALLOW_UNDEFINED_BEHAVIOR
    return_by_reference_dangling::main();
#endif

    return_non_const_by_reference::main();
    assign_normal_variable_with_returned_reference::main();
    return_reference_parameters_by_reference::main();
    modify_returned_value_by_reference::main();

    return 0;
}
