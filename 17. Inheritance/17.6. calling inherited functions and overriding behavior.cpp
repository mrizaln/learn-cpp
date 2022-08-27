#include <iostream>


// by default, derived classes inherit all of the behaviors defined in a base class.

/*---------------------------------------------------------------------------------------
                ============[ calling a base class function ]============
---------------------------------------------------------------------------------------*/

/*
  - when a member function is called with a derived class object, the compiler first look
    to see if that member exists in the derived class.
  - if not, it begins walking up the inheritance chain and checking whether the member has
    been defined in any of the parent classes.
  - it uses the first one it finds.
*/

class Base
{
protected:
    int m_value{};

public:
    Base(int value)
        : m_value{ value }
    {
    }

    void identify() const { std::cout << "I am a Base\n"; }
};

namespace calling_a_base_class_function
{
    class Derived: public ::Base
    {
    public:
        Derived(int value)
            : Base{ value }
        {
        }
    };

    void main()
    {
        Base base{ 5 };
        base.identify();        // prints "I am a Base"

        Derived derived{ 4 };
        derived.identify();     // prints "I am a Base"
    }
}




/*---------------------------------------------------------------------------------------
                   ============[ redefining behaviors ]============
---------------------------------------------------------------------------------------*/
/*
  - we can make funcitons work differently with our derived classes by redefining them in
    the derived class.
  - in the example above it would be accurate if derived.identify() printed "I am a Derived".
*/

namespace redefining_behaviors
{
    class Derived: public ::Base
    {
    public:
        Derived(int value)
            : Base{ value }
        {
        }

        int getValue() const { return m_value; }

        // modified function
        void identify() const { std::cout << "I am a Derived\n"; }
    };

    void main()
    {
        Base base{ 5 };
        base.identify();        // prints "I am a Base"

        Derived derived{ 4 };
        derived.identify();     // prints "I am a Derivative"
    }
}

/*
  - when we redefine a funcion in the derived class, the derived function does not inherit
    the access speifier of the function with the same name in the base class.
  - it uses whatever access specifier it is defined under in the derived class.
*/




/*---------------------------------------------------------------------------------------
               ============[ adding to existing functionality ]===========
---------------------------------------------------------------------------------------*/

/*
  - sometimes we don't want to completely replace a base class function, but instead want
    to add additional functionality to it.
  - to have a derived function call a base function of the same name, simply do a normal
    function call, but prefix the function with the scope qualifier.
*/

namespace adding_to_existing_functionality
{
    class Derived: public ::Base
    {
    public:
        Derived(int value)
            : Base{ value }
        {
        }

        int getValue() const { return m_value; }

        void identify() const
        {
            Base::identify();       // call Base::identify() first
            std::cout << "I am a Derived\n";
        }
    };

        void main()
    {
        Base base{ 5 };
        base.identify();        // prints "I am a Base"

        Derived derived{ 4 };
        derived.identify();     // prints "I am a Base" and "I am a Derived"
    }
}

/*
  - there's one bit of trickiness that we can run into when trying to call friend functions
    in base classes, such as operator<<.
  - Because friend functions of the base class aren't actually part of the base class, using
    the scope resolution won't work.
  - instead we need a way to make our Derived class temporarily look like the Base class so
    that the right version of the function call can be called.

  - fortunately, that's easy to do: using static_cast.
*/

namespace tricky_friend_function_on_base_class
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

        friend std::ostream& operator<<(std::ostream& out, const Base& b)
        {
            out << "In Base\n";
            out << b.m_value << '\n';
            return out;
        }
    };

    class Derived: public Base
    {
    public:
        Derived(int value)
            : Base{ value }
        {
        }

        friend std::ostream& operator<<(std::ostream& out, const Derived& d)
        {
            out << "In Derived\n";
            // static_cast Derived to a Base object, so we call the right version of operator<<
            out << static_cast<const Base&>(d);
            return out;
        }
    };

    void main()
    {
        Derived derived{ 7 };
        std::cout << derived << '\n';
    }
}




//=======================================================================================

int main()
{
    calling_a_base_class_function::main();
    redefining_behaviors::main();
    adding_to_existing_functionality::main();
    tricky_friend_function_on_base_class::main();

    return 0;
}