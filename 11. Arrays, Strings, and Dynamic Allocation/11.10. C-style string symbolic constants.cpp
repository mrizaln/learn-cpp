#include <iostream>

/*---------------------------------------------------------------------------------------
    ============[ C-style string symbolic constants ]============
---------------------------------------------------------------------------------------*/

// in previous lesson, we discussed how you could create and initialize a C-style string
// like this:

namespace c_style_string_symbolic_constants
{
    void main()
    {
        char myName[] { "Alex" };       // fixed array
        std::cout << myName << '\n';
    }
}

// C++ also supports a way to create C-style string symbolic constants using pointers:

namespace c_style_string_symbolic_constants
{
    void main_0()
    {
        const char* myName { "Alex" };  // pointer to symbolic constant
        std::cout << myName << '\n';
    }
}

/*
  - those two program above operate and produce the same results, but C++ deals with the
    memory allocation for these slightly differently.

  - in the fixed array case, the program allocates memory for a fixed array og length 5,
    and initializes that memory with the string "Alex\0".
  - because memory has been specifically alloated for the array, you're free to alter the
    contents of the array.
  - the array is treated as a normal local variable, so when the array goes out of scope,
    the memory used by the array is freed up for other uses.

  - in the symbolic constant case, how the compiler handles this is implementation defined.
  - what usually happens is that the compiler places the string "Alex\0" into read-only memory
    somewhere, and then sets the pointer to point to it.
  - because thsi memory may be read only, best practice is to make sure the string is const.

  - as a result of string literals being stored in a fixed location in memory, string literals
    have static duration rather than automatic duration.
  - that means, when we use string literals, we don't have to worry about scoping issues.

  - C-style strings are used in a lot of old or low-level code, because they have a very
    small memory footprint.
  - modern code should favor the use of std::string and std::string_view, as those provide
    safe and easy access to the string.
*/




/*---------------------------------------------------------------------------------------
                 ============[ std::cout and char pointers ]============
---------------------------------------------------------------------------------------*/

namespace std_cout_and_char_pointer
{
    void main()
    {
        int nArray[5] { 9, 7, 5, 3, 1 };
        char cArray[] { "Hello!" };
        const char* name { "Alex" };

        std::cout << nArray << '\n';        // nArray will decay to type int*
        std::cout << cArray << '\n';        // cArray will decay ti type char*
        std::cout << name << '\n';          // name is already type char*
    }
}

// it will output:
/*-----------------
     <address>   
     "Hello!"
     "Alex"
-----------------*/

// here std::cout makes an assumption about your intent.
// if you pass it an object of type char* or const char*, it will assume you're intending
// to print a string.

// it may lead to unexpexted result:

namespace std_cout_and_char_pointer
{
    void main_0()
    {
        char c { 'Q' };
        std::cout << &c;
    }
}

// it assumed &c (which has type char*) was a string, so it printed the 'Q' and then kept
// going until ran into some memory holding a 0 value.




//=======================================================================================

int main()
{
    c_style_string_symbolic_constants::main();
    c_style_string_symbolic_constants::main_0();
    std_cout_and_char_pointer::main();
    std_cout_and_char_pointer::main_0();
}

