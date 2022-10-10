#include <iostream>
#include <string>
#include <string_view>


/*---------------------------------------------------------------------------------------
 ============[ pure virtual (abstract) functions and abstract base classes ]============
---------------------------------------------------------------------------------------*/

/*
  - C++ allows you to create a special kind of virtual function called a [pure virtual function]
    (or [abstract function]) that has no body at all.
  - a virtual function simply acts as a placeholder that is meant to be redefined by derived
    classes.

  - to create a pure virtual function, rather than define a body for the function, we simply
    assign the function the value 0

  - using a pure virtual function has two main consequences: first, any class with one or
    more pure virtual functions becomes an [abstract base class], which means that it can
    not be instantiated.
  - second, any derived class must define a body for this function, or that derived class
    will be considered an abstract base class as well
*/

namespace pure_virtual_function_and_abstract_class
{
    class Animal    // Animal is an abstract base class (because of speak() being pure virtual)
    {
    protected:
        std::string m_name{};

    public:
        Animal(std::string_view name)
            : m_name{ name }
        {
        }

        const std::string& getName() const { return m_name; }
        virtual const char* speak() const = 0;                  // speak() is now a pure virtual function 

        virtual ~Animal() = default;
    };

    class Cow: public Animal
    {
    public:
        Cow(std::string_view name)
            : Animal{ name }
        {
        }

        const char* speak() const override { return "Moo"; }
    };

    void main()
    {
        Cow cow{ "Betsy" };
        std::cout << cow.getName() << " says " << cow.speak() << '\n';
    }
}




/*---------------------------------------------------------------------------------------
            ===========[ pure virtual functions with definitions ]===========
---------------------------------------------------------------------------------------*/

// we can create pure virtual functions that have a definitions

namespace pure_virtual_function_with_definition
{
    class Animal // This Animal is an abstract base class
    {
    protected:
        std::string m_name;

    public:
        Animal(const std::string& name)
            : m_name{ name }
        {
        }

        std::string getName() { return m_name; }
        virtual const char* speak() const = 0; // The = 0 means this function is pure virtual

        virtual ~Animal() = default;
    };

    const char* Animal::speak() const  // even though it has a definition
    {
        return "buzz";
    }
}

/*
  - in this case speak() is still considered a pure virtual function because of the "=0"
    and Animal is still considered an abstract base class.

  - this paradigm can be useful when you want your base class to provide a default implementation
    for a function, but still force any derived classes to provide their own implementation.
  - if the derived class is happy with the default implementation provided by the base class,
    it can simply call the base class implementation directly.
*/

namespace pure_virtual_function_with_definition
{
    class Dragonfly: public Animal
    {

    public:
        Dragonfly(const std::string& name)
            : Animal{name}
        {
        }

        const char* speak() const override// this class is no longer abstract because we defined this function
        {
            return Animal::speak(); // use Animal's default implementation
        }
    };

    void main()
    {
        Dragonfly dfly{"Sally"};
        std::cout << dfly.getName() << " says " << dfly.speak() << '\n';
    }
}

// this capability isn't used very commonly




/*---------------------------------------------------------------------------------------
                       ===========[ interface classes ]===========
---------------------------------------------------------------------------------------*/

/*
  - an [inteface class] is a class that has no member variables, and where all of the
    functions are pure virtual!
  - in other words, the class is purely a definition and has no actual
    implementation.
  - interfaces are useful when you want to define the functionality that derived classes
    must implementation, but leave the details of how the derive class implements that
    functionality entirely up to the derived class.

  - interface classes are often named beginning with an I.
*/

namespace interface_class
{
    class IErrorLog
    {
    public:
        virtual bool openLog(const char* filename) = 0;
        virtual bool closeLog() = 0;

        virtual bool writeError(const char* errorMessage) = 0;

        virtual ~IErrorLog() {};    // make a virtual destructor in case we delete an
                                    // IErrorLog pointer, so the proper derived destructor
                                    // is called
    };
}

/*
  - any class inheriting from IErrorLog must provide implementations for all three functions
    in order to be instantiated.

  - lets's say you need to write some code that uses an error log.
  - the error log class itself can be anything that derived from IErrorLog, but we can use
    a reference to the interface like below.
*/

#include <cmath>    // for sqrt()
namespace interface_class
{
    double mySqrt(double value, IErrorLog& log)
    {
        if (value < 0.0)
        {
            log.writeError("Tried to take square root of value less than 0");
            return 0.0;
        }
        else
            return std::sqrt(value);
    }
}




//=======================================================================================

int main()
{
    pure_virtual_function_and_abstract_class::main();
    pure_virtual_function_with_definition::main();

    return 0;
}