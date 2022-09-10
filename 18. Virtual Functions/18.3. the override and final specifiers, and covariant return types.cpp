#include <iostream>
#include <string>
#include <string_view>


/*
  - to address some common challenges with inheritance, there are two special identifiers:
    override and final.
  - note that these identifiers are not considered keywords -- they are normal identifiers
    that have special meaning in certain contexts.
*/

/*---------------------------------------------------------------------------------------
                   ============[ the override specifier ]============
---------------------------------------------------------------------------------------*/

/*
  - to help address the issue of functions that are meant to override but aren't, the override
    specifier can be applied to any virtual function by placing the specifier in the same
    place  const would go.
  - if the function does not override a base class function (or is applied to a non-virtual
    function), the compiler will flag the function as an error.
*/

namespace the_override_specifier
{
    class A
    {
    public:
        virtual std::string_view getName1(int x ) { return "A"; }
        virtual std::string_view getName2(int x ) { return "A"; }
        virtual std::string_view getName3(int x ) { return "A"; }
    };

    class B: public A
    {
    public:
        // std::string_view getName1(short int x) override { return "B"; }      // compile error: does not override
        // std::string_view getName2(int x) const override { return "B"; }      // compile error: does not override
        std::string_view getName3(int x) override { return "B"; }
    };
}

// [ best practice ]
/*---------------------------------------------------------------------------------------
    use the virtual keyword on virtual functions in base class. use the override
    specifier (but not the virtual keyword) on override functions in derived class.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
                    ============[ the final specifier ]============
---------------------------------------------------------------------------------------*/

/*
  - there may be cases where you don't want someone to be able to override a virtual function,
    or inherit from a class.
  - the final specifier can be used to tell the compiler to enforce this.
  - in the case where we want to restrict the user from overriding a function, the [final
    specifier] is used in the same place the override specifier is.
*/

namespace the_final_specifier
{
    class A
    {
    public:
        virtual std::string_view getName() { return "A"; }
    };

    class B: public A
    {
    public:
        // this function is no longer overridable
        std::string_view getName() override final { return "B"; }
    };

    class C: public B
    {
    public:
        // std::string_view getName() override { return "C"; }     // compile error
    };
}

// in the case where we want to prevent inheriting from a class, the final specifier is applied
// after the class name.

namespace the_final_specifier
{
    class BB final: public A    // note use of final specifier here
    {
    public:
        std::string_view getName() override { return "B"; }
    };

    // class CC: public BB     // compile error: cannot inherit from final class
    // {
    // public:
    //     std::string_view getName() override { return "C"; }
    // }
}




/*---------------------------------------------------------------------------------------
                   ============[ covariant return types ]============
---------------------------------------------------------------------------------------*/

/*
  - there is one special case in which a derived class virtual function override can have
    a different return type than the base class and still be considered a matching override.
  - if the return type of a virtual function is a pointer or a reference to some class,
    override functions can return a pointer or reference to a derived class.
  - these are called [covariant return types].
*/

namespace covariant_return_types
{
    class Base
    {
    public:
        // this version of getThis() returns a pointer to a Base class
        virtual Base* getThis() { std::cout << "called Base::getThis()\n"; return this; }
        void printType() { std::cout << "returned a Base\n"; }
    };

    class Derived: public Base
    {
    public:
        // normally override functions have to return objects of the same type as the base
        // function. however, because Derived is derived from Base, it's okay to return Derived*
        // instead of Base*
        Derived* getThis() override { std::cout << "called Derived::getThis()\n"; return this; }
        void printType() { std::cout << "returned a Derived\n"; }
    };

    void main()
    {
        Derived d{};
        Base* b{ &d };
        d.getThis()->printType();       // calls Derived::getThis(), returns a Derived*, calls Derived::printType()
        b->getThis()->printType();      // calls Derived::getThis(), retuns a Base*, calls Base::printType()
    }
}


//=======================================================================================

int main()
{
    covariant_return_types::main();

    return 0;
}