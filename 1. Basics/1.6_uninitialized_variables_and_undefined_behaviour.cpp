#include <iostream>

int main()
{
    // uninitialized variable
    int x;
    std::cout << x << '\n';
}

// Undefined behavior

// Using the value from an uninitialized variable is our first example of undefined behavior.
// Undefined behavior (often abbreviated UB) is the result of executing code whose behavior
// is not well defined by the C++ language

// Code implementing undefined behavior may exhibit any of the following symptoms:
    // Your program produces different results every time it is run.
    // Your program consistently produces the same incorrect result.
    // Your program behaves inconsistently (sometimes produces the correct result, sometimes not).
    // Your program seems like its working but produces incorrect results later in the program.
    // Your program crashes, either immediately or later.
    // Your program works on some compilers but not others.
    // Your program works until you change some other seemingly unrelated code.