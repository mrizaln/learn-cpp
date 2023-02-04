// [ description ]
/*------------------------------------------------------------------------------
    write a Fraction class that has a constructor that takes a numerator and a
    denominator.

    if the user passes in a denominator of 0, throw an exception of type
    std::runtime_error.

    in your main program, ask the user to enter two integers.

    if the Fraction is valid, print the fraction.

    if the fraction is invalid, catch a std::exception, and tell the user that

    they entered an invalid fraction
------------------------------------------------------------------------------*/

#include <ostream>
#include <stdexcept>
#include <iostream>

class Fraction
{
private:
    int m_numerator{};
    int m_denominator{ 1 };

public:
    Fraction(int numerator, int denominator)
        : m_numerator{ numerator }
        , m_denominator{ denominator }
    {
        if (denominator == 0) {
            throw std::runtime_error{ "The denominator of a fraction can't be zero" };
        }
    }

    Fraction(int numerator)
        : Fraction{ numerator, 1 }
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& frac)
    {
        out << frac.m_numerator << '/' << frac.m_denominator;
        return out;
    }
};

int main()
{
    std::cout << "Welcome to Fraction creator\n";

    int numerator{};
    std::cout << "Input a numerator : ";
    std::cin >> numerator;

    int denominator{};
    std::cout << "Input a denomiator: ";
    std::cin >> denominator;

    try {
        Fraction fraction{ numerator, denominator };
        std::cout << fraction << '\n';
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
