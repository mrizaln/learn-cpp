#include <iostream>
#include <cassert>

/*---------------------------------------------------------------------------------------
                            ============[  ]============
---------------------------------------------------------------------------------------*/

// the [void pointer], also known as the generic pointer, is a special type of pointer that
// can be pointed at object of any data type!
// a void pointer is declated like a normal pointer.

namespace void_pointer
{
    int nValue;
    float fValue;

    struct Something
    {
        int n;
        float f;
    };

    Something sValue;

    void main()
    {
        void* ptr;
        ptr = &nValue;      // valid
        ptr = &fValue;      // valid
        ptr = &sValue;      // valid
    }
}

// however, because the void pointer desn not know what type of object it is pointing to,
// dereferencing a void pointer is illegal.
// instead, the void pointer must first be cast to another pointer type before the dereference
// can be performed.

namespace dereference_void_pointer
{
    void main()
    {
        int value { 5 };
        void* voidPtr { &value };

        // std::cout << *voidPtr << '\n';      // illegal: derefereeence of void pointer

        int* intPtr { static_cast<int*>(voidPtr) };
        std::cout << *intPtr << '\n';   // ok
    }
}

// if a void pointer doesn't know what it's pointing ti, how do we know what to cast it to?
// ultimately, that is up to you to keep track of

namespace keep_track_of_what_void_pointer_cast_into
{
    enum class Type
    {
        tInt,
        tFloat, 
        tCString,
    };

    void printValue(void* ptr, Type type)
    {
        switch (type)
        {
            case Type::tInt:
                std::cout << *static_cast<int*>(ptr) << '\n';
                break;
            case Type::tFloat:
                std::cout << *static_cast<float*>(ptr) << '\n';
                break;
            case Type::tCString:
                std::cout << static_cast<char*>(ptr) << '\n';
                break;
            default:
                assert(false && "type not found");
                break;
        }
    }
    
    void main()
    {
        int nValue { 5 };
        float fValue { 7.5f };
        char szValue[] { "Haokdamf!" };

        printValue(&nValue, Type::tInt);
        printValue(&fValue, Type::tFloat);
        printValue(&szValue, Type::tCString);
    }
}




/*---------------------------------------------------------------------------------------
                   ============[ void pointer miscellany ]============
---------------------------------------------------------------------------------------*/

// void pointer can be set to a null value

void* voidPtr { nullptr };

// although some compilers allow deleting a void pointer that points to dynamically allocated
// memory, doing so should be avoided, as it can result in udefined behavior.

// it is not possible to do pointer arithmetic on void pointer (pointer needs to know to know
// the type it points to in order to do this).

// there is no such thing as void reference




//=======================================================================================

int main()
{
    dereference_void_pointer::main();
    keep_track_of_what_void_pointer_cast_into::main();

    return 0;
}