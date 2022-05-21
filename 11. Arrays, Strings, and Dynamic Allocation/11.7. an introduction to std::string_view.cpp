#include <iostream>
#include <string_view>

/*---------------------------------------------------------------------------------------
                ============[ introducing std::string_view ]=============
---------------------------------------------------------------------------------------*/

// unlike [std::string], which keeps its own copy of the string, [std::string_view] provides
// a view of a string that is defined elsewhere.

namespace example
{
    void example_0()
    {
        std::string_view text { "hello" };      // view the text "hello", which is stored in the binary
        std::string_view str { text };          // view of the same "hello"
        std::string_view more { str };          // view of the same "hello"

        std::cout << text << ' ' << str << ' ' << more << '\n';
    }

    void example_1()
    {
        std::string_view str { "Trains are fast!" };

        std::cout << str.length() << '\n';      // 16
        std::cout << str.substr(0, str.find(' ')) << '\n';  // Trains
        std::cout << (str == "Trains are fast!") << '\n';   // 1

        // since C++20
        std::cout << str.starts_with("Boats") << '\n';      // 0
        std::cout << str.ends_with("fast!") << '\n';        // 1

        std::cout << str << '\n';
    }
}

// because std::string_view doesn't create a copy of the string, if we change the viewed string,
// the changes are reflected in the std::string_view

namespace change_viewed_string
{
    void main()
    {
        char arr[] { "Gold" };
        std::string_view str { arr };

        std::cout << str << '\n';       // Gold

        // change 'd' to 'f'
        arr[3] = 'f';

        std::cout << str << '\n';       // Golf
    }
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    prefer [std::string_view] pver [std::string] for read-only strings, unless you
    already have a [std::string]
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                 ============[ view modification functions ]============
---------------------------------------------------------------------------------------*/

// [std::string_view] contains functions that let us manipulate the view of the string.
// this allows us to change the view without modifying the viewed string.

// the functions are [remove_prefix] and [remove_suffix]

namespace view_modification
{
    void main()
    {
        std::string_view str { "Peach" };
        std::cout << str << '\n';

        // ignore the first character
        str.remove_prefix(1);
        std::cout << str << '\n';

        // ignore the last 2 character
        str.remove_suffix(2);
        std::cout << str << '\n';
    }
}

// once you shrink the area, it cannot be opened up.
// the only way to reset the view is to reassign the source string to it again.




/*---------------------------------------------------------------------------------------
   ============[ std::string_view works with not-null-terminated strings ]============
---------------------------------------------------------------------------------------*/

// [std::string_view] doesn't use null terminators to mark the end of the string.
// rather, it knows where the string ends because it keeps track of its length.

namespace work_with_non_null_terminated_string
{
    void main()
    {
        // No null-terminator.
        char vowels[]{ 'a', 'e', 'i', 'o', 'u' };

        // vowels isn't null-terminated. We need to pass the length manually.
        // Because vowels is an array, we can use std::size to get its length.
        std::string_view str{ vowels, std::size(vowels) };

        std::cout << str << '\n'; // This is safe. std::cout knows how to print std::string_view.
    }
}




/*---------------------------------------------------------------------------------------
       ============[ converting a std::string to a std::string_view ]============
---------------------------------------------------------------------------------------*/

// a [std::string_view] can be constructed from a [std::string], and a [std::string] will
// implicitly convert to a [std::string_view]




/*---------------------------------------------------------------------------------------
       ============[ converting a std::string_view to a std::string ]============
---------------------------------------------------------------------------------------*/

// an [std::string_view] will not implicitly convert to an [std::string], but can be explicitly
// converted.

namespace convert_string_view_to_string
{
    void print(std::string s)
    {
        std::cout << s << '\n';
    }

    void main()
    {
        std::string_view sv { "balloon" };
        // print(sv);      // error

        std::string str { sv };     // okay
        print(str);                 // okay
        print(static_cast<std::string>(sv));        // okay
    }
}




/*---------------------------------------------------------------------------------------
      ============[ converting a std::string_view to a C-style string ]============
---------------------------------------------------------------------------------------*/

// to convert a [std::string_view] to a C-style string, we can do so by first converting to
// a [std::string].

#include <cstring>  // for std::strlen

namespace convert_string_view_to_c_style_string
{
    void main()
    {
        std::string_view sv { "balloon" };
        sv.remove_suffix(3);

        // create a std::string from the std::string_view
        std::string str { sv };

        // get the null-terminated C-style string
        auto szNullTerminated { str.c_str() };

        // pass the null-terminated string to the function that we want to use
        std::cout << str << " has " << std::strlen(szNullTerminated) << " letter(s)\n";
    }
}



//=======================================================================================

int main()
{
    example::example_0();
    example::example_1();
    change_viewed_string::main();
    view_modification::main();
    convert_string_view_to_string::main();
    convert_string_view_to_c_style_string::main();

    return 0;
}