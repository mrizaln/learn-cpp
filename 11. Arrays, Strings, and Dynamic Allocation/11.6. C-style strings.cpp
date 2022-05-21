// #define IGNORE_ERROR

#include <iostream>
#include <iterator>

/*---------------------------------------------------------------------------------------
                       ============[ C-style string ]============
---------------------------------------------------------------------------------------*/

// a [C-style string] is simply an array of characters that uses a null termonator.
// a [null terminator] is a special character ('\0', ascii code 0) used to indicate the end
// of the string.
// C-style string is called a [null-terminated string].

namespace c_style_string
{
    int main()
    {
        char myString[] { "string" };       // a C-style string (null-terminator added automatically)

        const int length { static_cast<int>(std::size(myString)) };

        std::cout << myString << " has " << length << " characters.\n";

        for (int index { 0 }; index < length; ++index)
            std::cout << static_cast<int>(myString[index]) << ' ';
        
        std::cout << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                ============[ C-style strings and std::cin ]============
---------------------------------------------------------------------------------------*/

// there are amny cases where we don't know in advance how long our string is going to be.
// in this case, we can declare an array larger than we need

namespace read_from_cin
{
    int main()
    {
        char name[255] {};      // 254 char probably enough for a name
        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << "You entered: " << name << '\n';

        return 0;
    }
}

// above code is a poor programming practice, nothing is stopping the user from entering
// more than 254 characters.

// the recommended way of reading C-style strings using [std::cin] is as follows:

namespace read_from_cin_recommended_way
{
    int main()
    {
        char name[255] {};
        std::cout << "Enter your name: ";
        std::cin.getline(name, std::size(name));
        std::cout << "You entered: " << name << '\n';

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
                ============[ manipulating C-style strings ]============
---------------------------------------------------------------------------------------*/

// C++ provides many functions to manipulate C-style strings as part of the <cstring> header

#define __STDC_WANT_LIB_EXT1__ 1    // for strcpy_s()
#include <cstring>

namespace manipulating_c_style_strings
{
    // std::strcpy() allows you to copy a string to another string
    void using_strcpy()
    {
        char source[] { "Copy this!" };
        char dest[50];
        std::strcpy(dest, source);
        std::cout << dest << '\n';
    }
    // however, std::strcpy() can easily cause array overflows if you're not careful (e.g.
    // destination string is not big enough).

    // many programmers recommend using std::strncpy() instead, which allows you to specify
    // the size of the buffer, and ensures overflow doesn't occur.
    // unfortunately, std::strncpy() doesn't ensure strings are null terminated.

    // in C++11, strcpy_s() is preferred, which adds a new parameter to define the size of
    // the destination.
    // however, not all compiler support this function, and to use it, you have to define 
    // STDC_WANT_LIB_EXT with integer value 1

    // note: not working on my machine
#ifdef IGNORE_ERROR
    void using_strcpy_s()
    {
        char source[] { "Copy this!" };
        char dest[5];                       // note that the length of dest is less than source
        strcpy_s(dest, 5, source);
        std::cout << dest << '\n';
    }
#endif

    // another useful function is strlen() function, which returns the length of the C-style
    // string without the null terminator
    void using_strlen()
    {
        char name[20] { "Alex" };   // only use 5 char (4 letters + null)
        std::cout << "My name is " << name << '\n';
        std::cout << name << " has " << std::strlen(name) << " letters.\n";
        std::cout << name << " has " << std::size(name) << " characters in the array.\n";
    }

    /* other useful functions:
        - strcat()      appends one string to another (dangerous)
        - strncat()     appends one string to another (with buffer length check)
        - strcmp()      compare two strings (returns 0 if equal)
        - strncmp()     compare two strings up to a specific number of characters (returns 0 if equal)
    */
}




/*---------------------------------------------------------------------------------------
                ============[ dont use C-style strings ]=============
---------------------------------------------------------------------------------------*/





//=======================================================================================

#include <limits>

int main()
{
    // c_style_string::main();
    // read_from_cin::main();

    // // restore the state of std::cin
    // std::cin.clear();
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // read_from_cin_recommended_way::main();

    manipulating_c_style_strings::using_strcpy();

#ifdef IGNORE_ERROR
    manipulating_c_style_strings::using_strcpy_s();
#endif

    manipulating_c_style_strings::using_strlen();

    return 0;
}