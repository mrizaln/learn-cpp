// #define IGNORE_UNDEFINED_BEHAVIOR

#include <iostream>

/*---------------------------------------------------------------------------------------
                  ============[ initializing fixed arrays ]============
---------------------------------------------------------------------------------------*/

// array elements are treated just like normal variables, and as such, they are not initialized
// when created.

// one way to "initialie" an array is to do it element by element (in part I).

// C++ provides a more convenient way to initialize arrays using [initializer list]

namespace intitialize_an_array
{
    int prime[5] { 2, 3, 5, 7, 11 };

    // if there are more initializer than the length of the array, the compiler will generate
    // an error

    // if there are less initializer, the remaining elements are initialized to 0.
    int otherPrime[5] { 13, 17, 19 };
    void print()
    {
        std::cout << otherPrime[0] << '\n';
        std::cout << otherPrime[1] << '\n';
        std::cout << otherPrime[2] << '\n';
        std::cout << otherPrime[3] << '\n';
        std::cout << otherPrime[4] << '\n';
        std::cout << otherPrime[5] << '\n';
    }

    // to initialize zeroes in an array, you can do this
    int array[5] {};

    // if the initializer list is moitted, the elements are uninitialized
    int array1[5];
    // unless they are class-type
    std::string strArray[5];                    // initialize all elements to an empty string


    // omitted length
    int otherArray[] { 0, 1, 2, 3, 4, 5 };      // let the initializer list set length of the array
}




/*---------------------------------------------------------------------------------------
                      ============[ arrays an enums ]============
---------------------------------------------------------------------------------------*/

// one of the big documentation problems with arrays is that integer indices do not provide
// any information to the programmer abour the meaning of the index.

// this can be solved by setting up an enumeration.

namespace arrays_and_enums
{
    enum StudentNames
    {
        kenny,          // 0
        kyle,           // 1
        stan,           // 2
        butters,        // 3
        cartman,        // 4

        max_students,   // 5
    };

    int main()
    {
        int testScore[max_students] {};
        testScore[stan] = 76;

        return 0;
    }
}

// this "trick" only works if you do not change the enumerator values manually




/*---------------------------------------------------------------------------------------
                ============[ passing arrays to functions ]============
---------------------------------------------------------------------------------------*/

// C++ /does not/ copy an array when an array is passed into a function.
// instead, the actual array is passed.
// this has a side effect of allowing functions to directly change the value of array elements.

namespace passing_an_array
{
    void passValue(int value)
    {
        value = 99;
    }

    void passArray(int prime[5])
    {
        prime[0] = 11;
        prime[1] = 7;
        prime[2] = 5;
        prime[3] = 3;
        prime[4] = 2;
    }

    int main()
    {
        int value { 1 };
        std::cout << "before passValue: " << value << '\n';
        passValue(value);
        std::cout << "after passValue : " << value << '\n';

        int prime[5] { 2, 3, 5, 7, 11 };
        std::cout << "before passArray: " << prime[0] << ' '\
                                          << prime[1] << ' '\
                                          << prime[2] << ' '\
                                          << prime[3] << ' '\
                                          << prime[4] << '\n';
        passArray(prime);
        std::cout << "after passArray : " << prime[0] << ' '\
                                          << prime[1] << ' '\
                                          << prime[2] << ' '\
                                          << prime[3] << ' '\
                                          << prime[4] << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
              ============[ determining the length of an array ]============
---------------------------------------------------------------------------------------*/

// the std::size() function from the <iterator> header can be used to determine the length
// of arrays.

#include <iterator>     // for std::size
namespace length_of_an_array
{
    int main()
    {
        int array[]  { 1,1,2,3,1,3,56,2,5,6,3,2,4,6,43,23,24,5,2 };
        std::cout << "The array has: " << std::size(array) << " elements\n";

        return 0;
    }
}

// note that due to the way C++ passes arrays to functions, this will /not/ work for arrys
// that have been passed to functions.




/*---------------------------------------------------------------------------------------
              ============[ indexing an array out of range ]============
---------------------------------------------------------------------------------------*/

// consider this:
namespace indexing_out_of_range
{
    int main()
    {
    #ifdef IGNORE_UNDEFINED_BEHAVIOR
        int prime[5] {};    // hold 5 int
        prime[5] = 13;      // out of range
    #endif
        return 0;
    }
}

// C++ does not do any checking wheter your indices are valid for the array length.
// in the above example, the value of 13 is inseted into memory where the 6th element would
// have been had it existed.
// when this happens, you will get undefined behavior.



//=======================================================================================

int main()
{
    intitialize_an_array::print();
    passing_an_array::main();
    length_of_an_array::main();
    indexing_out_of_range::main();

    return 0;
}