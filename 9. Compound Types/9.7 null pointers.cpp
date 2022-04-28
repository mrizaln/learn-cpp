// #define ALLOW_RUNTIME_ERROR

#include <iostream>

/*---------------------------------------------------------------------------------------
                      ============[ null pointers ]============
---------------------------------------------------------------------------------------*/

// a pointer can holds a null value
// when a pointer holding a null value, it means the pointer is not pointing at anything.

namespace null_pointer
{
    int main()
    {
        int* ptr {};        // ptr is now a null pointer

        return 0;
    }
}

// a pointer that is initially set to a null can later be changed to point at a valid object

namespace change_to_point_valid_object
{
    int main()
    {    
        int* ptr{};

        int x { 5 };
        ptr = &x;               // ptr now pointing to an object

        std::cout << *ptr;

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ the nullptr keyword ]============
---------------------------------------------------------------------------------------*/

// [nullptr] keyword represents a null pointer literal.
// we can use nullptr to explicitly initialize or assign a pointer a null value.

namespace nullptr_keyword
{
    void someFunction(int* ptr)
    {
        // do something
    }

    int main()
    {
        int* ptr { nullptr };       // intitialize a pointer using nullptr

        int value { 5 };
        int* ptr2 { &value };       // valid pointer
        ptr2 = nullptr;             // assign nullptr to make the pointer null pointer

        someFunction(nullptr);      // pass nullptr to a function

        return 0;
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    use [nullptr] when you need a null pointer literal for initialization, assignment, or
    passing a null pointer to a function.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
  ============[ dereferencing anull pointer results in undefined behavior ]============
---------------------------------------------------------------------------------------*/

// like dereferencing a wild pointer, dereferencing a null pointer lead to undefined behavior

#ifdef ALLOW_RUNTIME_ERROR
namespace dereferencing_null_pointer
{
    int main()
    {
        int* ptr {};
        std::cout << *ptr;      // segmentation fault

        return 0;
    }
}
#endif

// [ warning ]
/*---------------------------------------------------------------------------------------
    whenever you are using pointers, you'll need to be extra careful that your code isn't
    dereferencing null or dangling pointers, as this will cause undefined behavior (most
    likely crash).
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                ============[ checking for null pointers ]============
---------------------------------------------------------------------------------------*/

// we can use a conditional to test whether a pointer has value [nullptr] or not.

namespace checking_null_pointer
{
    void explicit_test()
    {
        int x { 5 };
        int* ptr { &x };

        if (ptr == nullptr)     // explicit test for equivalence
            std::cout << "ptr is null\n";
        else
            std::cout << "ptr is non-null\n";

        int* nullPtr {};
        std::cout << "nullPtr is " << (nullPtr == nullptr ? "null\n" : "non-null\n");
    }

    // pointers will implicitly convert to boolean values: nullptr => false, and likewise
    void implicit_test()
    {
        int x { 5 };
        int* ptr { &x };

        if (ptr)        // implicit test
            std::cout << "ptr is non-null\n";
        else
            std::cout << "ptr is null\n";

        int* nullPtr {};
        std::cout << "nullPtr is " << (nullPtr ? "non-null\n" : "null\n");
    }

    int main()
    {
        explicit_test();
        implicit_test();

        return 0;
    }
}

// [ warning ]
/*---------------------------------------------------------------------------------------
    conditionals can only be used to differentiate null pointers from non-null pointers.
    there is no convenient way to determine whether a non-null pointer is pointing to a
    valid object or dangling.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
           ============[ use nullptr to avoid dangling pointers ]============
---------------------------------------------------------------------------------------*/

/*
  - because there is no way to detect whether a pointer is dangling, we need to avoid having
    any dangling pointers in out program in the first place.
  - we do that by ensuring that any pointer that is not pointing at a valid object is set
    to [nullptr].

  - unfortunately, avoiding dangling pointers isn't always easy" when an object is destroyed,
    any pointers to that object will be left dangling.
*/




/*---------------------------------------------------------------------------------------
          =============[ legacy null pointer literals: 0 and NULL ]============
---------------------------------------------------------------------------------------*/

// in older code, null pointer literals are 0 and NULL

namespace legacy_null_pointer_literals
{
    // 0
    void zero()
    {
        float* ptr { 0 };           // the only time you can assign an integral literal to a pointer

        float* ptr2 {};             // uninitialized
        ptr2 = 0;                   // ptr2 now is a null pointer
    }

    // NULL
    // it is a preprocessor macro defined in the <cstddef> header (inherited from C)
    #include <cstddef>      // for null
    void null()
    {
        double* ptr { NULL };       // ptr is a null pointer

        double* ptr2 {};
        ptr2 = NULL;
    }
}

// both [0] and [NULL] should be avoided in modern C++




/*---------------------------------------------------------------------------------------
      ============[ favor references over pointers whenever possible ]============
---------------------------------------------------------------------------------------*/

/*
  - pointer abilities are inherently dangerous: a null pointer runs the risk of being dereferenced,
    and the ability to change what apointer is pointing at can make creating a dangling pointers
    easier.
*/

namespace references_vs_pointers
{
    int main()
    {
        int* ptr {};
        {
            int x { 5 };
            ptr = &x;               // reseat pointer (not possible with a reference)
        } // ptr is now dangling
    }
}

/*
  - since references can't be bound to null, we don't have to worry about null references.
  - and because references must be bound to a valid object upon creation an then can't be
    reseated, dangling references are harder to create.
*/

// [ best practice ]
/*---------------------------------------------------------------------------------------
    because they are safer, references should be favored over pointers, unless the
    additional capabilities provided by pointers are needed.
---------------------------------------------------------------------------------------*/





//=======================================================================================

int main()
{
#ifdef ALLOW_RUNTIME_ERROR
    dereferencing_null_pointer::main();
#endif

    checking_null_pointer::main();

    return 0;
}