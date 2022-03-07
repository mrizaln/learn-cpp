//============[ global constants as internal variables ]============

// prior to C++17, the following is the easiest and most common solution
    // 1. create a header file to hold these constants
    // 2. inside this header file, define a namespace
    // 3. add all your constants inside the namespace (make sure they're constexpr)
    // 4. #include the header file wherever you need it

    // For example: read constants.h

#include "constants_0.h"

#include <iostream>

int main_0()
{
    std::cout << "Enter a radius: ";
    int radius {};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2.0 * radius * constants_0::pi << '\n';

    return 0;
}



//============[ global constants as external variables ]============

// above method has a few potential downsides.
// every time constants.h gets #included into a different code file, each of these 
// variables is copied into the including code file.

// this introduces two challenges:
    // 1. changing a single constant value would require recompiling every file that
    //    includes the constants header
    // 2. if the constants are large in size and can't be optimized away, this can use
    //    a lot of memory

// one way to avoid these problems i by turning these constants into external variables,
// since we can then have a single variable (initialized once) that is share across all
// files. in this method we'll define the constants in a .cpp file, and put forward declarations
// in the header

#include "constants_1.h"    // include all the forward declarations

int main_1()
{
    std::cout << "Enter a radius: ";
    int radius {};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2.0 * radius * constants_1::pi << '\n';

    return 0;
}

// there are a couple of downsides to this method
    // 1. these constants are now considered compile-time constants only within the fule
    //    they are actually defined in (constants_1.cpp). in other files, the compiler will
    //    only see the forward declaration, which doesn't define a constant values, not
    //    compile-time constants. thus outside of  constants_1.cpp  , these variables can't
    //    be used anywhere that requires a compile-time constants

    // 2. because compile-time constants can typically be optimized more than runtime
    //    constants, the compiler may not be able to optimize these as much

// given above downsides, prefer defining your constants in the header file.
// if you find that for some reason those constants are causing trouble, you can move some
// or all of them into a .cpp file as needed




//============[ global constants as inline variable (C++17) ]============

// C++17 introduces a new concept called   inline variable.
// in C++, the term  inline  has evolved to mean "multiple definitions are allowed".
// thus, an   inline variable   is one that is allowd to be defined in multiple files without
// violating the one definition rule.
// inline global variables have external linkage by default.

// inline variables have two primary restrictions that must be obeyed
    // 1. all definitions of the inline variable must be identical (otherwise, undefined)
    //    behaviour will result)
    // 2. the inline variable definition (not a forward declaration) must be present in
    //    any file that uses the variable

// with this we can go back to defining our globals in a header file wothout the downside
// of duplicated variables

#include "constants_2.h"

int main_2()
{
    std::cout << "Enter a radius: ";
    int radius {};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2.0 * radius * constants_2::pi << '\n';

    return 0;
}

/* best practice
    if you need global constants and your compiler is C++17 capable, prefer defining inline
    constexpr global variables in a header file.
*/

//=======================================================================================

int main()
{
    main_0();
    main_1();
    main_2();
}