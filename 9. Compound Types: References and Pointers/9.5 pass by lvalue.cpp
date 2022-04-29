// #define ALLOW_ERROR_LVALUE_REFERENCE

#include <iostream>
#include <string>

//---------------------------------------------------------------------------------------

// when we called a function, we made a copy of our arguments' values, only to use it briefly
// and then destroy it.

// for fundamental types, it is cheap to copy,
// BUT:

/*---------------------------------------------------------------------------------------
            ============[ some objects are expensive to copy ]============
---------------------------------------------------------------------------------------*/

/*
  - most of the types provided by the standard library (such as [std::string]) are [class types].
  - class types are usually expensive to copy.
  - whenever possible, we want to avoid making unnecessary copies of objects that are expensive
    to copy, especially when we will destroy those copies almost immediately.
*/




/*---------------------------------------------------------------------------------------
                    ============[ pass be reference ]============
---------------------------------------------------------------------------------------*/

/*
  - one way to avoid expensive copy is to use [pass by reference]
  - when using [pass by reference], we declare a function parameter as a reference type (or
    const reference type) rather than as a normal type.
  - when the function is called, each reference parameter is bound to the appropiate argument.
*/

namespace pass_by_reference
{
    void printValue(std::string& y)
    {
        std::cout << y << '\n';
    } // y is destroyed here

    int main()
    {
        std::string x { "hello world" };

        printValue(x);      // x is now passed by reference into reference parameter y

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
===========[ pass by reference allows use to change the value of an argument ]===========
---------------------------------------------------------------------------------------*/

// when using pass by reference, any changes made to the reference parameter /will/ affect
// the argument

namespace pass_by_reference_change_value
{
    void addOne(int& y)
    {
        ++y;
    }

    int main()
    {
        int x { 5 };
        std::cout << "value = " << x << '\n';   // prints 5

        addOne(x);

        std::cout << "value = " << x << '\n';   // (has been modified) prints 6

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
  ============| pass by reference to non-const can only accept modifiable  ]===========
  ============|                     lvalue arguments                       |===========
---------------------------------------------------------------------------------------*/

// this is because a reference to non-const value can only bind to a modifiable lvalue
// essentially, we can't pass const variables or literals

namespace pass_by_reference_accept_only_modifiable_lvalue
{
    void printValue(int& y)
    {
        std::cout << y << '\n';
    }

    int main()
    {
        int x { 5 };
        printValue(x);          // ok
    
    #ifdef ALLOW_ERROR_LVALUE_REFERENCE
        const int z { 5 };
        printValue(z);          // error: z is non-modifiable

        printValue(5);          // error: 5 is an rvalue
    #endif

        return 0;
    }
}

// fortunately there's an easy way around this




/*---------------------------------------------------------------------------------------
                  ============[ pass by const reference ]============
---------------------------------------------------------------------------------------*/

/*
  - unlike a reference to non-const, const reference can bind to modifiable lvalues, non-
    modifiable lvalues, and rvalues.
  - by using this, we can reference the object passed as arguments without copying it, while
    also guaranteeing that the function /can't/ change the value being referenced.
*/

namespace pass_by_reference_to_const
{
    void printValue(const int& y)
    {
        std::cout << y << '\n';
    }

    int main()
    {
        int x { 5 };
        printValue(x);      // ok: modifiable lvalue

        const int z { 5 };
        printValue(z);      // ok: non-modifiable lvalue

        printValue(5);      // ok: rvalue

        return 0;
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    favor passing by const reference over passing by non-const by reference unless you
    have a specific reason to do so.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
          ============[ mixing pass by value and pass by reference ]============
---------------------------------------------------------------------------------------*/

namespace mix_pass_by_value_and_reference
{
    void foo(int a, int& b, const std::string& c)
    {
        a += b;
        ++b;
        std::cout << a << ' ' << b << ' '<< c << '\n';
    }

    int main()
    {
        int x { 5 };
        const std::string s { "Hello there" };

        foo(5, x, s);

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                ============[ when to pass by reference ]============
---------------------------------------------------------------------------------------*/

/*
  - because class (or struct) types can be expensive to copy, they are usually passed by
    reference.
  - fundamental types are cheap to copy so they are usually passed by value
*/




/*---------------------------------------------------------------------------------------
              ============[ how do we define "cheap to copy"? ]============
---------------------------------------------------------------------------------------*/

/*
  - there is no absolute answer.
  - but, we can formulate a rule of thumb: an object is cheap to copy if uses 2 or fewer "words"
    of memory and it has no setup costs.
*/

// the following program defines a macro that can be used to determine if a type uses 2 or
// frwer memory addresses worth of memory

#define isSmall(T) (sizeof(T) <= 2 * sizeof(void*))

namespace test_macro
{
    struct S
    {
        double a, b, c;
    };

    int main()
    {
        std::cout << std::boolalpha;            // print true or false instead of 1 or 0
        std::cout << isSmall(int) << '\n';      // true
        std::cout << isSmall(double) << '\n';   // true
        std::cout << isSmall(S) << '\n';        // false

        return 0;
    }
}

// we use preprocessor macro here so that we can substitute in a type (normal function disallow this)




//=======================================================================================

int main()
{
    pass_by_reference_change_value::main();
    mix_pass_by_value_and_reference::main();
    test_macro::main();

    return 0;
}