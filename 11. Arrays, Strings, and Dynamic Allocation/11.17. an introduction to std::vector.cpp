#include <iostream>
#include <vector>

// besides std::array, C++ also provides functionality that makes working with dynamic arrays
// safer and easier.
// the functionality is std::vector.


/*---------------------------------------------------------------------------------------
                    =============[ introduction ]=============
---------------------------------------------------------------------------------------*/

// std::vector provides dynamic array functionality that handles its own memory management.
// this means, you can create dynamic arrays without explicit allocation/deallocation.
// std::vector lives in the <vector> header.

#include <vector>

namespace using_std_vector
{
    // declaration
    std::vector<int> array;
    std::vector<int> array0 = { 9, 7, 5, 3, 1 };    // use initializer list
    std::vector<int> array1 { 9, 7, 5, 3, 1 };      // use uniform initialization

    // since C++17 the type can be omitted
    std::vector array4 { 9, 7, 5, 3, 1 };
}

// note that in both the unitialized and initialized case, you don't need to include the
// array length at compile time.
// this is because std::vector will dynamically allocate memory for its contents as requested.

namespace using_std_vector
{
    // accessing the element
    void accessing()
    {
        std::vector arrayy {3, 3, 5, 23, 12, 36, 57, 67 };

        std::cout << arrayy[3] << '\n';         // no bound checking
        std::cout << arrayy.at(4) << '\n';      // does bound checking
    }
}

// as of C++11, you can also assign values to std::vector using an initializer list
// in this case, the vector will self-resize to match the number of elements provided

namespace using_std_vector
{
    void initializer_list()
    {
        std::vector<int> arrayyy;   // size 0

        arrayyy = { 12, 3, 4, 6, 78, 9 };     // array length is now 6
        arrayyy = { 24, 5, 7, 2 };            // array length is now 4
    }
}

// [ self-cleanup prevents memory leaks]
/*
  - when a vector variable goes out of scope, it automatically deallocates the memory it
    controls (if necessary).
  - this is not only handy but also helps memory leaks
*/




/*---------------------------------------------------------------------------------------
                ============[ vectors remember their length ]============
---------------------------------------------------------------------------------------*/

// unlike built-in dynamic arrays, which don't know the length of the array they are pointing
// to, std::vector keeps track of its length.

namespace vector_remembers_their_length
{
    void printLength(const std::vector<int>& array)
    {
        std::cout << "The length is " << array.size() << '\n';
    }

    void main()
    {
        std::vector array { 9, 7, 5, 3, 1 };
        printLength(array);

        std::vector<int> empty {};
        printLength(empty);
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ resizing a vector ]============
---------------------------------------------------------------------------------------*/

// resizing a built-in dynamically allocated array is complicated.
// resizing a std::vector is as simple as calling the resize() function

namespace resizing_vector
{
    void increase_length()
    {
        std::vector array { 0, 1, 2 };
        array.resize(5);                    // set the size to 5

        std::cout << "The length is: " << array.size() << '\n';

        for (auto i : array)
            std::cout << i << ' ';
        std::cout << '\n';
    }
}

// when we resized the vector, the existing element values were preserved.
// new elements are initialized to the default value for the type (0 for int).

// vector may be resized to be smaller

// resizing a vector is computationally expensive, you should minimize it.
// if you need a vector with a specific number of elements but don't know the values of the
// elements at the point of declaration, you can create a vector with default elements like

namespace resizing_vector
{
    void do_not_know_the_values()
    {
        std::vector<int> array(5);  // direct initialization
                                    // create a vector with 5 elements each element is 0

        std::cout << "The length is: " << array.size() << '\n';

        for (int i : array)
            std::cout << i << ' ';
        std::cout << '\n';
    }
}




/*---------------------------------------------------------------------------------------
                       ============[ compacting bools ]============
---------------------------------------------------------------------------------------*/

// there's a special implementation for std::vector of type bool that will compact 8 booleans
// into a byte.
// this is happends behind the scene.

namespace vector_cool_trick
{
    void main()
    {
        std::vector<bool> array { 1, 0, 0, 1, 1 };
        std::cout << "The length is: " << array.size() << '\n';

        for (int i : array)
            std::cout << i << ' ';
        std::cout << '\n';
    }
}



//=======================================================================================

int main()
{
    using_std_vector::accessing();
    
    vector_remembers_their_length::main();

    resizing_vector::increase_length();
    resizing_vector::do_not_know_the_values();

    vector_cool_trick::main();

    return 0;
}