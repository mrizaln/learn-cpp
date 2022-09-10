#include <iostream>
#include <string>
#include <string_view>


/*---------------------------------------------------------------------------------------
              ============[ virtual functions and polymorphism ]============
---------------------------------------------------------------------------------------*/

/*
  - a [virtual function] is a special type of function that, when called, resolves to the
    most-derived version of the function that exists between the base and derived class.
  - this capability is known as [polymorphism].
  - a derived function is considered a match if it has the same signature (name, parameter
    types, and whether it is const) and return type as the base version of the function.
  - such functions are called [overrides].
*/

namespace virtual_function
{
    class Base
    {
    public:
        virtual std::string_view getName() const { return "Base"; }     // note addition of virtual keyword
    };

    class Derived: public Base
    {
    public:
        virtual std::string_view getName() const { return "Derived"; }
    };

    void main()
    {
        Derived derived{};
        Base& rBase{ derived };
        std::cout << "rBase is a " << rBase.getName() << '\n';      // prints: rBase is a Derived
    }
}




/*---------------------------------------------------------------------------------------
                   ============[ a more complex example ]===========
---------------------------------------------------------------------------------------*/

namespace a_more_complex_example
{
    class Animal
    {
    protected:
        std::string m_name{};

        Animal(std::string_view name)
            : m_name{ name }
        {
        }

    public:
        const auto& getName() const { return m_name; }
        virtual std::string_view speak() const { return "???"; }
    };

    class Cat: public Animal
    {
    public:
        Cat(std::string_view name)
            : Animal{ name }
        {
        }

        virtual std::string_view speak() const { return "Meow"; }
    };

    class Dog: public Animal
    {
    public:
        Dog(std::string_view name)
            : Animal{ name }
        {
        }

        virtual std::string_view speak() const { return "Woof"; }
    };

    void report(const Animal& rAnimal)
    {
        std::cout << rAnimal.getName() << " says " << rAnimal.speak() << '\n';
    }

    void main()
    {
        Cat cat{ "Fred" };
        Dog dog{ "Garbo" };
        
        report(cat);    // prints: Fred saus Meow
        report(dog);    // prints: Garbo says Woof
    }
}

// [ a word of warning]
/*---------------------------------------------------------------------------------------
    the signature of the derived class function must exactly match the signature of the
    base class virtual function in order for the derived class function to be used.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
============[ do not call virtual function from constructors or destructors ]============
---------------------------------------------------------------------------------------*/

/*
  - if you were to call a virtual function from the Base constructor, and Derived portion
    of the class hadn't even been created yet, it would be unable to call the Derived version
    of the function because there's not Derived object for the Derived function to work on.
  - in C++, it will call the Base version instead.

  - if you call a virtual function ia Base class destructor, it will always resolve to the
    Base class version of the function, because the Derived potion of the class will already
    have been destroyed.
*/



//=======================================================================================

int main()
{
    virtual_function::main();
    a_more_complex_example::main();

    return 0;
}