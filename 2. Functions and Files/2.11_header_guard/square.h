#ifndef SQUARE_H        // these 2 lines are header guards
#define SQUARE_H

int getSquareSides();
int getSquarePerimeter(int sideLength);

#endif                  // down here also

// Header guards are conditional compilation directives that take the following form:
/*
    #ifndef SOME_UNIQUE_NAME_HERE
    #define SOME_UNIQUE_NAME_HERE

    // yout declaratinons here

    #endif
*/

/*
    in large programs, it's possible to have two separate header files that have the same
    filename (eg: dirA/config.h and dirB/config.h). if only the filename is used for the
    include guard, these twho files may end up using the same guard name. if that happens,
    only one of both files can will be included (#included first).
    because of this possibility, many devs recommend using a more complex name.
    like:
        <ROJECT>_<PATH>_<FILE>_H
        <FILE>_<LARGE RANDOM NUMBER>_H
        <FILE>_<CREATION>_<DATE>_H
*/

/*
    many compilers support a simpler, alternate form of header guards using
        # pragma once

        // your code here
    however, #pragma once is not an official part of the C++ language
    not all compilers support it (most modern compilers do though)
*/