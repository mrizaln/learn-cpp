#include <iostream>
#include <array>
#include <numeric>      // for std::midpoint
#include <cassert>

// description
/*---------------------------------------------------------------------------------------
    create a binary search algorithm
---------------------------------------------------------------------------------------*/

// binary search, return the index of found number
int binarySearch_iterative(const int* array, int target, int min, int max)
{
    assert(array && "invalid array");

    bool found{ false };        // not found yet
    int mid{};

    while (min <= max)
    {
        mid = std::midpoint(min, max);

        if (array[mid] > target)
            max = mid - 1;
        else if (array[mid] < target)
            min = mid + 1;
        else
            return mid;       // found
    }
    return -1;
}

int binarySearch_recursive(const int* array, int target, int min, int max)
{
    assert(array && "invalid array");

    // not found
    if (min > max)
        return -1;

    int mid{ std::midpoint(min, max) };

    if (array[mid] > target)
        return binarySearch_recursive(array, target, min, mid-1);
    else if (array[mid] < target)
        return binarySearch_recursive(array, target, mid+1, max);
    else
        return mid;     // found
}

int main()
{
    // test
    //------
    constexpr int array[]{ 3, 6, 8, 12, 14, 17, 20, 21, 26, 32, 36, 37, 42, 44, 48 };

    constexpr int numTestValues{ 9 };
    constexpr int testValues[numTestValues]{ 0, 3, 12, 13, 22, 26, 43, 44, 49 };
    int expectedValues[numTestValues]{ -1, 0, 3, -1, -1, 8, -1 ,13, -1 };

    // auto binarySearch{ binarySearch_iterative };
    auto binarySearch{ binarySearch_recursive };

    // loop
    for (int count{ 0 }; count < numTestValues; ++count)
    {
        // see if the test value is in the array
        int index{ binarySearch(array, testValues[count], 0, static_cast<int>(std::size(array)-1)) };

        if (index == expectedValues[count])
            std::cout << index << ' ' << expectedValues[count] << "\ttest value " << testValues[count] << " passed!\n";
        else
            std::cout << index << ' ' << expectedValues[count] << "\ttest value " << testValues[count] << " failed. There's something wrong with your code!\n";
    }

    return 0;
}