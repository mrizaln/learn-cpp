//========[ comparison of floating point values can be problematic ]========
#include <iostream>
int main_comparison()
{
    double d1{ 100.0 - 99.99 }; // should equal to 0.01
    double d2{ 10.0  - 9.99 };  // should equal to 0.01

    if (d1 == d2)
        std::cout << "d1 == d2" << '\n';
    else if (d1 > d2)
        std::cout << "d1 > d2" << '\n';
    else if (d1 < d2)
        std::cout << "d1 < d2" << '\n';
    
    return 0;
}
// the output will be:  d1 > d2

/* best practice
    avoid using operator== and operator!= with floating point operands
*/

//========[ comparing floating point numbers (advanced) ]========
// the most common method of doing floating point equality involves using a function that
// looks to see if two numbers are almost the same. if they are "colse enough", then we
// we call them equal.
// the value used to represent "colse enough" is traditionally called epsilon
// epsilon generally defined as a small positive number (e.g. 0.00000001, 1e-8)

//------[ new developers often try to write their own "clse enough" function:
#include <cmath>
bool isAlmostEqual(double a, double b, double epsilon)
{
    return std::abs(a - b) <= epsilon;
}
// while this is work, it's not great

//------[ Donald Knuth suggested the following method in his book:
#include <algorithm>
bool approximatelyEqual(double a, double b, double epsilon)
{
    return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b) * epsilon)));
}
// in this case, instead of epsilon being an absolute number, epsilon is now relative to
// the magitude of a or b.

// the function above will work for most cases, it is not perfect, especially as the number
// approaches zero
// one way to avoid this is to use both an absolute epsilon and relative epsilon
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
    // check if the numbers are really close -- needed when comparing numbers near zero
    double diff{ std::abs(a - b) };
    if (diff <= absEpsilon)
        return true;
    // otherwhise fall back to Knuth's algorithm
    return (diff <= (std::max(std::abs(a), std::abs(b) * relEpsilon)));
}


//=========================
int main()
{
    double a{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };
    std::cout << approximatelyEqual(a, 1.0, 1e-8) << '\n';                  // almost 1.0 to 1.0
    std::cout << approximatelyEqual(a-1.0, 0.0, 1e-8) << '\n';              // almost 0.0 to 0.0    close to zero (probably works, not great)
    std::cout << approximatelyEqualAbsRel(a-1.0, 0.0, 1e-12, 1e-8) << '\n'; // almost 0.0 to 0.0
}