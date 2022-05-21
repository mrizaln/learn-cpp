// #define IGNORE_ERROR

#include <iostream>

/*---------------------------------------------------------------------------------------
                ============[  ]============
---------------------------------------------------------------------------------------*/

// the elements of an array can be of ay data type, including arrays!
// an array of arrays is called a [multidimensional array]

int array[3][5] {};     // a 3-element array fo 5-element arrays

// something like this: (3 rows, 5 columns)

/*----------------------------------------------------
    [0][0]  [0][1]  [0][2]  [0][3]  [0][4]  [0][5]
    [1][0]  [1][1]  [1][2]  [1][3]  [1][4]  [1][5]
    [2][0]  [2][1]  [2][2]  [2][3]  [2][4]  [2][5]
----------------------------------------------------*/




/*---------------------------------------------------------------------------------------
            ============[ initializing two-dimensional arrays ]============
---------------------------------------------------------------------------------------*/

namespace initializing_two_dimensional_array
{
    int array[3][5]
    {
        { 1, 2, 3, 4, 5 },      // row 0
        { 6, 7, 8, 9, 10 },     // row 1
        { 11, 12, 13, 14, 15}   // row 2
    };

    // C++ can replace missing initializers with 0
    int array_0[3][5]
    {
        { 1, 2, 3 },        // row 0 = 1, 2, 3, 0, 0
        { 6, 7, 8, 9 },     // row 1 = 6, 7, 8, 9, 0
        { 11, 12,}          // row 2 = 11, 12, 0, 0, 0
    };

    // two-dimensional arrays with initializer lists can omit (only) the leftmost length specification
    int array_1[][5]
    {
        { 1, 2, 3, 4, 5 },      // row 0
        { 6, 7, 8, 9, 10 },     // row 1
        { 11, 12, 13, 14, 15}   // row 2
    };

#ifdef IGNORE_ERROR
    // this not allowed
    int array_2[][]
    {
        { 1, 2, 3, 4, 5 },      // row 0
        { 6, 7, 8, 9, 10 },     // row 1
        { 11, 12, 13, 14, 15}   // row 2
    };
#endif

    // zero initialization
    int array_3[3][5] {};
}




/*---------------------------------------------------------------------------------------
        ============[ acessing elements in a two-dimensional array ]============
---------------------------------------------------------------------------------------*/

namespace accessing_element_multidimensional_array
{
    int main()
    {
        const int row { 3 };
        const int column { 5 };

        int array[row][column]
        {
            { 1, 2, 3, 4, 5 },      // row 0
            { 6, 7, 8, 9, 10 },     // row 1
            { 11, 12, 13, 14, 15}   // row 2
        };
        
        for (int r { 0 }; r < row; ++r)
        {
            for (int c { 0 }; c < column; ++c)
            {
                std::cout << array[r][c] << '\t';
            }
            std::cout << '\n';
        }

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
      ============[ multidimensional arrays larger than two dimensions ]============
---------------------------------------------------------------------------------------*/

// yes, multidimensional array may be larger than two dimensionns

int array3d[5][4][3] {};




//=======================================================================================

int main()
{
    accessing_element_multidimensional_array::main();

    return 0;
}