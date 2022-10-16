#include <iostream>
#include <string>


/*---------------------------------------------------------------------------------------
                 ============[ the need for dynamic_cast ]============
---------------------------------------------------------------------------------------*/

// when dealing with polymorphism, you'll often encounter cases where you have a pointer
// to a base class, but you want to access some information that exists only in a derived
// class.

// consider the following

namespace dynamic_casting
{
    class Base
    {
    protected:
        int m_value{};

    public:
        Base(int value)
            : m_value{ value }
        {
        }

        virtual ~Base() = default;
    };

    class Derived: public Base
    {
    protected:
        std::string m_name{};

    public:
        Derived(int value, const std::string& name)
            : Base{ value }
            , m_name{ name }
        {
        }

        const auto& getName() const { return m_name; }
    };

    Base* getObject(bool returnDerived)
    {
        if (returnDerived)
            return new Derived{ 1, "Apple" };
        else
            return new Base{ 2 };
    }

    void main()
    {
        Base* b{ getObject(true) };

        // how do we print the Derived object's name here, having only a Base pointer?
        
        delete b;
    }
}

/*
  - C++ provides a casting operator named [dynamic_cast] that can be used for above purpose.
  - although dynamic casts have a few different capabilities, by far the most common use
    for dynamic casting is for converting base-class pointers into derived-class pointers.
  - this process is called [downcasting].

  - using dynamic_cast works just like static_cast.
*/

namespace dynamic_casting
{
    void main_using_dynamic_cast()
    {
        Base* b{ getObject(true) };
        
        Derived* d{ dynamic_cast<Derived*>(b) };    // convert Base pointer into Derived pointer

        if (d)      // read below section first
            std::cout << "The name of the Derived is: " << d->getName() << '\n';

        delete b;
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ dynamic_cast failure ]============
---------------------------------------------------------------------------------------*/

/*
  - the above example works because b is actually pointing to a Derived object, so converting
    b into a Derived pointer is successful.
  
  - however, we've made quite a dangerous assumption: that b is pointing to a Derive object.
  - what if b wasn't pointing to a Derived object?
  - in that case, dynamic_cast will fail.
  - if a dynamic_cast fails, the result of the conversion will be a null pointer.

  - in order to make this program safe, we need to ensure the result of the dynamic_cast
    actually succeeded.

  - note that because dynamic_cast does some consistency checking at runtime (to ensure
    conversion can be made), use of dynamic_cast does incur a performance penalty.
  - also note that there are several cases where downcasting using dynamic_cast will not work:
      > with protected or private inheritance
      > for classes that do not declare or inherit any virtual functions (and thus don't have
        a virtual table).
      > in certain cases involving virtual base classes.
*/




/*---------------------------------------------------------------------------------------
                ============[ downcasting with static_cast ]============
---------------------------------------------------------------------------------------*/

/*
  - yes, downcasting can also be done with static_cast.
  - the main difference is that static_cast does no runtime type checking to ensure that
    what you're doing makes sense.
  - this makes using static_cast faster, but more dangerous.
  - if you cast a Base* to a Derived*, it will "succeed" even if the Base pointer is not
    pointing to a Derived object.
  - this will result in undefined behavior.
*/




/*---------------------------------------------------------------------------------------
        ============[ dynamic_cast and references ]============
---------------------------------------------------------------------------------------*/

/*
  - dynamic_cast can also be used with references.
  - this works analogously to how dynamic_cast works with pointers.

        Derived d;
        Base& b{ d };
        Derived& rd{ dynamic_cast<Derived&>(b) };


  - because C++ does not have a "null reference", dynamic_cast can't return a null reference
    upon failure.
  - instead, if the dynamic_cast of a reference fails, an exception of type std::bad_cast
    is thrown.
*/




/*---------------------------------------------------------------------------------------
                ============[ dynamic_cast vs static_cast ]============
---------------------------------------------------------------------------------------*/

/*
  - use static_cast unless you're downcasting, in which case dynamic_cast usually is a better
    choice.
  - however, you should also consider avoiding casting altogether and just use virtual
    functions.
*/




/*---------------------------------------------------------------------------------------
              ============[ downcasting vs virtual functions ]============
---------------------------------------------------------------------------------------*/

/*
  - in general, using virtual function should be preferred over downcasting.
  - however, there are times when downcasting is the better choice:
      > when you can not modify the base class to add a virtual function (e.g. in a library).
      > when you need access to something that is derived-class specific.
      > when adding a virtual function to your base class doesn't make sense. using a pure
        virtual function may be an option here if you don'r need to instantiate the base
        class.
*/




//=======================================================================================

int main()
{
    dynamic_casting::main_using_dynamic_cast();

    return 0;
}