#include <iostream>

/*---------------------------------------------------------------------------------------
                    ============[ the copy constructor ]============
---------------------------------------------------------------------------------------*/

/*
  - a [copy constructor] is a special type of constructor used to create a new object as a
    copy of an existing object (of the same type).
  - and much like a default constructor, if you do not provide a copy constructor for your
    classes, C++ will create a public copy constructor for you.
  - because the compiler does not know much about your class, by default, the created copy
    constructor utilizes a method of initialization called memberwise initialization.
  - [memberwise initialization] simply means that each member of the copy is initialized
    directly from the member of the class being copied.

  - just like we can explicitly define a default constructor, we can also explicitly define
    a copy constructor.
*/


#include <cassert>

namespace the_copy_constructor
{
    class Fraction
    {
    private:
        int m_numerator{};
        int m_denominator{};

    public:
        // Default constructor
        Fraction(int numerator=0, int denominator=1)
            : m_numerator{ numerator }
            , m_denominator{ denominator }
        {
            assert((denominator != 0) && "denominator can't be zero");
        }

        // copy constructor
        Fraction(const Fraction& fraction)
            : m_numerator{ fraction.m_numerator }
            , m_denominator{ fraction.m_denominator }
            // we can access the members of parameter fraction directly, because we're inside the Fraction class
        {
            std::cout << "Copy constructor called\n";
        }

        friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction);
        int getNumerator() { return m_numerator; }
        int getDenominator() { return m_denominator; }
        void setNumerator(int numerator) { m_numerator = numerator; }
        void setDenominator(int denominator) { m_denominator = denominator; }
    };

    std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
    {
        out << fraction.m_numerator << '/' << fraction.m_denominator;
        return out;
    }


    void main()
    {
        Fraction fiveThirds{ 5, 3 };        // uniform initialize a fraction, calls Fraction(int, int)
        Fraction fCopy{ fiveThirds };       // uniform initialize a fraction -- with copy constructor
        std::cout << fCopy << '\n';
    }
}




/*---------------------------------------------------------------------------------------
    ============[ the copy constructor's parameter must be a reference ]============
---------------------------------------------------------------------------------------*/

/*
  - it is a requirement tht the parameter of a copy constrctor be a (const) reference.
  - this makes sense: if the argument were passed by value, then we'd need the copy constructor
    to copy the argument into the parameter of the copy constructor (which would result in
    an infinite recursion).
*/




/*---------------------------------------------------------------------------------------
                      ============[ preventing copies ]============
---------------------------------------------------------------------------------------*/

// we can prevent copies of our classes from being made by making the copy constructor private.




/*---------------------------------------------------------------------------------------
              ============[ the copy constructor may be elided ]============
---------------------------------------------------------------------------------------*/

/*
  - the process of omitting certain copy (or move) steps for performance purposes is called
    [elision].

  - prior to C++17, compilers are permitted (but not required) to perform copy elision in
    certain cases.
  - in such cases, a copy constructor must be accessble (e.g. non-private), even if the actual
    copy is elided.
  - as of C++17, some cases of copy elifion have been made mandatory.
  - in these mandatory elision cases, the copy constructor does not need to be accessible
    (or even present) since it is guaranteed not to be needed.
*/




/*---------------------------------------------------------------------------------------
                ============[ copy initialization for classes ]============
---------------------------------------------------------------------------------------*/


int x = 5;

/*
  - the statement above uses copy initialization to initialize newly created integer variable
    x to the value of 5.
  - however, classes are a little more complicated, since they use constructors for initialization.

  - there are other places where copy initialization used:
    > when you pass or return a class by value.
*/

namespace the_copy_constructor
{
    Fraction makeNegative(Fraction f)       // ideally we should do this by const reference
    {
        f.setNumerator(-f.getNumerator());
        return f;
    }
    
    void copy_used()
    {
        Fraction fiveThirds(5, 3);
        std::cout << makeNegative(fiveThirds);
    }
}

/*
  - in the above program, function makeNegative takes a Fraction by value and also returns
    a Fraction by value.
  - when we run the program, we get something like:

    $ Copy constructor called
    $ Copy constructor called
    $ -5/3
*/




//=======================================================================================

int main()
{
    the_copy_constructor::main();
    the_copy_constructor::copy_used();

    return 0;
}