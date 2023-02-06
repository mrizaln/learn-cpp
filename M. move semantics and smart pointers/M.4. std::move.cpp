/*------------------------------------------------------------------------------
                      ============[ std::move ]============
------------------------------------------------------------------------------*/

/*
  - in C++11, std::move is a standard library function that casts (using static_cast)
    its argument into an r-value reference, so that move semantics can be invoked.
  - thus, we can use std::move to cast an l-value into a type that will prefer being
    moved over being copied.
  - std::move is defined in the <utility> header.
*/

#include <iostream>
#include <string>
#include <utility>    // for std::move

namespace using_std_move
{
    template <class T>
    void myswapMove(T& a, T& b)
    {
        T tmp{ std::move(a) };    // invokes move constructor
        a = std::move(b);         // invokes move assignment
        b = std::move(tmp);       // invokes move assignment
    }

    void main()
    {
        std::string x{ "abc" };
        std::string y{ "de" };

        std::cout << "x: " << x << '\n';
        std::cout << "y: " << y << '\n';

        myswapMove(x, y);

        std::cout << "x: " << x << '\n';
        std::cout << "y: " << y << '\n';
    }
}

#include <iostream>
#include <string>
#include <utility>    // for std::move
#include <vector>

namespace another_example
{
    void main()
    {
        std::vector<std::string> v;

        // We use std::string because it is movable (std::string_view is not)
        std::string str{ "Knock" };

        std::cout << "Copying str\n";
        v.push_back(str);    // calls l-value version of push_back, which copies str into the array element

        std::cout << "str: " << str << '\n';
        std::cout << "vector: " << v[0] << '\n';

        std::cout << "\nMoving str\n";

        v.push_back(std::move(str));    // calls r-value version of push_back, which moves str into the array element

        std::cout << "str: " << str << '\n';    // The result of this is indeterminate
        std::cout << "vector:" << v[0] << ' ' << v[1] << '\n';
    }
}




/*------------------------------------------------------------------------------
       ============[ moved from objects will be in a valid, ]============
       ============[    but possibly indeterminate state    ]============
------------------------------------------------------------------------------*/

/*
  - when we move the value from a temporary object, it doesn't matter what the value
    the moved-from object is left with, because the temporaty object will be destroyed
    immediately anyway.
  - but what about l-value objects that we've used std::move() on?

  - the C++ standard says:
       "Unless otherwise specified, moved-from objects [of types defined in the
        C++ standard library] shall be placed in a valid but unspecified state.”
*/



//==============================================================================

int main()
{
    using_std_move::main();
    another_example::main();

    return 0;
}
