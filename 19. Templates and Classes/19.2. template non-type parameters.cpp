#include <iostream>


/*---------------------------------------------------------------------------------------
                    ============[ non-type parameters ]============
---------------------------------------------------------------------------------------*/

/*
  - a template non-type parameter is a template parameter where the type of the parameter
    is predefined and is substituted for a constexpr value passed in as an argument.

  - a non-type parameter can be any of the following types:
    > an integral type
    > an enumeration type
    > a pointer or reference to a class object
    > a pointer or reference to a funciton
    > std::nullptr_t
    > a floating point type (since C++20)
*/

// below is a non-dynamic (static) array class that uses both a type parameter and non-type
// parameter

template <typename T, int size>
class StaticArray
{
private:
    // the non-type parameter controls the size of the array
    T m_array[size]{};

public:
    T* getArray();
    T& operator[](int index)
    {
        return m_array[index];
    }
};

// outside of class
template <typename T, int size>
T* StaticArray<T, size>::getArray()
{
    return m_array;
}

int main()
{
    // integer array
    //---------------
    StaticArray<int, 12> intArray;

    // fill it up in order
    for (int count{ 0 }; count < 12; ++count)
        intArray[count] = count;

    // print it backwards
    for (int count{ 11 }; count >= 0; --count)
        std::cout << intArray[count] << ' ';
    std::cout << '\n';
    //---------------

    // double array
    //--------------
    StaticArray<double, 4> doubleArray;

    for (int count{ 0 }; count < 4; ++count)
        doubleArray[count] = 4.4 + 0.1 * count;

    for (int count{ 0 }; count < 4; ++count)
        std::cout << doubleArray[count] << ' ';
    std::cout << '\n';
    //--------------

    return 0;
}