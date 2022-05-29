#include <iostream>
#include <string>
#include <algorithm>    // for std::sort

/*---------------------------------------------------------------------------------------
                            ============[  ]============
---------------------------------------------------------------------------------------*/

// in addition to dynamically allocating single values, we can also dynamically allocate
// arrays of variables.

// to allocate an array dynamically, we use the array form of new and delete (new[] and delete[]).

namespace dynamically_allocate_arrays
{
    void main()
    {
        std::cout << "Enter a positive integer: ";
        int length {};
        std::cin >> length;

        int* array { new int[length] {} };  // use array new.

        std::cout << "I just allocated an array of integers of length " << length << '\n';

        array[0] = 5;

        delete[] array;         // use array delete to deallocate array
    }
}




/*---------------------------------------------------------------------------------------
                ============[ dynamically deleting arrays ]============
---------------------------------------------------------------------------------------*/

// when deleting a dynamically allocated array, we have to use the array version of delete
// which is delete[].




/*---------------------------------------------------------------------------------------
    ============[ dynamica arrays are almost identical to fixed arrays ]============
---------------------------------------------------------------------------------------*/

// a dynamic array starts it life as a pointer that points to the first element of the array.
// consequently, it has the same limitations in that it doesn't know its length or size.
// a dynamic array functions identically to a decayedficed array, with the exception that
// the programmer is responsible for deallocating the dynamic array via the delete[] keyword.




/*---------------------------------------------------------------------------------------
          ============[ initializing dynamically allocated arrays ]============
---------------------------------------------------------------------------------------*/

// prior to C++11, there was no easy way to initialize a dynamic array to a non-zero value
// (initializer lists only worked for fixed arrays).
// however, starting with C++11, it's now possible to initialize dynamic arrays using initializer
// lists!

namespace initializing_dynamically_allocated_arrays
{
    int length = 2048;
    // 0 initialization
    int* array { new int[length] {} };

    // non-zero initialization
    int fixedArray[5] = { 9, 7, 5, 3, 1 };          // initilize a fixed array before C++11
    int* arrayy { new int[5] { 9, 7, 5, 3, 1 } };   // initialize a dynamic array since C++11

    // to prevent writing the type twice we can use auto.
    auto* arrayyy { new int[5] { 9, 7, 5, 3, 1 } };
}

// explicitly stating the size of the array is optional




/*---------------------------------------------------------------------------------------
                    ============[ resizing arrays ]============
---------------------------------------------------------------------------------------*/

// C++ does not provide a built-in way to resize an array that has already been allocated.

// it is possible to work aound this limitaion by dinamically allocating a new array, copying
// the elements over, and deleting the old array.
// however, this is error prone.
// we recommend avoiding doing this yourself

// fortunately, C++ provide a resizable array as part of the standard libraary called std::vector.




//=======================================================================================

/*----------
    quiz
----------*/

namespace quiz_1
{
    /*
        write a program that:
          - asks the user how many names they with to enter
          - dynamically allocates a std::string array
          - asks the user to enter each name
          - calls std::sort to sort the names
          - prints the sorted list of names
    */

    std::string getNameCount(const int num)
    {
        std::cout << "Enter name #" << num << ": ";
        std::string name {};
        std::getline(std::cin >> std::ws, name);
        return name;
    }

    void printNames(std::string nameArr[], const int len)
    {
        for (int i { 0 }; i < len; ++i)
            std::cout << "Name #" << i+1 << ": " << nameArr[i] << '\n';;
    }

    int main()
    {
        // get array length
        std::cout << "How many names would you like to enter? ";
        int length {};
        std::cin >> length;

        // allocate string array
        auto* nameArray { new std::string[length] {} };

        // get names
        for (int i { 0 }; i < length; ++i)
            nameArray[i] = getNameCount(i+1);

        // sort and print
        std::sort(nameArray, nameArray+length);
        std::cout << '\n'
                  << "Here is your sorted list:\n";
        printNames(nameArray, length);

        return 0;
    }
}




//=======================================================================================

int main()
{
    // dynamically_allocate_arrays::main();

    quiz_1::main();

    return 0;
}

