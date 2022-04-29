#include <iostream>
#include <string>       // for std::string

// in prior lessons, we've covered two different ways to pass an argument to a function:
//  1. pass by value
//  2. pass by reference

// there is a 3rd way:

/*---------------------------------------------------------------------------------------
                    ============[ pass by address ]============
---------------------------------------------------------------------------------------*/

// with pass by address, instead of providing an object as an argument, the caller provides
// an object's address (via a pointer).

namespace three_ways_to_pass_argument
{
    void printByValue(std::string val)
    {
        std::cout << val << '\n';
    }

    void printByReference(const std::string& ref)
    {
        std::cout << ref << '\n';
    }

    // pass by address
    void printByAddress(const std::string* ptr)
    {
        std::cout << *ptr << '\n';
    }

    int main()
    {
        std::string str { "Hello world!" };

        printByValue(str);
        printByReference(str);
        printByAddress(&str);               // here we're passing the address of str

        std::string* ptr { &str };
        printByAddress(ptr);                // here we're passing a pointer thaht points to str

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
=========[ pass by address does not make a copy of the object being pointed to ]=========
---------------------------------------------------------------------------------------*/

// just like pass by reference, pass by address does ont copy the actual object, only the
// address of it. thus fast.




/*---------------------------------------------------------------------------------------
==========[ pass by address allows the function to modify the argument's value ]=========
---------------------------------------------------------------------------------------*/

// if the function parameter is a pointer to non-const, the function can modify the argument
// via the pointer parameter

namespace pass_by_address_modify_argument
{
    void changeValue(int* ptr)      // ptr is pointer to non-const
    {
        *ptr = 6;
    }

    int main()
    {
        int x { 5 };
        std::cout << "x = " << x << '\n';

        changeValue(&x);

        std::cout << "x = " << x << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                      ============[ null checking ]============
---------------------------------------------------------------------------------------*/

// when passing a parameter by address, care should be taken to ensure the pointer is not
// a null pointer before you dereference the value.

namespace null_checking
{
    void print(int* ptr)
    {
        if (ptr)        // if ptr is not nullptr
        {
            std::cout << *ptr <<'\n';
        }
    }

    int main()
    {
        int x { 5 };

        print(&x);
        print(nullptr);

        return 0;
    }
}

// nesting of the primary logic is not pretty
// it is more effective to test whether the function parameter is null as a precondition

namespace null_checking_precondition
{
    void print(int* ptr)
    {
        if (!ptr)           // if ptr is a null pointer, early return back to the caller
            return;
        
        // if we reached this point, we can assume ptr is valid
        // no more testing or nesting required

        std::cout << *ptr;
    }

    int main()
    {
        int x { 5 };

        print(&x);
        print(nullptr);

        return 0;
    }
}

// if a null pointer should never be passed to the function, an [assert] can be used instead

#include <cassert>      // for assert
namespace null_checking_assert
{
    void print(const int* ptr)
    {
        assert(ptr);        // fail in debug mode id ptr is nullptr

        // (optionally) handle this as an error case in production mode so we don't crash if it does happen

        if (!ptr)
            return;
        
        std::cout << *ptr << '\n';
    }

    int main()
    {
        int x { 5 };

        print(&x);
        // print(nullptr);      // aborted

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
              ============[ prefer pass by (const) reference ]============
---------------------------------------------------------------------------------------*/

// pass by const reference has a few advantages over pass by address

// first, pass by const reference is more flexible, as it can accept lvalues and rvalues:

namespace prefer_pass_by_const_reference
{
    void printByReference(const int& ref)
    {
        std::cout << ref << '\n';
    }

    void printByAddress(const int* ptr)
    {
        std::cout << *ptr << '\n';
    }

    int main()
    {
        printByReference(5);    // valid, rvalue can be passed
        // printByAddress(&5);     // invalid

        return 0;
    }
}

// second, the syntax for pass by reference is natural, as we can just pass in literals or
// objects.

// [ best practice ]
/*---------------------------------------------------------------------------------------
    prefer pass by reference to pass by address unless you have a specific reason to use
    pass by address.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
          ============[ pass by address for "optional" arguments ]============
---------------------------------------------------------------------------------------*/

// common uses for pass by address is to allow a function to accept an "optional" argument

namespace pass_by_address_optional_arguments
{
    void greet(std::string* name=nullptr)
    {
        std::cout << "Hello ";
        std::cout << (name ? *name : "guest") << '\n';
    }

    int main()
    {
        greet();

        std::string name { "joe" };
        greet(&name);

        return 0;
    }
}

// however, function overloading is a better alternative to achieve the same result

namespace overloading_for_optional_optional
{
    void greet()
    {
        std::cout << "Hello guest\n";
    }

    void greet(const std::string& name)
    {
        std::cout << "Hello " << name << '\n';
    }

    int main()
    {
        greet();

        std::string name { "joe" };
        greet(name);

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
        ============[ changing what a pointer parameter points at ]============
---------------------------------------------------------------------------------------*/

// when we pass an address to afunction, that address is copied from the argument into the
// pointer parameter

// this nullify() function won't work:

namespace trying_to_change_what_pointer_points_at
{
    void nullify(int* ptr2)
    {
        ptr2 = nullptr;     // make the function paramter a null pointer
    }

    int main()
    {
        int x { 5 };
        int* ptr { &x };        // ptr points to x

        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");      // non-null

        nullify(ptr);           // won't work

        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");      // non-null

        return 0;
    }
}

// so, what if we want to allow a function to change what a pointer argument points to?




/*---------------------------------------------------------------------------------------
            ============[ pass by address... by reference? ]============
---------------------------------------------------------------------------------------*/

// yes, this is a thing.
// we can pass pointers by reference, just like normal variables

namespace pass_by_address_by_reference
{
    void nullify(int*& refptr)
    {
        refptr = nullptr;       // make the function parameter a null pointer
    }

    int main()
    {
        int x { 5 };
        int* ptr { &x };

        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");      // non-null

        nullify(ptr);

        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");      // null

        return 0;
    }
}




//=======================================================================================

int main()
{
    three_ways_to_pass_argument::main();
    pass_by_address_modify_argument::main();
    null_checking::main();
    null_checking_precondition::main();
    null_checking_assert::main();
    pass_by_address_optional_arguments::main();
    trying_to_change_what_pointer_points_at::main();
    pass_by_address_by_reference::main();

    return 0;
}