#include <iostream>

// 1. it's fine to use either tabs or spaces for indentation, cause C++ is not indentation dependent

// 2. there are twho acceptable styles for function braes
    // google C++ style guid recommends the { on same line as fucntion
    void someFunction(){
    }

    // alternative
    void someFunctionToo()
    {
    }

// 3, each statement within curly braces sould start one tab from the opening brace of the function it belongs to
void thisIsAFuncion(){
    std::cout << "heeyyyyy";
    std::cout << "ayo bro";
}
void thisIsAFunctionToo()
{
    std::cout << "helllooooo";
    std::cout << "yyoooooooo";
}

// 4. lines should not be too long. typically 80 chars

// 5. if line is split with an operator (eg << or +) the operator sould be palced at the beginning of the next line
void tatambahan(int n1, int n2, int n3)
{
    std::cout << n1 + n2
        - 2 + n3 * 100;
}

// 6. use whitespaces to make your code easier to read by aligning values or comments or adding spacing between block of cade
float n = 213.12;
int couseWork = 10;
unsigned int k = 123;
char o = 'p';

float nn        = 213.12;
int couseWorkk  = 10;
unsigned int kk = 123;
char oo         = 'p';


