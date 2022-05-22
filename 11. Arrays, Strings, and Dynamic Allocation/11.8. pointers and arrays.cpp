#include <iostream>

/*---------------------------------------------------------------------------------------
                        ============[ array decay ]============
---------------------------------------------------------------------------------------*/

int array[5] { 9, 7, 5, 3, 1 };

// to us, the above is an array of 5 integers, but to the compiler array is a variable of
// type int[5].

// in all but two cases, when a fixed array is used in an expression, the fixed array will
// [decay] (be implicitly converted) into a pointer that points to the furst element array.

namespace array_decay
{
    void main()
    {
        int array[5] { 9, 7, 5, 3, 1 };

        // print address of the array's first element
        std::cout << "Element 0 has address: " << &array[0] << '\n';

        // print the value of the pointer the array decays to
        std::cout << "The array decays to a pointer holding address: " << array << '\n';

        // the two above will be the same
    }
}

// note: an array and a pointer to the array are not identical (many said it's identical!).




/*---------------------------------------------------------------------------------------
        ============[ differences between pointers and fixed arrays ]============
---------------------------------------------------------------------------------------*/

// the primary difference occurs when using the sizeof() operator.
// when used on a fixed array, sizeof returns the size of the entire array.
// when used on a pointer, sizeof returns the sie of a memory address (in bytes).

namespace pointer_array_difference
{
    void main()
    {
        int array[5] { 9, 7, 5, 3, 1 };

        std::cout << sizeof(array) << '\n';     // will print sizeof(int) * array length

        int* ptr { array };
        std::cout << sizeof(ptr) << '\n';       // will print the size of a pointer
    }
}

// the second difference occurs when using the address-of operator (&).
// taking the address of a pointer yields the memory address of the pointer variable.
// taking the address of the array returns a pointer to the entire array.

namespace pointer_array_difference
{
    void main_0()
    {
        int array[5] { 9, 7, 5, 3, 1 };
        std::cout << array << '\n';         // some address
        std::cout << &array << "\n\n";      // same as above

        int* ptr { array };
        std::cout << ptr << '\n';           // same as above
        std::cout << &ptr << '\n';          // different
    }
}




/*---------------------------------------------------------------------------------------
        ============[ revisiting passing fixed arrays to functions ]============
---------------------------------------------------------------------------------------*/

// when passing an array as an argument to a function, a fixed array decays into a pointer,
// and the pointer is passed to the function.

namespace passing_fixed_arrays_to_functions
{
    void printSize(int* array)
    {
        // array is treated as a pointer here
        std::cout << sizeof(array) << '\n';
    }

    void printSize_0(int array[])
    {
        // array is also treated as a pointer here
        std::cout << sizeof(array) << '\n';
    }

    void main()
    {
        int array[] { 1, 1, 2, 3, 5, 6, 8, 13, 21 };
        std::cout << sizeof(array) << '\n';

        printSize(array);       // returns pointer size
        printSize_0(array);     // same as above
    }
}

/* in the above example, these two are idential
        void printSize(int array[]);
        void printSize(int* array);
*/

// [ best practice ]
/*---------------------------------------------------------------------------------------
    favor the pointer syntax (*) over the array syntax ([]) for array function parameters
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                ============[ an intro to pass by address ]=============
---------------------------------------------------------------------------------------*/

// the fact that arrays decay into pointers when passed to a function explains the underlying
// reason why changin an array in a function changes the actual array argument passed in.




/*---------------------------------------------------------------------------------------
         ============[ arrays in structs and classes don't decay ]=============
---------------------------------------------------------------------------------------*/

// arrays that are part of structs or classes do not decay when the whole struct or class
// is passed to a function.




//=======================================================================================

int main()
{
    array_decay::main();
    pointer_array_difference::main();
    pointer_array_difference::main_0();
    passing_fixed_arrays_to_functions::main();

    return 0;
}