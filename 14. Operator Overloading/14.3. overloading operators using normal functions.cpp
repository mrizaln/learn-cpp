#include <iostream>

/*
  - overloading an operator using a friend function is convenient because it gives you direct
    access to the internal members of the classes you're operating on.
  - however, if you don't need that access, you can write your overloaded operators as normal
    functions.
*/


class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{ cents } { }

    int getCents() const { return m_cents; }
};

// overload (normal function)
Cents operator+(const Cents& c1, const Cents& c2)
{
    // we don't need direct access to private members her
    return { c1.getCents() + c2.getCents() };
}

int main()
{
    Cents cents1{ 6 };
    Cents cents2{ 8 };
    Cents centsSum{ cents1 + cents2 };
    std::cout << "I have " << centsSum.getCents() << " cents.\n";
}

/*
  - in general, a normal function should be preferred over a friend function if it's possible
    to do so without the existing member functions available (the less functions touching)
    your classes's internals, the better).
  - however, don't add additional access functions just to overload an operator as a normal
    function insted of a friend function!
*/