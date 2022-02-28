#include <iostream>

int five()
{
    return 5;
}

int main()
{
    int a{ 2 };
    int b{ 2 + 3 };
    int c{ (2 * 3) + 4 };
    int d{ b };
    int e{ five() };
    return 0;
}

// an expression is a combination of literals, variables, operators, and function
// calls that can be executed to produce a singular value

// expression statement is a statement that consist of an expression followed by
// a semicolon