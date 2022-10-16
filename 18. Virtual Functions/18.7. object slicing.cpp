#include <iostream>


/*---------------------------------------------------------------------------------------
                       ============[ object slicing ]============
---------------------------------------------------------------------------------------*/

namespace object_slicing
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

        virtual const char* getName() const { return "Base"; }
        int getValue() const { return m_value; }
    };

    class Derived: public Base
    {
    public:
        Derived(int value)
            : Base{ value }
        {
        }

        const char* getName() const override { return "Derived"; }
    };


    void main()
    {
        Derived derived{ 5 };
        std::cout << "derived is a " << derived.getName()
                  << " and has value " << derived.getValue() << '\n';

        Base& ref{ derived };
        std::cout << "ref is a " << ref.getName()
                  << " and has value " << ref.getValue() << '\n';

        Base* ptr{ &derived };
        std::cout << "ptr is a " << ptr->getName()
                  << " and has value " << ptr->getValue() << '\n';

        // both ref and ptr above points to derived, which has a Base part and Derived part.
        // but what happens if instead of setting a Base reference or pointer to a Derived
        // object, we simply /assign/ a Derived object to a Base object?
        
        Base base{ derived };       // what happens here?
        std::cout << "base is a " << base.getName()
                  << " and has value " << base.getValue() << '\n';
    }

    // void main() outputs:
    /*------------------------------------------
        derived is a Derived and has value 5
        ref is a Derived and has value 5
        ptr is a Derived and has value 5
        base is a Base and has value 5
    ------------------------------------------*/
}

/*
  - remember that derived has a Base a a Derived part.
  - when we assign a Derived object to a Base object, only the Base portion of the Derived
    object is copied, the Derived portion is not.
  - the Derived potions has effectively been "sliced off".
  - the assigning of a Derived class to a Base class object is called [object slicing].
*/




/*---------------------------------------------------------------------------------------
                   ============[ slicing and functions ]============
---------------------------------------------------------------------------------------*/

// consider the following function:

namespace slicing_and_function
{
    using object_slicing::Base, object_slicing::Derived;

    void printName(const Base base)     // base passed by value, not reference
    {
        std::cout << "I am a " << base.getName() << '\n';
    }

    void main()
    {
        Derived d{ 5 };
        printName(d);       // oops, didn't realize this was pass by value on the calling end
    }
}

/*
  - notice that the parameter of printName is in value not a reference.
  - when we pass Derived, it will be sliced to be copied into Base.
  - if we expect that printName() has a reference parameter, we expect base.getName() will
    call virtualized function getName() and print "I am Derived".
  - but because of the above this is not the case.

  - we can easily fix this by using pass by reference not by value.
*/




/*---------------------------------------------------------------------------------------
                      ============[ slicing vectors ]============
---------------------------------------------------------------------------------------*/

// other area we might run into trouble with slicing is trying to implement polymorphism
// with std::vector

#include <vector>
namespace slicing_vector
{
    using object_slicing::Base, object_slicing::Derived;

    void broken()
    {
        std::vector<Base> v{};
        v.push_back(Base{ 5 });     // add a Base object to our vector
        v.push_back(Derived{ 6 });  // add a Derived object to our vector

        // print out all of the elements in our vector
        for (const auto& element: v)
            std::cout << "I am a " << element.getName()
                      << " with value " << element.getValue() << '\n';
    }
}

/*
  - the code above compile fine, but when it run, it prints:
        I am a Base with value 5
        I am a Base with value 6
  - the object has been sliced.

  - there are two ways (at least?) to fix this:
    > using pointer
    > using std::reference_wrapper
*/

#include <functional>       // for std::reference_wrapper
namespace slicing_vector
{
    // using pointer
    void fix_using_pointer()
    {
        std::vector<Base*> v{};
        
        Base b{ 5 };
        Derived d{ 6 };

        v.push_back(&b);    // add a Base object to our vector
        v.push_back(&d);    // add a Derived object to our vector
        
        for (const auto* element: v)
        std::cout << "I am a " << element->getName()
                    << " with value " << element->getValue() << '\n';
    }

    // using std::reference_wrapper that mimics a reassignable reference
    void fix_using_reference_wrapper()
    {
        std::vector<std::reference_wrapper<Base>> v{};

        Base b{ 5 };        // b and de can't be anonymous objects
        Derived d{ 6 };

        v.push_back(b);     // add a Base object
        v.push_back(d);     // add a Derived object
    
        for (const auto& element: v)
            std::cout << "I am a " << element.get().getName()
                      << " with value " << element.get().getValue() << '\n';
    }
}




/*---------------------------------------------------------------------------------------
                    ============[ the frankenobject ]============
---------------------------------------------------------------------------------------*/

// consider the following

namespace the_frankenobject
{
    using object_slicing::Base, object_slicing::Derived;

    void main()
    {
        Derived d1{ 5 };
        Derived d2{ 6 };
        Base& b{ d2 };

        b = d1;         // this line is problematic
    }
}

/*
  - why problematic you ask?

  - since b points at d2, and we're assigning d1 to b, you might think the result would be
    that d1 would get copied into d2 -- and it would, if b were a Derived.
  - but b is a Base, and the operator= that C++ provides for classes isn't virtual by default.
  - consequently, only the Base portion of d1 is copied into d2.

  - congratulation, you have created a frankenobject.
  - d2 now has the Base portion of d1 and the Derived portion of d2.
*/


// [ conclusion ]
/*---------------------------------------------------------------------------------------
    although C++ supports assigning derived objects to base objects via object slicing,
    in general, this is likely to cause nothing but headaches, and you should generally
    try to avoid slicing. make sure your function parameters are references (or pointers)
    and try to avoid any kind of pass-by-value when it comes to derived classes.
---------------------------------------------------------------------------------------*/




//=======================================================================================

int main()
{
    object_slicing::main();
    slicing_vector::broken();
    slicing_vector::fix_using_pointer();
    slicing_vector::fix_using_reference_wrapper();

    return 0;
}