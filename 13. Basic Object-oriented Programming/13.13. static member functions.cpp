#include <iostream>
#include <vector>


/*---------------------------------------------------------------------------------------
                   ============[ static member functions ]============
---------------------------------------------------------------------------------------*/

/*
  - if a static member variable is private, we can't access them directly using the class
    name and the scope resolution operator.
  - normallly we access private members through public member functions.
  - we could do that, but we need to instantiate an object first to use the function.
  - fortunately, we can also make functions static.
*/

namespace static_member_function
{
    class Something
    {
    private:
        static inline int s_value{ 1 };

    public:
        static int getValue() { return s_value; }       // static member function
    };

    void main()
    {
        std::cout << Something::getValue() << '\n';
    }
}




/*---------------------------------------------------------------------------------------
        ============[ static member functions have no *this pointer ]============
---------------------------------------------------------------------------------------*/

// because member function does not belong to any object (rather belong to the class itself),
// *this pointer (which belong to instantiated object) is not needed.




/*---------------------------------------------------------------------------------------
                      ============[ another example ]============
---------------------------------------------------------------------------------------*/

// static member functions can also be defined outside of the class declaration.

namespace another_example
{
    class IDGenerator
    {
    private:
        static int s_nextID;

    public:
        static int getNextID();     // static member function declaration
    };

    int IDGenerator::s_nextID{ 1 };

    int IDGenerator::getNextID() { return s_nextID++; }

    void main()
    {
        for (int count{ 0 }; count < 5; ++count)
            std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';
    }
}




/*---------------------------------------------------------------------------------------
           ============[ C++ does not support static constructors ]============
---------------------------------------------------------------------------------------*/

/*
  - if you can initialize normal member variables via a constructor, then by extension it
    makes sense that you should be able to initialize static member variables via a static
    constructor.
  - fortunately C++ does not support that.

  - if your static variable can be directly initialized, no constructor is needed: you can
    initialize the static member variable at the point of definition.

  - if initializing your static member variable requires executing code, there are many
    different, somewhat obtuse ways of doing this.
  - on e way that works with all variables, static or not, is to use a lambda and call it
    immediately.
*/

namespace static_member_construction_using_lambda
{
    class MyClass
    {
    public:
        static std::vector<char> s_mychars;
    };

    std::vector<char> MyClass::s_mychars{
        []{
            std::vector<char> v{};

            for (char ch{ 'a' }; ch <= 'z'; ++ch)
                v.push_back(ch);

            return v;
        }() // call the lambda right away
    };
}




//=======================================================================================

int main()
{
    static_member_function::main();
    another_example::main();
}