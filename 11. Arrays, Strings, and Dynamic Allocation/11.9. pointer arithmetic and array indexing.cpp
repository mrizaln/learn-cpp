#include <iostream>
#include <iterator>

/*---------------------------------------------------------------------------------------
                    ============[ pointer arithmetic ]============
---------------------------------------------------------------------------------------*/

// the C++ language allows you to perform integer addition or subtraction operations on pointers.
// for example, [ptr + 1] return the memory address of the next object of the type that [ptr]
// points to.

// when calculating the result of a pointer arithmetic expression, the compiler always multiplies
// the integer operand by the size of the object being pointer to.
// this is called [scaling].

namespace pointer_arithmetic
{
    void main()
    {
        int value { 7 };
        int* ptr { &value };

        std::cout << ptr << '\n';       // address
        std::cout << ptr + 1 << '\n';   // address + sizeof(int) * 1
        std::cout << ptr + 2 << '\n';   // address + sizeof(int) * 2
        std::cout << ptr + 3 << '\n';   // address + sizeof(int) * 3
    }
}




/*---------------------------------------------------------------------------------------
         ============[ arrays are laid out sequentially in memory ]============
---------------------------------------------------------------------------------------*/

namespace arrays_are_laid_out_sequentially
{
    void main()
    {
        int array[] { 9, 7, 5, 3, 1 };

        std::cout << "Element 0 is at address: " << &array[0] << '\n';
        std::cout << "Element 1 is at address: " << &array[1] << '\n';
        std::cout << "Element 2 is at address: " << &array[2] << '\n';
        std::cout << "Element 3 is at address: " << &array[3] << '\n';
        std::cout << "Element 4 is at address: " << &array[4] << '\n';
    }
}




/*---------------------------------------------------------------------------------------
        ============[ using a pointer to iterate through an array ]============
---------------------------------------------------------------------------------------*/

namespace using_pointer_to_iterate_array
{
    bool isVowel(char ch)
    {
        switch (ch)
        {
            case 'A':
            case 'a':
            case 'E':
            case 'e':
            case 'I':
            case 'i':
            case 'O':
            case 'o':
            case 'U':
            case 'u':
                return true;
            default:
                return false;
        }
    }

    void main()
    {
        char name[] { "Mollie" };
        int arrayLength { std::ssize(name) };
        int numVowels { 0 };

        for (char* ptr{ name }; ptr != (name+arrayLength); ++ptr)
        {
            if (isVowel(*ptr))
                ++numVowels;
        }

        std::cout << name << " has " << numVowels << " vowels\n";
    }
}

// because counting elements is common, the algorithm library offers [std::count_if], which
// counts elements that fulfull a condition.

#include <algorithm>

namespace using_pointer_to_iterate_array
{
    void main_0()
    {
        char name[] { "Mollie" };

        auto numVowels { std::count_if(std::begin(name), std::end(name), isVowel) };

        std::cout << name << " has " << numVowels << " vowels\n";
    }
}

// std::begin returns an iterator (pointer) to the first element.
// std::end returns an iterator to the element that would be one after the last.




//=======================================================================================

/*----------
    quiz
----------*/

namespace quiz_2
{
    int* find(int* begin, int* end, int value)
    {
        for (int* ptr{ begin }; ptr != end; ++ptr)
        {
            if (*ptr == value)
                return ptr;
        }
        
        return end;
    }

    int main()
    {
        int arr[] { 2, 5, 4, 10, 8, 20, 16, 40 };

        // search for the first element with value 20.
        int* found { find(std::begin(arr), std::end(arr), 20) };

        if (found != std::end(arr))
            std::cout << *found << '\n';
        
        return 0;
    }
}



//=======================================================================================

int main()
{
    // pointer_arithmetic::main();
    // arrays_are_laid_out_sequentially::main();
    // using_pointer_to_iterate_array::main();
    // using_pointer_to_iterate_array::main_0();

    quiz_2::main();

    return 0;
}