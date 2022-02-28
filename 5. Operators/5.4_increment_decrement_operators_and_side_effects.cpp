//============[ incrementing and decrementing variables ]============

/*    operator        symbol   form         operation
    pre-increment       ++      ++x     increment x, then return x
    pre-decrement       --      --x     decrement x, then return x
    post-increment      ++      x++     copy x, then increment x, then return the copy
    post-decrement      --      x--     copy x, then decrement x, then return the copy
*/

//--------[ prefix increment/decrement ]-------
#include <iostream>

int main_prefix()
{
    int x { 5 };
    int y = ++x;    // x is incremented to 6, x is evaluated to the value 6, and 6 is assigned to y
    std::cout << x << ' ' << y << '\n';
    return 0;
}

//-------[ postfix increment/decrement ]-------

int main_postfix()
{
    int x { 5 };
    int y = x++;    // x is incremented to 6, copy of original x is evaluated to the value 5, and 5 is assigned to y
    std::cout << x << ' ' << y << '\n';
    return 0;
}

//-------[ prefix vs postfix increment/decrement in action ]-------

int main_difference()
{
    int x{ 5 };
    int y{ 5 };
    std::cout << x << ' ' << y << '\n';
    std::cout << ++x << ' ' << --y << '\n'; // prefix
    std::cout << x << ' ' << y << '\n';
    std::cout << x++ << ' ' << y-- << '\n'; // postfix
    std::cout << x << ' ' << y << '\n';

    return 0;
}

/* best practice
    strongly favor the prefix version of the increment and decrement operators as they are
    generally more performant, and you're less likely run into strange issue with them
*/



//============[ side effects ]============

// a function or expression is said to have a side effect if it does anything that persists
// beyond the life of the function or expression itself

// most of the time the side effects are useful:
void useful_side_effects()
{
    int x{};
    x = 5;              // the assignment operator modifes the state of x
    ++x;                // operator++ modifies the state of x
    std::cout << x;     // operator<< modifies the state of the console
}

// however side effects can alsso lead to unexpected results:
int add(int x, int y)
{
    return x + y;
}

int main_unexpected_side_effect()
{
    int x { 5 };
    int value { add(x, ++x) };  // is thsi 5 + 6, or 6 + 6?
                                // it depends on what order your compiler evaluates the function arguments in

    std::cout << value << '\n'; // value could be 11 or 12, depending on how the above line eavaluates!
    return 0;
}


/* as an aside...
    the C++ standard intentionally does not define these things so that compilers can do
    whatever is most natural (and thus most performant) for a given architecture
*/


//=======================================================================================

int main()
{
    main_prefix();
    main_postfix();
    main_difference();
    main_unexpected_side_effect();
}