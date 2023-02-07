/*------------------------------------------------------------------------------
                  ============[ std::unique_ptr ]============
------------------------------------------------------------------------------*/

/*
  - std::unique_ptr is the C++11 replacement for std::auto_ptr
  - it should be used to manage any dynamically allocated object that is not shared
    by multiple objects.
  - std::unique_ptr should completely own the object it manages, not share that
    ownership with other classes.

  - unlike std::auto_ptr, std::unique_ptr properly implements move semantics.

  - unlike std::auto_ptr, std::unique_ptr is smart enough to know whether to use
    scalar delete or array delete, so std::unique_ptr is okay to use with both
    scalar objects and arrays.
*/

#include <iostream>
#include <memory>    // for std::unique_ptr

namespace example
{
    class Resource
    {
    public:
        Resource() { std::cout << "Resource acquired\n"; }
        ~Resource() { std::cout << "Resource destroyed\n"; }
    };

    void main()
    {
        // allocate a Resource object and have it owned by std::unique_ptr
        std::unique_ptr<Resource> res{ new Resource() };

        std::unique_ptr<Resource> res1{ new Resource{} };    // Resource created here
        std::unique_ptr<Resource> res2{};                    // Start as nullptr

        std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
        std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

        // res2 = res1; // Won't compile: copy assignment is disabled
        res2 = std::move(res1);    // res2 assumes ownership, res1 is set to null

        std::cout << "Ownership transferred\n";

        std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
        std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");
    }    // res goes out of scope here, and the allocated Resource is destroyed
}




/*------------------------------------------------------------------------------
            ============[ accessing the managed object ]============
------------------------------------------------------------------------------*/

/*
  - std::unique_ptr has an overloaded operator* and operator-> that can be used
    to return the resource being managed.

  - std::unique_ptr may not always be managing an object, so before we use either
    of these operators, we should check whether the std::unique_ptr has a resource.
  - to do that, std::unique_ptr has a cast to bool that returns true if the std::unique_ptr
    is managing a resource.
*/

namespace unique_ptr_access
{
    class Resource
    {
    public:
        Resource() { std::cout << "Resource acquired\n"; }
        ~Resource() { std::cout << "Resource destroyed\n"; }
        friend std::ostream& operator<<(std::ostream& out, const Resource& res)
        {
            out << "I am a resource";
            return out;
        }
    };

    void main()
    {
        std::unique_ptr<Resource> res{ new Resource{} };

        if (res) {                        // use implicit cast to bool to ensure res contains a Resource
            std::cout << *res << '\n';    // print the Resource that res is owning
        }
    }
}




/*------------------------------------------------------------------------------
                  ============[ std::make_unique ]============
------------------------------------------------------------------------------*/

/*
  - C++14 comes with an additional function named std::make_unique()
  - this templated function constructs an object of the template type and initializes
    it with the arguments passed into the function.

  - use of std::make_unique is optional but is recommended.
  - it resolves an exception safety issue that can result from C++ leaving the order
    of evaluation for function arguments unspecified.
*/

namespace make_unique
{
    class Fraction
    {
    private:
        int m_numerator{ 0 };
        int m_denominator{ 1 };

    public:
        Fraction(int numerator = 0, int denominator = 1) :
            m_numerator{ numerator }, m_denominator{ denominator }
        {
        }

        friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
        {
            out << f1.m_numerator << '/' << f1.m_denominator;
            return out;
        }
    };


    void main()
    {
        // Create a single dynamically allocated Fraction with numerator 3 and denominator 5
        // We can also use automatic type deduction to good effect here
        auto f1{ std::make_unique<Fraction>(3, 5) };
        std::cout << *f1 << '\n';

        // Create a dynamically allocated array of Fractions of length 4
        auto f2{ std::make_unique<Fraction[]>(4) };
        std::cout << f2[0] << '\n';
    }
}

// [ best practice ]
/*------------------------------------------------------------------------------
    use std::make_unique() instead of creating std::unique_ptr and using new
    yourself.
------------------------------------------------------------------------------*/




/*------------------------------------------------------------------------------
       ============[ return std::unique_ptr from a function ]============
------------------------------------------------------------------------------*/

// std::unique_ptr can be safely returned from a function by value.
// in general you should not return std::unique_ptr by pointer (ever) or reference
// (unless you have specific reason)

namespace returning_unique_ptr
{
    using example::Resource;
    std::unique_ptr<Resource> createResource()
    {
        return std::make_unique<Resource>();
    }

    int main()
    {
        auto ptr{ createResource() };

        // do whatever

        return 0;
    }
}




/*------------------------------------------------------------------------------
        ============[ passing std::unique_ptr to a function ]============
------------------------------------------------------------------------------*/

// if you want the functino to take the ownership of the resource of the pointer,
// pass the std::unique_ptr by value (use std::move since the copy semantics is deleted)

namespace passing_unique_ptr
{
    using unique_ptr_access::Resource;

    void takeOwnership(std::unique_ptr<Resource> res)
    {
         if (res)
              std::cout << *res << '\n';
    } // the Resource is destroyed here

    void transfer()
    {
        auto ptr{ std::make_unique<Resource>() };

       // takeOwnership(ptr); // This doesn't work, need to use move semantics
        takeOwnership(std::move(ptr)); // ok: use move semantics

        std::cout << "Ending program\n";
    }
}

// most of the time though, you don't want to transfer the ownership of  the resource
// to a function.
// in that case, you can pass it by reference or pointer.

namespace passing_unique_ptr
{
    // The function only uses the resource, so we'll accept a pointer to the resource, not a reference to the whole std::unique_ptr<Resource>
    void useResource(Resource* res)
    {
        if (res)
            std::cout << *res << '\n';
        else
            std::cout << "No resource\n";
    }

    void no_transfer()
    {
        auto ptr{ std::make_unique<Resource>() };
        useResource(ptr.get()); // note: get() used here to get a pointer to the Resource
        std::cout << "Ending program\n";
    }
}




//==============================================================================

int main()
{
    example::main();
    std::cout << '\n';
    unique_ptr_access::main();
    std::cout << '\n';
    make_unique::main();
    std::cout << '\n';
    returning_unique_ptr::main();
    std::cout << '\n';
    passing_unique_ptr::transfer();
    std::cout << '\n';
    passing_unique_ptr::no_transfer();

    return 0;
}
