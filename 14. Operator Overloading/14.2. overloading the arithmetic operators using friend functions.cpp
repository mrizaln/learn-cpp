#include <iostream>


/*
  - some of the most commonly used operators in C++ are the arithmetic operators.

  - it turns out that there are three different ways to overload an operator:
    1. the member function way
    2. the friend function way
    3. the normal function way

  - in this lesson, we'll cover the friend function way.
*/


/*---------------------------------------------------------------------------------------
         ============[ overloading operators using friend functions ]============
---------------------------------------------------------------------------------------*/

namespace overloading_operators_using_friend_functions
{
    class Cents
    {
    private:
        int m_cents{};

    public:
        Cents(int cents) : m_cents{ cents } { }

        // add Cents ± Cents using a friend function
        friend Cents operator+(const Cents& c1, const Cents& c2);
        friend Cents operator-(const Cents& c1, const Cents& c2);

        int getCents() const { return m_cents; }
    };

    // note: these function is not a member function
    Cents operator+(const Cents& c1, const Cents& c2)
    {
        return Cents{ c1.m_cents + c2.m_cents };
    }

    Cents operator-(const Cents& c1, const Cents& c2)
    {
        return Cents{ c1.m_cents + c2.m_cents };
    }


    void main()
    {
        Cents cents1{ 6 };
        Cents cents2{ 8 };
        Cents centsSum{ cents1 - cents2 };
        std::cout << "I have " << centsSum.getCents() << " cents.\n";
    }
}




/*---------------------------------------------------------------------------------------
       ============[ friend function can be defined inside the class ]============
---------------------------------------------------------------------------------------*/

// even though friend functions are not members of the class, they can still be defined
// inside the class if desired.

namespace define_friend_function_inside_class
{
    class Cents
    {
    private:
        int m_cents{};

    public:
        Cents(int cents) : m_cents{ cents } { }

        // this function is not considered a member of the class, even though the definition
        // is inside the class.
        friend Cents operator+(const Cents& c1, const Cents& c2)
        {
            return Cents{ c1.m_cents + c2.m_cents };
        }

        int getCents() const { return m_cents; }
    };
}

// this way of programming is not recommended, as non-trivial function definitions are better
// kept in a separate .cpp file, outside of the class definition.




/*---------------------------------------------------------------------------------------
    ============[ overloading operators for operands of different types ]============
---------------------------------------------------------------------------------------*/

/*
  - when C++ evaluates the expression [x + y], x becomes the first parameter, and y becomes
    the second parameter.
  - when x and y have the same type, it doesn't matter if you add x + y or y + x.
  - however, when the operands have different types, x + y doesn't call the same function
    as y + x.
*/

namespace different_operands
{
    class Cents
    {
    private:
        int m_cents{};

    public:
        Cents(int cents) : m_cents{ cents } { }

        // overload declaration
        friend Cents operator+(const Cents& c, int value);
        friend Cents operator+(int value, const Cents& c);
    };

    // definition
    Cents operator+(const Cents& c, int value)
    {
        return { c.m_cents + value };
    }

    Cents operator+(int value, const Cents& c)
    {   
        // call operator+(Cents, int)
        return { c + value };
    }
}




//=======================================================================================

#include <numeric>      // for std::gcd

namespace quiz
{
    // [ description ]
    /*
        a) write a class named Fraction that has an integer numerator and denominator member.
           write a print() functin that prints out the fraction.
    
        b) add overloaded multiplication operators to handle multiplication between a Fraction
           and integer, and between two Fraction. use friend function method.

        c) reduce the Fraction using greatest common divisor: create a reduce() function
           (use std::gcd from the <numeric> header (C++17)).
    */

    // a)
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
            reduce();
        }

        void print() const { std::cout << m_numerator << '/' << m_denominator << '\n'; }

        // b)
        // overloaded multiplication function
        friend Fraction operator*(const Fraction& f1, const Fraction& f2)
        {
            return { f1.m_numerator*f2.m_numerator, f1.m_denominator*f2.m_denominator };
        }

        friend Fraction operator*(const Fraction& f, int value) { return { f.m_numerator*value, f.m_denominator }; }
        friend Fraction operator*(int value, const Fraction& f) { return { f*value }; }

    private:
        // c)
        void reduce()
        {
            int gcd{ std::gcd(m_numerator, m_denominator) };
            if (gcd)
            {
                m_numerator /= gcd;
                m_denominator /= gcd;
            }
        }
    };

    void main()
    {
        Fraction f1{2, 5};
        f1.print();

        Fraction f2{3, 8};
        f2.print();

        Fraction f3{ f1 * f2 };
        f3.print();

        Fraction f4{ f1 * 2 };
        f4.print();

        Fraction f5{ 2 * f2 };
        f5.print();

        Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
        f6.print();
    }
}



//=======================================================================================

int main()
{
    overloading_operators_using_friend_functions::main();

    quiz::main();

    return 0;
}