//========[ declaring and naming global variables ]========
// by convention, global variables are declared at the top of a file, below the includes,
// but above any code

//========[ global variables have file scope and static duration ]========
// global variables have file scope (also global scope / global namespace scope)
// which means they are visible from the point of declaration until the end of the file
// in which they are declared

#include <iostream>

// global variable
int g_x {};
const int g_y { 1 };
constexpr int g_z { 2 };

void printSomething()
{
    std::cout << "this is the value of the global variable g_x: " << g_x << '\n';
}

int main()
{
    printSomething();
}

/* best practice
    consider using   "g"   or   "g_"   prefix for global variables to help differentiate
    them from local variables
*/
