#include <iostream>

/*---------------------------------------------------------------------------------------
                  ============[ pointer to const value ]============
---------------------------------------------------------------------------------------*/

// a pointer to const value is a (non-const) pointer that points to a constant value

namespace pointer_to_cosnt_declaration
{
    int main()
    {
        const int x { 5 };
        const int* ptr { &x };      // ok

        // *ptr = 6;           // not allowed

        return 0;
    }
}

// the pointer to const is not const itself, so we can change what the pointer is pointing
// at by assigning the pointer a new address.

namespace change_what_being_pointed
{
    int main()
    {
        const int x { 5 };
        const int* ptr { &x };

        const int y { 6 };
        ptr = &y;               // ok

        return 0;
    }
}

// like reference to const, pointer to const can point to non-const variables too.
// it will treats the value being pointed to as constant.

namespace assign_non_const_variable_to_pointer_to_const
{
    int main()
    {
        int x { 5 };                // non-const
        const int* ptr { &x };      // ptr points to a "const int"

        // *ptr = 6;           // not allowed
        x = 6;                      // allowed

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ const pointers ]============
---------------------------------------------------------------------------------------*/

// we can also make a pointer itself constant.
// a [const pointer] is a pointer whose address can not be changed after initialization

namespace const_pointer_declaration
{
    int main()
    {
        int x { 5 };
        int* const ptr { &x };      // const after the asterisk means this is a const pointer

        return 0;
    }
}

// const pointer must be initialized upon definition.
// this value can't be changed via assignment.

namespace const_pointer_initialization
{
    int main()
    {
        int x { 5 };
        int y { 6 };

        int* const ptr { &x };          // ok
        // ptr = &y;           // not ok: error

        return 0;
    }
}

// it is possible to change the value being pointed to via dereferencing the const pointer

namespace const_pointer_change_value_being_pointed
{
    int main()
    {
        int x { 5 };
        int* const ptr { &x };

        *ptr = 6;                   // ok

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
               ============[ const pointer to a const value ]============
---------------------------------------------------------------------------------------*/

namespace const_pointer_to_const_value
{
    int main()
    {
        int value { 5 };
        const int* const ptr { &value };

        return 0;
    }
}

// a const pointer to a const value can't have its address changed, nor the value it is pointing
// to be changed through the pointer.





//=======================================================================================

int main()
{
    change_what_being_pointed::main();

    return 0;
}