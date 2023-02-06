/*------------------------------------------------------------------------------
                ============[ r-value references ]============
------------------------------------------------------------------------------*/

/*
  - prior to C++11, only one type of reference existed in C++, and so it was just
    called a "reference".
  - however, in C++11, it's called an l-value reference.

  - C++11 adds new type of reference called an r-value reference.
  - an r-value reference is a reference that is designed to be initialized with
    an r-value (only)
  - an r-value reference is created using a double ampersand:
        int x{ 5 };
        int& lref{ x };
        int& &rref{ 5 };

  - r-value references have two propertis that are useful:
    1. r-value references extend the lifespan of the object they are initialized
       with to the lifespan of the r-value reference.
    2. non-const r-value references allow you to modify the r-value!
*/

#include <iostream>
#include <ostream>
#include <type_traits>

namespace example
{
    class Fraction
    {
    private:
        int m_numerator{};
        int m_denominator{ 1 };

    public:
        Fraction(int numerator = 0, int denominator = 1)
            : m_numerator{ numerator }
            , m_denominator{ denominator }
        {
        }

        friend std::ostream& operator<<(std::ostream& out, const Fraction& f)
        {
            out << f.m_numerator << '/' << f.m_denominator;
            return out;
        }
    };

    void main()
    {
        auto&& rref{ Fraction{ 3, 5 } };    // r-value referece to temporary Fraction
        std::cout << rref << '\n';

        int&& irrref{ 5 };
        irrref = 10;
        std::cout << irrref << '\n';
    }    // rref (and the temporary Fraction) goes out of scope here
}

// r-value references are not very often used in either of the maneers illustrated
// above




/*------------------------------------------------------------------------------
     ============[ r-value references as function parameters ]============
------------------------------------------------------------------------------*/

// r-value references are more often used as function parameters.
// this is most useful for function overloads when you want to have different
// behavior for l-value and r-value arguments.

namespace r_value_function_parameters
{
    void fun(const int &lref) // l-value arguments will select this function
    {
        std::cout << "l-value reference to const: " << lref << '\n';
    }

    void fun(int &&rref) // r-value arguments will select this function
    {
        std::cout << "r-value reference: " << rref << '\n';
    }

    void main()
    {
        int x{ 5 };
        fun(x); // l-value argument calls l-value version of function
        fun(5); // r-value argument calls r-value version of function

        int&& ref{ 5 };
        fun(ref);       /// calls l-value version of function* (???)
    }
}

// *) r-value reference variables are l-values, like all other variables.




// you should almost never return an r-value reference, for the same reason you
// should almost never return an l-value reference.




//==============================================================================

int main()
{
    example::main();
    r_value_function_parameters::main();

    return 0;
}
