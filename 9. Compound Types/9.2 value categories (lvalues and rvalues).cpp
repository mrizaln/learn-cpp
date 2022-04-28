// #define ALLOW_ERROR_VALUE

#include <iostream>

//---------------------------------------------------------------------------------------

/*
  - besides producing values and side effects, expressions can do one more thing: they can
    evaluate to objects or functions.
  - to help determine how expressions should evaluate and where they can be used, all expressions
    in C++ have two properties: a type and a value category.
*/




/*---------------------------------------------------------------------------------------
               ============[ the type of an expression ]============
---------------------------------------------------------------------------------------*/

/*
  - the type of an expression is equivalent to the type of the value, object, or function that
    results from the evaluated expression
  - the compiler can use the type of an expression to determine whether an expression is valid
    in a given context
*/

namespace type_of_expression
{
    auto v1 { 12 / 4 };         // int / int => int
    auto v2 { 12.0 / 4 };       // double / int => double
}

/*
  - note that the type of an expression must be determinable at compile time, otherwise type
    type checking and type deduction wouldn't work.
  - however, the value of an expression may be determined at either compile time or runtime
*/




/*---------------------------------------------------------------------------------------
            ============[ the value category of an expression ]============
---------------------------------------------------------------------------------------*/

// consider following program 

namespace value_category_of_expression
{
    int main()
    {
        int x{};

        x = 5;
    #ifdef ALLOW_ERROR_VALUE
        5  = x;     // error: cannot assign value of x to literal value 5
    #endif
        return 0;
    }
}

/*
  - one of these assignment statements is valid (assigning 5 to variable x)
  - one is not (what would it mean to assign the value of x to the literal value 5?)
  - so, how does the compiler know which expressions can legally appear on either side of
    an assignment statement?

  - the answer lies in the second property of expressions: the [value category]
  - the value category of an expression indicates whether an expression resolves to a value,
    a function, or an objext of some kind.

  - prior to C++11, there were only two possible value categories: [lvalue] and [rvalue].
  - in C++11, three additional value categories added: [glvalue], [prvalue], and [xvalue]
    these are added to support a new feature called [move semantics]
*/




/*---------------------------------------------------------------------------------------
            ============[ lvalue and rvalue expressions ]============
---------------------------------------------------------------------------------------*/

/*
  - an [lvalue] is an expression that evaluates to a function or object that has an identity.
  - an object or function has an identity if it has an identifier or an identifieable memory
    address (one that can be retrieved using operator&).
  - identifieable objects persist beyond the scope of the expression
*/

namespace lvalue_expression
{
    int main()
    {
        int x{};

        std::cout << x << '\n';     // x is an lvalue expression

        return 0;
    }
}

/*
  - lvalues come in two subtypes: a [modifiable lvalue] is an lvalue whose value can be modifed.
    and [non-modifiable lvalue] is an lvalue whose value cant'be modified (because const or
    constexpr)
*/

/*
  - an [rvalue] is an expression that is not an l-value.
  - commonly seen rvalues include literals (except string literals, which are lvalues) and
    the return type of functions or operators.
  - rvalues only exist within the scope of the expression in which they are used
*/

namespace rvalue_expression
{
    int return5()
    {
        return 5;
    }

    int main()
    {
        int x { 5 };                // 5 is an rvalue expression
        const double d { 1.2 };     // 1.2 is an rvalue expression

        std::cout << x << '\n';                     // x is a modifieable lvalue expression
        std::cout << d << '\n';                     // d is a non-modifiable lvalue expression
        std::cout << return5();                     // return 5() is an rvalue expression
        std::cout << x + 1 << '\n';                 // x + 1 is an rvalue
        std::cout << static_cast<int>(d) << '\n';   // the result of static casting d to an int is an rvalue

        return 0;
    }
}

// you may be wondering why [return5()] and [x + 1] are rvalues: the answer is because these
// expressions produce values that must be used immediately (within the scope of the expression)
// or they are discarded.




/*---------------------------------------------------------------------------------------
               ============[ l-value to r-value conversion ]============
---------------------------------------------------------------------------------------*/

// assignment operator expect the right operand to be an rvalue expression, and the left
// operand to be an lvalue, that's why an expression of [5 = x] won't work.

// but why does this code work?
namespace assignment
{
    int main()
    {
        int x { 1 };
        int y { 2 };

        x = y;      // y is modifiable lvalue, not rvalue, but this is legal.

        return 0;
    }
}

// the answer is because lvalues will implicity convert to rvalues, so an lvalue can be used
// wherever an rvalue is required.