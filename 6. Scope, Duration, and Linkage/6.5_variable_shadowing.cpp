/*
    each block defines its own scope region.
    what happens when we have a variable inside a nested block that has the same name as
    a variable in an outer block?
    when this happens, the nested variable "hides" the outer variable in areas where they
    are both in scop.
    this called   name hiding   or   shadowing.
*/



//========[ shadowing of local variables ]========

#include <iostream>

int local_shadowing()
{ // outer block
    int apples { 5 };   // outer block apples

    { // nested block

        // apples refers to outer block apples here
        std::cout << apples << '\n';    // print value of outer block apples

        int apples { 0 };               // define apples in the scope of the nested block

        // apples now refers to the nested block apples
        // the outer block apples is temporarily hidden

        apples = 10;                    // this assigns value 10 to nested block apples, not outer block apples
        std::cout << apples << '\n';    // print value of nested block apples

    } // nested block apples destroyed

    std::cout << apples << '\n';    // prints value of outer block apples

    return 0;
} // outer block apples destroyed



//========[ shadowing of global variables ]========

int value { 5 };    // global variable

void foo()
{
    std::cout << "global variable value: " << value << '\n';    // value is not shadowed here
}

int global_shadowing()
{
    int value { 7 };    // hides the global variable value until the end of this block
    ++value;            // increments local value, not global value
    --(::value);        // decrement global value
    std::cout << "local variable value: " << value << '\n';
    foo();

    return 0;
}


/* best practice
    avoid variable shadowing
*/

//=======================================================================================

int main()
{
    local_shadowing();
    global_shadowing();
}
