#include <iostream>


/*
  - "when a member function is called, how does C++ keep track of which object it was called
    on?"
  - the answer is that C++ utilizes a hidden pointer named "this"!
  - let's take a look at "this" in more detail.
*/


/*---------------------------------------------------------------------------------------
                  ============[ the hidden *this pointer ]============
---------------------------------------------------------------------------------------*/

namespace the_hidden_this_pointer
{
    class Simple
    {
    private:
        int m_id{};

    public:
        Simple(int id)
            : m_id{ id }
        {
        }

        void setID(int id) { m_id = id; }
        int getID() { return m_id; }
    };

    void main()
    {
        Simple simple{ 1 };

        // take a look at the following line of code:
        simple.setID(2);
        /* 
            ^^^ the above function setID() looks like it only has one argument, it actually
            has two!
            when compiled, the compiler converts simple.setID92) into the following:
                    setID(&simple, 2);

            consequently, the setID(int) member function is converted by the compiler into
                    void setID(Simple* const this, int id) { this->m_id = id; }
        */
    }
}

/*
  - when the compiler compiles a normal member function, it imlicitly adds a new parameter
    to the function named "this".
  - the [this pointer] is a hidden const pointer that holds the address of the object the
    member function was called on.
  - inside the member function, any class memebrs also need to be updated so they refer
    to the object the member function was called on (it's done by adding "this->" prefix
    to each of them).
  - the good news is that all of this happens automatically.
*/




/*---------------------------------------------------------------------------------------
                ============[ explicitly referencing "this" ]============
---------------------------------------------------------------------------------------*/

/*
  - most of the time, you never need to explicitly reference the "this" pointer.
  - however, there are a few occasions where doing so can be useful.
*/

// if you have a constructor (or member function) that has aparameter with the same name
// as a member variable, you can disambiguate them by using "this".

namespace explicitly_referencing_this
{
    class Something
    {
    private:
        int data{};

    public:
        Something(int data)
        {
            this->data = data;
        }
    };
}




/*---------------------------------------------------------------------------------------
                  ============[ chaining member functions ]============
---------------------------------------------------------------------------------------*/

/*
  - it can sometismes be useful to have a class member function return the object it was
    working with as a return value.
  - the primary reason to do this is to allow a series of member functions to be "chained"
    together, so several member functions can be called on the same object!

  - the example of it is when we use std::cout
            std::cout << "first string" << "second string" << '\n';
*/

namespace chaining_member_functions
{
    class Calc
    {
    private:
        int m_value{ 0 };

    public:
        Calc& add(int value) { m_value += value; return *this; }
        Calc& sub(int value) { m_value -= value; return *this; }
        Calc& mul(int value) { m_value *= value; return *this; }

        int getValue() { return m_value; }
    };

    void main()
    {
        Calc calc{};
        calc.add(5).sub(3).mul(4);      // chaining member functions

        std::cout << calc.getValue() << '\n';
    }
}




//=======================================================================================

int main()
{
    chaining_member_functions::main();

    return 0;
}