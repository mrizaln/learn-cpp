#include <iostream>

 /*---------------------------------------------------------------------------------------
                    ============[ pointers to pointers ]============
---------------------------------------------------------------------------------------*/

// a pointer to a pointer is declared using two asterisks

namespace pointer_to_pointer
{
    int** ptrptr;   // pointer to a pointer to an int
    int** ptrptr1 { nullptr };      // can be set to a null pointer
}

// a pointer to a pointer works just like a normal pointer -- you can perform idirection
// through it to retrieve the value pointed to.
// and because that value is itself a pointer, you can perform indirection through it again
// to get to the underlying value.

namespace pointer_to_pointer
{
    void main()
    {
        int value { 5 };

        int* ptr { &value };
        std::cout << *ptr << '\n';

        int** ptrptr { &ptr };
        std::cout << *ptrptr << '\n';       // address of value
        std::cout << **ptrptr << '\n';      // value
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ arrays of pointers ]============
---------------------------------------------------------------------------------------*/

// pointers to pointers have a few uses.
// the most common use is to dynamically allocate an array of pointers.

namespace pointer_array
{
    int** array { new int*[10] };
}




/*---------------------------------------------------------------------------------------
        ============[ two-dimensional dynamically allocated arrays ]============
---------------------------------------------------------------------------------------*/

// another common use fo pointers to pointers is to facilitate dynamically allocated multi-
// dimensional arrays

namespace two_dimensional_dynamic_array
{
    // int** array {new int[10][5] };      // won't work

    // if the rightmost dimension is constexpr
    void right_constexpr()
    {
        int x { 7 };        // non-constant
        int (*array)[5] { new int[x][5] };
        auto array_ { new int[x][5] };

        delete[] array;
        delete[] array_;
    }

    // if rightmost dimension not constexpr
    void no_constexpr()
    {
        int row { 10 };
        int col { 5 };

        // allocating array
        int** array { new int*[row] };              // rows
        for (int count { 0 }; count < row; ++count)
            array[count] = new int[col];            // columns
    
        // deallocating the array
        for (int count { 0 }; count < col; ++count)
            delete[] array[count];                      // delete column
        delete[] array;                                 // delete row
    }
}

// using above method is error prone
// we can instead flatten the two-dimensional array to a one-dimensional array
namespace two_dimensional_dynamic_array
{
    int getSingleIndex(int row, int col, int numberOfColumnsInArray);

    int row { 10 };
    int col { 5 };

    // allocating
    void main()
    {
        int* array { new int[row*col]};
        array[getSingleIndex(9, 4, 5)] = 3;
    }

    // using math to convert a row and column index for rectangular two dimensional array
    // into a single index for a one-dimnsional array
    int getSingleIndex(int row, int col, int numberOfColumnsInArray)
    {
        return (row * numberOfColumnsInArray) + col;
    }

}




/*---------------------------------------------------------------------------------------
           ============[ pointer to a pointer to a pointer to ... ]============
---------------------------------------------------------------------------------------*/

// yes, it's possible




//=======================================================================================

int main()
{
    pointer_to_pointer::main();

    return 0;
}