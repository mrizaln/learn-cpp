/*
    an identifier with external linkage can be seen and used both from the file in which
    it is defined, and from other code files (via forward declaration).
    in this sense, identifiers with external linkage are truly "global" in that they can
    be used anywhere in your program
*/

//========[ functions have external linkage by default ]========
// in order to call a function defined in another file, you mus place a  forward declaration
// for the function in any other files wishing to use the function.
// the forward declarationtells the compiler about the existence of the function, and the
// linker connects the function calls to the actual function definition.

#include <iostream>
// #include "a.cpp"

void sayHi();   // the definition is in a.cpp

void function_external()
{
    sayHi();
}



//========[ global variables with external linkage ]========
// global variables with external linkage are sometimes called   external variables   
// to make a global variables external, we can use   extern   keyword to do so.

//========[ variable forward declarations via the extern keyword ]========

// these globals are initialized in a.cpp file
extern int g_x;         // forward declaration
extern const int g_y;   // forward declaration

void external_globals()
{
    std::cout << g_x << '\n';
    std::cout << g_y << '\n';
}



//========[ file scope vs global scope ]========
// file scope is global scope
// a variable that has a global scope is accessible throughout the file (aka file scope)

int main()
{
    function_external();
    external_globals();
}