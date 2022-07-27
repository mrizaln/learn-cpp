#include <iostream>


/*---------------------------------------------------------------------------------------
    ============[  ]============
---------------------------------------------------------------------------------------*/

/*
  - C++ already knows how to convert between the built-in data types.
  - however, it does not know how to convert any of user-defined classes.
  - that's where overloading the typecast operators comes into play.

  - [user-defined conversions] allow us to convert our class into another data type.
*/

namespace an_example
{
    class Cents
    {
    private:
        int m_cents{};

    public:
        Cents(int cents) : m_cents{ cents } { }

        // overloading int cast
        operator int() const { return m_cents; }

        int getCents() const { return m_cents; }
        void setCents(int cents) { m_cents = cents; }
    };
}

/*
  - there are three things to note:
    1. to overload the function that casts out class to an int, we write a new function in
       our class called operator int(). note that there is a space between the word operator
       and the type we are casting to.
    2. user-defined conversions do not take parameters, as ther is no way to pass arguments
       to them.
    3. user-defined conversions do not have a return type. C++ assumes you will be returning
       the correct type.

  - you can provide user-defined conversions for any data type you wish, including your own
    user-defined data types.
*/

namespace an_example
{
    class Dollars
    {
    private:
        int m_dollars{};

    public:
        Dollars(int dollars) : m_dollars{ dollars } { }

        // allow us to convert Dollars into Cents
        operator Cents() const { return Cents{ m_dollars * 100 }; }
    };

    void printCents(Cents cents)
    {
        std::cout << cents << '\n';     // cents will be implicitly converted to an int here
    }

    
    void main()
    {
        Dollars dollars{ 9 };
        printCents(dollars);        // dollars will be implicitly cast to a Cents here
    }
}





//=======================================================================================

int main()
{
    an_example::main();

    return 0;
}