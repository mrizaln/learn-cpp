#include <iostream>


/*---------------------------------------------------------------------------------------
                        ============[ ]============
---------------------------------------------------------------------------------------*/

class Base
{
public:
    // overloaded operator<<
    friend std::ostream& operator<<(std::ostream& out, const Base& b)
    {
        return b.print(out);
    }

    // we'll rely on member function print() to do the actual printing
    virtual std::ostream& print(std::ostream& out) const
    {
        out << "Base";
        return out;
    }
};

class Derived: public Base
{
public:
    // here's our override print function to handle the Derived case
    std::ostream& print(std::ostream& out) const override
    {
        out << "Derived";
        return out;
    }
};


int main()
{
    Base b{};
    std::cout << b << '\n';

    Derived d{};
    std::cout << d << '\n';

    Base& bref{ d };
    std::cout << bref << '\n';

    return 0;
}