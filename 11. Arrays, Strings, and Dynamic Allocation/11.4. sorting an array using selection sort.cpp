#include <iostream>
#include <iterator>     // for std::size
#include <utility>      // for std::swap


/*---------------------------------------------------------------------------------------
            ============[ selection sort ]============
---------------------------------------------------------------------------------------*/

/*
    selection sort performs the following steps to sort an array from smallest to largest:
        1. starting at array index 0, search the entire array to find the smallest value.
        2. swap the smallest value found in the array with the value at index 0.
        3. repeat steps 1 and 2 starting from the next index.
*/

namespace selection_sort
{
    int main()
    {
        int array[] { 30, 50, 20, 10, 40 };
        constexpr int length{ static_cast<int>(std::size(array))};

        for (int startIndex { 0 }; startIndex < length-1; ++startIndex)
        {
            int smallestIndex { startIndex };

            for (int currentIndex { startIndex+1 }; currentIndex < length; ++currentIndex )
            {
                if (array[currentIndex] < array[smallestIndex])
                    smallestIndex = currentIndex;
            }

            std::swap(array[startIndex], array[smallestIndex]);
        }

        for (int index { 0 }; index < length; ++index)
            std::cout << array[index] << ' ';
        
        std::cout << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                        ============[ std::sort ]============
---------------------------------------------------------------------------------------*/

// because sorting is common, the C++ standard library includes a sorting function named
// std::sort (in the <algorithm> header)

#include <algorithm>

namespace std_sort
{
    int main()
    {
        int array[] { 30, 50, 20, 10, 40 };

        std::sort(std::begin(array), std::end(array));

        for (int i { 0 }; i < static_cast<int>(std::size(array)); ++i)
            std::cout << array[i] << ' ';
        
        std::cout << '\n';

        return 0;
    }
}

// by default, std::sort sorts in ascending order using operator<




//=======================================================================================

/*----------
    quiz
----------*/

namespace quiz_1
{
    // bubble sort

    void bubbleSort(int array[], int size)
    {
        for (int iteration { 0 }; iteration < size-1; ++iteration)
        {
            for (int index { 0 }; index < size-1; ++index)
            {
                if (array[index] > array[index+1])
                    std::swap(array[index], array[index+1]);
            }
        }
    }

    int main()
    {
        int array[] { 6, 3, 2, 9, 7, 1, 5, 4, 8, };
        constexpr int size { static_cast<int>(std::size(array)) };

        // before sorting
        for (int i { 0 }; i < size; ++i)
            std::cout << array[i] << ' ';
        
        std::cout << '\n';

        bubbleSort(array, size);

        // after sorting
        for (int i { 0 }; i < size; ++i)
            std::cout << array[i] << ' ';
        
        std::cout << '\n';

        return 0;
    }
}




namespace quiz_2
{
    // optimized bubble sort

    void optimizedBubbleSort(int array[], int size)
    {
        for (int iteration { 0 }; iteration < size-1; ++iteration)
        {
            bool noSwap { true };

            for (int index { 0 }; index < size-iteration-1; ++index)
            {
                if (array[index] > array[index+1])
                {
                    std::swap(array[index], array[index+1]);
                    noSwap = false;
                }
            }

            if (noSwap)
            {
                std::cout << "early termination on iteration " << iteration << '\n';
                break;
            }
        }
    }

    int main()
    {
        int array[] { 6, 3, 2, 9, 7, 1, 5, 4, 8, };
        constexpr int size { static_cast<int>(std::size(array)) };

        // before sorting
        for (int i { 0 }; i < size; ++i)
            std::cout << array[i] << ' ';
        
        std::cout << '\n';

        optimizedBubbleSort(array, size);

        // after sorting
        for (int i { 0 }; i < size; ++i)
            std::cout << array[i] << ' ';
        
        std::cout << '\n';

        return 0;
    }
}




//=======================================================================================

int main()
{
    // selection_sort::main();
    // std_sort::main();

    // quiz_1::main();
    quiz_2::main();
}