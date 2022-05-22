#include <iostream>
#include <string>
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




/*---------------------------------------------------------------------------------------
  ============[ passing strings by const std::string& or std::string_view? ]============
---------------------------------------------------------------------------------------*/

// [std::string_view] is the most flexible choice, because it can work efficiently with C-
// style string arguments, std::string arguments, and std::string_view arguments.

namespace passing_by_string_view
{
    void printSV(std::string_view sv)
    {
        std::cout << sv << '\n';
    }

    int main()
    {
        std::string s { "Hello, world" };
        std::string_view sv { s };
        
        printSV(s);                 // ok: pass std::string
        printSV(sv);                // ok: pass std::string_view
        printSV("Hello, world");    // ok: pass C-style string literal

        return 0;
    }
}

// if your function needs to call some other funcion that takes a C-style string or std::string
// parameter, then const std::string& may be a better choice.




/*---------------------------------------------------------------------------------------
                        ============[ ownership issues ]============
---------------------------------------------------------------------------------------*/

// being only a view, std::string_view lifetime is independent of that of the string it is
// viewing.
// if the viewed string goes out of scope, std::string_view has nothing to observe and accessing
// it causes undefined behavior.

namespace std_string_view_issues
{
    std::string_view askForName()
    {
        std::cout << "What is your name? ";

        std::string name {};
        std::cin >> name;

        // for demonstration only, we're switching to std::string_view
        std::string_view view { name };

        return view;
    } // name dies, and so does the string that name created

    int main()
    {
        std::string_view view { askForName() };

        std::cout << "Your name is " << view << '\n';   // undefined behavior

        return 0;
    }
}




/*---------------------------------------------------------------------------------------
      ============[ opening the window (kinda) via the data() function ]============
---------------------------------------------------------------------------------------*/

// the string being viewed by std::string_view can be accessed by using the data() function
// which returns a C-style string.
// it should only be used if the std::string_view's view hasn't been modified and the string
// being viewed is null-terminated.

namespace view_std_string_view_via_data
{
    int main()
        {
        std::string_view str{ "balloon" };

        std::cout << str << '\n';

        // We use std::strlen because it's simple, this could be any other function
        // that needs a null-terminated string.
        // It's okay to use data() because we haven't modified the view, and the
        // string is null-terminated.
        std::cout << std::strlen(str.data()) << '\n';

        return 0;
    }
}




//=======================================================================================

int main()
{
    // example::example_0();
    // example::example_1();
    // change_viewed_string::main();
    // view_modification::main();
    // convert_string_view_to_string::main();
    // convert_string_view_to_c_style_string::main();
    passing_by_string_view::main();
    std_string_view_issues::main();

    return 0;
}