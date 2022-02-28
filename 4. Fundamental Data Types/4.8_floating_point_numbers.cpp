//                  min         typical
float f;            // 4 B      4         B
double d;           // 8 B      8         B
long double ld;     // 8 B      8, 12, 16 B

int x{5};
double y{5.0};   // no suffix means double
float z{5.0f};   // f suffix means float type

/* floating point precision
4 B          6 -  9 significant digits (typically  7)
8 B         15 - 18                               16
80-bits     18 - 21
16 B        33 - 36
*/

// The precision of a floating point number defines how many significant digits it can
// represent without information loss.

// We can override the default precision that std::cout shows by using an output manipulator
// function named std::setprecision(). Output manipulators alter how data is output, and
// are defined in the iomanip header.

#include <iostream>
#include <iomanip> // for output manipulator std::setprecision()

int main_0()
{
    std::cout << std::setprecision(16); // show 16 digits of precision
    std::cout << 3.33333333333333333333333333333333333333f <<'\n'; // f suffix means float
    std::cout << 3.33333333333333333333333333333333333333 << '\n'; // no suffix means double
    
    std::cout << std::setprecision(9);
    std::cout << 123456789.0f << '\n';

    double d1{0.1};
    std::cout << std::setprecision(6);  // use default precision of 6
    std::cout << d1 << '\n';
    std::cout << std::setprecision(17);
    std::cout << d1 << '\n';

    double d2{1.0};
    std::cout << d2 << '\n';
    double d3{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };     // should equal to 1.0
    std::cout << d3 << '\n';    

    return 0;
}

/* Best practice
    favor double over float unless space is at premium, as lack of precision in a float will
    often lead to inaccuracies
*/

//======[ NaN and Inf ]======
int main_1()
{
    double zero {0.0};
    double posinf { 5.0 / zero };   // positive infinity
    std::cout << posinf << '\n';
    double neginf { -5.0 / zero };  // negative infinity
    std::cout << neginf << '\n';
    double nan { zero / zero };     // not a number (mathematically invalid)
    std::cout << nan << '\n';

    return 0;
}

int main()
{
    main_1();
}