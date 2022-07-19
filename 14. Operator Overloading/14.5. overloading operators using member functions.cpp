#include <iostream>


/*
  - overloading operators using a member function is very similar to overloading operators
    using a friend function.
  - when overloading an operator using a member function:
    1) the overloaded operator must be added as a member function of the left operand.
    2) the left operand becomes the implicit *this object.
    3) all other operands become function parameters.
*/

namespace overloading_operator_as_member_function
{
    class Cents
    {
    private:
        int m_cents{};

    public:
        Cents(int cents) : m_cents{ cents } { }

        // overload Cents + int
        Cents operator+(int value);

        int getCents() const { return m_cents; }
    };


    // this function is a member function!
    // the cents paramater is the implicit *this parameter
    Cents Cents::operator+(int value)
    {
        return { m_cents + value };
    }

    void main()
    {
        Cents cents1{ 6 };
        Cents cents2{ cents1 + 2 };
        std::cout << "I have " << cents2.getCents() << " cents.\n";
    }
}

// in the member function version, the expression [cents1 + 2] becomes function call
// [cents1.operator+(2)].




/*---------------------------------------------------------------------------------------
    ============[ not everything can be overloaded as a friend function ]============
---------------------------------------------------------------------------------------*/

/*
    the assignment (=), subscript ([]), function call (()), and member selection (->) operators
    must be overloaded as member functions, because the language requires them to be.
*/




/*---------------------------------------------------------------------------------------
    ============[ not everything can be overloaded as a member function ]============
---------------------------------------------------------------------------------------*/

/*
  - in previous chapter, we overloaded operator<< as a friend function.
  - however, we can't overload operator<< as a member function, because the overloaded operator
    must be added as a member of the left operand.
  - in this case, the left operand is an object of type std::ostream, std::ostream is fixed
    as part of the standard library.
  - we can't modify the calss declaration to add the overload as a member function of std::ostream.

  - similarly, although we can overload operator+(Cents, int) as a member function (above),
    we can't overload operator+(int, Cents) as a member function, because int isn't a class
    we can add members to.
*/




/*---------------------------------------------------------------------------------------
  ============[ when to use a normal, friend, or member function overload ]============
---------------------------------------------------------------------------------------*/

/*
  - when dealing with [binary operators that don't modify the left operand] (e.g. operator+),
    the [normal or friend function] version is typically preferred.
  - the normal or friend function version has the added benefit of "symmetry", as all operands
    become explicit parameters.

  - when dealing with [binary operators that do modify the left operand] (e.g. operator+=),
    the [member function] version is typically preferred.
  - in these cases, the leftmost operand will always be a class type, and having the object
    being modified become the one pointed to by *this is natural.

  - [unary operators] are usually overloaded as member functions as well, since the member
    version has no parameters.

    the following rules of thumb can help you determine which form is best for a given situation:
    
      > operator=, operator[], operator(), operator->       use member function
      > unary operator                                      use member function
      > binary operator, doesn't modify its left operand:   use normal function or friend function
      > binary operator, modify its left operand, can't add members to its left operand:    use normal function or friend function
      > binary operator, modify its left operand, can add members to its left operand:      use member function
*/



//=======================================================================================

int main()
{
    overloading_operator_as_member_function::main();

    return 0;
}