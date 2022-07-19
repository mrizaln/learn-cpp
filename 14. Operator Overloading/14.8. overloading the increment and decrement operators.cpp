#include <iostream>


/*
  - overloading the incrment (++) and decrement (--) operators is pretty straightforward,
    with one small exception.
  - there are actually two versions of the increment and decrement operators: a prefix and
    a postfix operator of increment and decrement;

  - because the increment and decrement operators are both unary operators and they modify
    their operands, they're best overloaded as member functions.
*/


/*---------------------------------------------------------------------------------------
         ============[ overloading prefix increment and decrement ]============
---------------------------------------------------------------------------------------*/

// prefix increment and decrement are overloaded exactly the same as any normal unary operator.

namespace overloading_prefix_increment_and_decrement
{
    class Digit
    {
    private:
        int m_digit{};

    public:
        Digit(int digit) : m_digit{ digit } { }

        Digit& operator++();
        Digit& operator--();

        friend std::ostream& operator<<(std::ostream& out, const Digit& d);
    };

    Digit& Digit::operator++()
    {
        if (m_digit == 9)
            m_digit = 0;
        else
            ++m_digit;

        return *this;
    }

    Digit& Digit::operator--()
    {
        if (m_digit == 0)
            m_digit = 9;
        else
            --m_digit;

        return *this;
    }

    std::ostream& operator<<(std::ostream& out, const Digit& d)
    {
        out << d.m_digit;
        return out;
    }

    
    void main()
    {
        Digit digit(8);

        std::cout << digit;
        std::cout << ++digit;
        std::cout << ++digit;
        std::cout << --digit;
        std::cout << --digit;
    }
}




/*---------------------------------------------------------------------------------------
         ============[ overloading postfix increment and decrement ]============
---------------------------------------------------------------------------------------*/

/*
  - normally, functions can be overloaded when they have the same name but a different number
    and/or different type of parameters.
  - however, consider the case of the prefix and postfix increment and decrement operators.
  - both have the same name, are unary, and take one parameter of the same type.
  - so how it is possible to differentiate the two when overloading?

  - the C++ language spcs. has a special case that provides the answer: the compiler looks
    to see if the overloaded operator ahs an int parameter.
  - if the overloaded operator has an int parameter, the operator is a postfix overload.
  - if the overloaded operator has no parameter, the operator is a prefix overload.
*/

namespace overloading_postfix_increment_and_decrement
{
    class Digit
    {
    private:
        int m_digit{};

    public:
        Digit(int digit) : m_digit{ digit } { }

        Digit& operator++();    // prefix increment has no parameter
        Digit& operator--();    // prefix decrement has nor parameter

        Digit operator++(int);  // postfix increment has an int parameter
        Digit operator--(int);  // postfix decrement has an int parameter

        friend std::ostream& operator<<(std::ostream& out, const Digit& d);
    };

    // prefix increment has no parameter
    Digit& Digit::operator++()
    {
        if (m_digit == 9)
            m_digit = 0;
        else
            ++m_digit;

        return *this;
    }

    // prefix decrement has no parameter
    Digit& Digit::operator--()
    {
        if (m_digit == 0)
            m_digit = 9;
        else
            --m_digit;

        return *this;
    }

    // postfix increment has an int parameter
    Digit Digit::operator++(int)
    {
        Digit temp{ *this };    // save state
        ++(*this);              // apply operator

        return temp;            // return saved state
    }

    //postfix decrement has an int parameter
    Digit Digit::operator--(int)
    {
        Digit temp{ *this };    // save state
        --(*this);              // apply operator

        return temp;            // return saved state
    }

    std::ostream& operator<<(std::ostream& out, const Digit& d)
    {
        out << d.m_digit;
        return out;
    }

    
    void main()
    {
        Digit digit(5);

        std::cout << digit;
        std::cout << ++digit;   // calls Digit::operator++();
        std::cout << digit++;   // calls Digit::operator++(int);
        std::cout << digit;
        std::cout << --digit;   // calls Digit::operator--();
        std::cout << digit--;   // calls Digit::operator--(int);
        std::cout << digit;
    }
}

/*
  - first, note that we've distinguished the prefix from the postfix operators by providing
    an integer dummy parameter on the postfix version.
  - second, because the dummy parameter is not used in the function implementation, we have
    not even given it a name.
  - third, note that the prefix and postfix operators do the same job -- they both increment
    or decrement the object, the difference between the two is in the value they return.
  - finally, note that we've written the post-increment and post-decrement in such a way that
    it calls the pre-increment and pre-decrement to do most of the work.
*/




//=======================================================================================

int main()
{
    overloading_prefix_increment_and_decrement::main();

    std::cout << '\n';

    overloading_postfix_increment_and_decrement::main();

    return 0;
}