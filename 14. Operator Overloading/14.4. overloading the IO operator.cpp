#include <iostream>


/*---------------------------------------------------------------------------------------
                  ============[ overloading operator<< ]============
---------------------------------------------------------------------------------------*/

/*
  - overloading operator<< is similar to overloading operator+, except that the parameter
    types are different.

  - consider the expression [std::cout << point].   (point is an instance of Point class)
  - if the operator is [<<], what are the operands?
  - the left operand is the std::cout object, and the right operand is a Point class object.
  - std::cout is actually an object of type std::ostream.
  - therefore, our overloaded function will look like this:

        friend std::ostream& operator<< (std::ostream& out, const Point& point);
*/

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0.0, double y=0.0, double z=0.0)
        : m_x{ x }, m_y{ y }, m_z{ z }
    {
    }

    // prototype
    friend std::ostream& operator<<(std::ostream& out, const Point& point);
    friend std::istream& operator>>(std::istream& in, Point& point);
};

// insertion operator overload definition
std::ostream& operator<<(std::ostream& out, const Point& point)
{
    // operator<< is a friend of Point now, we can access Point members directly
    out << "Point(" << point.m_x
        << ", " << point.m_y
        << ", " << point.m_z
        << ')';

    return out;     // return std::ostream so we can chain calls to operator<<
}


void main_insertion()
{
    const Point point1{ 2.7, 3.8, 4.9 };
    const Point point2{ 5.0, 6.1, 7.2 };
    std::cout << point1 << ' ' << point2 << '\n';
}




/*---------------------------------------------------------------------------------------
                  ============[ overloading operator>> ]============
---------------------------------------------------------------------------------------*/

/*
  - it is also possible to overload the extraction operator.
  - this is done in a manner analogous to overloading the output operator.
  - the key thing you need to know is that [std::cin] is an object of type [std::istream].
*/

// extraction operator overload definition
std::istream& operator>>(std::istream& in, Point& point)
{
    in >> point.m_x;
    in >> point.m_y;
    in >> point.m_z;
    
    return in;
}


void main_extraction()
{
    std::cout << "Enter a point: ";
    Point point;
    std::cin >> point;

    std::cout << "You entered: " << point << '\n';
}




//=======================================================================================

#include <numeric> // for std::gcd
#include <limits>

namespace quiz
{
    // [ description ]
    /*
        take the Fraction class we wrote in the previous quiz and add an overloaded
        operator << and operator>>
    */

    class Fraction
    {
    private:
        int m_numerator{};
        int m_denominator{};

    public:
        Fraction(int numerator=0, int denominator=1):
            m_numerator{numerator}, m_denominator{denominator}
        {
            // We put reduce() in the constructor to ensure any new fractions we make get reduced!
            // Any fractions that are overwritten will need to be re-reduced
            reduce();
        }

        void reduce()
        {
            int gcd{ std::gcd(m_numerator, m_denominator) };
            if (gcd)
            {
                m_numerator /= gcd;
                m_denominator /= gcd;
            }
        }

        friend Fraction operator*(const Fraction& f1, const Fraction& f2);
        friend Fraction operator*(const Fraction& f1, int value);
        friend Fraction operator*(int value, const Fraction& f1);
        friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction);
        friend std::istream& operator>>(std::istream& in, Fraction& fraction);

        void print() const
        {
            std::cout << m_numerator << '/' << m_denominator << '\n';
        }
    };

    Fraction operator*(const Fraction& f1, const Fraction& f2)
    {
        return Fraction(f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator);
    }

    Fraction operator*(const Fraction& f1, int value)
    {
        return Fraction(f1.m_numerator * value, f1.m_denominator);
    }

    Fraction operator*(int value, const Fraction& f1)
    {
        return Fraction(f1.m_numerator * value, f1.m_denominator);
    }

    std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
    {
        out << fraction.m_numerator << '/' << fraction.m_denominator;
        return out;
    }

    std::istream& operator>>(std::istream& in, Fraction& fraction)
    {
        in >> fraction.m_numerator;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '/');    // ignore '/'
        in >> fraction.m_denominator;
        fraction.reduce();
        return in;
    }


    void main()
    {
        Fraction f1;
        std::cout << "Enter fraction 1: ";
        std::cin >> f1;

        Fraction f2;
        std::cout << "Enter fraction 2: ";
        std::cin >> f2;

        std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n'; // note: The result of f1 * f2 is an r-value
    }
}



//=======================================================================================

int main()
{
    main_insertion();
    main_extraction();

    quiz::main();

    return 0;
}