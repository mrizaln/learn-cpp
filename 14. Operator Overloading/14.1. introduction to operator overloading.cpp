#include <iostream>


/*
  - in previous chapter, we have discusse about function overloading, which provides a
    mechanism to create and resolve function calls to multiple functions with the same
    name.
  - in C++, operators are implemented as functions.
  - by using function overloading on the operator functions, you can define your own versions
    of the operators that work with different data types.
  - using function overloading to overload operators is called [operator overloading].
*/


/*---------------------------------------------------------------------------------------
                  ============[ operators as functions ]============
---------------------------------------------------------------------------------------*/

namespace operators_as_functions
{
    void main()
    {
        int x{ 2 };
        int y{ 3 };
        std::cout << x + y << '\n';

        double z{ 2.0 };
        double w{ 3.0 };
        std::cout << z + w << '\n';
    }
}

/*
  - when you see the expression [x + y] above, you can translate this in your head to the
    function call [operator+(x, y)] where operator+ is the name of the function.

        x + y    ------>    operator+(x, y)
        z + w    ------>    operator+(z, w)
*/




/*---------------------------------------------------------------------------------------
               ============[ resolving overloaded operators ]============
---------------------------------------------------------------------------------------*/

/*
    when evaluating an expression containing an operator, the compiler uses the following
    rules:
      - if all of the operands are fundamental data types, the compiler will call a built-in
        routine if one exists. if one does not exist, the compiler will produce a compile
        error.
      - if any of the operands are user data types, the compiler looks to see whether the
        type has a matching overloaded operator function that it can call. if it can't find
        one, it will try to convert one or more of the user-defined type operands into fundamental
        data types so it can use a matching built-in operator (via an overloaded typecast).
        if that fails, then it will produce a compile error.
*/




/*---------------------------------------------------------------------------------------
        ============[ operator overloading limitations ]============
---------------------------------------------------------------------------------------*/

/*
  - almost any existing operator in C++ can be overloaded, except: conditional (?:), sizeof,
    scope(::), member selector (.), member pointer selector (.*), typeid, and the casting
    operators.
  - you can only overload the operators that exist.
  - at least one of the operands in an ovrloaded operator must be a user-defined type.
  - it is not possible to change the number of operands oan operator supports.
  - all operators keep their default precedence and associativity and this can't be changed.
*/


// [ best practice]
/*---------------------------------------------------------------------------------------
    when overloading operators, it's best to keep the function of the operators as close
    to the original intent of the operators as possible
-----------------------------------------------------------------------------------------
    if the meaning of an overloaded operator is not clear and intuituve, use a named
    function instead.
---------------------------------------------------------------------------------------*/
