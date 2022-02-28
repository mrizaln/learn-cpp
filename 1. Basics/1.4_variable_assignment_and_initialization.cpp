#include <iostream>

int main()
{
    int a;          // no initializer
    int b = 5;      // initializer after assignment     copy initialization
    int c(2);       // initializer in paranthesis       direct initialization
    int d {7};      // initializer in braces            brace initialization

    // Brace initialization has the added benefit of disallowing “narrowing” conversions.
    // This means that if you try to use brace initialization to initialize a variable with
    // a value it can not safely hold, the compiler will throw a warning or an error.
    // For example:
        // int width { 4.5 };  // error: not all double values fit into an int

    // Favor initialization using braces whenever possible.

    //======[ value initialization and zero initialization ]======
    int width {};           // zero intialization to value 0    use this if the value is temporary
    int height { 0 };       // use an explicit initialization value if you're actually using that value

    //======[ initializing multiple variables ]======
    int e = 5, f = 6;
    int g( 7 ), h( 8 );
    int i{ 9 }, j{ 10 };    // preferred
}
