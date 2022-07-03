#include <iostream>


/*---------------------------------------------------------------------------------------
                        ============[ const classes ]============
---------------------------------------------------------------------------------------*/

/*
  - instantiated class objects can also be made const by using the const keyword

  - once a const class object has been initialized via a constructor, any attempt to modify
    the member variables of the object is disallowed, as it would violate the const-ness
    of the object.
*/

namespace const_classes
{
    class Something
    {
    public:
        int m_value{};

        Something() : m_value{ 0 } { }

        void setValue(int value) { m_value = value; }
        int getValue() { return m_value; }
    };

    void main()
    {
        const Something something{};

        // something.m_value = 5;      // error: violates const
        // something.setValue(5);      // error: violates const
    }
}




/*---------------------------------------------------------------------------------------
                   ============[ const member functions ]============
---------------------------------------------------------------------------------------*/

namespace const_classes
{
    void main0()
    {
        const Something something{};

        // std::cout << something.getValue();  // error
    }
}

/*
  - const class objects can only explicitly call const member functions, and getValue() has
    not been marked as a const member function.\
  - a [const member function] is a member function that guarantees it will not modify or call
    any non-const member functions (as they may modify the object).
  - to make getValue() a const member function, we simply append the const keyword to the
    function prototype, after the prameter list, but before the function body.
*/

namespace const_member_functions
{
    class Something
    {
    public:
        int m_value{};

        Something() : m_value{ 0 } { }

        void resetValue() { m_value = 0; }
        void setValue(int value) { m_value = value; }

        int getValue() const { return m_value; }
    };

    void main()
    {
        const Something something{};

        std::cout << something.getValue();
    }
}

// furthermore, any const member functions that attempts to change a member variable or call
// a non-const member function will cause a compiler error to occur.


// [ best practice]
/*---------------------------------------------------------------------------------------
    make any member function that does not modify the state of the class object to const,
    so that it can be called by const object.
---------------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------------
          ============[ const object via pass by const reference ]============
---------------------------------------------------------------------------------------*/

// although instantiating const class object is one way to create const objects, a more
// common way to get a const object is by passing an object to a function by const reference.




/*---------------------------------------------------------------------------------------
============[ const members can not return non-const references to members ]============
---------------------------------------------------------------------------------------*/

/*
  - when a member function is const, the hidden *this pointer is also const, which means
    all members are treated as const within that function.
  - therefore,, a const member functions can not return a non-const reference to a member,
    as that would allow the caller to have non-const access to that const member.
  - const member functions can return const reference to members.
*/




/*---------------------------------------------------------------------------------------
          ============[ overloading const and non-const function ]============
---------------------------------------------------------------------------------------*/

/*
  - it is possible to overload a function in such a way to have a const and non-const version
    of the same function.
  - this works bevause the const qualifier is considered part of the function's signature.
*/

namespace overload_const_and_non_const
{
    class Something
    {
    private:
        std::string m_value{};

    public:
        Something(const std::string& value="") : m_value{ value } { }

        const std::string& getValue() const { return m_value; }     // getValue() for const objects
        std::string& getValue() { return m_value; }                 // getValue() for non-const objects
    };
}




/*---------------------------------------------------------------------------------------
                          ============[ summary ]============
---------------------------------------------------------------------------------------*/

// because passing objects by const reference is common, your classes should be const-friendly.




//=======================================================================================

int main()
{
    const_classes::main();
    const_member_functions::main();

    return 0;
}