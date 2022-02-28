#include "square.h"
#include "geometry.h"
#include <iostream>

// if no header guards
    // won't compile, duplicate definition
    // geometry.h already include square.h

// if exist header guards
    // compile

// explanation is inside   square.h   file

int main()
{
    std::cout << "a square has " << getSquareSides() << " sides\n";
    std::cout << "a square of length 5 has perimeter length " << getSquarePerimeter(5) << '\n';
    return 0;
}