#include <iostream>


/*---------------------------------------------------------------------------------------
          ============[ order of construction of derived classes ]============
---------------------------------------------------------------------------------------*/

/*
  - when C++ constructs  derived objects, it does so in phases.
  - first, the most-base class (at the top of the inheritance tree) is constructed first.
  - then each child class is constructed in order, until the most-child class (at the bottom
    of the inheritance tree) is constructed last.
*/

class Base
{
public:
    int m_id {};

    Base(int id=0)
        : m_id { id }
    {
        std::cout << "Base\n";
    }

    int getId() const { return m_id; }
};

class Derived: public Base
{
public:
    double m_cost {};

    Derived(double cost=0.0)
        : m_cost { cost }
    {
        std::cout << "Derived\n";
    }

    double getCost() const { return m_cost; }
};

int main()
{
    std::cout << "Instantiating Base\n";
    Base base;

    std::cout << "Instantiating Derived\n";
    Derived derived;

    return 0;
}