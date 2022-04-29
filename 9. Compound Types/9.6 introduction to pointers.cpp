// #define ALLOW_ERROR

#include <iostream>

/*---------------------------------------------------------------------------------------
                ============[ the address-of operator (&) ]============
---------------------------------------------------------------------------------------*/

// the address-of operator returns the memory address of its operand

namespace address_of
{
    int main()
    {
        int x { 5 };
        std::cout << x << '\n';     // print the value of variable x
        std::cout << &x << '\n';    // print the memory address of variable x

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                ============[ the dereference operator (*) ]============
---------------------------------------------------------------------------------------*/

// the dereference operator returns the value at a given memory address as an lvalue

namespace dereference
{
    int main()
    {
        int x { 5 };
        std::cout << x << '\n';         // print the value of x
        std::cout << &x << '\n';        // print the address of x
        
        std::cout << *(&x) << '\n';     // print the value at the memory address of x

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                           ============[ pointers ]============
---------------------------------------------------------------------------------------*/

// a pointer is an object that holds a memory addresss as its value.

namespace pointer_declaration
{
    int a;          // a normal int
    int& b { a };   // an lvalue reference to an int value
    
    int* c;         // a pointer to an int value

    int main()
    {
        int x { 5 };            // normal variable
        int& ref { x };         // a reference to an integer

        int* ptr;               // a pointer to an integer

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                ============[ pointer initialization ]============
---------------------------------------------------------------------------------------*/

/*
  - pointers are not initialized by default.
  - a pointer that has not been initialized is called [wild pointer].
  - wild pointer contains garbage address, accessing it will result in undefined behavior.
  - you should always initialize your pointer to a known value
*/

namespace pointer_initialization
{
    int main()
    {
        int x { 5 };

        int* ptr;                   // wild pointer
        int* ptr2 {};               // null pointer
        int* ptr3 { &x };           // a pointer initialized with the address of variable x

    // once we have a pointer holding the address of another object, we can then use the dereference
    // operator to access the value of that address.

        std::cout << *ptr3 << '\n';

        return 0;
    }
}

// the type of the pointer has to match the type of the object being pointed to.

namespace match_type
{
    int i { 5 };
    double d { 7.0 };

    int* iPtr { &i };       // ok
    // int* iPtr2 { &d };      // not ok, type mismatch

    double* dPtr { &d };    // ok
    // double* dPtr2 { &i };   // not ok, type mismatch
}

// initializing a pointer with a literal value is disallowed (with one exception)

#ifdef ALLOW_ERROR
namespace pointer_initialization_with_literal
{
    int* ptr { 5 };                 // not ok
    int* ptr2 { 0x02021FAF };       // also not ok
}
#endif




/*---------------------------------------------------------------------------------------
                ============[ pointers and assignment ]============
---------------------------------------------------------------------------------------*/

/*
    we can use assignment operator with pointer:
        1. to change what the pointer is pointing at
        2. to change the value being pointed at
*/

// case 1 //
namespace change_what_being_pointed
{
    int main()
    {
        int x { 5 };
        int* ptr { &x };        // ptr points at x

        std::cout << *ptr;      // print the value at the address being pointed to (x)

        int y { 6 };
        ptr = &y;               // change ptr to point at y

        std::cout << *ptr;      // print the value at the address being pointed to (y)

        return 0;
    }
}

// case 2 //
namespace change_value_being_pointed_at
{
    int main()
    {
        int x { 5 };
        int* ptr { &x };        // ptr points at x

        std::cout << x;         // print the value of x
        std::cout << *ptr;      // print the value at the address being pointed to

        *ptr = 6;               // change the value at address ptr is hoding

        std::cout << x;         // x has been changed
        std::cout << *ptr;

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
        ============[ pointers behave much like lvalue references ]============
---------------------------------------------------------------------------------------*/

namespace similar_behaviour
{
    int main()
    {
        int x { 5 };
        int& ref { x };         // get a reference to x
        int* ptr { &x };        // get a pointer to x

        std::cout << x;
        std::cout << ref;
        std::cout << *ptr;

        ref = 6;                // use reference to change the value of x
        std::cout << x;
        std::cout << ref;
        std::cout << *ptr;

        *ptr = 7;               // use pointer to change the value of x
        std::cout << x;
        std::cout << ref;
        std::cout << *ptr;

        return 0;
    }
}

/*
    despite the similarity, there are differences between pointers and refereces
        1. references must be initialized, pointers are not required to be initialized (but should be).
        2. references are not object, pointers are.
        3. references can't be reseated, pointers can.
        4. references must always point at an object, pointers can point to nothing.
        5. references are "safe", pointers are inherently dangerous.
*/




/*---------------------------------------------------------------------------------------
        ============[ the address-of operator returns a pointer ]============
---------------------------------------------------------------------------------------*/

/*
  - the address-of operator doesn't return the address of its operand as a literal.
  - it instead returns a pointer containing the address of the operand whose type is derived
    from the argument.
*/

namespace address_of_operator_return_type
{
    int main()
    {
        int x { 4 };
        std::cout << typeid(&x).name() << '\n';     // print the type of &x

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                   ============[ the size of pointers ]============
---------------------------------------------------------------------------------------*/

// the size of a pointer is dependent upon the architecture the executable is compiled for.

namespace check_size
{
    int main() // on my 64-bit machine
    {
        char* chPtr{};        // chars are 1 byte
        int* iPtr{};          // ints are 4 bytes
        long double* ldPtr{}; // long doubles are 16 bytes

        std::cout << sizeof(chPtr) << '\n'; // prints 8
        std::cout << sizeof(iPtr) << '\n';  // prints 8
        std::cout << sizeof(ldPtr) << '\n'; // prints 8

        return 0;
    }
}

// on 64-bit machine, the pointer size is 64 bits (8 bytes)




/*---------------------------------------------------------------------------------------
                    ============[ dangling pointers ]============
---------------------------------------------------------------------------------------*/

// a [dangling pointer] is a pointer that is holding the address of an object that is no
// longer valid.

namespace dangling_pointer
{
    int main()
    {
        int x{ 5 };
        int* ptr{ &x };

        std::cout << *ptr; // valid

        {
            int y{ 6 };
            ptr = &y;

            std::cout << *ptr; // valid
        } // y goes out of scope, and ptr is now dangling

        std::cout << *ptr; // undefined behavior from dereferencing a dangling pointer

        return 0;
    }
}




//=======================================================================================

int main()
{
    // address_of::main();
    // dereference::main();
    // change_what_being_pointed::main();
    // change_value_being_pointed_at::main();
    // similar_behaviour::main();
    // address_of_operator_return_type::main();
    // check_size::main();
    dangling_pointer::main();

    return 0;
}