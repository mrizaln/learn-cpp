#define IGNORE_ERROR

#include <iostream>

// C++ provides a functionality of safer built-in fixed arrays in the form of std::array
// std::array is a zero-overhead class

/*---------------------------------------------------------------------------------------
                        ============[ introduction ]============
---------------------------------------------------------------------------------------*/

// std::array provides fixed array functionality that won't decay when passed into a function.
// std::array is defined in the <array> header, insided the std namespace.

#include <array>

namespace using_std_array
{
    std::array<int, 3> myArray;
    // the length of std::array must be known at compile time

    // initialization
    std::array<int, 5> myArrayy = { 9, 7, 5, 3, 1 };    // initializer list
    std::array<int, 5> myArrayyy { 9, 7, 5, 3, 1 };     // list initialization

    // unlike built-in fixed array, you can't omit the array length
    // std::array<int, > adsfjh { 9, 7, 5, 3, 1 };         // error

    // however since C++17, it is allowed to omit the type and size
    // they can only be omitted together
    std::array myArrayyyy { 9, 7, 5, 3, 1};         // std::array<int, 5>
    std::array myArrayyyyy { 1.3, 3.4, 3.3 };       // std::array<double, 3>

    // since C++20, it is possible to specify the element type but omit the array length.
    auto myArray0 { std::to_array<int, 5>({9, 7, 5, 3, 1 }) };
    auto myArray1 { std::to_array<int>({9, 7, 5, 3, 1 }) };
    auto myArray2 { std::to_array({9, 7, 5, 3, 1 }) };

    // you can alos assign values to the array using initializer list
    void assign()
    {
        std::array<int, 5> myArray_;
        myArray_ = { 0, 1, 2, 3, 4 };   // ok
        myArray_ = { 9, 6, 2 };         // ok
    }

    // to acceess, you can use the subscript operator (no bound checking)
    // or using at() function that do bound checking
    void access()
    {
        std::array theArray { 0, 3, 5, 8, 6, 7 };
        std::cout << theArray[3] << '\n';
        std::cout << theArray[9] << '\n';       // out of bound, no error (bad things may happen)
        
        // using at()
        std::cout << theArray.at(3) << '\n';
        // std::cout << theArray.at(9) << '\n';    // out of bound, throws error
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ size and sorting ]============
---------------------------------------------------------------------------------------*/

// the size function can be used to retrieve the length of the std::array

namespace size_and_sorting
{
    void retrieve_size()
    {
        std::array myArray { 9.0, 7.2, 5.4, 5.4, 3.6, 1.8 };
        std::cout << myArray.size() << '\n';
    }
}

// because std::array doesn't decay to a pointer when passed to a function, the size() function
// will work even if you call it from within a function.

namespace size_and_sorting
{
    void printLength(const std::array<double, 5>& myArray)
    {
        std::cout << "length " << myArray.size() << '\n';
    }

    void length_main()
    {
        std::array myArray { 9.0, 7.2, 5.4, 3.6, 1.8 };

        printLength(myArray);
    }
}

// you can sort std::array using std::sort in the <algorithm>

#include <algorithm>
namespace size_and_sorting
{
    void sorting()
    {
        std::array myArray { 65, 3, 2, 7, 3, 28, 0, 9 };
        // std::sort(std::begin(myArray), std::end(myArray));
        std::sort(myArray.begin(), myArray.end());              // sort the array forwards
        // std::sort(myArray.rbegin(), myArray.rend());            // sort the array backwards

        for (int element : myArray)
            std::cout << element << ' ';
        std::cout << '\n';
    }
}




/*---------------------------------------------------------------------------------------
    ============[ passing std::array of different lengths to a function ]============
---------------------------------------------------------------------------------------*/

// with a std::array, the element type and array length are part of the type information.
// therefore, wen we use a std::array as a function parameter, we have to specify the element
// type and array length.
// fortunately, this limits our function to only handling arrays of specific type and lenght.

// fortunately, template came to rescue:

namespace passing_std_array_different_length
{
    template <typename T, std::size_t size>
    void printArray(const std::array<T, size>& myArray)
    {
        for (T element : myArray)
            std::cout << element << ' ';
        std::cout << '\n';
    }

    void main()
    {
        std::array myArray5{ 9.0, 7.2, 5.4, 3.6, 1.8 };
        printArray(myArray5);

        std::array myArray7{ 9.0, 7.2, 5.4, 3.6, 1.8, 1.2, 0.7 };
        printArray(myArray7);
    }
}




/*---------------------------------------------------------------------------------------
    ============[ manually indexing std::array via size_type ]============
---------------------------------------------------------------------------------------*/

namespace manually_indexing_std_array
{
    void mismatch()
    {
        std::array myArray { 7, 3, 1, 9, 5 };

        // Iterate through the array and print the value of the elements
        for (int i{ 0 }; i < myArray.size(); ++i)   // type mismatch
            std::cout << myArray[i] << ' ';         // type mismatch

        std::cout << '\n';
    }

    // i is int, and myArray.size() is std::size_t
    // operator[] on std::array accepts std::size_t type
}

// the correct way to manually index std::array is as follows

namespace manually_indexing_std_array
{
    void correct()
    {
        std::array myArray { 7, 3, 1, 9, 5 };

        // std::array<int, 5>::size_type is the return type of size()!
        for (std::size_t i{ 0 }; i < myArray.size(); ++i)
            std::cout << myArray[i] << ' ';

        std::cout << '\n';

    }
}




/*---------------------------------------------------------------------------------------
                    ============[ array of struct ]============
---------------------------------------------------------------------------------------*/

// of course we can use other type as std::array element, one of them is struct

namespace array_of_struct
{
    struct House
    {
        int number {};
        int stories {};
        int roomsPerStory {};
    };

    void no_initialize_main()
    {
        std::array<House, 3> houses {};     // zero initialization
        
        houses[0] = { 13, 4, 30 };
        houses[1] = { 14, 3, 10 };
        houses[2] = { 15, 3, 40 };

        for (const auto& house: houses)
        {
            std::cout << "House number " << house.number
                      << " has " << (house.stories * house.roomsPerStory)
                      << " rooms\n";
        }
    }
}

// above code works, but there's something wrong if we want to initialize house

namespace array_of_struct
{
#ifndef IGNORE_ERROR
    void initialize_something_wrong()
    {
        // doesn't work
        std::array<House, 3> houses{
            { 13, 4, 30 },
            { 14, 3, 10 },
            { 15, 3, 40 }
        };
        
        // above code try to initialize the first member with 9 values (?)
        // i don't really understand this one actually
    }
#endif
}

// to fix this, we can do this:

namespace array_of_struct
{
    void initialize_work()
    {
        std::array<House, 3> house0 {
            { 13, 4, 30, 14, 3, 10, 15, 3, 40 }
        };

        // above code is confusing, so use this instead
        std::array<House, 3> houses1 {
            {{13, 4, 30}, {14, 3, 10}, {15, 3, 40}}
        };
    }
}




//=======================================================================================

int main()
{
    using_std_array::access();

    size_and_sorting::retrieve_size();
    size_and_sorting::length_main();
    size_and_sorting::sorting();

    passing_std_array_different_length::main();

    array_of_struct::no_initialize_main();
    array_of_struct::initialize_work();

    return 0;
}