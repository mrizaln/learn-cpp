#include <iostream>


/*---------------------------------------------------------------------------------------
                   ============[ virtual destructors ]============
---------------------------------------------------------------------------------------*/

/*
  - although C++ provides a default destructor for your classes if you do not provide one
    yourself, it is sometimes the case that you will want to provide your own destructor
    (particularly if the class needs to deallocate memory).

  - you should [always] make your destructors virtual if you're dealing with inheritance.
*/

namespace virtual_destructor
{
    class Base
    {
    public:
        virtual ~Base()     // note: virtual
        {
            std::cout << "Calling ~Base()\n";
        }

        // virtual ~Base() = default;      // if you want the default destructor
    };

    class Derived: public Base
    {
    private:
        int* m_array{};

    public:
        Derived(int length)
            : m_array{ new int[length] }
        {
        }

        ~Derived() override
        {
            std::cout << "Calling ~Derived()\n";
            delete[] m_array;
        }
    };

    void main()
    {
        Derived* derived{ new Derived(5) };
        Base* base{ derived };

        delete base;        // this action will call Base destructor, but since it is virtual,
                            // it will call the destructor of Derived class that is lowest
                            // in the inheritance tree 
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ virtual assignment ]============
---------------------------------------------------------------------------------------*/


/*
  - it is possible to make the assignment operator viartual.
  - however, unlike the destructor case where viatualization is always a good idea, virtualizing
    the assignment operator really opens up a bag full of worms and gets into some advanced
    topics outside of the scope of this tutorial.
  - consequently, we are going to recommend you leave your assignments non-virtual for now,
    in the interest of simplicity.
*/




/*---------------------------------------------------------------------------------------
                   ============[ ignoring virtualization ]============
---------------------------------------------------------------------------------------*/

// there may be cases where you want a Base pointer to a Derived object to call Base function
// instead of Derived function.

namespace ignoring_virtualization
{
    class Base
    {
    public:
        virtual ~Base() = default;
        virtual const char* getName() const { return "Base"; }
    };

    class Derived: public Base
    {
    public:
        virtual const char* getName() const { return "Derived"; }
    };

    void main()
    {
        Derived derived;
        const Base& base{ derived };

        // calls Base::getName() instead of virtualized Derived::getName()
        std::cout << base.Base::getName() << '\n';
    }
}




//=======================================================================================

int main()
{
    virtual_destructor::main();
    ignoring_virtualization::main();

    return 0;
}