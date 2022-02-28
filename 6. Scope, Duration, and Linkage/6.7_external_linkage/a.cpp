#include <iostream>

// global variables
int g_x { 2 };                  // non-constant globals are external by default
const int g_xx { 22 };          // internal linkage
extern const int g_y { 3 };     // const globals can be defined as extern, making them external
extern constexpr int g_z { 4 }; // constexpr globals can be defined as extern as well, (but this is useless, see note)

/* note
    although constexpr variables can be gicin external linkage via the extern keyword,
    they can not be forward declared, so there is no value in giving them external linkage    
*/


void sayHi()    // this function has external linkage 
{
    std::cout << "Hi!\n";
}