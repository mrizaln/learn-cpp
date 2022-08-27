#include <iostream>


/*---------------------------------------------------------------------------------------
        ============[ changing an inherited member's access level ]=============
---------------------------------------------------------------------------------------*/

/*
  - C++ gives us the ability to change an inherited member's access specifier in the derived
    class.
  - this is done by using a [using declaration] to identify the base class member that is
    having its access changed in the derived class, under the new access specifier.
*/

namespace change_access_level
{
    class Base
    {
    private:
        int m_value{};

    public:
        Base(int value)
            : m_value{ value }
        {
        }

    protected:
        void printValue() const { std::cout << m_value << '\n'; }
    };


    class Derived: public Base
    {
    public:
        Derived(int value)
            : Base{ value }
        {
        }

        // Base::printValue was inherited as protected, so the public has no access
        // but we're changing it to public via a using declaration
        using Base::printValue;
    };

    void main()
    {
        Derived derived{ 7 };

        // printValue is public in Derived, so this is okay
        derived.printValue();
    }
}

/*
  - you can only change the access specifiers of base members the derived class would normally
    be able to access.
  - therefore, you can never change the access specifier of a base member from private to
    other.
*/




/*---------------------------------------------------------------------------------------
                    ============[ hiding functionality ]============
---------------------------------------------------------------------------------------*/

/*
  - in C++, it is not possible to remove or restrict functionality from a base class other
    than by modifying the source code.
  - however, in a derived class, it is possible to hide functionality that exists in the
    base class, so that it can not be accessed through the derived classs.
  - this can be done simply by changing the relevant access specifier.

  - you can also mark member functions as deleted in the derived class, which ensures they
    can't be called at all through a derived object.
*/

namespace hiding_functionality
{
    class Base
    {
    public:
        int m_value{};

        int getValue() const { return m_value; }
    };

    class Derived: public Base
    {
    private:
        using Base::m_value;            // make Base::m_value private

    public:
        Derived(int value)
        // we can't initialize m_value, no Base constructor for it
        {
            // but we can assign it a value
            m_value = value;
        }

        int getValue() = delete;        // mark this function as inaccessible
    };

    void main()
    {
        Derived derived{ 7 };

        // the following won't work because m_value has been redefined as private
        // std::cout << derived.m_value;

        // std::cout << derived.getValue();                                // not work
        std::cout << derived.Base::getValue() << '\n';                  // though we can access it directly
        std::cout << static_cast<Base&>(derived).getValue() << '\n';    // or upcast the object to access the function
    }
}




//=======================================================================================

int main()
{
    change_access_level::main();
    hiding_functionality::main();

    return 0;
}