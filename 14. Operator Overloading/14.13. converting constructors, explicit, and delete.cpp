#include <iostream>
#include <cassert>


// by default, C++ will treat any constructor as an implicit conversion operator.

namespace implicit_conversion
{
    class Fraction
    {
    private:
        int m_numerator{};
        int m_denominator{ 1 };

    public:
        // default constructor
        Fraction(int numerator=0, int denominator=1)
            : m_numerator{ numerator }
            , m_denominator{ denominator }
        {
            assert(denominator != 0 && "denominator cannot be zero");
        }

        // copy constructor
        Fraction(const Fraction& copy)
            : m_numerator{ copy.m_numerator }
            , m_denominator{ copy.m_denominator }
        {
            std::cout << "Copy constructor called\n";
        }

        friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
        int getNumerator() { return m_numerator; }
        int getDenominator() { return m_denominator; }
        void setNumerator(int numerator) { m_numerator = numerator; }
        void setDenominator(int denominator) { m_denominator = denominator; }
    };

    void printFraction(const Fraction& f)
    {
        std::cout << f;
    }

    std::ostream& operator<<(std::ostream& out, const Fraction& f)
    {
        out << f.m_numerator << '/' << f.m_denominator;
        return out;
    }


    void main()
    {
        printFraction(6);
        std::cout << '\n';
    }
}

/*
  - although function printFraction() is expecting a Fraction, we've given it the integer
    literal 6 instead.
  - because Fraction has a constructor willing to take a single integer, the compiler will
    implicitly convert the literal 6 into a Fraction object.

  - this implicit conversion works for all kinds of initialization (direct, uniform, and copy).

  - constructors eligible to be used for implicit conversions are called [converting constructors].
*/




/*---------------------------------------------------------------------------------------
                    ============[ the explicit keyword ]===========
---------------------------------------------------------------------------------------*/

// while doing implicit conversions makes sense in the Fraction case, in other cases, this
// may be undesirable, or lead to unexpected behaviors.

namespace explicit_keyword
{
    class MyString
    {
    private:
        std::string m_string;

    public:
        MyString() = default;

        explicit MyString(int x)         // alloacte string of size x
        {
            m_string.resize(x);
        }

        MyString(const char* string)    // allocate string to hold string value
        {
            m_string = string;
        }

        friend std::ostream& operator<<(std::ostream& out, const MyString& s);
    };

    std::ostream& operator<<(std::ostream& out, const MyString& s)
    {
        out << s.m_string;
        return out;
    }

    void printString(const MyString& s)
    {
        std::cout << s;
    }


    void main()
    {
        MyString mine;
        // mine = 'x';    // use MyString(int) if explicit keyword is removed
                                // otherwise compile error
        std::cout << mine << '\n';

        // printString('x');       // use MyString(int) if explicit keyword is removed
                                // oterwise compile error
        std::cout << '\n';
    }
}

/*
  - the commented section of code (if not commented) will not compile, since MyString(int)
    was maed explict, and an appropiate converting constructor could not be found to implicitly
    convert 'x' to a MyString.

  - however, note that making a constructor explicit only prevents implicit conversions.
  - explicit conversions are still allowed.
*/




/*---------------------------------------------------------------------------------------
                    ============[ the delete keyword ]============
---------------------------------------------------------------------------------------*/

/*
  - in our MyString case, we really want to completely disallow 'x' from being converted
    to a MyString (whether implicit or explicit).
  - we can do that using the "delete" keyword to delete the function
*/

namespace delete_keyword
{
    class MyString
    {
    private:
        std::string m_string;

    public:
        MyString(char) = delete; // any use of this constructor is an error

        // explicit keyword makes this constructor ineligible for implicit conversions
        explicit MyString(int x) // allocate string of size x /
        {
            m_string.resize(x);
        }

        MyString(const char* string) // allocate string to hold string value
        {
            m_string = string;
        }

        friend std::ostream& operator<<(std::ostream& out, const MyString& s);

    };

    std::ostream& operator<<(std::ostream& out, const MyString& s)
    {
        out << s.m_string;
        return out;
    }

    void main()
    {
        // MyString mine('x'); // compile error, since MyString(char) is deleted
        // std::cout << mine;
    }
}




//=======================================================================================

int main()
{
    implicit_conversion::main();
    explicit_keyword::main();

    return 0;
}