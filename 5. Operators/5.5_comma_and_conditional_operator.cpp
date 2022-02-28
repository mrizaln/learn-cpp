//======[ comma operator (,) ]======
// this operator allows you to evaluate multiple expressions wherever a single expression
// is allowed. this operator evaluates the left operand, then the right operand, and then
// returns the result of the right operand.

#include <iostream>
int main_comma()
{
    int x{ 1 };
    int y{ 2 };
    std::cout << (++x, ++y);    //increment x and y, evaluates to the right operand
    return 0;
}
// note that comma has the lowest presedence of all the operators, even lower than assignment

/* best practice
    avoid using the comma operator, except within for loops
*/


//======[ conditional operator (?:) ]======
// syntax       c ? x : y       if c is nonzero (true) then evaluate x, otherwise evaluate y
int main_conditional()
{
    int x{ 10 };
    int y{ 45 };
    int larger = ((x > y) ? x : y);
    (x > y) ? std::cout << x : std::cout <<y;
    return 0;
}
/* best practice
    always paranthesize the conditional part of the conditional operator, and consider
    paranthesizing the whole thing as well
*/

// the conditional operator evaluates as an expression
int main_conditional_expression()
{
    constexpr bool inBigClassroom{ false };
    constexpr int classSize{ inBigClassroom ? 30 : 20 };
    std::cout << "The class size is: " << classSize << '\n';

    constexpr int x{ 5 };
    // std::cout << (x != 5 ? x : "x is 5");   // this won't compile
    // because the type of the expressions must match (or convertible)
    return 0;
}

/* best practice
    only use the conditional operator for simple conditionals where you use the result
    and where it enhances readability
*/


int main()
{
    main_comma();
    main_conditional();

    return 0;
}