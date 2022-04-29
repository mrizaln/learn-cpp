// #define ALLOW_ERROR

#include <iostream>
#include <string>

// we know [auto] keyword can be used to have the compiler deduce the type of a variable from 
// the initializer

// we also know, that type deduction will drop [const] qualifiers by default


/*---------------------------------------------------------------------------------------
              ============[ type deduction drops references ]============
---------------------------------------------------------------------------------------*/

// in addition to dropping const qualifiers, type deduction will also drop references

namespace type_deduction_drops_references
{
    std::string& getRef()
    {
        static std::string name { "Maiuna"};
        return name;
    }

    int main()
    {
        auto ref1 { getRef() };     // std::string (reference dropped)
        auto& ref2 { getRef() };    // std::string& (reference reapplied)

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
            ============[ top-level const and low-level const ]============
---------------------------------------------------------------------------------------*/

// a top-level const is a const qualifier that applies to an object itself

#ifdef ALLOW_ERROR              // uninitialized const int and uninitialized const pointer
namespace top_level_const
{
    const int x;        // this const applies to x, so it is top-level
    int* const ptr;     // this const applies to ptr, so it is top-level
}
#endif

// a low-lelvel const is a const qualifier that applies to the object being referenced or
// pointed to

#ifdef ALLOW_ERROR              // uninitialized reference to const
namespace low_level_const
{
    const int& ref;     // this const applies to the object being referenced, so it is low-level
    const int* ptr;     // this const applies to the object being pointed to, so it is low-level
}
#endif

// a reference to a const value is always a low-level const.
// a pointer can have low-level, top-level, or both.

#ifdef ALLOW_ERROR              // uninitialized const pointer to const
namespace top_level_and_low_level
{
    const int* const ptr;
}
#endif

// when we say that a type deduction drops const qualifiers, it only drops top-level consts,
// low-level consts are not dropped.




/*---------------------------------------------------------------------------------------
            ============[ type deduction and const references ]============
---------------------------------------------------------------------------------------*/

// if the initializer is a reference to const, the reference is dropped first (and then
// reapplied if applicable), and then any top-level const is dropped from the result.

namespace type_deduction_and_const_references
{
    const std::string& getRef()
    {
        static const std::string name { "Maiuna"};
        return name;
    }

    int main()
    {
        auto ref1 { getRef() };     // std::string (top-level const and reference dropped)

        std::cout << typeid(ref1).name() << '\n';

        return 0;
    }
}

// we can reapply either or both of these

namespace type_deduction_and_const_references_reapply
{
    using type_deduction_and_const_references::getRef;

    int main()
    {
        auto ref1 { getRef() };             // std::string (top-level const and reference dropped)

        const auto  ref2 { getRef() };      // const std::string  (const reapplied)
        auto&       ref3 { getRef() };      // const std::string& (reference reapplied, low-level const not dropped)
        const auto& ref4 { getRef() };      // const std::string& (reference and const reapplied)

        return 0;
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    if you want a const reference, reapply the [const] qualifier even when it is not
    strictly necessary, as it makes your intent clear and helps prevenet mistakes.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                ============[ type deduction and pointers ]============
---------------------------------------------------------------------------------------*/

// unlike references, type deduction does not drop pointers

namespace type_deduction_and_pointers
{
    std::string* getPtr()
    {
        static std::string name { "Maiuna" };
        return &name;
    }

    int main()
    {
        auto  ptr1 { getPtr() };        // std::string*     // preferred
        auto* ptr2 { getPtr() };        // std::string*     // auto deduced to be std::string, then the pointer is reapplied afterwards

        std::cout << typeid(ptr1).name() << '\n';
        std::cout << typeid(ptr2).name() << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
            ============[ type deduction and const pointers ]============
---------------------------------------------------------------------------------------*/

namespace type_deduction_const_pointers
{
    using type_deduction_and_pointers::getPtr;

    int main()
    {
        const auto  ptr1 { getPtr() };      // std::string* const
        auto const  ptr2 { getPtr() };      // std::string* const

        const auto* ptr3 { getPtr() };      // const std::string*
        auto* const ptr4 { getPtr() };      // std::string* const

        return 0;
    }
}

namespace type_deduction_const_pointers_to_const
{
    const std::string* const getConstPtr()
    {
        static const std::string name { "Maiuna" };
        return &name;
    }

    int main()
    {
        auto  ptr1 { getConstPtr() };               // const std::string*
        auto* ptr2 { getConstPtr() };               // const std::string*

        auto const ptr3 { getConstPtr() };          // const std::string* const
        const auto ptr4 { getConstPtr() };          // const std::string* const

        auto* const ptr5 { getConstPtr() };         // const std::string* const
        const auto* ptr6 { getConstPtr() };         // const std::string*

        // const auto const  ptr7 { getConstPtr() };   // error: const qualifer can not be applied twice
        const auto* const ptr8 { getConstPtr() };   // const std::string* const

        return 0;
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    if you want a const pointer, reapply the [const] qualifier even when it is not
    strictly necessary, as it makes your intent clear and helps prevent mistakes.
---------------------------------------------------------------------------------------*/




//=======================================================================================

int main()
{
    type_deduction_and_const_references::main();
    type_deduction_and_pointers::main();

    return 0;
}