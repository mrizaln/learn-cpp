#include <iostream>

/*---------------------------------------------------------------------------------------
           ============[ the need for dynamic memory allocation ]============
---------------------------------------------------------------------------------------*/

/*
  - so far, we've already seed static and automatic memory allocation.
  - both have two things in common:
        1. the size of the variable/array must be known at compile time.
        2. memory allocation and dealocation happens automatically.

  - most normal variables (including fixed arrays) are allocated in a portion of memory
    called the [stack].
  - the amount of stack memory for a program is generally quite small.

  - [dynamic memory allocation] is a way for running programs to request memory from the
    operating system when needed.
  - this memory does not come from the program's limited stack memory; instead, it is
    allocated from a much larger pool of memory managed by the operating system called
    the [heap].
*/




/*---------------------------------------------------------------------------------------
           ============[ dynamically allocating single variables ]============
---------------------------------------------------------------------------------------*/

// to allocate a single variable dynamically, we use the scalar (non-array) form of the
// [new] operator.

namespace dynamically_allocate_a_single_variable
{
    // most of ten, we'll assign the return value to our own pointer variable.
    int* ptr { new int };
}

// when you dynamically allocate memory, you're asking the operating system to reserve
// some of the memory for your program use.
// if it can fulfill the request, it will return the address of that memory to your application.




/*---------------------------------------------------------------------------------------
        ============[ initializing a dynamically allocated variable ]============
---------------------------------------------------------------------------------------*/

namespace initializing_a_dynamically_allocated_variable
{
    int* ptr1 { new int (5) };      // use direct initialization
    int* ptr2 { new int { 6 } };    // use uniform initialization 
}




/*---------------------------------------------------------------------------------------
                ============[ deleting single variable ]============
---------------------------------------------------------------------------------------*/

// when we are done with a dynamically allocated variable, we need to explicitly tell C++
// to free the memory for reuse.
// for single variables, this is done via the scalar (non-array) form of the [delete] operator.

namespace deleting_a_dynamically_allocated_variable
{
    void main()
    {
        // allocate a memory
        int* ptr { new int { 19 } };
        *ptr = 231;

        // use it
        std::cout << *ptr << '\n';

        // you've done using it, so delete it
        delete ptr;
        ptr = nullptr;
    }
}

// when we delete an dynamically allocated variable, we are not actually delete anything,
// it simply returns the memory being pointed back to the operating system

// although it looks like we're deleting a variable, this is not the case.
// the pointer variable still has the same scope as before, and can be assigned a new value
// just like any other variable.




/*---------------------------------------------------------------------------------------
                    ============[ dangling pointers ]============
---------------------------------------------------------------------------------------*/

// a pointer that is pointing to deallocated memory is called a dangling pointer.
// indirection through- or deleting a dangling pointer will lead to undefined behavior.

namespace dangling_pointer
{
    void main()
    {
        int* ptr { new int {} };       // dynamically allocate an integer
        *ptr = 7;

        delete ptr;         // return the memory to the operaing system
                            // ptr is now a dangling pointer

        std::cout << *ptr;  // undefined behavior
        delete ptr;         // undefined behavior
    }
}

// deallocating memory may create multiple dangling pointers

namespace multiple_dangling_pointer
{
    void main()
    {
        int* ptr { new int {} };    // dynaically allocate an integer
        int* otherPtr { ptr };      // otherPtr is now pointed at the same memory as ptr;

        delete ptr;                 // return the memory to the operating system.
                                    // ptr and otherPtr are now dangling pointer
        
        ptr = nullptr;              // ptr is now a nullptr

        // however, otherPtr is still a dangling pointer
    }
}

/*
  - there are a few best practices that can help here.

  - first, try to avoid having multiple pointers point at the same piece of dynamic memory.
    if it's not possible, be clear about which pointer "owns" the memory (and responsible
    for deleting it) and which pointers are just accessing it.

  - second, when you delete a pointer, if that pointer is not going out of scope immediately
    afterward, set the pointer to nullptr.
*/




/*---------------------------------------------------------------------------------------
                   ============[ operator new can fail ]============
---------------------------------------------------------------------------------------*/

// by default, if [new] fails, a bad_alloc exception is thrown,
// if this exception isn't properly handled, the program will simply terminate (crash) with
// an unhandled exception error.

// in many cases, having new throw an exception is undesirable, so there's an alternate form
// of [new] that can be used instead to tell [new] to return a null pointer if memory can't
// be allocated.
// this is done by adding the constant std::nothrow between the new keyword and the allocation
// type.

int* ptr { new (std::nothrow) int };




/*---------------------------------------------------------------------------------------
          ============[ null pointer and dynamic memory allocation ]============
---------------------------------------------------------------------------------------*/

// null pointers are particularlu useful when dealing with dynamic memory allocation.
// in the context of dynamic memory allocation, a null pointer basically says "no memory
// has been allocated to this pointer".
// this allows us to do thins like conditionally allocate memory:

namespace null_pointer_and_dynamic_memory_allocation
{
    void idk(int* ptr)
    {
        if (!ptr)
            ptr = new int;

        delete ptr;
    }

    void delete_allocated_memory(int* ptr)
    {
        // deleting a null pointer has no effec
        delete ptr;     // no check needed
    }
}




/*---------------------------------------------------------------------------------------
                        ============[ memory leaks ]============
---------------------------------------------------------------------------------------*/

/*
  - dynamically allocated memory stays allocated unil it is explicitly deallocated until
    the program ends.
  - however, the pointers used to hold dynamically allocated memory addresses follow the
    normal scoping rules for local variables.

  - [memory leak]s happen when your program loses the address of some but of dynamically
    allocated memory before giving it back to the operating system.
  - when this happens, your program can't delete the dynamically allocated memory, because
    it is no longer knows where it is.
  - the operating system also can't use this memory, because that memory is considered to
    be still in use by your program.
*/

namespace memory_leaks
{
    void leak1()
    {
        int* ptr { new int {} };
    } // ptr is destroyed here, memory can't be deallocated

    void leak2()
    {
        int value = 5;
        int* ptr { new int {} };    // allocate memory
        ptr = &value;               // old address lost, memory leak results
    }

    void leak3()
    {
        int* ptr { new int{} };
        ptr = new int {};           // old address lost, memory leak results
    }
}




//=======================================================================================

int main()
{
    deleting_a_dynamically_allocated_variable::main();

    return 0;
}