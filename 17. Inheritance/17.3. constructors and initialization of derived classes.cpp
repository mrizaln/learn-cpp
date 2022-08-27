#include <iostream>


/*---------------------------------------------------------------------------------------
              ============[ initializing base class members ]============
---------------------------------------------------------------------------------------*/

// C++ gives us the ability to expicitly choose which base class constructor will be called.

class Base
{
public:
    int m_id {};

    Base(int id=0)
        : m_id{ id }
    {
    }

    int getId() const { return m_id; }
};

class Derived: public Base
{
public:
    double m_cost {};

    Derived(double cost=0.0, int id=0)
        : Base{ id }        // call Base(int) constructor with value id
        , m_cost{ cost }
    {
    }

    double getCost() const { return m_cost; }
};

int main()
{
    Derived derived{ 1.3, 5 };      // use Derived(double, int) ctor
    std::cout << derived.getId() << ' ' << derived.getCost() << '\n';

    return 0;
}




/*---------------------------------------------------------------------------------------
            ============[ now we can make our members private ]============
---------------------------------------------------------------------------------------*/

/*
  - now that we know how to initialize base class members, there's no need to keep our member
    variables public.
  - we make our member variables private again, as they should be.

  - private members can only be accessed by members of the same class.
  - this means derived classes cannot access private members of the base class directly.
*/




/*---------------------------------------------------------------------------------------
                        ============[ destructors ]===========
---------------------------------------------------------------------------------------*/

// when a derived class is destroyed, each destructor is called in the reverse order of
// construction.